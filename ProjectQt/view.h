#ifndef VIEW_H
#define VIEW_H
#include "mainwindow.h"
#include <QDialog>
#include <QLabel>


class view : public QDialog
{
    Q_OBJECT
    QLabel *info0;
    QLabel *info1;
    QLabel *info2;
    QLabel *info3;
    QLabel *info4;
    QLabel *info5;
    QLabel *info6;
    QLabel *info7;
    QLabel *info8;
    QLabel *info9;
    QLabel *info10;
    QLabel *info11;

public:
    explicit view(QWidget *parent = nullptr);
    ~view();

signals:
    void update_cart_sum();

private slots:
    void recieveData(Movie& air);

};

#endif // VIEW_H
