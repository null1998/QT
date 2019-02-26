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
        graph[l.startCircular.num-1][l.endCircular.num-1]=l.length;
        graph[l.endCircular.num-1][l.startCircular.num-1]=l.length;
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
        }
        lset.erase(lset.begin() + index);
    }
       return lresult;
}

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
    successLset=f(count,lset);
    isSuccess=true;
    update();
}
