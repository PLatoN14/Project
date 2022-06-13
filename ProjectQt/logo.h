#ifndef LOGO_H
#define LOGO_H

#include <QDialog>

namespace Ui {
class logo;
}

class logo : public QDialog
{
    Q_OBJECT

public:
    explicit logo(QWidget *parent = nullptr);
    ~logo();

protected:
    void paintEvent(QPaintEvent*);

private:
    Ui::logo *ui;
};

#endif // LOGO_H
