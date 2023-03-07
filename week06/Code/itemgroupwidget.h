#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

#include <QWidget>

namespace Ui {
class GroupWidget;
}

class ItemGroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemGroupWidget(QWidget *parent = nullptr);
    ~ItemGroupWidget();
    void setName(QString name);

private:
    Ui::GroupWidget *ui;
};

#endif // GROUPWIDGET_H
