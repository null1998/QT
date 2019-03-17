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
void Dialog::kruskal(){
    int identify[COUNT_MAX];
    std::vector<Line> lresult;
    for (int i = 0; i < count; i++)
    {
            identify[i] = i;
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
        if (identify[min_l.startCircular.num-1] != identify[min_l.endCircular.num-1]) {
           int mark = identify[min_l.endCircular.num-1];
           for (int i = 0; i < count; i++) {
               if (identify[i] == mark) {
                    identify[i] = identify[min_l.startCircular.num-1];
               }
           }
                    lresult.push_back(min_l);
                    v1.push_back(lresult);
        }
        lset.erase(lset.begin() + index);
    }

}
//std::vector<Line> deleteLine(std::vector<Line> lset,std::vector<Line> successLset){
//    for(int i=0;i<successLset.size();i++){
//        Line l=successLset.at(i);
//        for(int j=0;j<lset.size();j++){
//            Line l2=lset.at(j);
//            if(l.length==l2.length&&!(l.startCircular.num==l2.startCircular.num&&l.endCircular.num==l2.endCircular.num)){
//                lset.erase(lset.begin()+j);
//                return lset;
//            }
//        }
//    }
//}
//bool isNext(){

//}

Line initLine(std::vector<Circular> cset,QPoint startPoint,QPoint endPoint){
    Line l;
    Circular markC;
    for(int i=0;i<cset.size();i++){
        Circular c=cset.at(i);
        if((c.point.x()-startPoint.x()<40&&c.point.x()-startPoint.x()>-40)&&(c.point.y()-startPoint.y()<40&&c.point.y()-startPoint.y()>-40)){
            l.startCircular=c;
            markC=c;
            cset.erase(cset.begin()+i);
            for(int j=0;j<cset.size();j++){
                Circular c2=cset.at(j);
                if((c2.point.x()-endPoint.x()<40&&c2.point.x()-endPoint.x()>-40)&&(c2.point.y()-endPoint.y()<40&&c2.point.y()-endPoint.y()>-40)){
                    l.endCircular=c2;
                    cset.push_back(markC);
                    break;
                }
            }
            break;
        }
    }
    return l;
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
    isNum=false;
    isSuccess=false;
    count=0;
    ww=0;
}

Dialog::~Dialog()
{
    delete ui;

}

void Dialog::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPainter paint(&pix);
    if(isSuccess){
        for(int i=0;i<cset.size();i++){
            Circular c=cset.at(i);
            paint.drawText(c.point.x(),c.point.y(),QString::fromStdString(std::to_string(c.num)));
            c.point.setX(c.point.x()-25);
            c.point.setY(c.point.y()-25);
            paint.drawEllipse(c.point.x(),c.point.y(),50,50);
        }
        for(int i=0;i<successLset.size();i++){
            Line l=successLset.at(i);
            QPoint s=l.startCircular.point;
            QPoint e=l.endCircular.point;
            paint.drawLine(s,e);
            QPoint w;
            w.setX((s.x()+e.x())/2);
            w.setY((s.y()+e.y())/2);
            paint.drawText(w.x(),w.y(),QString::fromStdString(std::to_string(l.length)));

        }
        isSuccess=false;
    }
    if(isNum){
       paint.drawText(WPoint.x(),WPoint.y(),QString::fromStdString(std::to_string(ww)));
       isNum=false;
    }

    if(isDrawLine){
        paint.drawLine(startPoint,endPoint);
        Line l=initLine(cset,startPoint,endPoint);
        lset.push_back(l);
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

void Dialog::on_pushButton_clicked()
{
    QString s1=ui->lineEdit->displayText();
    QString s2=ui->lineEdit_2->displayText();
    QString s3=ui->lineEdit_3->displayText();
    int s=s1.toInt();
    int e=s2.toInt();
    int w=s3.toInt();
    for(int i=0;i<lset.size();i++){
        Line l=lset.at(i);
        if((l.startCircular.num==s&&l.endCircular.num==e)||(l.startCircular.num==e&&l.endCircular.num==s)){
            lset.erase(lset.begin()+i);
            l.length=w;
            lset.push_back(l);
            ww=w;
            WPoint.setX((l.startCircular.point.x()+l.endCircular.point.x())/2);
            WPoint.setY((l.startCircular.point.y()+l.endCircular.point.y())/2);
            isNum=true;
            update();
        }
    }


}

void Dialog::on_pushButton_2_clicked()
{


    kruskal();
    if(!v1.empty()){
    successLset=v1.at(0);
    v1.erase(v1.begin()+0);
    isSuccess=true;
    clear();
    }
}
void Dialog::clear(){
    QPixmap newpix=QPixmap(600,600);
    newpix.fill(Qt::white);
    pix=newpix;
    update();
}

void Dialog::on_pushButton_3_clicked()
{
    //下一个
    if(!v1.empty()){
    successLset=v1.at(0);
    v1.erase(v1.begin()+0);
    isSuccess=true;
    clear();
    }

}

void Dialog::on_pushButton_4_clicked()
{
    count=0;
    cset.clear();
    lset.clear();
    v1.clear();
    clear();

}
