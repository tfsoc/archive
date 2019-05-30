const eInput = document.getElementById('eInput');
const dInput = document.getElementById('dInput');
const nInput = document.getElementById('nInput');
const solutionSteps = document.getElementById('solution-steps');
const calculateButton = document.getElementById('runSolve');
const resetButton = document.getElementById('resetInput');
const upperCalculationBound = 67108864;
const invalidInput = document.getElementsByClassName('invalid-input')[0];
//FIXME: step iterator, also add aanswer highlighted area/border
//TODO: add case for p or q being 1


calculateButton.addEventListener('click', solve);
resetButton.addEventListener('click', function () {
    eInput.value = "";
    dInput.value = "";
    nInput.value = "";
    invalidInput.style.display = "none";
    resetSolution();
})

function resetSolution() {
    solutionSteps.innerHTML = `
    <div class="solution-step-0">
        <div class="step-count">Step 0</div>
        <hr class="step-divider">
        <div class="step-body">
            <div class="step-alg">Enter data and Press "Calculate".</div>
        </div>
    </div>`;
}

eInput.addEventListener('input', createBoundaryControl(3, upperCalculationBound));
dInput.addEventListener('input', createBoundaryControl(3, upperCalculationBound));
nInput.addEventListener('input', createBoundaryControl(6, upperCalculationBound));

function createBoundaryControl(a,b) {
    function f(e) {
        let x = Number(this.value);
        if (x < a) {
            this.value = a;
        } else if (x > b) {
            this.value = b;
        }
    }
    return f;
}

function pow(a, s, n){
    a = a % n;
    let M = 1;
    let aj = a;
    while (s > 0) {
        let sj = s % 2;
        s = Math.floor(s / 2);
        if (sj) {
            M *= aj;
            M = M % n;
        }
        aj = aj * aj;
        aj = aj % n;
    }
    return M;
}

function gcd(a, b) {
    if (b)
        return gcd(b, a % b);
    else
        return Math.abs(a);
}

