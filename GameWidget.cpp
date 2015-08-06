#include "GameWidget.h"
#include <QKeyEvent>
//to=2048时为反向2048
int to;
//颜色
int getnumber(int n)
{
    if(to!=2048)
    switch (n) {
    case 2:
        return 0;
    case 4:
        return 1;
    case 8:
        return 2;
    case 16:
        return 3;
    case 32:
        return 4;
    case 64:
        return 5;
    case 128:
        return 6;
    case 256:
        return 7;
    case 512:
        return 8;
        break;
    case 1024:
        return 9;
    case 2048:
        return 10;
    default:
        return 0;
    }
    else
        switch (n) {
        case 2:
            return 10;
        case 4:
            return 9;
        case 8:
            return 8;
        case 16:
            return 7;
        case 32:
            return 6;
        case 64:
            return 5;
        case 128:
            return 4;
        case 256:
            return 3;
        case 512:
            return 2;
            break;
        case 1024:
            return 1;
        case 2048:
            return 0;
        default:
            return 0;
        }
}

//获取小格子的图片
QPixmap GameWidget::getmyimage(int n)
{

     QPixmap a1(":/1.png");
     QPixmap a2(":/2.png");
     QPixmap a3(":/3.png");
     QPixmap a4(":/4.png");
     QPixmap a5(":/5.png");
     QPixmap a6(":/6.png");
     QPixmap a7(":/7.png");
     QPixmap a8(":/8.png");
     QPixmap a9(":/9.png");
     QPixmap a10(":/10.png");
     QPixmap a11(":/11.png");
     switch (n) {
     case 2:
         return a1;
     case 4:
         return a2;
     case 8:
         return a3;
     case 16:
         return a4;
     case 32:
         return a5;
     case 64:
         return a6;
     case 128:
         return a7;
     case 256:
         return a8;
     case 512:
         return a9;
         break;
     case 1024:
         return a10;
     case 2048:
         return a11;
     default:
         return a1;
     }
}
//获取2048的小格子的图片
QPixmap GameWidget::getmyimage2(int n)
{
     QPixmap a1(":/image/a1.png");
     QPixmap a2(":/image/a2.png");
     QPixmap a3(":/image/a3.png");
     QPixmap a4(":/image/a4.png");
     QPixmap a5(":/image/a5.png");
     QPixmap a6(":/image/a6.png");
     QPixmap a7(":/image/a7.png");
     QPixmap a8(":/image/a8.png");
     QPixmap a9(":/image/a9.png");
     QPixmap a10(":/image/a10.png");
     QPixmap a11(":/image/a11.png");
     switch (n)
     {
     case 2:
         return a1;
     case 4:
         return a2;
     case 8:
         return a3;
     case 16:
         return a4;
     case 32:
         return a5;
     case 64:
         return a6;
     case 128:
         return a7;
     case 256:
         return a8;
     case 512:
         return a9;
         break;
     case 1024:
         return a10;
     case 2048:
         return a11;
     default:
         return a1;
     }
}

// 每个方向位置的增量
QPointF dPos[5];

GameWidget::GameWidget(QWidget *parent,int gmode) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    timer(this)
{
    if (gmode == 0)
    {
        Mult=4;
        to=2;
    }
    else if(gmode == 1)
    {
        Mult=5;
        to=2;
    }
    else if(gmode == 2)
    {
        Mult=4;
        to=2048;
    }
    // 连接手势移动信号和相应的槽函数
    connect(this, SIGNAL(GestureMove(GestureDirect)), SLOT(onGestureMove(GestureDirect)));
    // 连接时钟信号和画板更新的槽
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    // 初始化board数组
    for(int z=0;z<Mult;z++)
           for(int z2=0;z2<Mult;z2++)
               board[z][z2]=0;
    // 分数初始化为0
    score = 0;
    // 数码个数初始化为2
    digitCount = 2;
    // 没有在播放动画效果
    isAnimating = false;
    // 初始化两个方格
    init2Block();
}

void GameWidget::init2Block()
{
    setFocus();
    if(to!=2048)
    {
        board[rand() % Mult][rand() % Mult] = 2;
        int i = rand() % Mult, j = rand() % Mult;
        while (board[i][j] != 0)
            i = rand() % Mult, j = rand() % Mult;
        board[i][j] = 2;
    }
    else
    {
        board[rand() % 4][rand() % 4] = 1024;
        int i = rand() % 4, j = rand() % 4;
        while (board[i][j] != 0)
            i = rand() % 4, j = rand() % 4;
        board[i][j] = 2048;
    }
    update();
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    // 获取起点坐标
    startPos = e->pos();
}

void GameWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // 如果在播放动画效果则直接退出防止重复产生手势事件
    if (isAnimating)
        return;
    // 根据终点坐标和起点坐标计算XY坐标的增量
    float dX = (float)(e->pos().x() - startPos.x());
    float dY = (float)(e->pos().y() - startPos.y());
    // 确定手势方向
    if (abs(dX) > abs(dY))
    {
        if (dX < 0)
            emit GestureMove(LEFT);
        else
            emit GestureMove(RIGHT);
    }
    else
    {
        if (dY < 0)
            emit GestureMove(UP);
        else
            emit GestureMove(DOWN);
    }
}

void GameWidget::onGestureMove(GestureDirect direct)
{
    int i, j, k;
    Animation a;
    // 记录是否移动过方格以及是否有方格合并
    bool move = false, combine = false;
    // 记录某个格子是否参与过合并
    bool isCombined[Mult][Mult];
    for(int z=0;z<Mult;z++)
           for(int z2=0;z2<Mult;z2++)
               isCombined[z][z2]=0;
    if(to==2048)
    {    // 处理不同方向
        switch (direct)
        {
        // 向左
        case LEFT:
            QSound::play("1.wav");
            // 循环每一行
            for (i = 0; i < 4; i++)
            {
                /* 初始化j k为0
                 * 这里j表示要交换的数字列号
                 * k表示交换到的位置的列号
                 * */
                j = 0, k = 0;
                while (true)
                {
                    // 循环找到第一个不是0的数字对应的列号
                    while (j < 4 && board[i][j] == 0)
                        j++;
                    // 如果超过了3则说明搜索完毕 推出循环
                    if (j > 3)
                        break;
                    // 交换两个数字
                    qSwap(board[i][k], board[i][j]);
                    if (j != k)
                        move = true;
                    // 记录动画信息
                    a.type = MOVE;
                    a.startPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
                    a.endPos = QPointF(7 + (w + 5) * k, 7 + (h + 5) * i);
                    a.digit = a.digit2 = board[i][k];
                    a.direct = LEFT;
                    //如果交换后的数字与其前一列的数字相同
                    if (k > 0 && board[i][k] == board[i][k - 1] && !isCombined[i][k - 1])
                    {
                        // 前一列的数字/2
                          board[i][k - 1]=board[i][k - 1]/2;
                        // i k-1 方格参与过合并
                        isCombined[i][k - 1] = true;
                        // 这一列的数字置为0
                        board[i][k] = 0;
                        // 有方格合并
                        combine = true;
                        // 记录动画信息
                        a.digit2 = board[i][k - 1];
                        a.endPos = QPointF(7 + (w + 5) * (k - 1), 7 + (h + 5) * i);
                        // 增加分数
                        score += board[i][k - 1];
                        // 发射增加分数的信号
                        emit ScoreInc(score);
                        // 数码个数-1
                        digitCount--;
                    }
                    else
                        k++;
                    j++;
                    // 添加到动画链表
                    animationList.append(a);
                }
            }
            break;
            // 其余三个方向与左向类似
        case RIGHT:
            QSound::play("1.wav");
            for (i = 0; i < 4; i++)
            {
                j = 3, k = 3;
                while (true)
                {
                    while (j > -1 && board[i][j] == 0)
                        j--;
                    if (j < 0)
                        break;
                    qSwap(board[i][k], board[i][j]);
                    if (j != k)
                        move = true;
                    a.type = MOVE;
                    a.startPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
                    a.endPos = QPointF(7 + (w + 5) * k, 7 + (h + 5) * i);
                    a.digit = a.digit2 = board[i][k];
                    a.direct = RIGHT;
                    if (k < 3 && board[i][k] == board[i][k + 1] && !isCombined[i][k + 1])
                    {
                        board[i][k + 1]=board[i][k + 1]/2;
                        isCombined[i][k + 1] = true;
                        board[i][k] = 0;
                        combine = true;
                        a.digit2 = board[i][k + 1];
                        a.endPos = QPointF(7 + (w + 5) * (k + 1), 7 + (h + 5) * i);
                        score += board[i][k + 1];
                        emit ScoreInc(score);
                        digitCount--;
                    }
                    else
                        k--;
                    j--;
                    animationList.append(a);
                }
            }
            break;
        case UP:
            QSound::play("1.wav");
            for (i = 0; i < 4; i++)
            {
                j = 0, k = 0;
                while (true)
                {
                    while (j < 4 && board[j][i] == 0)
                        j++;
                    if (j > 3)
                        break;
                    qSwap(board[k][i], board[j][i]);
                    if (j != k)
                        move = true;
                    a.type = MOVE;
                    a.startPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * j);
                    a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * k);
                    a.digit = a.digit2 = board[k][i];
                    a.direct = UP;
                    if (k > 0 && board[k][i] == board[k - 1][i] && !isCombined[k - 1][i])
                    {
                        board[k - 1][i]=board[k - 1][i]/2;
                        isCombined[k - 1][i] = true;
                        board[k][i] = 0;
                        combine = true;
                        a.digit2 = board[k - 1][i];
                        a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * (k - 1));
                        score += board[k - 1][i];
                        emit ScoreInc(score);
                        digitCount--;
                    }
                    else
                        k++;
                    j++;
                    animationList.append(a);
                }
            }
            break;
        case DOWN:
            QSound::play("1.wav");
            for (i = 0; i < 4; i++)
            {
                j = 3, k = 3;
                while (true)
                {
                    while (j > -1 && board[j][i] == 0)
                        j--;
                    if (j < 0)
                        break;
                    qSwap(board[k][i], board[j][i]);
                    if (j != k)
                        move = true;
                    a.type = MOVE;
                    a.startPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * j);
                    a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * k);
                    a.digit = a.digit2 = board[k][i];
                    a.direct = DOWN;
                    if (k < (Mult-1) && board[k][i] == board[k + 1][i] && !isCombined[k + 1][i])
                    {
                        board[k + 1][i] =board[k + 1][i]/2;
                        isCombined[k + 1][i] = true;
                        board[k][i] = 0;
                        combine = true;
                        a.digit2 = board[k + 1][i];
                        a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * (k + 1));
                        score += board[k + 1][i];
                        emit ScoreInc(score);
                        digitCount--;
                    }
                    else
                        k--;
                    j--;
                    animationList.append(a);
                }
            }
            break;
        }

        // 如果数字木有填满
        if ((move || combine) && digitCount != Mult*Mult)
        {
            // 随机产生行号和列号
            i = rand() % 4, j = rand() % 4;
            //0000 循环直到行和列对应的元素为0
            while (board[i][j] != 0)
                i = rand() % 4, j = rand() % 4;
            // 填入1024 2048
            board[i][j] = (rand() % 2 + 1) * 1024;
            // 记录动画信息
            a.type = APPEARANCE;
            a.startPos = a.endPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
            a.startPos += QPointF(w / 2, h / 2);
            a.digit = board[i][j];
            animationList.append(a);
            // 数码个数加一
            digitCount++;
        }
        // 开始绘制动画效果
        isAnimating = true;
        // 启动计时器
        timer.start(10);
    }
    //如果不是2048模式
    else
    {
        // 处理不同方向
        switch (direct)
        {
        // 向左
        case LEFT:
            QSound::play("1.wav");
            // 循环每一行
            for (i = 0; i < Mult; i++)
            {
                /* 初始化j k为0
                 * 这里j表示要交换的数字列号
                 * k表示交换到的位置的列号
                 * */
                j = 0, k = 0;
                while (true)
                {
                    // 循环找到第一个不是0的数字对应的列号
                    while (j < Mult && board[i][j] == 0)
                        j++;
                    // 如果超过了3则说明搜索完毕 推出循环
                    if (j > (Mult-1))
                        break;
                    // 交换两个数字
                    qSwap(board[i][k], board[i][j]);
                    if (j != k)
                        move = true;
                    // 记录动画信息
                    a.type = MOVE;
                    a.startPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
                    a.endPos = QPointF(7 + (w + 5) * k, 7 + (h + 5) * i);
                    a.digit = a.digit2 = board[i][k];
                    a.direct = LEFT;
                    //如果交换后的数字与其前一列的数字相同
                    if (k > 0 && board[i][k] == board[i][k - 1] && !isCombined[i][k - 1])
                    {
                        board[i][k - 1]=board[i][k - 1]*2;
                        // i k-1 方格参与过合并
                        isCombined[i][k - 1] = true;
                        // 这一列的数字置为0
                        board[i][k] = 0;
                        // 有方格合并
                        combine = true;
                        // 记录动画信息
                        a.digit2 = board[i][k - 1];
                        a.endPos = QPointF(7 + (w + 5) * (k - 1), 7 + (h + 5) * i);
                        // 增加分数
                        score += board[i][k - 1];
                        // 发射增加分数的信号
                        emit ScoreInc(score);
                        // 数码个数-1
                        digitCount--;
                    }
                    else
                        k++;
                    j++;
                    // 添加到动画链表
                    animationList.append(a);
                }
            }
            break;
            // 其余三个方向与左向类似
        case RIGHT:
            QSound::play("1.wav");
            for (i = 0; i < Mult; i++)
            {
                j = Mult-1, k = Mult-1;
                while (true)
                {
                    while (j > -1 && board[i][j] == 0)
                        j--;
                    if (j < 0)
                        break;
                    qSwap(board[i][k], board[i][j]);
                    if (j != k)
                        move = true;
                    a.type = MOVE;
                    a.startPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
                    a.endPos = QPointF(7 + (w + 5) * k, 7 + (h + 5) * i);
                    a.digit = a.digit2 = board[i][k];
                    a.direct = RIGHT;
                    if (k < (Mult-1) && board[i][k] == board[i][k + 1] && !isCombined[i][k + 1])
                    {
                        board[i][k + 1]=board[i][k + 1]*2;
                        isCombined[i][k + 1] = true;
                        board[i][k] = 0;
                        combine = true;
                        a.digit2 = board[i][k + 1];
                        a.endPos = QPointF(7 + (w + 5) * (k + 1), 7 + (h + 5) * i);
                        score += board[i][k + 1];
                        emit ScoreInc(score);
                        digitCount--;
                    }
                    else
                        k--;
                    j--;
                    animationList.append(a);
                }
            }
            break;
        case UP:
            QSound::play("1.wav");
            for (i = 0; i < Mult; i++)
            {
                j = 0, k = 0;
                while (true)
                {
                    while (j < Mult && board[j][i] == 0)
                        j++;
                    if (j > (Mult-1))
                        break;
                    qSwap(board[k][i], board[j][i]);
                    if (j != k)
                        move = true;
                    a.type = MOVE;
                    a.startPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * j);
                    a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * k);
                    a.digit = a.digit2 = board[k][i];
                    a.direct = UP;
                    if (k > 0 && board[k][i] == board[k - 1][i] && !isCombined[k - 1][i])
                    {
                        board[k - 1][i]=board[k - 1][i]*2;
                        isCombined[k - 1][i] = true;
                        board[k][i] = 0;
                        combine = true;
                        a.digit2 = board[k - 1][i];
                        a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * (k - 1));
                        score += board[k - 1][i];
                        emit ScoreInc(score);
                        digitCount--;
                    }
                    else
                        k++;
                    j++;
                    animationList.append(a);
                }
            }
            break;
        case DOWN:
            QSound::play("1.wav");
            for (i = 0; i < Mult; i++)
            {
                j = (Mult-1), k = (Mult-1);
                while (true)
                {
                    while (j > -1 && board[j][i] == 0)
                        j--;
                    if (j < 0)
                        break;
                    qSwap(board[k][i], board[j][i]);
                    if (j != k)
                        move = true;
                    a.type = MOVE;
                    a.startPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * j);
                    a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * k);
                    a.digit = a.digit2 = board[k][i];
                    a.direct = DOWN;
                    if (k < (Mult-1) && board[k][i] == board[k + 1][i] && !isCombined[k + 1][i])
                    {
                        board[k + 1][i] =board[k + 1][i]*2;
                        isCombined[k + 1][i] = true;
                        board[k][i] = 0;
                        combine = true;
                        a.digit2 = board[k + 1][i];
                        a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * (k + 1));
                        score += board[k + 1][i];
                        emit ScoreInc(score);
                        digitCount--;
                    }
                    else
                        k--;
                    j--;
                    animationList.append(a);
                }
            }
            break;
        }

        // 如果数字木有填满
        if ((move || combine) && digitCount != Mult*Mult)
        {
            // 随机产生行号和列号
            i = rand() % Mult, j = rand() % Mult;
            // 循环直到行和列对应的元素为0
            while (board[i][j] != 0)
                i = rand() % Mult, j = rand() % Mult;
            // 填入2 4
            board[i][j] = (rand() % 2 + 1) * 2;
            // 记录动画信息
            a.type = APPEARANCE;
            a.startPos = a.endPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
            a.startPos += QPointF(w / 2, h / 2);
            a.digit = board[i][j];
            animationList.append(a);
            // 数码个数加一
            digitCount++;
        }
        // 开始绘制动画效果
        isAnimating = true;
        // 启动计时器
        timer.start(10);
    }
}

