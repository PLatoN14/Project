#ifndef LIKE_H
#define LIKE_H
#include <QMainWindow>
#include <QDialog>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QLabel>

class LikeModel;
class LikeItem;


class like : public QWidget
{
    Q_OBJECT
    QTableView *like_view = nullptr;
    QPushButton *delete_button;

    public:
    LikeModel *like_model = nullptr;

public:
    explicit like(QWidget *parent = nullptr);
    ~like();

private slots:
    void delete_from_cart_function();
    void info(const QModelIndex & ind);

signals:
    void send_data(LikeItem &res);

};

enum class like_fields
{
    type,
    title,
    year,
    COUNT
};

const char *enum_to_string_cart (like_fields field);

class LikeItem
{
public:
    std::array<QVariant, (static_cast<int> (like_fields::COUNT))> data_like;
    friend bool operator==(const LikeItem &a, const LikeItem &b) {
        return(a.data_like[0] == b.data_like[0] && a.data_like[1] == b.data_like[1]);
    }
};

class LikeModel : public QAbstractTableModel
{
Q_OBJECT

public:
    std::vector<LikeItem> l_data;

int rowCount(const QModelIndex &/*parent*/) const override
{
    return l_data.size ();
}

int columnCount(const QModelIndex &/*parent*/) const override
{
    return static_cast<int> (like_fields::COUNT);
}

void add_data(const LikeItem &data)
{
    beginResetModel ();
    bool flag = true;
    std::vector<LikeItem>::iterator it = l_data.begin();
    for(;it != l_data.end(); it++) {
        if(*it == data)
        {
            flag = false;
            break;
        }
    }
    if(flag)
        l_data.push_back(data);
    endResetModel ();
    emit layoutChanged ();
}

void delete_data(const LikeItem &data)
{
    beginResetModel ();
    std::vector<LikeItem>::iterator it = l_data.begin();
    for(;it != l_data.end(); it++) {
        if(*it == data) {
            l_data.erase(it);
            break;
        }
    }
    endResetModel ();
    emit layoutChanged ();
}

QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const override;
QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
#endif // LIKE_H
