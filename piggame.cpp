#include "piggame.h"
#include "ui_piggame.h"
#include<QPushButton>
#include"page1.h"
#include"page2.h"
#include"page3.h"
#include"page4.h"
#include"page5.h"
#include"config.h"
#include"store.h"
#include"honor.h"
#include<QTime>
#include<QTimer>
#include<QString>
#include<QDebug>
#include<QFile>
#include<QStringList>
#include<QMediaPlayer>
#include<QMessageBox>
#include<QSound>
QTimer*my_timer=new QTimer();//设置一个Qtimer
QTimer*my_timer1=new QTimer();//设置一个Qtimer
QTimer*my_timer2=new QTimer();//设置一个Qtimer
QTimer*my_timer4=new QTimer();//设置一个Qtimer

const QString bgmstr = ":/res/res/1.wav";

QMediaPlayer * player = new QMediaPlayer();
int healthtime = 0,nowspeed = 1;
PigGame::PigGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PigGame)
{
    ui->setupUi(this);
    PigGame::new_game(); 
    /*connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    player->setMedia(QUrl("qrc:/res/res/1.mp3"));
    player->setVolume(100);
    player->play();*/
    bells1 = new QSound(":/res/res/1.wav");
    bells2 = new QSound(":/res/res/2.wav");
    bells3 = new QSound(":/res/res/3.wav");
       bells1->play();
        bells1->setLoops(-1);
    connect(my_timer,SIGNAL(timeout()),this,SLOT(goout()));//将QTimer绑定给goout函数
    my_timer->start(speed*1000);//开始1000毫秒执行一次goout
    connect(my_timer1,SIGNAL(timeout()),this,SLOT(illmode()));//将QTimer绑定给illmode函数
    my_timer1->start(speed*1000);//开始1000毫秒执行一次goout
    connect(my_timer2,SIGNAL(timeout()),this,SLOT(healthemode()));//将QTimer绑定给healthemode函数

    connect(my_timer4,SIGNAL(timeout()),this,SLOT(pig_grow()));

    my_timer4->start(speed*1000);
    PigGame::loadgame();
}

