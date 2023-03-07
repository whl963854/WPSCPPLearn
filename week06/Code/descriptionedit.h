#ifndef DESCRIPTIONEDIT_H
#define DESCRIPTIONEDIT_H

#include <QWidget>

namespace Ui {
class DescriptionEdit;
}

class DescriptionEdit : public QWidget
{
    Q_OBJECT

public:
    explicit DescriptionEdit(QWidget *parent = nullptr);
    ~DescriptionEdit();

private:
    Ui::DescriptionEdit *ui;
};

#endif // DESCRIPTIONEDIT_H
