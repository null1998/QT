#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QMouseEvent>

namespace Ui {
class Dialog;
}

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
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::Dialog *ui;





};
#endif // DIALOG_H
