#ifndef SHOWMENU_H
#define SHOWMENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QSound>
#include "menu.h"

//#define LBLSTYLESHEET "QLabel {color: #fff449;background: #002d71;border-radius: %0.2px;}"
//#define BTNSTYLESHEET "QPushButton {color: #fff449;background: #002d71;border-radius: %0.2px;} QPushButton:pressed{color: #fff449;background: #002d71;border-radius: %0.2px;}"

class ShowMenu : public QWidget
{

    Q_OBJECT

public:
    // 构造&析构函数
    ShowMenu(QWidget *parent = 0);
    ~ShowMenu();

private:
    // “经典模式”按钮
    QPushButton *classicBtn;
    // 游戏部件
    Menu *mainMenu;

protected:
    // 窗口尺寸改变触发的事件
    void resizeEvent(QResizeEvent *);

};

#endif // SHOWMENU_H
