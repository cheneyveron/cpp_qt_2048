#include "widget.h"
#include "gameover.h"
#include <QWindow>
Widget::Widget(QWidget *parent,int mode)
    : QWidget(parent)
{
    // 初始化最高分为0
    highScore = 0;
    // 读取存储最高分的文件
    QFile file("score.j");
    if (file.open(QIODevice::ReadOnly))
    {
        file.read((char *)&highScore, sizeof(highScore));
        file.close();
    }

    // 构造一个游戏部件对象
    gameWidget = new GameWidget(this,mode);
    connect(gameWidget, SIGNAL(ScoreInc(int)), this, SLOT(onScoreInc(int)));
    connect(gameWidget, SIGNAL(GameOver()), this, SLOT(onGameOver()));
    connect(gameWidget, SIGNAL(win()), this, SLOT(onWin()));

    // 构造一个字体对象
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setBold(false);
    font.setPixelSize(15);

    // 构造一个标签对象
    highScoreLbl = new QLabel(QString("最高分: %1").arg(highScore),this);
    highScoreLbl->setGeometry(209, 20, 180, 70);
    highScoreLbl->setFont(font);
    highScoreLbl->setAlignment(Qt::AlignCenter);
    highScoreLbl->setStyleSheet(QString(LBLSTYLESHEET).arg(5).arg(20));

    // 构造一个标签对象
    scoreLbl = new QLabel("分数: 0", this);
    scoreLbl->setGeometry(15, 20, 180, 70);
    scoreLbl->setFont(font);
    scoreLbl->setAlignment(Qt::AlignCenter);
    scoreLbl->setStyleSheet(QString(LBLSTYLESHEET).arg(5).arg(20));
    // 构造restart按钮对象
    restartBtn = new QPushButton("重玩", this);
    restartBtn->setGeometry(100, 120, 200, 50);
    restartBtn->setFont(font);
    restartBtn->setStyleSheet(QString(BTNSTYLESHEET).arg(3).arg(15));
    connect(restartBtn, SIGNAL(clicked()), gameWidget, SLOT(restart()));
    // 构造back按钮对象
    backBtn = new QPushButton("返回", this);
    backBtn->setGeometry(100, 120, 200, 50);
    backBtn->setFont(font);
    backBtn->setStyleSheet(QString(BTNSTYLESHEET).arg(3).arg(15));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(back()));

    // 锁定窗口大小
    setMaximumSize(404,650);
    setMinimumSize(404,650);
}

Widget::~Widget()
{
    // 释放相关对象
    delete restartBtn;
    delete scoreLbl;
    delete highScoreLbl;
    delete gameWidget;
    delete backBtn;
}
void Widget::back()
{

    Menu *mainmenu = new Menu;
    mainmenu->setAutoFillBackground(true);
    QPalette palettea;
    QPixmap pixmapa(":/image/menu.png");
    palettea.setBrush(QPalette::Window, QBrush(pixmapa));
    mainmenu->setPalette(palettea);
    mainmenu->show();
    this->close();
}

void Widget::onScoreInc(int score)
{
    // 更新分数显示
    scoreLbl->setText(QString("得分: %1").arg(score));
    // 如果当前分数高于最高分
    if (score > highScore)
    {
        // 更新最高分
        highScore = score;
        highScoreLbl->setText(QString("最高分: %1").arg(highScore));

        // 将新的最高分存入文件
        QFile file("score.j");
        file.open(QIODevice::WriteOnly);
        file.write((char *)&highScore, sizeof(highScore));
        file.close();
    }
}

void Widget::onGameOver()
{
    QSound::play("gameover.wav");
    //QMessageBox::information(this, "GameOver", "You lost !");
    gameover *g = new gameover(this);
    g->show();
}

void Widget::onWin()
{
    QSound::play("win.wav");
    QMessageBox::information(this, "Congratulation", "You win !");
}

void Widget::resizeEvent(QResizeEvent *)
{
    // 计算宽度和高度的缩放比例
    ratioW = width() / 404.0;
    ratioH = height() / 650.0;
    // 构造一个字体对象
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setBold(false);
    font.setPixelSize(15 * ratioH);
    restartBtn->setFont(font);
    backBtn->setFont(font);
    highScoreLbl->setFont(font);
    scoreLbl->setFont(font);
    restartBtn->setStyleSheet(QString(BTNSTYLESHEET).arg(3 * ratioW).arg(15 * ratioW));
    backBtn->setStyleSheet(QString(BTNSTYLESHEET).arg(3 * ratioW).arg(15 * ratioW));
    highScoreLbl->setStyleSheet(QString(LBLSTYLESHEET).arg(5 * ratioW).arg(20 * ratioW));
    scoreLbl->setStyleSheet(QString(LBLSTYLESHEET).arg(5 * ratioW).arg(20 * ratioW));
    // 重置子部件大小和位置
    gameWidget->setGeometry(2 * ratioW, 246 * ratioH, 400 * ratioW, 400 * ratioH);
    restartBtn->setGeometry(39 * ratioW, 87 * ratioH, 78 * ratioW, 25 * ratioH);
    backBtn->setGeometry(39 * ratioW, 40 * ratioH, 78 * ratioW, 25 * ratioH);
    highScoreLbl->setGeometry(191 * ratioW, 126 * ratioH, 147 * ratioW, 25 * ratioH);
    scoreLbl->setGeometry(191 * ratioW, 168 * ratioW, 147 * ratioW, 25 * ratioH);
}