void GameWidget::keyPressEvent(QKeyEvent *b)
{

    int i, j, k;
    Animation a;
    // 记录是否移动过方格以及是否有方格合并
    bool move = false, combine = false;
    // 记录某个格子是否参与过合并
    bool isCombined[Mult][Mult];
    for(int z=0;z<Mult;z++)
           for(int z2=0;z2<Mult;z2++)
               isCombined[z][z2]=0;


    switch (b->key())
    {
    case Qt::Key_Up:
        QSound::play("1.wav");
        for (i = 0; i < Mult; i++)
        {
            j = 0, k = 0;
            while (true)
            {
                while (j < Mult && board[j][i] == 0)
                    j++;
                if (j > (Mult-1))
                    break;
                qSwap(board[k][i], board[j][i]);
                if (j != k)
                    move = true;
                a.type = MOVE;
                a.startPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * j);
                a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * k);
                a.digit = a.digit2 = board[k][i];
                a.direct = UP;
                if (k > 0 && board[k][i] == board[k - 1][i] && !isCombined[k - 1][i])
                {
                    if(to!=2048)
                        board[k - 1][i] =board[k - 1][i]*2;
                    else
                        board[k - 1][i] =board[k - 1][i]/2;
                    isCombined[k - 1][i] = true;
                    board[k][i] = 0;
                    combine = true;
                    a.digit2 = board[k - 1][i];
                    a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * (k - 1));
                    score += board[k - 1][i];
                    emit ScoreInc(score);
                    digitCount--;
                }
                else
                    k++;
                j++;
                animationList.append(a);
            }
        }
        break;
    case Qt::Key_Down:
        QSound::play("1.wav");
        for (i = 0; i < Mult; i++)
        {
            j = Mult-1, k = Mult-1;
            while (true)
            {
                while (j > -1 && board[j][i] == 0)
                    j--;
                if (j < 0)
                    break;
                qSwap(board[k][i], board[j][i]);
                if (j != k)
                    move = true;
                a.type = MOVE;
                a.startPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * j);
                a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * k);
                a.digit = a.digit2 = board[k][i];
                a.direct = DOWN;
                if (k < (Mult-1) && board[k][i] == board[k + 1][i] && !isCombined[k + 1][i])
                {
                    if(to!=2048)
                         board[k + 1][i]=board[k + 1][i]*2;
                    else
                         board[k + 1][i]=board[k + 1][i]/2;
                    isCombined[k + 1][i] = true;
                    board[k][i] = 0;
                    combine = true;
                    a.digit2 = board[k + 1][i];
                    a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * (k + 1));
                    score += board[k + 1][i];
                    emit ScoreInc(score);
                    digitCount--;
                }
                else
                    k--;
                j--;
                animationList.append(a);
            }
        }
        break;
    case Qt::Key_Left:
        //音效
        QSound::play("1.wav");
        // 循环每一行
        for (i = 0; i < Mult; i++)
        {
            /* 初始化j k为0
             * 这里j表示要交换的数字列号
             * k表示交换到的位置的列号
             * */
            j = 0, k = 0;
            while (true)
            {
                // 循环找到第一个不是0的数字对应的列号
                while (j < Mult && board[i][j] == 0)
                    j++;
                // 如果超过了3则说明搜索完毕 推出循环
                if (j > (Mult-1))
                    break;
                // 交换两个数字
                qSwap(board[i][k], board[i][j]);
                if (j != k)
                    move = true;
                // 记录动画信息
                a.type = MOVE;
                a.startPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
                a.endPos = QPointF(7 + (w + 5) * k, 7 + (h + 5) * i);
                a.digit = a.digit2 = board[i][k];
                a.direct = LEFT;
                if (k > 0 && board[i][k] == board[i][k - 1] && !isCombined[i][k - 1])
                {
                    if(to!=2048)
                        board[i][k - 1]=board[i][k - 1]*2;
                    else
                        board[i][k - 1]+=board[i][k - 1]/2;
                    isCombined[i][k - 1] = true;
                    // 这一列的数字置为0
                    board[i][k] = 0;
                    // 有方格合并
                    combine = true;
                    // 记录动画信息
                    a.digit2 = board[i][k - 1];
                    a.endPos = QPointF(7 + (w + 5) * (k - 1), 7 + (h + 5) * i);

                    // 增加分数
                    score += board[i][k - 1];
                    // 发射增加分数的信号
                    emit ScoreInc(score);
                    // 数码个数-1
                    digitCount--;
                }
                else
                    k++;
                j++;
                // 添加到动画链表
                animationList.append(a);
            }
        }
        break;
    case Qt::Key_Right:
        QSound::play("1.wav");
        for (i = 0; i < Mult; i++)
        {
            j = Mult-1, k = Mult-1;
            while (true)
            {
                while (j > -1 && board[i][j] == 0)
                    j--;
                if (j < 0)
                    break;
                qSwap(board[i][k], board[i][j]);
                if (j != k)
                    move = true;
                a.type = MOVE;
                a.startPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
                a.endPos = QPointF(7 + (w + 5) * k, 7 + (h + 5) * i);
                a.digit = a.digit2 = board[i][k];
                a.direct = RIGHT;
                if (k < (Mult-1) && board[i][k] == board[i][k + 1] && !isCombined[i][k + 1])
                {
                    if(to!=2048)
                         board[i][k + 1] =board[i][k + 1]*2;
                    else
                         board[i][k + 1] =board[i][k + 1]/2;
                    isCombined[i][k + 1] = true;
                    board[i][k] = 0;
                    combine = true;
                    a.digit2 = board[i][k + 1];
                    a.endPos = QPointF(7 + (w + 5) * (k + 1), 7 + (h + 5) * i);
                    score += board[i][k + 1];
                    emit ScoreInc(score);
                    digitCount--;
                }
                else
                    k--;
                j--;
                animationList.append(a);
            }
        }
        break;
    default:
        break;
    }
    // 如果数字没有填满
    if ((move || combine) && digitCount != 16)
    {
        // 随机产生行号和列号
        i = rand() % Mult, j = rand() % Mult;
        // 循环直到行和列对应的元素为0
        while (board[i][j] != 0)
            i = rand() % Mult, j = rand() % Mult;
        if(to!=2048)
            // 填入数字 2/4
            board[i][j] = (rand() % 2 + 1)*2;
        else
            // 填入数字1024/2048
            board[i][j] = (rand() % 2 + 1)*1024;
        // 记录动画信息
        a.type = APPEARANCE;
        a.startPos = a.endPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
        a.startPos += QPointF(w / 2, h / 2);
        a.digit= board[i][j];
        animationList.append(a);
        // 数码个数加一
        digitCount++;
    }

    // 开始绘制动画效果
    isAnimating = true;

    // 启动计时器
    timer.start(10);
}