function solve() {
    let e = Number(eInput.value);
    let d = Number(dInput.value);
    let n = Number(nInput.value);
	
    if (!inputTest(e, d, n)) {
        invalidInput.style.display = "block";
        resetSolution();
        return;
    } else {
        invalidInput.style.display = "none";
    }


    let i = 1; //step Iterator
    let outHtml = "";
    let algI = [];
    algI[1] = `Liczb&#281; <i>ed &ndash; </i>1 przedstawiamy w postaci 2<i><sup>s</sup>t</i>, gdzie <i>t</i> jest liczb&#261; nieparzyst&#261;.`;
    algI[2] = `Wybieramy losowo liczb&#281; <i>a</i> z przedzialu 1 &lt; <i>a</i> &lt; <i>n</i>.`;
    algI[3] = `Obliczamy <i>d</i> &#xff1d; NWD(<i>a</i>, <i>n</i>).`;
    algI[4] = `Je&#347;li <i>d</i> &gt; 1, to zwr&#243;&#263; <i>d</i> i STOP.`;
    algI[5] = `Obliczamy <i>b</i> &#xff1d; <i>a<sup>t</sup></i> mod <i>n</i>.`;
    algI[6] = `Je&#347;li <i>b</i> &#xff1d; 1, to wracamy do 2.`;
    algI[7] = `Obliczamy rekurencyjnie ci&#261;g <i>c<sub>0</sub></i> &#xff1d; <i>b</i>, <i>c<sub>i+1</sub></i> &#xff1d; <i>c<span class='supsub'><sub>i</sub><sup>2</sup></span></i> mod <i>n</i>, a&#380; do uzyskania 1.`;
    algI[8] = `Niech <i>c</i> b&#281;dzie ostatnim wyrazem powy&#380;szego ci&#261;gu r&#243;&#380;nym od 1.`;
    algI[9] = `Je&#347;li <i>c</i> &#xff1d; <i>n</i> &ndash; 1, to wracamy do 2.`;
    algI[10] = `<i>d</i> &#xff1d; NWD(<i>c</i> &ndash; 1, <i>n</i>) jest dzielnikiem pierwszym <i>n</i>; zwr&#243;&#263; <i>d</i> i STOP.`;

    let ed1 = e * d - 1;
    let s = 1;
    let t = ed1 / 2;
    
    while (t % 2 === 0) {
        s = s + 1;
        t = t / 2;
    }

    let a, b, c, ck;
    let repI = 1;
    function algRep(repI) {
        if (repI == 1)
            return "";
        else
            return ` [${repI}]`;
    }

    while (true) {
        let bodyI = `<span class="step-alg">${algI[i]}</span>`;
        let ii = i;
        let ij = repI;
        switch (i) {
            case 1:
                bodyI += `<p class="text-center step-calc">${e} &#183; ${d} &ndash; 1 &#xff1d; ${ed1}</p>`;
                bodyI += `<p class="text-center step-calc">${ed1} &#xff1d; 2<sup>${s}</sup>&#183;${t}</p>`;
                break;
            case 2:
                a = Math.floor((Math.random() * n) + 1);
                bodyI += `<p class="text-center step-calc">1 &lt; ${a} &lt; ${n}</p>`;
                break;
            case 3:
                d = gcd(a, n);
                bodyI += `<p class="text-center step-calc">NWD(${a},${n}) &#xff1d; ${d}</p>`;
                break;
            case 4:
                if (d !== 1) {
                    bodyI += `<p class="text-center step-calc">${d} &gt; 1</p>`;
                    i = 11;
                } else {
                    bodyI += `<p class="text-center step-calc">1 &#xff1d; 1</p>`;
                }
                break;
            case 5:
                b = pow(a, t, n);
                bodyI += `<p class="text-center step-calc">${a}<sup>${t}</sup> mod ${n} &#xff1d; ${b}</p>`;
                break;
            case 6:
                if (b === 1) {
                    bodyI += `<p class="text-center step-calc">${b} &#xff1d; 1</p>`;
                    i = 1;
                    repI++;
                    //goto2
                } else {
                    bodyI += `<p class="text-center step-calc">${b} &ne; 1</p>`;
                }
                break;
            case 7:
                c = b;
                bodyI += `<p class="text-center step-calc">c<sub>0</sub> &#xff1d; ${c}</p>`;
                for (let j = 1; j <= s; j++){
                    ck = c;
                    c = pow(c, 2, n);
                    bodyI += `<p class="text-center step-calc">c<sub>${j}</sub> &#xff1d; ${c}</p>`;
                    if (c === 1) break;
                }
                break;
            case 8:
                bodyI += `<p class="text-center step-calc">c &#xff1d; ${ck}</p>`;
                break;
            case 9:
                if (ck === (n - 1)) {
                    bodyI += `<p class="text-center step-calc">${ck} &#xff1d; ${n - 1}</p>`;
                    i = 1;
                    repI++;
                } else {
                    bodyI += `<p class="text-center step-calc">${ck} &ne; ${n - 1}</p>`;
                }
                break;
            case 10:
                d = gcd(ck - 1, n);
				bodyI += `<p class="text-center step-calc">NWD(${ck-1}, ${n}) &#xff1d; ${d}</p>`;
                //i = 11;
                break;
            // no default really required here
        }

        if (i === 11) {
            bodyI = `
            <div class='step-ans'>
                <p class="text-center step-calc step-ans-p">p &#xff1d; ${d}</p>
                <p class="text-center step-calc step-ans-q">q &#xff1d; ${n / d}</p>
            </div>`;
        }
        outHtml += `
        <div class="solution-step-${ii}">
            <div class="step-count">Step ${ii + algRep(ij)}</div>
            <hr class="step-divider">
            <div class="step-body">
                ${bodyI}
            </div>
        </div>`;
        if (i === 11) break;
        i += 1;
    }   

    solutionSteps.innerHTML = outHtml;
}


function inputTest(e, d, n) {
	if(e===0 ||d===0 || n===0 )return false;
    for (let i = 0; i < 1000; i++)    {
        let t = Math.floor((Math.random() * n) + 1);
        let s = pow(t, e, n);
        if (pow(s, d, n) === t) continue;
        else
            return false;
    }
    return true;
}