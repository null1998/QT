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
    Line(){}
    ~Line(){}
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
    QPoint WPoint;
    int ww;
    QPixmap pix;
    QPainter *paint;
    bool isDoubleClick;
    bool isDrawLine;
    bool isNum;
    bool isSuccess;
    std::vector<Circular> cset;//已存在的顶点的集合
    std::vector<Line> lset;//已存在的边的集合
    std::vector<Line> successLset;//已通过验证的边的集合
    std::vector<std::vector<Line>> v1;//每一步生成的successLset集合的集合，主要为了分步显示过程
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void kruskal();
    void clear();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Dialog *ui;
};


#endif // DIALOG_H