//鼠标滑动以后重新绘制画布
bool GameWidget::drawAnimation(QPainter &painter)
{
    // 动画列表的迭代器
    QList<Animation>::iterator it;

    // 标识所有方格动画是否都播放完毕
    bool ok = true;

    if(to==2048)
    {
        // 字体
        QFont font;
        font.setFamily("Consolas");
        font.setBold(true);
        font.setPixelSize(40);
        painter.setFont(font);
        // 构造一个画刷 颜色为背景蓝色
            QBrush brush(QColor::fromRgb(1, 72, 179));
            // 使painter应用这个画刷
            painter.setBrush(brush);

            // 设置画笔为空笔 目的是使绘制的图形没有描边
            painter.setPen(Qt::NoPen);
                // 绘制纯色背景矩形
            painter.drawRoundedRect(QRectF(0, 0, width(), height()), 0, 0);

            /* // 设置画刷颜色为 RGB分量为171 165 141的颜色
            brush.setColor(QColor::fromRgb(171, 165, 141));
            // 应用这个画刷
            painter.setBrush(brush);

           循环绘制游戏面板
            for (int i = 0; i < Mult; i++)
                for (int j = 0; j < Mult; j++)
                    // 绘制所有的背景小方格
                    painter.drawRoundedRect(QRectF(7 + (w + 5) * j, 7 + (h + 5) * i, w, h), rX, rY);    */
    }
    else
    {
        if(Mult==4)
        {
            //填充4x4背景大矩形
            QPixmap image(":/image/start2.png");
            painter.drawPixmap(0, 0,400,400,image);
        }
        else
        {
            //填充5x5背景大矩形
            QPixmap image(":/image/start3.png");
            painter.drawPixmap(0, 0,400,400,image);
        }
    }

    // 循环播放每个方格动画
    for (it = animationList.begin(); it != animationList.end(); it++)
        if (!playAnimation(*it, painter))
            ok = false;
    return ok;
}

