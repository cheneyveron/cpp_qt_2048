#include "about.h"
#include "ui_about.h"
#include <menu.h>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_pushButton_clicked()
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
