#ifndef LOTTERYTICKET_H
#define LOTTERYTICKET_H

#include <QMainWindow>
#include <QVector>


namespace Ui {
class lotteryticket;
}

class LotteryTicket : public QMainWindow
{
    Q_OBJECT

public:
    explicit LotteryTicket(QWidget *parent = 0);
    ~LotteryTicket();

private slots:

    void numOnClick();

    void numClear();

    void numCommit();

    void showWinningNum();

    void rechooseNum();

    void btnRestart();

    void menuExit();

private:
    Ui::lotteryticket *ui;

    QVector<int> savingNum;

};

#endif // LOTTERYTICKET_H
