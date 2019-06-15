/*
	C = A x B where
	A is m x n
	B is n x k
	C is m x k

	Assume the m,n,k are divisibles of BLOCK_SIZE
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <device_functions.h>
#include <chrono>

// hide red underline for __syncthreads (nvidia forum based solution)
#pragma once
#ifdef __INTELLISENSE__
void __syncthreads();
#endif

#define BLOCK_SIZE 32

/*
	naive algorythm of matrix multiplication C = A * B
	where each thread calculates one element of C
*/
__global__ void matrixMultiplicationGPU1(float* a, float* b, float* c, int m, int n, int k) {
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	
	float sum = 0;
	if(!(col < k && row < m))return;

	//accumulate sum
	for (int i = 0; i < n; i++) {
		sum += a[row*n + i] * b[i*k + col];
	}

	//copy result to c
	c[row*k + col] = sum;
}

__global__ void matrixMultiplicationGPU(float* A, float* B, float* C, int N, int K) {
	//Block and Thread indices
	int bx = blockIdx.x, tx = threadIdx.x;
	int by = blockIdx.y, ty = threadIdx.y;


	//stores element of the block sub-matrix that is computed by the thread
	float Pvalue = 0;

	//loop over all sub-matrices of A and B required to compute the block sub-matrix
	for (int t = 0; t < N / BLOCK_SIZE; t++) {

		//shared memory declaration
		__shared__ float As[BLOCK_SIZE][BLOCK_SIZE];
		__shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];

		As[ty][tx] = A[N * BLOCK_SIZE * by +  t * BLOCK_SIZE   + N * ty + tx];
		Bs[ty][tx] = B[BLOCK_SIZE * bx + t * K  *BLOCK_SIZE + K * ty + tx];

		__syncthreads();


#pragma unroll
		for (int i = 0; i < BLOCK_SIZE; i++) {
			Pvalue += As[ty][i] * Bs[i][tx];
		}
		
		__syncthreads();

	}

	C[K * BLOCK_SIZE * by + K * ty + BLOCK_SIZE * bx + tx] = Pvalue;
}


void matrixMultiplicationCPU(float* a, float* b, float* c, int m, int n, int k) {
	for (int i = 0; i < m; i++){
		for (int j = 0; j < k; j++){
			float res = 0;
			
			for (int ii = 0; ii < n; ii++) {
				res += a[i*n + ii] * b[ii*k + j];
			}
			
			c[i*k + j] = res;
		}
	}
}

bool equalMatrixCheckCPU(float* a, float* b, int m, int k) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			if (a[i*k + j] != b[i*k + j]) {
				printf("err: m1[%d][%d] != m2[%d][%d]\n", i, j, i, j);
				return false;
			}
		}
	}
	return true;
}

int main(){
	printf("Starting program...\n");

	int dId = 0;
	cudaError_t err;
	
	cudaSetDevice(dId);

	err = cudaGetDevice(&dId);
	if (err != cudaSuccess) {
		printf("%d: \t error %s (code %d) \n", __LINE__, cudaGetErrorString(err), err); return 1;
	}

	dim3 dimsA(20 * BLOCK_SIZE, 2 * BLOCK_SIZE, 1);
	dim3 dimsB(40 * BLOCK_SIZE, 20 * BLOCK_SIZE, 1);
	dim3 dimsC(dimsB.x, dimsA.y, 1);

	if (dimsA.x != dimsB.y) {
		printf("product A x B does not exits! \n"); return 1;
	}

	
	int M = dimsA.y;
	int	N = dimsA.x; // == dimsB.y
	int K = dimsB.x;


	float *h_A, *h_B, *h_C, *h_C1;
	float *d_A, *d_B, *d_C;

	cudaMallocHost((void **)&h_A, sizeof(int)*M*N);
	cudaMallocHost((void **)&h_B, sizeof(int)*N*K);
	cudaMallocHost((void **)&h_C, sizeof(int)*M*K);
	cudaMallocHost((void **)&h_C1, sizeof(int)*M*K);
	
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			h_A[i*N + j] = (i + j) % 10;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			h_B[i*K + j] = (i * j) % 10;
		}
	}

	cudaMalloc((void **)&d_A, sizeof(float)*M*N);
	cudaMalloc((void **)&d_B, sizeof(float)*N*K);
	cudaMalloc((void **)&d_C, sizeof(float)*M*K);

	cudaMemcpy(d_A, h_A, sizeof(float)*M*N, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, sizeof(float)*N*K, cudaMemcpyHostToDevice);



	dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
	dim3 dimGrid(dimsB.x / dimBlock.x, dimsA.y / dimBlock.y);
	//          (B.width / dimBlock.x, A.height/ dimBlock.y)
	

	cudaEvent_t start, stop;
	float gpuTime = 0.0f;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaEventRecord(start, NULL);
	matrixMultiplicationGPU<<<dimGrid, dimBlock>>>(d_A, d_B, d_C, N, K);
	cudaEventRecord(stop, NULL);

	cudaMemcpy(h_C, d_C, sizeof(float)*M*K, cudaMemcpyDeviceToHost);
	cudaEventSynchronize(stop);

	cudaEventElapsedTime(&gpuTime, start, stop);
	printf("It took %f msec to perform %dx%d by %dx%d matrix multiplication on GPU.\n", gpuTime,M,N,N,K);

	cudaDeviceSynchronize();
	


	auto begin = std::chrono::high_resolution_clock::now();
	matrixMultiplicationCPU(h_A, h_B, h_C1, M, N, K);
	auto end = std::chrono::high_resolution_clock::now();

	int cpuNano = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
	float cpuTime = cpuNano / 1000000.0;
	printf("It took %f msec to perform %dx%d by %dx%d matrix multiplication on CPU.\n", cpuTime, M, N, N, K);
	
	


	bool sameResult = equalMatrixCheckCPU(h_C, h_C1, M, K);
	if (sameResult)
		printf("Result is correct!\n");
	else
		printf("Check the code...\n");


	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	printf("Free memory...\n");
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	cudaFreeHost(h_A);
	cudaFreeHost(h_B);
	cudaFreeHost(h_C);
	cudaFreeHost(h_C1);

	printf("Done...\n");




	return 0;
}


/*
	Reference:
		Slides on moodle
		"Shared Memory Matrix Multiplication" on https://www.youtube.com/watch?v=SqZaletdPCY
		CUDA by examples
		"Naive Matrix Multiplication CUDA" https://github.com/lzhengchun/matrix-cuda/blob/master/matrix_cuda.cu
		Forum topics from https://devtalk.nvidia.com/
*/