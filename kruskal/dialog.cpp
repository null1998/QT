#include "dialog.h"
#include "ui_dialog.h"
#include<QPainter>
#include<QPushButton>
#include<QMouseEvent>
#include <string>
#include<QString>
#include<vector>

const int COUNT_MAX =100 ;
const int NUM_MAX = 1000;
std::vector<Line> f(int count,std::vector<Line> lset){
    int graph[COUNT_MAX][COUNT_MAX];
    int identify[COUNT_MAX];
    std::vector<Line> lresult;
    for (int i = 0; i <count; i++)
    {
        for (int j = 0; j < count; j++) {
            graph[i][j] = NUM_MAX;
        }
    }
    for (int i = 0; i < count; i++)
    {
            identify[i] = i;
    }
    for(int i=0;i<lset.size();i++){
        Line l=lset.at(i);
        graph[l.startCircular.num][l.endCircular.num]=l.length;
        graph[l.endCircular.num][l.startCircular.num]=l.length;
    }
    while(!lset.empty()){
        int min=NUM_MAX;
        int index=-1;
        for (int i = 0; i < lset.size(); i++)
        {
           Line l=lset.at(i);
           if (l.length < min) {
               min = l.length;
               index = i;
           }
        }
        Line min_l = lset.at(index);
        if (identify[min_l.startCircular.num] != identify[min_l.endCircular.num]) {
           int mark = identify[min_l.endCircular.num];
           for (int i = 0; i < count; i++) {
               if (identify[i] == mark) {
                    identify[i] = identify[min_l.startCircular.num];
               }
           }
                    lresult.push_back(min_l);
        }
        lset.erase(lset.begin() + index);
    }
       return lresult;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    resize(900,750);
    pix=QPixmap(600,600);
    pix.fill(Qt::white);
    isDoubleClick=false;
    isDrawLine=false;
    count=0;

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPainter paint(&pix);
    if(isDrawLine){
        paint.drawLine(startPoint,endPoint);

        isDrawLine=false;
    }


    if(isDoubleClick){
        count++;
        Circular c;
        c.initCircular(CPoint,count);
        cset.push_back(c);

        paint.drawText(CPoint.x(),CPoint.y(),QString::fromStdString(std::to_string(count)));
        CPoint.setX(CPoint.x()-25);
        CPoint.setY(CPoint.y()-25);
        paint.drawEllipse(CPoint.x(),CPoint.y(),50,50);


        isDoubleClick=false;
    }
    painter.drawPixmap(0,0,pix);

}

void Dialog::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        startPoint=event->pos();
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        endPoint=event->pos();
        isDrawLine=true;
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
