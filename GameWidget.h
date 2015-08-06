#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QEventLoop>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <QSound>
#include <QKeyEvent>
// 手势的方向
enum GestureDirect
{
    LEFT = 0,   // 向左
    RIGHT = 1,  // 向右
    UP = 2,     // 向上
    DOWN = 3    // 向下
};

// 定义动画的类型
enum AnimationType
{
    MOVE = 0,       // 方格移动动画
    APPEARANCE = 1  // 方格出现动画
};

// 动画结构体
struct Animation
{
    AnimationType type;     // 动画类型
    GestureDirect direct;   // 方向
    QPointF startPos;       // 起始点坐标 出现动画仅仅使用这个坐标
    QPointF endPos;         // 终止点坐标 移动动画的终点坐标
    int digit;              // 数码
    int digit2;             // 第二数码 数码可能被合并
};

// 游戏部件类 继承自QWidget
class GameWidget : public QGLWidget
{
    Q_OBJECT
public:
    // 构造函数
    explicit GameWidget(QWidget *parent = 0,int gmode = 0);

private:
    //获取2048模式小图片
    QPixmap getmyimage2(int n);
    //获取其他模式小图片
    QPixmap getmyimage(int n);
    //Play 4x4 or 8x8
    int Mult;
    // 游戏面板 存储每个格子的数值
    int board[8][8];
    // 数码的个数 存储当前面板上的数字的个数
    int digitCount;
    // 分数 存储当前得分
    int score;
    // 起始点坐标 存储手势起点坐标
    QPoint startPos;
    // 存储所有需要展现的动画
    QList<Animation> animationList;
    // 小格子的宽度和高度
    qreal w, h;
    // 宽度和高度的缩放比例
    qreal ratioW, ratioH;
    // 小圆角的 x y
    qreal rX, rY;
    // 缓存图像
    //QImage *cacheImg;
    // 是否在播放动画效果
    bool isAnimating;
    // 计时器
    QTimer timer;

    // 初始化两个方格
    void init2Block();
    // 检测游戏是否结束
    bool checkGameOver();
    // 检测游戏是否获胜
    bool checkWin();
    // 播放一帧动画
    bool playAnimation(Animation&, QPainter&);
    // 绘制动画效果
    bool drawAnimation(QPainter&);
    // 鼠标按下触发的事件
    void mousePressEvent(QMouseEvent *);
    // 鼠标释放触发的时间
    void mouseReleaseEvent(QMouseEvent *);
    // 绘制事件
    void paintEvent(QPaintEvent *);
    // 窗口尺寸改变事件
    void resizeEvent(QResizeEvent *);
    //键盘
     void keyPressEvent(QKeyEvent *b);
signals:
    // 手势移动信号
    void GestureMove(GestureDirect);
    // 分数增加信号
    void ScoreInc(int);
    // 游戏结束信号
    void GameOver();
    // 游戏获胜信号
    void win();

public slots:
    // 处理手势移动信号的槽函数
    void onGestureMove(GestureDirect);
    // 重新开始的槽函数
    void restart();
};

#endif // GAMEWIDGET_H