//鼠标移动以后绘制方块动画
bool GameWidget::playAnimation(Animation& a, QPainter& painter)
{
    bool rtn = false;

    QBrush brush(Qt::SolidPattern);
    //判断是否是2048模式
    if(to==2048)
    {
        // 移动方格位置
        if (a.type == MOVE)
        {
            switch (a.direct)
            {
            case LEFT:
                if (a.startPos.x() > a.endPos.x())
                    a.startPos += dPos[LEFT];
                else
                    a.startPos = a.endPos, rtn = true;
                break;
            case RIGHT:
                if (a.startPos.x() < a.endPos.x())
                    a.startPos += dPos[RIGHT];
                else
                    a.startPos = a.endPos, rtn = true;
                break;
            case UP:
                if (a.startPos.y() > a.endPos.y())
                    a.startPos += dPos[UP];
                else
                    a.startPos = a.endPos, rtn = true;
                break;
            case DOWN:
                if (a.startPos.y() < a.endPos.y())
                    a.startPos += dPos[DOWN];
                else
                    a.startPos = a.endPos, rtn = true;
            }
            // 如果方格移动到终点
            if (!rtn)
            {
                //绘制方格背景图片
                painter.drawPixmap(a.startPos.x(), a.startPos.y(), w, h,getmyimage2(a.digit));
            }
            else
            {
                //绘制方格背景图片
                painter.drawPixmap(a.startPos.x(), a.startPos.y(), w, h,getmyimage2(a.digit2));
            }
            painter.setPen(Qt::NoPen);
        }
        //如果不动，播放出现的效果
        else
        {
            // 方格出现的动画效果
            if (a.startPos.x() > a.endPos.x())
                a.startPos += QPointF(-25, -25);
            else
                a.startPos = a.endPos, rtn = true;
                //绘制方格背景图片
                QPixmap image(":/image/b1.png");
                painter.drawPixmap(a.startPos.x(), a.startPos.y(),w - 2 * (a.startPos.x() - a.endPos.x()),h - 2 * (a.startPos.y() - a.endPos.y()),getmyimage2(a.digit2));
                painter.setPen(Qt::NoPen);
        }
        return rtn;
    }


    //如果不是2048模式
    else
    {
        // 移动方格位置
        if (a.type == MOVE)
        {
            switch (a.direct)
            {
            case LEFT:
                if (a.startPos.x() > a.endPos.x())
                    a.startPos += dPos[LEFT];
                else
                    a.startPos = a.endPos, rtn = true;
                break;
            case RIGHT:
                if (a.startPos.x() < a.endPos.x())
                    a.startPos += dPos[RIGHT];
                else
                    a.startPos = a.endPos, rtn = true;
                break;
            case UP:
                if (a.startPos.y() > a.endPos.y())
                    a.startPos += dPos[UP];
                else
                    a.startPos = a.endPos, rtn = true;
                break;
            case DOWN:
                if (a.startPos.y() < a.endPos.y())
                    a.startPos += dPos[DOWN];
                else
                    a.startPos = a.endPos, rtn = true;
            }
            // 如果方格移动到终点
            if (!rtn)
            {
                //填充图像
                painter.drawPixmap(a.startPos.x(), a.startPos.y(),w, h,getmyimage(a.digit));
            }
            else
            {
                 //填充图像
                 painter.drawPixmap(a.startPos.x(), a.startPos.y(),w, h,getmyimage(a.digit2));
            }
            painter.setPen(Qt::NoPen);
        }
        //如果方格不动，就播放出现动画
        else
        {
            // 方格出现的动画效果
            if (a.startPos.x() > a.endPos.x())
                a.startPos += QPointF(-25, -25);
            else
                a.startPos = a.endPos, rtn = true;
            //填充图像
             painter.drawPixmap(a.startPos.x(), a.startPos.y(),w, h,getmyimage(a.digit));
        }
        return rtn;
    }
}

