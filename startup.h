#ifndef STARTUP_H
#define STARTUP_H

#include <QDialog>

namespace Ui {
class Startup;
}

class Startup : public QDialog
{
    Q_OBJECT

public:
    explicit Startup(QWidget *parent = 0);
    ~Startup();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Startup *ui;
};

#endif // STARTUP_H
