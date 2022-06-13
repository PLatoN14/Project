#include "mainwindow.h"
#include "view.h"
#include <QGridLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <QDebug>
#include "logo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central_widget = new QWidget (this);
    like_window = new like;
    movie_model = new MovieModel();
    filter_model = new FilterModel(this, this);
    setCentralWidget(central_widget);
    m_view = new QTableView(central_widget);

    QGridLayout *layout = new QGridLayout(central_widget);

    search_text = new QLineEdit();
    search_button = new QPushButton();
    like_button = new QPushButton();
    add_button = new QPushButton();
    filter_button = new QPushButton();
    sort = new QComboBox();
    model_filter = new QLineEdit ();
    proxyModel = new QSortFilterProxyModel(this);

    m_view->setModel(filter_model);
    filter_model->setSourceModel(movie_model);
    proxyModel->setSourceModel(movie_model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    m_view->setColumnHidden(0, true);
    m_view->setColumnHidden(3, true);
    m_view->setColumnHidden(4, true);
    m_view->setColumnHidden(5, true);
    m_view->setColumnHidden(6, true);
    m_view->setColumnHidden(8, true);
    m_view->setColumnHidden(9, true);
    m_view->setColumnHidden(10, true);
    m_view->setColumnHidden(11, true);
    search_button->setStyleSheet(QString("font-size: %1px").arg(25));
    search_text->setStyleSheet(QString("font-size: %1px").arg(20));
    search_button->setText("Search");
    add_button->setText("Add to Favourite");
    like_button->setText("Open Favourite");
    filter_button->setText("Apply");
    sort->addItem("Default");
    sort->addItem("Title Ascending");
    sort->addItem("Title Descending");
    sort->addItem("Year Ascending");
    sort->addItem("Year Descending");

    connect(m_view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(get_info(QModelIndex)));
    connect(search_button, SIGNAL(clicked()), this, SLOT(search()));
    connect(sort, SIGNAL(currentIndexChanged(QString)), SLOT(sort_function()));
    connect(like_button, SIGNAL(clicked()), this, SLOT(open_like()));
    connect(add_button, SIGNAL(clicked()), this, SLOT(add_to_favourite_function()));
    connect(like_window, SIGNAL(send_data(LikeItem&)), this, SLOT(get_info_like(LikeItem&)));
    connect (filter_button, SIGNAL(clicked()), this, SLOT(filter_data()));


    layout->addWidget(search_button);
    layout->addWidget(search_text);
    layout->addWidget(like_button);
    layout->addWidget(add_button);
    layout->addWidget (m_view);
    layout->addWidget(sort);
    layout->addWidget(model_filter);
    layout->addWidget(filter_button);

    auto file_menu = menuBar ()->addMenu ("File");
    QAction *open_action = new QAction ("Open");
    connect (open_action, &QAction::triggered, this, &MainWindow::load_data_function);
    file_menu->addAction  (open_action);

    QAction *saveas_action = new QAction ("Save As");
    connect (saveas_action, &QAction::triggered, this, &MainWindow::save_data_function);
    file_menu->addAction  (saveas_action);

    QAction *logo = new QAction ("Logo");
        connect(logo, SIGNAL(triggered()), this, SLOT(logo_window()));
        menuBar()->addAction(logo);

}

void MainWindow::logo_window()
{
    logo Logo;
    Logo.exec();
}

void MainWindow::filter_data()
{
  filter_model->invalidate();
}

void MainWindow::add_to_favourite_function()
{
    LikeItem res;
    QItemSelectionModel *selectModel = m_view->selectionModel();
    QModelIndexList indexes = selectModel->selectedIndexes();
    for (QModelIndex ind : indexes)
    {
        int row = ind.row();
        QModelIndex index = m_view->model()->index(row,1,QModelIndex());
        std::string s = index.data().toString().toStdString();
        res.data_like[0] = QString(s.c_str());
        index = m_view->model()->index(row,2,QModelIndex());
        s = index.data().toString().toStdString();
        res.data_like[1] = QString(s.c_str());
        index = m_view->model()->index(row,7,QModelIndex());
        s = index.data().toString().toStdString();
        res.data_like[2] = QString(s.c_str());
    }
    like_window->like_model->add_data(res);
}

void MainWindow::open_like()
{
    like_window->show();
}

void MainWindow::sort_function()
{
    QString text = sort->currentText();
    if(text == "Default")
        filter_model->sort(0, Qt::AscendingOrder);
    else if (text == "Title Ascending")
        filter_model->sort(2, Qt::AscendingOrder);
    else if (text == "Title Descending")
        filter_model->sort(2, Qt::DescendingOrder);
    else if (text == "Year Ascending")
        filter_model->sort(7, Qt::AscendingOrder);
    else if (text == "Year Descending")
        filter_model->sort(7, Qt::DescendingOrder);
    m_view->setModel(filter_model);
}

void MainWindow::search()
{
    QString s = search_text->text();
    if(s.isNull()) //if there is no text it won't go throw all data
        return;
    for(Movie &item : movie_model->m_data)
        if(item.data[2] == s)
        {
            view v;
            connect(this, SIGNAL(sendData(Movie&)), &v, SLOT(recieveData(Movie&)));
            emit sendData(item);
            v.exec();
            break;
        }
}

