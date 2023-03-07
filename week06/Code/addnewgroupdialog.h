#ifndef ADDNEWTODODIALOG_H
#define ADDNEWTODODIALOG_H

#include <QDialog>
#include <QPushButton>
#include<QLineEdit>
namespace Ui {
class AddNewTodoDialog;
}

class AddNewGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewGroupDialog(QWidget *parent = nullptr);
    ~AddNewGroupDialog();

signals:
    void confirm(QString groupName);
    void cancel();

private:

    Ui::AddNewTodoDialog *ui;
    QPushButton* m_confirmBtn;
    QPushButton* m_cancelBtn;
    QLineEdit* m_groupLine;
private slots:
    void emitConfirm();
    void emitCancel();
};

#endif // ADDNEWTODODIALOG_H
