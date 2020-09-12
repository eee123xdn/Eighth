#ifndef PIGGAME_H
#define PIGGAME_H
#include<QSound>
#include <QMainWindow>
#include<page1.h>
#include<QTimer>
namespace Ui {
class PigGame;
}
class Node
{
public:
    Node()
    {
     ;
    }
    int number,data[15][5],kind[3][6];
    //1 = hua 2 = write 3 =blake;
    int type;
    bool flag;
    Node *F = NULL,*N = NULL;
};
extern Node *p,*head,*tail;
extern int sum,day,money,sum_money,cnt,healthtime,bgm,bgpic;
extern const QString bgmstr;
extern int buy_bai,buy_hua,buy_hei;
extern bool _60,_120,_180;
extern double speed;
extern QTimer* my_timer;//=new QTimer();//设置一个Qtimer
extern QTimer* my_timer1;//=new QTimer();//设置一个Qtimer
extern QTimer* my_timer2;//=new QTimer();//设置一个Qtimer
extern QTimer* my_timer4;//=new QTimer();//设置一个Qtimer
class PigGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit PigGame(QWidget *parent = nullptr);
    ~PigGame();
    int illsum();
    QSound *bells1,*bells2,*bells3;
public slots:
    void change_BGM_and_BGPIC();
    void goout();
    void new_game();
    void illmode();
    void healthemode();
    void loadgame();
    bool check();
    void pig_grow();
    static bool illcheck();
private slots:
    void on_btn_config_clicked();

    void on_btn_store_clicked();

    void on_btn_honor_clicked();

    void on_btn_nextpage_clicked();

    void on_btn_frontpage_clicked();

    void on_btn_geli_clicked();

private:

    Ui::PigGame *ui;
};

#endif // PIGGAME_H
