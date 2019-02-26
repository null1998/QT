#include "dialog.h"
#include "ui_dialog.h"
#include<QPainter>
#include<QPushButton>
#include<QMouseEvent>
#include <string>
#include<QString>
#include <sstream>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    resize(900,750);
    pix=QPixmap(600,600);
    pix.fill(Qt::white);
    isDoubleClick=false;

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPainter paint(&pix);
    paint.drawLine(startPoint,endPoint);
    painter.drawPixmap(0,0,pix);
    if(isDoubleClick){
        paint.drawText(CPoint.x(),CPoint.y(),QString::fromStdString(std::to_string(++count)));
        CPoint.setX(CPoint.x()-25);
        CPoint.setY(CPoint.y()-25);
        paint.drawEllipse(CPoint.x(),CPoint.y(),50,50);
        painter.drawPixmap(0,0,pix);

        isDoubleClick=false;
    }

}

void Dialog::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        startPoint=event->pos();
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        endPoint=event->pos();
        update();
    }
}
void Dialog::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton){
        CPoint=event->pos();
        isDoubleClick=true;
        update();
    }
}
