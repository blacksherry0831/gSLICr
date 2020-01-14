#ifndef CLOUDPANEL_H
#define CLOUDPANEL_H

#include <QWidget>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QtUiPlugin/QDesignerExportWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT CloudPanel : public QWidget
#else
class CloudPanel : public QWidget
#endif

{
    Q_OBJECT
    Q_ENUMS(CloudStyle)

    Q_PROPERTY(QColor baseColor READ getBaseColor WRITE setBaseColor)
    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor arcColor READ getArcColor WRITE setArcColor)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor pressColor READ getPressColor WRITE setPressColor)

    Q_PROPERTY(QString iconText READ getIconText WRITE setIconText)
    Q_PROPERTY(QString centerText READ getCenterText WRITE setCenterText)
    Q_PROPERTY(CloudStyle cloudStyle READ getCloudStyle WRITE setCloudStyle)

public:
    enum CloudStyle {
        CloudStyle_Black = 0,   //黑色风格
        CloudStyle_White = 1,   //白色风格
        CloudStyle_Blue = 2,    //蓝色风格
        CloudStyle_Purple = 3   //紫色风格
    };

    explicit CloudPanel(QWidget *parent = 0);
    ~CloudPanel();

protected:
    void enterEvent(QEvent *); //*
    void leaveEvent(QEvent *); //*
    void mousePressEvent(QMouseEvent *);  //*
    void mouseReleaseEvent(QMouseEvent *);  //*
    void paintEvent(QPaintEvent *);  //*
    void drawCircle(QPainter *painter, int radius, const QBrush &brush); //*
    void drawArc(QPainter *painter);  //*
    void drawText(QPainter *painter);  //*
    bool isPointIn(const QPoint pos,int &bp);

private:
    QColor bgColor;                 //背景颜色
    QColor baseColor;               //基准颜色
    QColor arcColor;                //圆弧颜色
    QColor borderColor;             //边框颜色
    QColor textColor;               //文字颜色
    QColor pressColor;              //按下文字颜色

    QString iconText;               //八个角图标
    QString centerText;             //中间图标
    CloudStyle cloudStyle;          //云台样式

    bool enter;                     //鼠标是否进入
    bool pressed;                   //鼠标是否按下
    QPoint lastPoint;               //鼠标按下处的坐标
    QRectF centerRect;              //中间区域
    QRectF leftRect;                //左侧图标区域
    QRectF topRect;                 //上侧图标区域
    QRectF rightRect;               //右侧图标区域
    QRectF bottomRect;              //下侧图标区域
    QRectF leftTopRect;             //左上角图标区域
    QRectF rightTopRect;            //右上角图标区域
    QRectF leftBottomRect;          //左下角图标区域
    QRectF rightBottomRect;         //右下角图标区域

    QFont iconFont;                 //图形字体

public:
    QColor getBgColor() const {return bgColor;}  //获取背景颜色
    QColor getBaseColor() const {return baseColor;}  //获取基准颜色
    QColor getArcColor() const {return arcColor;}  //获取圆弧颜色
    QColor getBorderColor() const {return borderColor;}  //获取边框颜色
    QColor getTextColor() const {return textColor;}  //获取文本颜色
    QColor getPressColor() const {return pressColor;}  //获取按下的颜色

    QString getIconText() const {return iconText;}  //获取八个角图标
    QString getCenterText() const {return centerText;}  //获取中间图标
    CloudStyle getCloudStyle() const {return cloudStyle;}  //云台样式

//    QSize sizeHint()                const;  //返回一个被推荐的尺寸 widget 没有布局（layout），返回无效值；否则返回其 layout 的首选尺寸（preferred size）。
//    QSize minimumSizeHint()         const;  //在 widget 无 layout 的情况下返回无效值；否则返回 layout 的最小尺寸（minimum size）

public Q_SLOTS:
    //设置背景颜色
    void setBgColor(const QColor &bgColor);
    //设置基准颜色
    void setBaseColor(const QColor &baseColor);
    //设置圆弧颜色
    void setArcColor(const QColor &arcColor);
    //设置边框颜色
    void setBorderColor(const QColor &borderColor);
    //设置文本颜色
    void setTextColor(const QColor &textColor);
    //设置按下文本颜色
    void setPressColor(const QColor &pressColor);

    //设置八个角图标
    void setIconText(const QString &iconText);
    //设置中间图标
    void setCenterText(const QString &centerText);
    //设置云台样式
    void setCloudStyle(const CloudStyle &cloudStyle);

Q_SIGNALS:
    //鼠标按下的区域,共9个,从0-8依次表示底部/左下角/左侧/左上角/顶部/右上角/右侧/右下角/中间
    void mousePressed(int position);
};

#endif //GAUGECLOUD_H