//绘制初始界面
void GameWidget::paintEvent(QPaintEvent *)
{
    // 构造一个QPainter对象 使用它来进行绘图
    QPainter painter(this);

    // 设置反锯齿绘图
    painter.setRenderHint(QPainter::Antialiasing);

    // 如果正在播放动画效果则绘制缓存位图
    if (isAnimating)
    {
        if (drawAnimation(painter))
        {
            isAnimating = false;
            timer.stop();
            //清除所有动画
            animationList.clear();
            if (digitCount == Mult*Mult)
            {
                // 如果数字填满了 检测游戏是否over
                if (checkGameOver())
                    emit GameOver();// 如果游戏over了则发射GameOver信号
            }
            // 检测游戏是否获胜
            if (checkWin())
                emit win();// 如果获胜则发射win信号
        }
        return;
    }
    //判断是不是2048模式
    if(to==2048)
    {
            // 构造一个画刷 颜色为背景蓝色
            QBrush brush(QColor::fromRgb(1, 72, 179));
            // 使painter应用这个画刷
            painter.setBrush(brush);
            // 设置画笔为空笔 目的是使绘制的图形没有描边
            painter.setPen(Qt::NoPen);
            // 绘制一个矩形
            painter.drawRoundedRect(QRectF(0, 0, width(), height()), 0, 0);
            /* 构造一个字体
             * 字体名字为Consolas
             * 字体设置为粗体
             * 字体大小为40像素
             * */
            QFont font;
            font.setFamily("Consolas");
            font.setBold(true);
            font.setPixelSize(40);
            // 使painter应用这个字体
            painter.setFont(font);
            // 循环绘制游戏面板
            for (int i = 0; i < Mult; i++)
            {
                for (int j = 0; j < Mult; j++)
                {
                   // 如果方格中有数字
                    if (board[i][j])
                    {
                        //绘制小方格背景图片
                        painter.drawPixmap(7 + (w + 5) * j, 7 + (h + 5) * i, w, h,getmyimage2(board[i][j]));
                        // 设置画笔为空笔
                        painter.setPen(Qt::NoPen);
                    }
                    /* 如果方格中没有数字
                    else
                    {
                        // 设置画刷颜色为 RGB分量为171 165 141的颜色
                        brush.setColor(QColor::fromRgb(171, 165, 141));
                        // 应用这个画刷
                        painter.setBrush(brush);
                        // 绘制小方格
                        painter.drawRoundedRect(QRectF(7 + (w + 5) * j, 7 + (h + 5) * i, w, h), 0, 0);
                    }*/
                 }
             }//绘制游戏面板结束
    }
    //如果不是2048模式
    else
    {
            //填充背景大矩形
            if(Mult==4)
                {

                    QPixmap image(":/image/start2.png");
                    painter.drawPixmap(0, 0,400,400,image);
                }
                else
                {
                    QPixmap image(":/image/start3.png");
                    painter.drawPixmap(0, 0,400,400,image);
                }
            // 循环绘制游戏面板
            for (int i = 0; i < Mult; i++)
            {
                for (int j = 0; j < Mult; j++)
                {
                    // 如果方格中有数字
                    if (board[i][j])
                    {
                        //填充图像
                        painter.drawPixmap(7 + (w + 5) * j, 7 + (h + 5) * i, w, h,getmyimage(board[i][j]));
                        // 设置画笔为空笔
                        painter.setPen(Qt::NoPen);
                    }
                }
            }
    }
}
void GameWidget::resizeEvent(QResizeEvent *)
{
    ratioW = width() / (Mult*100.0), ratioH = height() / (Mult*100.0);
    // 计算每个小格子的宽度和高度
    w = width() - Mult, h = height() - Mult;
    w = (w - 25) / Mult, h = (h - 25) / Mult;
    rX = 15, rY = 15;
    dPos[0] = QPointF(-25, 0);
    dPos[1] = QPointF(25, 0);
    dPos[2] = QPointF(0, -25);
    dPos[3] = QPointF(0, 25);
    dPos[4] = QPointF(-4, -4);
}

void GameWidget::restart()
{

    // 初始化相关变量 同构造函数
    score = 0;
    digitCount = 2;
    for(int z=0;z<Mult;z++)
           for(int z2=0;z2<Mult;z2++)
               board[z][z2]=0;
    init2Block();
    emit ScoreInc(score);
    setFocus();
    update();
}

bool GameWidget::checkGameOver()
{
    // 循环检测是否含有相邻的相同数码
    for (int i = 0; i < Mult; i++)
        for (int j = 0; j < Mult; j++)
        {
            if (j != (Mult-1) && board[i][j] == board[i][j + 1])
                return false;
            if (i != (Mult-1) && board[i][j] == board[i + 1][j])
                return false;
        }
    return true;
}

bool GameWidget::checkWin()
{
    if(to!=2048)
    {
       // 循环检测是否某个方格的数字为2048
          for (int i = 0; i < Mult; i++)
             for (int j = 0; j < Mult; j++)
                if (board[i][j] ==2048)
                   return true;
    }
    else
    {
       // 循环检测是否某个方格的数字为2
          for (int i = 0; i < Mult; i++)
             for (int j = 0; j < Mult; j++)
                if (board[i][j] ==2)
                    return true;
    }
    return false;
}
