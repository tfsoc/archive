#include "mywindow.h"
#include <cmath>
#include <QVBoxLayout>
#include <QList>
#include <QPoint>
#include <QSlider>
#include <QSpinBox>
#include <QStringList>
#include <QString>
#include <math.h>
#include <QThread>
#include <algorithm> 
#include <QMutex>

#define PI 3.14159265


MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Blender");    
    szer = 800;
    wys = 600;
	setFixedSize(szer,wys);
	img = new QImage(szer,wys,QImage::Format_RGB32);
	ptr1 = img->bits();
	
	grupa = new QGroupBox("RGB",this);
	grupa->setGeometry(801,0,200, 600);
	boxLayout = new QVBoxLayout;
	signalMapper = new QSignalMapper(this);
	
	QString nazwy[] = {"Translacja X","Translacja Y","Translacja Z","Skalowanie X","Skalowanie Y","Skalowanie Z","Obrot XY","Obrot XZ","Obrot YZ"};
	for(int i=0;i<9;i++)
	{
		slider[i]=new QSlider(Qt::Horizontal);
		slider[i]->setRange(0,360);
		slider[i]->setValue(180);
		label[i]=new QLabel(nazwy[i]+" = 0");
		connect(slider[i], SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
		boxLayout->addWidget(label[i]);
		boxLayout->addWidget(slider[i]);
		//connect(slider[i], &QSlider::valueChanged, signalMapper, &QSignalMapper::map);
		signalMapper->setMapping(slider[i], i);
	}
	connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(setLabels(int))) ;

	grupa->setLayout(boxLayout);
	
	p[0] = QVector3D(-40 ,100,-100);
	p[1] = QVector3D( 40 ,100,-100);
	p[2] = QVector3D( 100,100,-40);
	p[3] = QVector3D( 100,100, 40);
	p[4] = QVector3D( 40 ,100, 100);
	p[5] = QVector3D(-40 ,100, 100);
	p[6] = QVector3D(-100,100, 40);
	p[7] = QVector3D(-100,100,-40);
	
	p[8] =  QVector3D(-100, 40,-100);
	p[9] =  QVector3D( 100, 40,-100);
	p[10] = QVector3D( 100, 40, 100);
	p[11] = QVector3D(-100, 40, 100);
	p[12] = QVector3D(-100,-40,-100);
	p[13] = QVector3D( 100,-40,-100);
	p[14] = QVector3D( 100,-40, 100);
	p[15] = QVector3D(-100,-40, 100);
	
	p[16] = QVector3D(-40 ,-100,-100);
	p[17] = QVector3D( 40 ,-100,-100);
	p[18] = QVector3D( 100,-100,-40);
	p[19] = QVector3D( 100,-100, 40);
	p[20] = QVector3D( 40 ,-100, 100);
	p[21] = QVector3D(-40 ,-100, 100);
	p[22] = QVector3D(-100,-100, 40);
	p[23] = QVector3D(-100,-100,-40);
	slider[8]->setValue(230);
	bryla();
}

MyWindow::~MyWindow()
{
    delete img;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0,0,*img);
}

