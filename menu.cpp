#include "menu.h"
#include "ui_menu.h"
#include <QPushButton>
#include <widget.h>
#include <help.h>
#include <about.h>
Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    // 构造大字体对象
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setBold(false);
    font.setPixelSize(25);

    // 构造小字体对象
    QFont font2;
    font2.setFamily("Microsoft YaHei");
    font2.setBold(false);
    font2.setPixelSize(15);

    //经典模式
    classicBtn = new QPushButton("  ", this);
    classicBtn->setGeometry(104, 230, 193, 77);
    classicBtn->setFont(font);
    classicBtn->setStyleSheet(QString(BTNSTYLECLASSIC).arg(3).arg(15));
    connect(classicBtn, SIGNAL(clicked()), this, SLOT(classic()));
    //5x5模式
    x5Btn = new QPushButton("  ", this);
    x5Btn->setGeometry(104, 328, 193, 77);
    x5Btn->setFont(font);
    x5Btn->setStyleSheet(QString(BTNSTYLEX5).arg(3).arg(15));
    connect(x5Btn, SIGNAL(clicked()), this, SLOT(x5()));
    //反向模式
    oppoBtn = new QPushButton("  ", this);
    oppoBtn->setGeometry(104, 428, 193, 77);
    oppoBtn->setFont(font);
    oppoBtn->setStyleSheet(QString(BTNSTYLEOPPO).arg(3).arg(15));
    connect(oppoBtn, SIGNAL(clicked()), this, SLOT(oppo()));
    //帮助
    helpBtn = new QPushButton("  ", this);
    helpBtn->setGeometry(103, 525, 193, 77);
    helpBtn->setFont(font);
    helpBtn->setStyleSheet(QString(BTNSTYLEHELP).arg(3).arg(15));
    connect(helpBtn, SIGNAL(clicked()), this, SLOT(helpx()));
    //关于
    aboutBtn = new QPushButton("关于", this);
    aboutBtn->setGeometry(9, 612, 69, 31);
    aboutBtn->setFont(font2);
    aboutBtn->setStyleSheet(QString(BTNSTYLESHEET).arg(3).arg(15));
    connect(aboutBtn, SIGNAL(clicked()), this, SLOT(about()));
    //退出
    exitBtn = new QPushButton("退出", this);
    exitBtn->setGeometry(329, 612, 69, 31);
    exitBtn->setFont(font2);
    exitBtn->setStyleSheet(QString(BTNSTYLESHEET).arg(3).arg(15));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitx()));
}

Menu::~Menu()
{
    delete ui;
}
void Menu::classic()
{

    Widget *w=new Widget(0,0);
    w->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/image/start.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    w->setPalette(palette);close();
    w->show();
}
void Menu::x5()
{
   // close();
    Widget *w=new Widget(0,1);
    w->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/image/start.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    w->setPalette(palette);close();
    w->show();
}
void Menu::oppo()
{
    Widget *w=new Widget(0,2);
    w->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/image/start.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    w->setPalette(palette);
    close();
    w->show();
    // 初始化相关变量 同构造函数
}
void Menu::about()
{
    About *w=new About;
    close();
    w->show();
}
void Menu::helpx()
{
    help *w = new help;
    close();
    w->show();
}
void Menu::exitx()
{
    close();
}
