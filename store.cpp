#include "store.h"
#include "ui_store.h"
#include"QString"
#include"QDebug"
#include"algorithm"
#include"QMessageBox"
#include<piggame.h>
#include<QTimer>
#include<QTime>
    QTimer* my_timer3 = new QTimer();
store::store(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::store)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    connect(my_timer3,SIGNAL(timeout()),this,SLOT(viewmoney()));//将QTimer绑定给goout函数
    my_timer3->start(50);//开始1000毫秒执行一次goout

}

store::~store()
{
    my_timer3->stop();
    delete ui;

}

void store::on_pushButton_2_clicked()
{
    this->close();
}

void store::on_pushButton_clicked()
{
    buy_bai = 0;buy_hua = 0;buy_hei = 0;
    _60 = 0;_120 = 0;_180 = 0;
    buy_bai = ui->le_bai->text().toInt();
    buy_hua = ui->le_hua->text().toInt();
    buy_hei = ui->le_hei->text().toInt();
    _60 = ui->cb_60->isChecked();
    _120 = ui->cb_120->isChecked();
    _180 = ui->cb_180->isChecked();


    /*
    // * 测试模块
    qDebug()<<buy_bai<<"  "<<buy_hei<<"  "<<buy_hua<<"  "<<endl;
    if(_60)
        qDebug()<<"-60"<<endl;
    if(_120)
        qDebug()<<"-120"<<endl;
    if(_180)
        qDebug()<<"-180"<<endl;
   // *
    */
    check(buy_hei,buy_bai,buy_hua,_60,_120,_180);

}
bool store::check(int hei,int bai,int hua,bool yimiao,bool kangti,bool jiyin)
{
/*测试使用*/
//  money = 999999999;


/*测试使用*/
    int need=hei*150+bai*100+hua*50;
    if(yimiao)
        need+=300;
     if(kangti)
         need+=550;
     if(jiyin)
         need+=1000;
    int f=0;
    if(hei<0||bai<0||hua<0)
    {
        f=1;
        QMessageBox::information(this,"提示","所选的某一项小于0,购买不成功,请重新选择\n","确定");
        return false;
    }
    else if(need>money)    //如果需要的钱大于已有的
    {
        f=1;
        QMessageBox::information(this,"提示","现有的钱还不够购买，购买不成功,请重新选择\n","确定");
        return false;
    }
    else if(hei+bai+hua>1000-sum)   //如果总共购买的猪大于剩下的空位
    {
        f=1;
       QMessageBox::information(this,"提示","购买的猪大于所剩空位，购买不成功,请重新选择\n","确定");
        return false;
    }
    p=head;
    int hei_res=0;
    for(int i=0;i<100;i++)     //计算所有黑猪圈的空余数
    {
        if(p->type==1)
        {
            hei_res+=10-p->number;
        }
    }
    if(hei>hei_res)
    {

        f=1;
        QMessageBox::information(this,"提示","购买的黑猪大于所剩黑猪空位，购买不成功,请重新选择\n","确定");
        return false;
    }
    else{
        //购买能成功
        //首先，先购买疫苗，抗体等
        money-=need;
        if(jiyin>0) healthtime=0;        //有基因，隔离天数变为0
        else {
             healthtime-=(60*yimiao+kangti*550);
             if(healthtime<0) healthtime=0;
        }
        //接下来，补充猪
        p=head;
        for(int i=0;i<100;i++)
        {
           if(p->type==1&&p->number<10&&hei) //如果猪圈是黑猪圈且猪圈有空且黑猪还有没入猪圈的
           {
               if(hei<=10-p->number)    //该猪圈能把剩下黑猪装完
               {
                   for(int k=p->number;k<p->number+hei;k++)
                   {
                       p->data[k][0]=1;
                       qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+k*100+i);
                       p->data[k][1]=qrand()%300+200;
                       p->data[k][2]=1;
                       p->data[k][3]=0;
                       p->data[k][4]=0;
                   }
                   hei=0;
                   p->number+=hei;
               }
               else{
                   for(int k=p->number;k<10;k++)
                   {
                       p->data[k][0]=1;
                       qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+k*100+i);
                       p->data[k][1]=qrand()%300+200;
                       p->data[k][2]=1;
                       p->data[k][3]=0;
                       p->data[k][4]=0;
                   }
                   p->number=10;
                   hei-=(10-p->number);
               }
            }
           if(p->type==0&&p->number<10&&bai)
           {
               if(bai<=10-p->number)    //该猪圈能把剩下白猪装完
               {
                   for(int k=p->number;k<p->number+bai;k++)
                   {
                       p->data[k][0]=1;
                       qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+k*100+i);
                       p->data[k][1]=qrand()%300+200;
                       p->data[k][2]=1;
                       p->data[k][3]=0;
                       p->data[k][4]=0;
                   }
                   bai=0;
                   p->number+=bai;
               }
               else{
                   for(int k=p->number;k<10;k++)
                   {
                       p->data[k][0]=1;
                       qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+k*100+i);
                       p->data[k][1]=qrand()%300+200;
                       p->data[k][2]=1;
                       p->data[k][3]=0;
                       p->data[k][4]=0;
                   }
                   p->number=10;
                   bai-=(10-p->number);
               }
           }
          p=p->N;
        }
        p=head;
        for(int i=0;i<100;i++)
        {
            if(p->type==0&&p->number<10&&hua)
            {
                if(hua<=10-p->number)    //该猪圈能把剩下花猪装完
                {
                    for(int k=p->number;k<p->number+hua;k++)
                    {
                        p->data[k][0]=1;
                        qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+k*100+i);
                        p->data[k][1]=qrand()%300+200;
                        p->data[k][2]=1;
                        p->data[k][3]=0;
                        p->data[k][4]=0;
                    }
                    hua=0;
                    p->number+=hua;
                }
                else{
                    for(int k=p->number;k<10;k++)
                    {
                        p->data[k][0]=1;
                        qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+k*100+i);
                        p->data[k][1]=qrand()%300+200;
                        p->data[k][2]=1;
                        p->data[k][3]=0;
                        p->data[k][4]=0;
                    }
                    p->number=10;
                    hua-=(10-p->number);
                }
            }
            p=p->N;
        }
    }
}
void store::viewmoney()
{

     ui->label_21->setText("剩余金钱： "+QString::number(money)+"元");
}
