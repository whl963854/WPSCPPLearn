#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QObject>

class EditLabel : public QWidget {
    Q_OBJECT

public:
    EditLabel(QWidget *parent = Q_NULLPTR);

protected:
    bool eventFilter(QObject * obj, QEvent * e);

private:
    QStackedWidget * m_stackWidget;
    QLabel * m_label;
    QLineEdit * m_lineEdit;

private:
    void initCtrls(void);
};

