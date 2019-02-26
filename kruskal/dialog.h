#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QMouseEvent>
#include<vector>

namespace Ui {
class Dialog;
}
class Circular{
public:
    QPoint point;
    int num;
    Circular(){}
    ~Circular(){}
    void initCircular(QPoint point,int num){this->point=point;this->num=num;}
};
class Line{
public:
    Circular startCircular;
    Circular endCircular;
    int length;
};
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    int count;
    QPoint startPoint;
    QPoint endPoint;
    QPoint CPoint;
    QPixmap pix;
    QPixmap tempPix;
    QPainter *paint;
    bool isDoubleClick;
    bool isDrawLine;
    std::vector<Circular> cset;
    std::vector<Line> lset;
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::Dialog *ui;
};


#endif // DIALOG_H
