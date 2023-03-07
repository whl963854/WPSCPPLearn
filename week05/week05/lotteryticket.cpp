#include "lotteryticket.h"
#include "ui_lotteryticket.h"
#include <QCoreApplication>
#include<QString>
#include<QPushButton>
#include<QPlainTextEdit>
#include<QLineEdit>
#include<QTime>
#include<QVector>
#include<QRegExp>

LotteryTicket::LotteryTicket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lotteryticket)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    for(int i=0;i<10;i++)
    {
        QString numName="btnNum"+QString::number(i);
        QPushButton *numBtn=LotteryTicket::findChild<QPushButton *>(numName);
        connect(numBtn,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    }
    ui->btnOk->setShortcut(tr("return"));
    connect(ui->btnClear,SIGNAL(clicked(bool)),this,SLOT(numClear()));
    connect(ui->btnOk,SIGNAL(clicked(bool)),this,SLOT(numCommit()));
    connect(ui->btnLottery,SIGNAL(clicked(bool)),this,SLOT(showWinningNum()));
    connect(ui->btnRechoose,SIGNAL(clicked(bool)),this,SLOT(rechooseNum()));
    connect(ui->btnRestart,SIGNAL(clicked(bool)),this,SLOT(btnRestart()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(menuExit()));
}

LotteryTicket::~LotteryTicket()
{
    delete ui;
}

void LotteryTicket::numOnClick()
{
    QPushButton *numName = (QPushButton *)sender();
    auto str = ui->inputNumEdit->text()+numName->text();
    int inputNum=ui->inputNumEdit->text().toInt();
    ui->inputNumEdit->setText(QString::number(inputNum));
    ui->inputNumEdit->setText(str);
}
void LotteryTicket::numClear()
{
    ui->inputNumEdit->setText("");
}
void LotteryTicket::numCommit()
{
    int inputNum=ui->inputNumEdit->text().toInt();
    if(inputNum>35||inputNum==0)
    {
        ui->warningEdit->setText("请输入1-35的数字");
        return ;
    }
    if(savingNum.contains(inputNum))
    {
        ui->warningEdit->setText("请不要选择重复的数字");
        return ;
    }
    if(savingNum.size()==7)
    {
        ui->warningEdit->setText("您已经选择了七个号码");
        return ;
    }
    savingNum.push_back(inputNum);
    auto str = ui->chooseNum->text()+" "+QString::number(inputNum);
    ui->chooseNum->setText(str);
    ui->inputNumEdit->setText("");
    ui->inputNumEdit->cursorBackward(1,2);
}
void LotteryTicket::showWinningNum()
{
    int bonusAmount[10]={0,5,50,100,500,100000,300000,5000000};
    int count=0;
    if(savingNum.size()!=7)
    {
        ui->warningEdit->setText("请选择七个号码再开奖");
        return;
    }
    qsrand(QTime::currentTime().msec());	//设置种子，该种子作为qrand生成随机数的起始值，RAND_MAX为32767，即随机数在种子值到32767之间
    QSet<int>lotteryNum;
    QString str="";
    for(int i=0;i<7;i++)
    {
        int num = qrand()%35+1;
        if(lotteryNum.find(num)!=lotteryNum.end())
        {
            i--;
            continue;
        }
        str+=QString::number(num);
        str+=" ";
        lotteryNum.insert(num);
        if(savingNum[i]==num)
        {
            count++;
        }
    }
    ui->winningNumEdit->setText(str);
    int lastBonus=bonusAmount[count];
    if(!count)
        ui->bonus->setText("谢谢参与");
    else
        ui->bonus->setText(QString::number(lastBonus)+"!");
}

void LotteryTicket::rechooseNum()
{
    savingNum.clear();
    ui->chooseNum->setText("");
}

void LotteryTicket::btnRestart()
{
    savingNum.clear();
    ui->bonus->setText("");
    ui->warningEdit->setText("");
    ui->chooseNum->setText("");
    ui->inputNumEdit->setText("");
    ui->winningNumEdit->setText("");
}
void LotteryTicket::menuExit()
{
    this->close();
}
