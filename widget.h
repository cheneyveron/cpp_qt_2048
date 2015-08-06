#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QSound>
#include "GameWidget.h"
#include <QApplication>
#include <menu.h>

#define LBLSTYLESHEET "QLabel {color: #fff449;background: #002d71;border-radius: %0.2px;}"
#define BTNSTYLESHEET "QPushButton {color: #fff449;background: #002d71;border-radius: %0.2px;} QPushButton:pressed{color: #fff449;background: #002d71;border-radius: %0.2px;}"

// 主窗口部件类
class Widget : public QWidget
{
    Q_OBJECT

public:
    // 构造&析构函数
    Widget(QWidget *parent = 0,int Mode = 0);
    ~Widget();

private:
    // “restart”按钮
    QPushButton *restartBtn;
    // “restart”按钮
    QPushButton *backBtn;
    // “score”标签
    QLabel *scoreLbl;
    // “HightScore”标签
    QLabel *highScoreLbl;
    // 游戏部件
    GameWidget *gameWidget;
    // 宽度和高度的缩放比例 用来使窗口部件随主窗口的尺寸改变而改变位置与尺寸
    qreal ratioW, ratioH;
    // 记录最高分
    int highScore;

protected:
    // 窗口尺寸改变触发的事件
    void resizeEvent(QResizeEvent *);

public slots:
    // 处理分数增加信号的槽函数
    void onScoreInc(int);
    // 处理游戏结束信号的槽函数
    void onGameOver();
    // 处理游戏获胜信号的槽函数
    void onWin();
    // 返回主界面的槽函数
    void back();
};

#endif // WIDGET_H
