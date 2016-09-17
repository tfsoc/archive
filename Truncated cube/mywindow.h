#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QColor>
#include <QList>
#include <vector>
#include <stack> 
#include <QPainter>
#include <QPushButton>
#include <QImage>
#include <QPoint>
#include <QGroupBox>
#include <QLabel>
#include <QDir>
#include <QSlider>
#include <QVBoxLayout>
#include <QComboBox>
#include <QString>
#include <QSignalMapper>
#include <QVector2D>
#include <QVector3D>
#include <QStack>


class MyWindow : public QWidget
{
    Q_OBJECT
public:
    MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:

    QImage *img;
    int szer;
    int wys;
	QVector3D p[24];
	QVector2D p1[24];
	
	QGroupBox *grupa;
	QSlider * slider[9];
	QLabel * label[9];
	QVBoxLayout *boxLayout;
	QComboBox * comboBox;
	QSignalMapper * signalMapper;
	
	QPoint pt;
	QList<QPoint> lista;
	QList<QPoint> punkty;
	unsigned char *ptr1;
	
	int myKolor;
	
private slots:

	void koloruj(int, int, int);
	void wstawPiksel(int,int,QColor);
	void wstawPiksel1(int,int);
    void paintEvent(QPaintEvent*);
	void wstawKreske(int,int,int,int);
	void wstawKreske1(int,int,int,int);
	void wstawLinie(int,int);
	void wstawLinie1(int,int);
	void bryla();
	void czysc();
	void setLabels(int);
	void mousePressEvent(QMouseEvent *event);
};