PigGame::~PigGame()
{
    delete ui;

}
void PigGame::new_game()
{
    p = head;
    //350hua or bai
    for(int i = 0;i<70;i++)
    {
        for(int K=0;K<5;K++)
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*10000+i);
            p->data[K][0]=qrand()%2+1;

            //p->data[K][1] = 200;
            p->data[K][2] = 1;
            p->data[K][3] = 0;
            p->data[K][4] = 0;
        }
        for(int K=5;K<10;K++)         //每个猪圈后面五个位置没装，种类定为4
        {
            p->data[K][0] = 4;
            p->data[K][1] = 0;
            p->data[K][2] = 0;
            p->data[K][3] = 0;
            p->data[K][4] = 0;
        }
        p->type=0;
        p->number=5;
        p->flag=0;
        p->N = new Node();
        p=p->N;
    }
    //150hei
    for(int i = 70;i<100;i++)
    {
        p->type = true;
        for(int K=0;K<5;K++)
        {
           //qDebug()<<"1";
            p->data[K][0] = 3;
           // p->data[K][1] = 200;00
            p->data[K][2] = 1;
            //qDebug()<<p->data[K][0];
            p->data[K][3] = 0;            //改动
            p->data[K][4] = 0;
        }
        for(int K=5;K<10;K++)         //每个猪圈后面五个位置没装，种类定为4
        {
            p->data[K][0] = 4;
            p->data[K][1] = 0;
            p->data[K][2] = 0;
            p->data[K][3] = 0;
            p->data[K][4] = 0;
        }
        p->type=1;
        p->number=5;
        p->flag=0;//改动
        p->N = new Node();
        p=p->N;
    }
    p=head;
    for(int i = 0;i<100;i++)
    {

        for(int K=0;K<5;K++)
        {


                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                    p->data[K][1]=qrand()%300+200;
                    //if(i>=70)

                    //qDebug()<<p->data[K][0];
                    }


        p=p->N;

        }

     sum = 500;           //sum一开始赋予500
    //MainWindow::savefile_zhuangtai("a");

}
void PigGame::illmode()
{
    p=head;

        int m;
        if(illcheck() == false)
        {
            //qDebug()<<"no problem";
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            //qDebug()<<"no problem";
            int x=qrand()%20+60;
            //qDebug()<<"no problem";
            if(x==61)
            {

                 qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                m=qrand()%100;

                for(int i=0;i<100;i++)
                {//qDebug()<<"                "<<i;
                    if(i==m)
                    {//qDebug()<<"                "<<i;
                        int n=qrand()%10;
                       // qDebug()<<"pa";
                        p->data[n][3]=1;       //该猪已经被感染
                       // qDebug()<<"pa";
                        p->flag=1;             //猪圈已经被感染
                       // qDebug()<<"pa";
                        cnt=std::max(m,100-m)*7+50;
                       // qDebug()<<"pa";
                        break;
                    }
                   // qDebug()<<"                "<<i;
                    p=p->N;
                   // qDebug()<<"                "<<i;
                }
            }
        }
       // qDebug()<<"no problem";
        if(cnt == 0&&illcheck()==true)
        {
            QString ac = "有瘟疫的猪圈有"+QString::number(illsum())+"个，占到了所有猪圈的"+QString::number(illsum())+"%";
            this->ui->lb_ill_pigsty->setText(ac);
            this->ui->lb_ill_arise->setText("养猪场出现瘟疫");
            this->ui->lb_daed_day->setText("如果未隔离，最快"+QString::number(cnt)+"天后全部猪就会死亡");
        }
        else if(illcheck()==false)
        {
            this->ui->lb_ill_pigsty->setText("有瘟疫的猪圈有0个，占到了所有猪圈的0%");
            this->ui->lb_ill_arise->setText("养猪场未出现瘟疫");
            this->ui->lb_daed_day->setText("恭喜你，目前你的猪尚未感染瘟疫");
        }
            else
       {
            QString ac = "有瘟疫的猪圈有"+QString::number(illsum())+"个，占到了所有猪圈的"+QString::number(illsum())+"%";
            this->ui->lb_ill_pigsty->setText(ac);
            this->ui->lb_ill_arise->setText("养猪场出现瘟疫");
           QString ab = "如果未隔离，最快"+QString::number(cnt)+"天后全部猪就会死亡";
        //qDebug()<<"no problem";
        this->ui->lb_daed_day->setText(ab);
        //qDebug()<<"no problem";
         cnt--;
        }
          //qDebug()<<"no problem";
        p=head;
// qDebug()<<"no problem";
        if(check())        //没有全部死亡
            {
            //qDebug()<<"no prblm";
                for(int i=0;i<100;i++)
                {//qDebug()<<"no prblm";
                    for(int k=0;k<10;k++)
                    {//qDebug()<<"no prblm";
                        if(p->data[k][3]==1)
                        {
                             //qDebug()<<"no prblm";
                            continue;
                        //qDebug()<<"no prblm";
                        }
                        else if(p->flag==1)
                        {//qDebug()<<"no prblm";

                            int x=qrand()%100;
                            if(x<50)
                            {//qDebug()<<"no prblm";
                                p->data[k][3]=1;
                                p->data[k][4]=180;
                            }
                        }
                        else if(p->flag==0&&((p->F!=NULL&&p->F->flag==1)||(p->N!=NULL&&p->N->flag==1)))
                        {//qDebug()<<"no prblm";
                            int x=qrand()%100;
                            if(x<15)
                            {//qDebug()<<"no prblm";
                                p->flag=1;
                                p->data[k][3]=1;
                                p->data[k][4]=180;
                            }
                        }
                    }
                    p=p->N;
                }
            }


}
void PigGame::on_btn_config_clicked()
{
    config *a = new config(this);
    connect(a,SIGNAL(change_BGM_and_BGPIC()),this,SLOT(change_BGM_and_BGPIC()));
    a->show();
}

void PigGame::on_btn_store_clicked()
{
    store *a = new store(this);
    a->show();

    p=head;
}

