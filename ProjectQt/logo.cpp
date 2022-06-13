#include "logo.h"
#include "ui_logo.h"
#include <QPainter>
#include <QLayout>

logo::logo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logo)
{
    ui->setupUi(this);
    //this->setFixedSize(this->width(),this->height());

}

logo::~logo()
{
    delete ui;
}

void logo::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen({Qt::black, 1.0});
    painter.setBrush(QBrush(Qt::black));
    painter.translate(width()/2,height()/2);
    //painter.drawEllipse(-150,-250,300,300);
    painter.drawEllipse(-180,-270,350,350);
    painter.setPen({Qt::red, 30.0});
    //painter.drawEllipse(-125,-225,250,250);
    //painter.drawLine(-85,-50,85,-50);
    //painter.drawLine(-85,-655,-65);
    painter.drawLine(-60,-10, -60,-190);
    painter.drawLine(60,-10,60,-190);
    painter.setPen({Qt::red, 29.0});
    painter.drawLine(-55,-185,55,-15);


}
