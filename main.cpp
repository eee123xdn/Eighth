#include "startgame.h"
#include "piggame.h"
#include <QApplication>
#include<piggame.h>
int sum=0,day=0,money=500,sum_money=0 , cnt=0,bgm=1,bgpic=1;
double speed = 1;
Node *p =  new Node(),*head =  new Node(),*tail =  new Node();
int buy_bai = 0,buy_hua = 0,buy_hei = 0;
bool _60 = 0,_120 = 0,_180 = 0;
//QString bgmstr = "";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartGame w;
    w.show();
    return a.exec();
}
