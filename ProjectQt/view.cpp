#include "view.h"
#include "mainwindow.h"
#include <QDialog>
#include <QGridLayout>
#include <fstream>
#include <sstream>

view::view(QWidget *parent) :
    QDialog(parent)
{

    QGridLayout *l = new QGridLayout(this);

    info0 = new QLabel;
    info1 = new QLabel;
    info2 = new QLabel;
    info3 = new QLabel;
    info4 = new QLabel;
    info5 = new QLabel;
    info6 = new QLabel;
    info7 = new QLabel;
    info8 = new QLabel;
    info9 = new QLabel;
    info10 = new QLabel;
    info11 = new QLabel;

    info0->setStyleSheet(QString("font-size: %1px").arg(20));
    info1->setStyleSheet(QString("font-size: %1px").arg(20));
    info2->setStyleSheet(QString("font-size: %1px").arg(20));
    info3->setStyleSheet(QString("font-size: %1px").arg(20));
    info4->setStyleSheet(QString("font-size: %1px").arg(20));
    info5->setStyleSheet(QString("font-size: %1px").arg(20));
    info6->setStyleSheet(QString("font-size: %1px").arg(20));
    info7->setStyleSheet(QString("font-size: %1px").arg(20));
    info8->setStyleSheet(QString("font-size: %1px").arg(20));
    info9->setStyleSheet(QString("font-size: %1px").arg(20));
    info10->setStyleSheet(QString("font-size: %1px").arg(20));
    info11->setStyleSheet(QString("font-size: %1px").arg(20));

    l->addWidget(info0);
    l->addWidget(info1);
    l->addWidget(info2);
    l->addWidget(info3);
    l->addWidget(info4);
    l->addWidget(info5);
    l->addWidget(info6);
    l->addWidget(info7);
    l->addWidget(info8);
    l->addWidget(info9);
    l->addWidget(info10);
    l->addWidget(info11);
}

void view::recieveData(Movie& air)
{
    info0->setText(("Id: " + air.data[0].toString().toStdString()).c_str());
    info1->setText(("Type: " + air.data[1].toString().toStdString()).c_str());
    info2->setText(("Title: " + air.data[2].toString().toStdString()).c_str());
    info3->setText(("Director: " + air.data[3].toString().toStdString()).c_str());
    info4->setText(("Cast: " + air.data[4].toString().toStdString()).c_str());
    info5->setText(("Country: " + air.data[5].toString().toStdString()).c_str());
    info6->setText(("Date of adding: " + air.data[6].toString().toStdString()).c_str());
    info7->setText(("Release year: " + air.data[7].toString().toStdString()).c_str());
    info8->setText(("Rating: " + air.data[8].toString().toStdString()).c_str());
    info9->setText(("Duration: " + air.data[9].toString().toStdString()).c_str());
    info10->setText(("Listed in: " + air.data[10].toString().toStdString()).c_str());
    info11->setText(("Sescription: " + air.data[11].toString().toStdString()).c_str());
}

view::~view()
{
}