void PigGame::on_btn_honor_clicked()
{
    honor *a = new honor(this);
    a->show();

}

void PigGame::on_btn_nextpage_clicked()
{
    int nIndex = ui->stackedWidget->currentIndex();

        // 获取下一个需要显示的页面索引
        ++nIndex;

        // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nIndex == 5)
            nIndex = 0;

       ui->stackedWidget->setCurrentIndex(nIndex);
}

void PigGame::on_btn_frontpage_clicked()
{
    int nIndex = ui->stackedWidget->currentIndex();

        // 获取下一个需要显示的页面索引
        --nIndex;

        // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nIndex == -1)
            nIndex = 4;

       ui->stackedWidget->setCurrentIndex(nIndex);
}
void PigGame::goout()//chu lan
{
    if(day%90 == 0)
    {
    //qDebug()<<"go out";
    sum_money = 0;
    int hua=0,bai = 0,hei = 0;;
    int numpig = 0;
    *p = *head;
    //grow shuiji
    for(int i = 0;i<100;i++)
    {
        for(int K=0;K<10;K++)
        {
            if((p->data[K][1]>=750||p->data[K][2]>360)&&p->data[K][0]<=3&&p->data[K][3]==0)//一个月30天//注意：要该猪不是空，且未被感染
            {
                numpig ++;
                if(p->data[K][0]==1)
                    sum_money += 7*p->data[K][1]/10;        //如果要统计出栏的，就在这个地方数量++
                if(p->data[K][0]==2)
                    sum_money += 6*p->data[K][1]/10;
                if(p->data[K][0]==3)
                    sum_money += 15*p->data[K][1]/10;
                if(p->type == false)                         //如果盖猪圈出栏不是黑猪，补入白猪或者花猪，bai++或者hei++
                {
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*10000+i);
                p->data[K][0]=qrand()%2+1;
                if(p->data[K][0] == 1)
                    hua++;
                if(p->data[K][0] == 2)
                    bai++;
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                p->data[K][1]=qrand()%300+200;
                p->data[K][2]=1;           //补充的几个信息都要初始化//还有，之前全局变量和总金钱都用的一个名，现在把卖出的钱改成了sum_money
                p->data[K][3]=0;
                p->data[K][4]=0;
                }
                else
                {
                    hei++;
                    p->data[K][0]=3;
                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                    p->data[K][1]=qrand()%300+200;
                    p->data[K][2]=1;
                    p->data[K][3]=0;
                    p->data[K][4]=0;
                }
            }
        }

        p=p->N;
    }
    money+=sum_money;
    //MainWindow::savefile_chulan(QString::number(sum)+"|"+QString::number(numpig)+"|"+QString::number(hua)+"|"+QString::number(bai)+"|"+QString::number(hei));
    //MainWindow::savefile_zhuangtai("a");
    QString ab = QString::number(sum_money) + "|" +QString::number(numpig);//返回，一会用正则表达式搞一波
    }

}
 bool PigGame::check()
 {
     p=head;
     for(int i=0;i<100;i++)
     {
         //qDebug()<<"check1";
         for(int k=0;k<10;k++)
         {
           //  qDebug()<<"check2";
             if(p->data[k][3] == 0&&p->data[k][0]<=3)
                {p=head;
                 return true;
             }

         }

         p=p->N;

     }
     p=head;
     return false;
 }
  bool PigGame::illcheck()
 {
     p=head;
     for(int i=0;i<100;i++)
     {
         for(int k=0;k<10;k++)
         {
             if(p->data[k][3] == 1)
             {
                 p=head;
                 return true;
             }
         }

         p=p->N;

     }
     //qDebug()<<"illcheck";
     p=head;
     return false;
 }

