#include "like.h"
#include "mainwindow.h"
#include <QDialog>
#include <QGridLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <QDebug>

like::like(QWidget *parent) :
    QWidget(parent)
{
    like_model = new LikeModel();
    like_view = new QTableView(this);

    QGridLayout *l = new QGridLayout(this);

    delete_button = new QPushButton();

    like_view->setModel(like_model);

    delete_button->setText("Delete Item");

    connect(delete_button, SIGNAL(clicked()), this, SLOT(delete_from_cart_function()));
    connect(like_view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(info(QModelIndex)));

    l->addWidget(delete_button);
    l->addWidget(like_view);
}

void like::info(const QModelIndex & ind)
{
    LikeItem res;
    int row = ind.row();
    QModelIndex index;
    std::string s;
    for(int i = 0; i < 3; i++) {
        index = like_view->model()->index(row,i,QModelIndex());
        s = index.data().toString().toStdString();
        res.data_like[i] = QString(s.c_str());
    }
    emit send_data(res);
}

void like::delete_from_cart_function()
{
    LikeItem res;
    QItemSelectionModel *selectModel = like_view->selectionModel();
    QModelIndexList indexes = selectModel->selectedIndexes();
    for (QModelIndex ind : indexes)
    {
        int row = ind.row();
        QModelIndex index = like_view->model()->index(row,0,QModelIndex());
        res.data_like[0] = QString(index.data().toString().toStdString().c_str());
        index = like_view->model()->index(row,1,QModelIndex());
        res.data_like[1] = QString(index.data().toString().toStdString().c_str());
        index = like_view->model()->index(row,2,QModelIndex());
        res.data_like[2] = QString(index.data().toString().toStdString().c_str());
    }
    like_model->delete_data(res);
}

like::~like()
{
}

QVariant LikeModel::data (const QModelIndex &index, int role) const
{
   if (role == Qt::DisplayRole || role == Qt::EditRole)
   {
       const LikeItem &current_like = l_data[index.row ()];
       return current_like.data_like[index.column ()];
   }
   return {};
}


const char *enum_to_string_cart (like_fields field)
{
    switch (field)
    {
        case like_fields::type      : return "Type";
        case like_fields::title     : return "Title";
        case like_fields::year      : return "Year";
        case like_fields::COUNT     : return "";
    }
    return {};
}

QVariant LikeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        like_fields field = (like_fields)section;
        return enum_to_string_cart(field);
    }
    return {};
}