void MainWindow::get_info(const QModelIndex & ind)
{
    Movie res;
    int row = ind.row();
    QModelIndex index;
    std::string s;
    for(int i = 0; i < 12; i++) {
        index = m_view->model()->index(row,i,QModelIndex());
        s = index.data().toString().toStdString();
        if(s.size() == 0)
            res.data[i] = QString("No Info");
        else
            res.data[i] = QString(s.c_str());
    }
    view v;
    connect(this, SIGNAL(sendData(Movie&)), &v, SLOT(recieveData(Movie&)));
    emit sendData(res);
    v.exec();
}

void MainWindow::get_info_like(LikeItem &res)
{
    Movie data;
    for(auto &item : movie_model->m_data) {
        if(res.data_like[1] == item.data[2] && res.data_like[2] == item.data[7]) {
            data = item;
            break;
        }
    }
    view v;
    connect(this, SIGNAL(sendData(Movie&)), &v, SLOT(recieveData(Movie&)));
    emit sendData(data);
    v.exec();
}

void MainWindow::load_data_function ()
{
    auto dir = QFileDialog::getOpenFileName (this, "Open File", QDir::currentPath ());
    if (!dir.size ())
        return;
    auto data = load_data(dir);
    movie_model->set_data (data);
}


void MainWindow::save_data_function ()
{
  auto dir = QFileDialog::getSaveFileName (this, "Save File As", QDir::currentPath ());
  if (!dir.size ())
    return;
  save_data (dir);
}

std::vector<Movie> MainWindow::load_data (const QString &dir)
{
    std::fstream file;
    std::vector<Movie> result;
    file.open(dir.toStdString ());
    std::string temp1, temp2;
    int j = 0;
    while(std::getline(file, temp1))
    {
        Movie res;
        int i = 0;
        std::stringstream str(temp1);
        std::string temp3 = "";
        bool flag = false;
        while(std::getline(str, temp2, ','))
        {
            if(flag)
            {
                if(temp2[temp2.size()-1] == '"' && temp2[temp2.size()-2] != '"')
                {
                    temp3 += temp2 + ',';
                    flag = false;
                    temp3.erase(temp3.begin());
                    temp3.erase(temp3.end()-1);
                    temp3.erase(temp3.end()-1);
                    res.data[i] = QString(temp3.c_str());
                    temp3="";
                    ++i;
                    continue;
                }
                else
                {
                    temp3 += temp2 + ',';
                    continue;
                }
            }
            if((temp2[0] == '"' && temp2[temp2.size()-1] != '"') || temp2 == "\"")
            {
                temp3 += temp2 + ',';
                flag = true;
            }
            else
            {
                if(temp2[0]=='"')
                {
                    temp2.erase(temp2.begin());
                    temp2.erase(temp2.end()-1);
                }
                res.data[i] = QString(temp2.c_str());
                ++i;
            }
        }
        if(j && res.data[0] != " and probably will.\"" && res.data[0] != "Flying Fortress\"" && res.data[0] != "s8420") {
            std::string s = res.data[0].toString().toStdString();
            s.erase(s.begin());
            res.data[0] = std::stod(s);
            result.push_back(res);
        }
        j++;
    }
    file.close();
    return result;
}

void MainWindow::save_data (const QString &dir)
{
    std::ofstream file (dir.toStdString ());
    int total_columns = static_cast<int> (movie_fields::COUNT);
    for (auto &item : movie_model->m_data)
    {
        for (int i_column = 0; i_column < total_columns; ++i_column)
        {
            file << item.data[i_column].toString().toStdString();
            if (i_column < total_columns - 1)
                file << ",";
            else
                file << "\n";
        }
    }
}


MainWindow::~MainWindow()
{
}

FilterModel::FilterModel (QObject *parent, const MainWindow *main_window) : QSortFilterProxyModel (parent), main_window (main_window)
{}

QVariant MovieModel::data (const QModelIndex &index, int role) const
{
   if (role == Qt::DisplayRole || role == Qt::EditRole)
   {
       const Movie &current_movie = m_data[index.row ()];
        return current_movie.data[index.column()];
   }
   return {};
}


const char *enum_to_string (movie_fields field)
{
    switch (field)
    {
        case movie_fields::id           : return "ID";
        case movie_fields::type         : return "Type";
        case movie_fields::title        : return "Title";
        case movie_fields::director     : return "Director";
        case movie_fields::cast         : return "Cast";
        case movie_fields::country      : return "Country";
        case movie_fields::date         : return "Date";
        case movie_fields::year         : return "Year";
        case movie_fields::rating       : return "Rating";
        case movie_fields::duration     : return "Duration";
        case movie_fields::list         : return "List";
        case movie_fields::description  : return "Description";
        case movie_fields::COUNT        : return "";
    }
    return {};
}

bool FilterModel::filterAcceptsRow (int source_row, const QModelIndex &/*source_parent*/) const
{
  auto model = main_window->model_filter->text();
  const Movie& movie = main_window->movie_model->m_data[source_row];
  return (!model.size () || movie.data[(int)movie_fields::type].toString () == model);
}

QVariant MovieModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        movie_fields field = (movie_fields)section;
        return enum_to_string (field);
    }
    return {};
}
