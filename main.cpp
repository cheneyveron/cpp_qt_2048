#include "widget.h"
#include <QApplication>
#include <menu.h>
#include "startup.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //背景音乐 单曲循环
    QSound bells("背景音乐.wav"); bells.setLoops(-1); bells.play();

    Startup *w=new Startup;
    w->show();

    return a.exec();
}
