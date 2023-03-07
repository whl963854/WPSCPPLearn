#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>

namespace Ui {
class LineWidget;
}

class LineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineWidget(QWidget *parent = nullptr);
    ~LineWidget();

private:
    Ui::LineWidget *ui;
};

#endif // LINEWIDGET_H
