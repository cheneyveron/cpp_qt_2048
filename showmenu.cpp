#include "showmenu.h"
#include <menu.h>
#include <QSound>
ShowMenu::ShowMenu(QWidget *parent) : QWidget(parent)
{
    // 构造一个游戏部件对象
    mainMenu = new Menu(this);

    // 构造一个字体对象
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setBold(false);
    font.setPixelSize(15);

    // 构造restart按钮对象
    classicBtn = new QPushButton("经典模式", this);
    classicBtn->setGeometry(100, 120, 200, 50);
    classicBtn->setFont(font);
  //  classicBtn->setStyleSheet(QString("QPushButton {color: #fff449;background: #002d71;border-radius: %0.2px;} QPushButton:pressed{color: #fff449;background: #002d71;border-radius: %0.2px;}").arg(3).arg(15));
    connect(classicBtn, SIGNAL(clicked()), mainMenu, SLOT(classic()));
}
ShowMenu::~ShowMenu()
{
    // 释放相关对象
    delete classicBtn;
    delete mainMenu;
}

void ShowMenu::resizeEvent(QResizeEvent *)
{
    // 构造一个字体对象
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setBold(false);
    font.setPixelSize(15);
    classicBtn->setFont(font);
 //   classicBtn->setStyleSheet(QString("QPushButton {color: #fff449;background: #002d71;border-radius: %0.2px;} QPushButton:pressed{color: #fff449;background: #002d71;border-radius: %0.2px;}").arg(3).arg(15));
    // 重置子部件大小和位置
    mainMenu->setGeometry(2, 246, 400, 400);
    classicBtn->setGeometry(39, 87, 78, 25);
}
