#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QPushButton>
#define BTNSTYLEHELP "QPushButton {border-image: url(:/image/helpx1.png);} QPushButton:pressed{border-image: url(:/image/helpx2.png);}"
#define BTNSTYLECLASSIC "QPushButton {border-image: url(:/image/classic1.png);} QPushButton:pressed{border-image: url(:/image/classic2.png);}"
#define BTNSTYLEX5 "QPushButton {border-image: url(:/image/x51.png);} QPushButton:pressed{border-image: url(:/image/x52.png);}"
#define BTNSTYLEOPPO "QPushButton {border-image: url(:/image/oppo1.png);} QPushButton:pressed{border-image: url(:/image/oppo2.png);}"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private:
    Ui::Menu *ui;
    // “classic”按钮
    QPushButton *classicBtn;
    // “5x5”按钮
    QPushButton *x5Btn;
    // “反向”按钮
    QPushButton *oppoBtn;
    // “关于”按钮
    QPushButton *aboutBtn;
    // “帮助”按钮
    QPushButton *helpBtn;
    // “退出”按钮
    QPushButton *exitBtn;
public slots:
    // Classic的槽函数
    void classic();
    // 5x5的槽函数
    void x5();
    // 反向的槽函数
    void oppo();
    // 关于的槽函数
    void about();
    // 帮助的槽函数
    void helpx();
    // 退出的槽函数
    void exitx();
};

#endif // MENU_H