void PigGame::on_btn_geli_clicked()
{
    if(illcheck()&&my_timer2->isActive() == false)
    {
        p=head;
    healthtime = 180;
    my_timer1->stop();
    this->ui->lb_daed_day->setText("开始隔离，停止计算死亡时间");
    this->ui->lb_ill_arise->setText("出现瘟疫，开始隔离");


    my_timer2->start(speed*1000);//开始1000毫秒执行一次healthemode
    }

}
void PigGame::healthemode()
{
    this->ui->lb_health_day->setText("还有"+QString::number(healthtime)+"天隔离完成,在此期间病猪不可出栏");
    healthtime--;
    if(healthtime == -1)
    {
        this->ui->lb_health_day->setText("目前处于非隔离状态");
        p = head;
        for(int i = 0;i<100;i++)
        {
            for (int k = 0;k<10;k++)
            {
                p->data[k][3] = 0;
            }
            p->flag = 0;
            p=p->N;
        }
        p = head;
        my_timer2->stop();
        my_timer1->start(speed*1000);
    }
}
int PigGame::illsum()
{
    int summ = 0;
    p=head;
    for(int i = 0;i<=99;i++)
    {
        if(p->flag == 1)
            summ++;
        p=p->N;
    }
    p=head;
    return summ;
}
void PigGame::loadgame()
{
    /*
     * 载入文件记得加上day
     *
     */
    p = head;
    QFile file("pigdata.mt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    int numcnt = 0;
    int healthtimecnt,in_geli = 0,in_ill,cntcnt,moneycnt;
    while(!file.atEnd())
    {
        numcnt++;

        //qDebug()<<"666";

        if(numcnt == 1)
        {

            QByteArray line = file.readLine();
            QString str(line);
            QStringList list = str.split("|");
            healthtimecnt =list[1].toInt();
            in_geli = list[0].toInt();
            in_ill = list[2].toInt();
            cntcnt = list[3].toInt();
            moneycnt = list[4].toInt();
            day = list[5].toInt();
            cnt = cntcnt;
            money = moneycnt;

            //qDebug()<<healthtimecnt<<in_geli<<in_ill<<cntcnt<<moneycnt<<endl;
        }
        else
        {
            for(int k=0;k<10;k++)
            {
                QByteArray line = file.readLine();
                QString str(line);
                QStringList list = str.split("|");
                p->data[k][0] = list[0].toInt();
                p->data[k][1] = list[1].toInt();
                p->data[k][2] = list[2].toInt();
                p->data[k][3] = list[3].toInt();
                p->data[k][4] = list[4].toInt();
                if(p->data[k][3] == 1)
                    p->flag = 1;
                qDebug()<<k;
            }
            p = p -> N;

        }
        //qDebug()<< str;
    }
    if(in_geli == 1&&in_ill == 1)
    {
        QString ac = "有瘟疫的猪圈有"+QString::number(illsum())+"个，占到了所有猪圈的"+QString::number(illsum())+"%";
        this->ui->lb_ill_pigsty->setText(ac);
       // qDebug()<<"666";
        if(my_timer1->isActive())
        PigGame::on_btn_geli_clicked();
        healthtime=healthtimecnt;
    }
    file.close();
    p= head;
}
void PigGame::change_BGM_and_BGPIC()
{
    if(bgpic == 1)
    ui->backimg->setStyleSheet("background-image: url(:/res/res/game3.jpg);");
    if(bgpic == 2)
    ui->backimg->setStyleSheet("background-image: url(:/res/res/game2.jpg);");
    if(bgpic == 3)
    ui->backimg->setStyleSheet("background-image: url(:/res/res/game1.jpg);");
    if(bgm == 1)
    {
        bells2->stop();
        bells3->stop();
        bells1->stop();
        bells1->play();
    }
    if(bgm == 2)
    {
        bells2->stop();
        bells3->stop();
        bells1->stop();
        bells2->play();
    }
    if(bgm == 3)
    {
        bells2->stop();
        bells3->stop();
        bells1->stop();
        bells3->play();
    }
}
void PigGame::pig_grow()
{
    qDebug()<<day<<endl;
    p = head;
    //grow shuiji
    for(int i = 0;i<100;i++)
    {
        for(int K=0;K<10;K++)
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*day*1000+i);
            int test =qrand()%13;
            //注意：十倍
         p->data[K][1]+=test;
         p->data[K][2]++;
        }
        p=p->N;
    }
    p=head;
    day++;
}
