#include "help.h"
#include "ui_help.h"
#include "menu.h"
help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
}

help::~help()
{
    delete ui;
}

void help::on_backBtn_clicked()
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
