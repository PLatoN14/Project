#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <like.h>
#include <QPushButton>
#include <QComboBox>
#include <QSortFilterProxyModel>

class MovieModel;
class Movie;
class FilterModel;

class MainWindow : public QMainWindow
{
public:
    Q_OBJECT
    QTableView *m_view = nullptr;
    MovieModel *movie_model = nullptr;
    QLineEdit *search_text;
    QComboBox *sort;
    QPushButton *search_button;
    QPushButton *like_button;
    QPushButton *add_button;
    QPushButton *filter_button;
    QSortFilterProxyModel *proxyModel;
    FilterModel *filter_model = nullptr;
    QLineEdit *model_filter;

public:
    MainWindow(QWidget *parent = nullptr);
    std::vector<Movie> load_data (const QString &dir);
    void save_data (const QString &dir);
    like *like_window;
    ~MainWindow();

public slots:
    void load_data_function();
    void save_data_function();
    void get_info(const QModelIndex &ind);
    void get_info_like(LikeItem &res);
    void search();
    void sort_function();
    void open_like();
    void add_to_favourite_function();
    void filter_data();
    void logo_window();

signals:
    void sendData(Movie& air);

friend class FilterModel;
};

enum class movie_fields
{
    id,
    type,
    title,
    director,
    cast,
    country,
    date,
    year,
    rating,
    duration,
    list,
    description,
    COUNT
};

const char *enum_to_string (movie_fields field);

class Movie
{
public:
    std::array<QVariant, (static_cast<int> (movie_fields::COUNT))> data;
};

class FilterModel : public QSortFilterProxyModel
{
   Q_OBJECT
public:
  FilterModel (QObject *parent, const MainWindow *main_window);
protected:
  virtual bool filterAcceptsRow (int source_row, const QModelIndex &source_parent) const override;
private:
  const MainWindow *main_window = nullptr;
};

class MovieModel : public QAbstractTableModel
{
Q_OBJECT

public:
std::vector<Movie> m_data;
int rowCount(const QModelIndex &/*parent*/) const override
{
    return m_data.size ();
}

int columnCount(const QModelIndex &/*parent*/) const override
{
    return static_cast<int> (movie_fields::COUNT);
}

void set_data (const std::vector<Movie> &data)
{
  beginResetModel ();
  m_data = data; // dangerous
  endResetModel ();
  emit layoutChanged ();
}

QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const override;
QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // MAINWINDOW_H