void MyWindow::wstawPiksel(int j, int i, QColor kolor=QColor(255,255,255))
{
	unsigned char *ptr;
	ptr = img->bits();
	if((j>=0)&&(i>=0)&&(j<szer)&&(i<wys))
	{
		ptr[szer*4*i + 4*j]=kolor.blue();
		ptr[szer*4*i + 4*j + 1] = kolor.green();
		ptr[szer*4*i + 4*j + 2] = kolor.red();
	}
}
void MyWindow::wstawPiksel1(int j, int i)
{
	if(myKolor>0 && myKolor<=255){
		unsigned char *ptr;
		ptr = img->bits();
		if((j>=0)&&(i>=0)&&(j<szer)&&(i<wys))
		{
			ptr[szer*4*i + 4*j]=myKolor;
			ptr[szer*4*i + 4*j + 1] = myKolor;
			ptr[szer*4*i + 4*j + 2] = myKolor;
		}
	}
}
void MyWindow::wstawKreske(int x0, int y0, int x1, int y1)
{
	int tmp=1;
	int mian=y1-y0;
	if(y1-y0==0)mian=1;
	if((x1-x0)/(mian)!=0){
		if((x1-x0)<0)tmp=-1;
		for(int i=x0; i!=x1; i+=tmp)
		{
			float k=(-(y0-y1)*i-(x0*y1-x1*y0))/(x1-x0)+0.5;
			int j = k;
			wstawPiksel(i,j);
		}
	}else{
		if((y1-y0)<0)tmp=-1;
		for(int j=y0; j!=y1; j+=tmp)
		{
			float k=(-(x1-x0)*j-(x0*y1-x1*y0))/(y0-y1)+0.5;
			int i = k;
			wstawPiksel(i,j);
		}
	}
}
void MyWindow::wstawKreske1(int x0, int y0, int x1, int y1)
{
	int tmp=1;
	int mian=y1-y0;
	if(y1-y0==0)mian=1;
	if((x1-x0)/(mian)!=0){
		if((x1-x0)<0)tmp=-1;
		for(int i=x0; i!=x1; i+=tmp)
		{
			float k=(-(y0-y1)*i-(x0*y1-x1*y0))/(x1-x0)+0.5;
			int j = k;
			wstawPiksel1(i,j);
		}
	}else{
		if((y1-y0)<0)tmp=-1;
		for(int j=y0; j!=y1; j+=tmp)
		{
			float k=(-(x1-x0)*j-(x0*y1-x1*y0))/(y0-y1)+0.5;
			int i = k;
			wstawPiksel1(i,j);
		}
	}
}
void MyWindow::wstawLinie(int i, int j)
{
	wstawKreske(p1[i].x(),p1[i].y(),p1[j].x(),p1[j].y());
}
void MyWindow::wstawLinie1(int i, int j)
{
	wstawKreske1(p1[i].x(),p1[i].y(),p1[j].x(),p1[j].y());
}
void MyWindow::czysc()
{
	unsigned char *ptr;
	ptr = img->bits();
	int kolor = 0;
	for(int i=0;i<wys;i++)
		for(int j=0;j<szer;j++)
		{
			ptr[szer*4*i + 4*j]=kolor;
			ptr[szer*4*i + 4*j + 1] = kolor;
			ptr[szer*4*i + 4*j + 2] = kolor;
		}
}
void MyWindow::bryla()
{
	for(int i=0;i<24;i++)
	{
		p1[i]=p[i].toVector2D();
		//p1[i]+=QVector2D(100,100);
		
		//float tmp=100/(p[i].z()-100);
		//int tmp=1+(p[i].z())/1000;
		float d = 1000;
		float tmp = 1 + p[i].z()/d;
		p1[i].setX((p1[i].x()/tmp+szer/2));
		p1[i].setY((p1[i].y()/tmp+wys/2));

	}
	
	

	QVector3D viewPoint = QVector3D(0,0,-1000);
	
	QVector3D u;
	QVector3D v;
	QVector3D n;
	
	
	//u=p[1]-p[0];
	//v=p[2]-p[1];
	
	n= QVector3D::crossProduct(p[1]-p[2],p[0]-p[1]);
	if(QVector3D::dotProduct(p[1]-viewPoint,n)<0){
		wstawKreske(p1[0].x(),p1[0].y(),p1[1].x(),p1[1].y());
		wstawKreske(p1[1].x(),p1[1].y(),p1[2].x(),p1[2].y());
		wstawKreske(p1[2].x(),p1[2].y(),p1[3].x(),p1[3].y());
		wstawKreske(p1[3].x(),p1[3].y(),p1[4].x(),p1[4].y());
		wstawKreske(p1[4].x(),p1[4].y(),p1[5].x(),p1[5].y());
		wstawKreske(p1[5].x(),p1[5].y(),p1[6].x(),p1[6].y());
		wstawKreske(p1[6].x(),p1[6].y(),p1[7].x(),p1[7].y());
		wstawKreske(p1[7].x(),p1[7].y(),p1[0].x(),p1[0].y());
		
		float koef = QVector3D::dotProduct((p[1]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(1,0,7);
			koloruj(1,7,6);
			koloruj(1,6,5);
			koloruj(1,5,4);
			koloruj(1,4,3);
			koloruj(1,3,2);
		}
	}
	
	n= QVector3D::crossProduct(p[3]-p[2],p[10]-p[3]);
	if(QVector3D::dotProduct(p[3]-viewPoint,n)<0){
		wstawLinie(2,3);
		wstawLinie(3,10);
		wstawLinie(10,14);
		wstawLinie(14,19);
		
		wstawLinie(19,18);
		wstawLinie(18,13);
		wstawLinie(13,9);
		wstawLinie(9,2);
		
		float koef = QVector3D::dotProduct((p[3]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(3,2,9);
			koloruj(3,9,13);
			koloruj(3,13,18);
			koloruj(3,18,19);
			koloruj(3,19,14);
			koloruj(3,14,10);
		}
	}
	
	n= QVector3D::crossProduct(p[1]-p[0],p[9]-p[1]);
	if(QVector3D::dotProduct(p[1]-viewPoint,n)<0){
		wstawLinie(0,1);
		wstawLinie(1,9);
		wstawLinie(9,13);
		wstawLinie(13,17);
		
		wstawLinie(17,16);
		wstawLinie(16,12);
		wstawLinie(12,8);
		wstawLinie(8,0);
		
		float koef = QVector3D::dotProduct((p[1]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(1,9,13);
			koloruj(1,13,17);
			koloruj(1,17,16);
			koloruj(1,16,12);
			koloruj(1,12,8);
			koloruj(1,8,0);
		}
	}
	
	n= QVector3D::crossProduct(p[17]-p[16],p[18]-p[17]);
	if(QVector3D::dotProduct(p[17]-viewPoint,n)<0){
		wstawLinie(16,17);
		wstawLinie(17,18);
		wstawLinie(18,19);
		wstawLinie(19,20);
		
		wstawLinie(20,21);
		wstawLinie(21,22);
		wstawLinie(22,23);
		wstawLinie(23,16);
		
		float koef = QVector3D::dotProduct((p[17]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(16,17,18);
			koloruj(16,18,19);
			koloruj(16,19,20);
			koloruj(16,20,21);
			koloruj(16,21,22);
			koloruj(16,22,23);
		}
	}
	
	n= QVector3D::crossProduct(p[7]-p[6],p[8]-p[7]);
	if(QVector3D::dotProduct(p[7]-viewPoint,n)<0){
		wstawLinie(6,7);
		wstawLinie(7,8);
		wstawLinie(8,12);
		wstawLinie(12,23);
		
		wstawLinie(23,22);
		wstawLinie(22,15);
		wstawLinie(15,11);
		wstawLinie(11,6);
		
		float koef = QVector3D::dotProduct((p[7]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(6,7,8);
			koloruj(6,8,12);
			koloruj(6,12,23);
			koloruj(6,23,22);
			koloruj(6,22,15);
			koloruj(6,15,11);
		}
	}
	
	n= QVector3D::crossProduct(p[10]-p[4],p[4]-p[5]);
	if(QVector3D::dotProduct(p[4]-viewPoint,n)<0){
		wstawLinie(5,4);
		wstawLinie(4,10);
		wstawLinie(10,14);
		wstawLinie(14,20);
		
		wstawLinie(20,21);
		wstawLinie(21,15);
		wstawLinie(15,11);
		wstawLinie(11,5);
		
		float koef = QVector3D::dotProduct((p[4]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(4,5,11);
			koloruj(4,11,15);
			koloruj(4,15,21);
			koloruj(4,21,20);
			koloruj(4,20,14);
			koloruj(4,14,10);
		}
	}
	
	
	
	n= QVector3D::crossProduct(p[17]-p[18],p[13]-p[17]);
	if(QVector3D::dotProduct(p[17]-viewPoint,n)<0){
		wstawLinie(17,18);
		wstawLinie(18,13);
		wstawLinie(13,17);
		
		float koef = QVector3D::dotProduct((p[17]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(17,18,13);
		}
		//QString l = QString("koef = %1").arg(koef);
		//label[0]->setText(l);
	}
	n= QVector3D::crossProduct(p[9]-p[2],p[1]-p[9]);
	if(QVector3D::dotProduct(p[9]-viewPoint,n)<0){
		wstawLinie(2,9);
		wstawLinie(9,1);
		wstawLinie(1,2);
		
		float koef = QVector3D::dotProduct((p[9]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(1,2,9);
		}
	}
	n= QVector3D::crossProduct(p[10]-p[3],p[3]-p[4]);
	if(QVector3D::dotProduct(p[3]-viewPoint,n)<0){
		wstawLinie(10,3);
		wstawLinie(3,4);
		wstawLinie(4,10);
		float koef = QVector3D::dotProduct((p[3]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(10,4,3);
		}
	}
	n= QVector3D::crossProduct(p[20]-p[14],p[19]-p[20]);
	if(QVector3D::dotProduct(p[20]-viewPoint,n)<0){
		wstawLinie(20,19);
		wstawLinie(19,14);
		wstawLinie(14,20);
		float koef = QVector3D::dotProduct((p[20]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(20,19,14);
		}
	}
	n= QVector3D::crossProduct(p[21]-p[22],p[15]-p[21]);
	if(QVector3D::dotProduct(p[21]-viewPoint,n)<0){
		wstawLinie(21,22);
		wstawLinie(21,15);
		wstawLinie(22,15);
		float koef = QVector3D::dotProduct((p[21]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(21,15,22);
		}
	}
	n= QVector3D::crossProduct(p[11]-p[6],p[5]-p[11]);
	if(QVector3D::dotProduct(p[11]-viewPoint,n)<0){
		wstawLinie(11,5);
		wstawLinie(11,6);
		wstawLinie(6,5);
		float koef = QVector3D::dotProduct((p[11]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(11,6,5);
		}
	}
	n= QVector3D::crossProduct(p[23]-p[16],p[12]-p[23]);
	if(QVector3D::dotProduct(p[23]-viewPoint,n)<0){
		wstawLinie(16,23);
		wstawLinie(12,16);
		wstawLinie(23,12);
		float koef = QVector3D::dotProduct((p[23]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(16,23,12);
		}
	}
	n= QVector3D::crossProduct(p[0]-p[8],p[8]-p[7]);
	if(QVector3D::dotProduct(p[8]-viewPoint,n)<0){
		wstawLinie(7,8);
		wstawLinie(8,0);
		wstawLinie(0,7);
		float koef = QVector3D::dotProduct((p[8]-viewPoint).normalized(),n.normalized());
		if(koef<0)
			koef=-koef;
		koef=koef*255;
		if(koef>=0){
			myKolor = koef;
			koloruj(7,8,0);
		}
	}
	
	
	/*
	
	wstawKreske(p1[0].x(),p1[0].y(),p1[1].x(),p1[1].y());
	wstawKreske(p1[0].x(),p1[0].y(),p1[3].x(),p1[3].y());
	wstawKreske(p1[0].x(),p1[0].y(),p1[4].x(),p1[4].y());
	
	wstawKreske(p1[2].x(),p1[2].y(),p1[1].x(),p1[1].y());
	wstawKreske(p1[2].x(),p1[2].y(),p1[3].x(),p1[3].y());
	wstawKreske(p1[2].x(),p1[2].y(),p1[6].x(),p1[6].y());
	
	wstawKreske(p1[5].x(),p1[5].y(),p1[1].x(),p1[1].y());
	wstawKreske(p1[5].x(),p1[5].y(),p1[4].x(),p1[4].y());
	wstawKreske(p1[5].x(),p1[5].y(),p1[6].x(),p1[6].y());
	
	wstawKreske(p1[7].x(),p1[7].y(),p1[3].x(),p1[3].y());
	wstawKreske(p1[7].x(),p1[7].y(),p1[4].x(),p1[4].y());
	wstawKreske(p1[7].x(),p1[7].y(),p1[6].x(),p1[6].y());

	*/
}
void MyWindow::koloruj(int i1, int i2, int i3)
{
	
	float tmp;
	float x1 = p1[i1].x();
	float x2 = p1[i2].x();
	float x3 = p1[i3].x();
	
	float y1 = p1[i1].y();
	float y2 = p1[i2].y();
	float y3 = p1[i3].y();
	
	if(y1>y2){
		tmp=y1;
		y1=y2;
		y2=tmp;
		
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if(y1>y3){
		tmp=y1;
		y1=y3;
		y3=tmp;
		
		tmp=x1;
		x1=x3;
		x3=tmp;
	}
	if(y2>y3){
		tmp=y2;
		y2=y3;
		y3=tmp;
		
		tmp=x2;
		x2=x3;
		x3=tmp;
	}

	float dx12=(y2-y1<=0) ? 0 :(x2-x1)/(y2-y1);
	float dx13=(y3-y1<=0) ? 0 :(x3-x1)/(y3-y1);
	float dx23=(y3-y2<=0) ? 0 :(x3-x2)/(y3-y2);

	
	
	float y=y1;
	float x11=x1;
	float x12=x1;
	while(y<=y2){
		wstawKreske1(x11,y,x12,y);
		x11+=dx13;
		x12+=dx12;
		y++;
	}
	y=y2;
	x11=x11;
	x12=x2;
	
	while(y<=y3){
		wstawKreske1(x11,y,x12,y);
		x11+=dx13;
		x12+=dx23;
		y++;
	}
	
	wstawKreske1(x1,y1,x2,y2);
	wstawKreske1(x3,y3,x2,y2);
	wstawKreske1(x1,y1,x3,y3);
}	

void MyWindow::mousePressEvent(QMouseEvent *event)
{
	
	for(int i=0;i<360;i++){
		int val =slider[7]->value();
		if(val==359)
			val=0;
		else
			val++;
		slider[7]->setValue(val);
		//QWidget::setUpdatesEnabled (true);
		repaint();
		//QWidget::setUpdatesEnabled (false);
		QMutex mut;
		mut.lock();
		mut.tryLock(5);
		mut.unlock();
		//QThread::msleep(100);
	}
	

	/*
	for(int x=0;x<100;x++){
	int val =slider[0]->value();
	slider[0]->setValue(val+1);
	czysc();
	bryla();
	//update();
	repaint();
	QThread::msleep(10);
	}
	*/
}
void MyWindow::setLabels(int m_i)
{
	QString nazwy[] = {"Translacja X","Translacja Y","Translacja Z","Skalowanie X","Skalowanie Y","Skalowanie Z","Obrot XY","Obrot XZ","Obrot YZ"};
    int val=slider[m_i]->value();
	//int x=10;
	QString l = QString(" = %1").arg(val-180);
	label[m_i]->setText(nazwy[m_i]+l);
	
	p[0] = QVector3D(-40 ,100,-100);
	p[1] = QVector3D( 40 ,100,-100);
	p[2] = QVector3D( 100,100,-40);
	p[3] = QVector3D( 100,100, 40);
	p[4] = QVector3D( 40 ,100, 100);
	p[5] = QVector3D(-40 ,100, 100);
	p[6] = QVector3D(-100,100, 40);
	p[7] = QVector3D(-100,100,-40);
	
	p[8] =  QVector3D(-100, 40,-100);
	p[9] =  QVector3D( 100, 40,-100);
	p[10] = QVector3D( 100, 40, 100);
	p[11] = QVector3D(-100, 40, 100);
	p[12] = QVector3D(-100,-40,-100);
	p[13] = QVector3D( 100,-40,-100);
	p[14] = QVector3D( 100,-40, 100);
	p[15] = QVector3D(-100,-40, 100);
	
	p[16] = QVector3D(-40 ,-100,-100);
	p[17] = QVector3D( 40 ,-100,-100);
	p[18] = QVector3D( 100,-100,-40);
	p[19] = QVector3D( 100,-100, 40);
	p[20] = QVector3D( 40 ,-100, 100);
	p[21] = QVector3D(-40 ,-100, 100);
	p[22] = QVector3D(-100,-100, 40);
	p[23] = QVector3D(-100,-100,-40);
	
	
	
	float tx=slider[0]->value()-180;
	float ty=-slider[1]->value()+180;
	float tz=slider[2]->value()-180;
	
	//skalowanie jest wartoscia zmienny w procentach (np jak sx=20, to wartosci x beda powiekszane o 20%)
	float sx=slider[3]->value()-180;
	float sy=slider[4]->value()-180;
	float sz=slider[5]->value()-180;	
	
	float kat_xy=(slider[6]->value()-180)*PI / 180.0;
	float kat_xz=(slider[7]->value()-180)*PI / 180.0;
	float kat_yz=(slider[8]->value()-180)*PI / 180.0;
	
	float s[3];
	float c[3];
	
	s[0]=sin(kat_xy);
	s[1]=sin(kat_xz);
	s[2]=sin(kat_yz);
	
	c[0]=cos(kat_xy);
	c[1]=cos(kat_xz);
	c[2]=cos(kat_yz);
	
	for(int i=0;i<24;i++)
	{
		//operacje nie sa przemienne, wiec mozna zmienic ich kolejnosc, aby otrzymac inny wynik
		/*
		jesli obrot bedzie stal przed translacja to translacja wedlug wsp Z nie bedzie miala jakiegokolwiek wplywu (oprocz perspektywy), dlatego najperw wykonujemy translacje, a potem juz obracamy wzgledem centrum ekjranu (jak wymienimy kolejnosc, obrot bedzie wzgledem centrum szescianu)
		*/
		p[i]=QVector3D(p[i].x()+tx, p[i].y()+ty, p[i].z()+tz);
		
		
		//skalowanie
		p[i]=QVector3D(p[i].x()*(1+sx/100), p[i].y()*(1+sy/100), p[i].z()*(1+sz/100));
		
		//obrot XO
		p[i]=QVector3D(p[i].x(), p[i].y()*c[2]-p[i].z()*s[2], p[i].y()*s[2]+p[i].z()*c[2]);
		//obrot OY
		p[i]=QVector3D(p[i].x()*c[1]+p[i].z()*s[1], p[i].y(), -p[i].x()*s[1]+p[i].z()*c[1]);
		//obrot OZ
		p[i]=QVector3D(p[i].x()*c[0]-p[i].y()*s[0], p[i].x()*s[0]+p[i].y()*c[0], p[i].z());
		
		
		
	}
	
	czysc();
	bryla();
}


