#include "startup.h"
#include "ui_startup.h"
#include "menu.h"
Startup::Startup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startup)
{
    ui->setupUi(this);
}

Startup::~Startup()
{
    delete ui;
}

void Startup::on_pushButton_clicked()
{
    Menu *mainmenu = new Menu;
    mainmenu->setAutoFillBackground(true);
    QPalette palettea;
    QPixmap pixmapa(":/image/menu.png");
    palettea.setBrush(QPalette::Window, QBrush(pixmapa));
    mainmenu->setPalette(palettea);
    close();
    mainmenu->show();
}
