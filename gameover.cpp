#include "gameover.h"
#include "ui_gameover.h"
#include <QMovie>
gameover::gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
    setWindowTitle(tr("GAMEOVER"));
    //取消对话框
    //this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    //背景色
    this->setStyleSheet("background-color: rgb(55, 135, 215);");
    //GIF动画播放
    QMovie *movie = new QMovie("fail.gif");
    ui->label->setMovie(movie);
    movie->start();
}

gameover::~gameover()
{
    delete ui;
}

void gameover::on_pushButton_clicked()
{
    close();
}
