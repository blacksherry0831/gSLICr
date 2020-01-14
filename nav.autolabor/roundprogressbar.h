#ifndef ROUNDPROGRESSBAR_H
#define ROUNDPROGRESSBAR_H

#include <QWidget>

class RoundProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit RoundProgressBar(QWidget *parent = 0);
    ~RoundProgressBar();

    //进度条显示类型
    enum BarStyle
    {
        StyleDonut,//圆环
        StylePie,//饼状
        StyleLine,//线条
    };
    //起始角度
    static const int PositionLeft = 180;
    static const int PositionTop = 90;
    static const int PositionRight = 0;
    static const int PositionBottom = -90;

    void setStartAngle(double angle); //设置起始角度
    void setBarStyle(BarStyle style); //设置进度条风格
    void setOutlinePenWidth(double penWidth); //设置外圆画笔宽度
    void setDataPenWidth(double penWidth); //设置外圆画笔宽度
    void setDataColors(const QGradientStops& stopPoints); //设置数据颜色
    void setFormat(const QString& format);  //设置文字样式
    void setDecimals(int count); //设置小数点位数
    void setClockwise(bool clockwise); //设置是否顺时针

public slots:
    void setRange(double min, double max); //设置角度范围
    void setValue(int val);  //设角度值
    void setValue(double val);  //设角度值 小数
    void setBaseCircleVisible(bool visible); //设置外圆是否隐形
    void setDataCircleVisible(bool visible); //设置数据圈是否隐形
    void setCenterCircleVisible(bool visible); //设置内圆是否隐形
    void setTextVisible(bool visible); //设置文字是否隐形

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void drawBackground(QPainter& p, const QRectF& baseRect);
    virtual void drawBase(QPainter& p, const QRectF& baseRect);
    virtual void drawValue(QPainter& p, const QRectF& baseRect, double value, double delta);
    virtual void calculateInnerRect(const QRectF& baseRect, double outerRadius, QRectF& innerRect, double& innerRadius);
    virtual void drawInnerBackground(QPainter& p, const QRectF& innerRect);
    virtual void drawText(QPainter& p, const QRectF& innerRect, double innerRadius, double value);
    virtual QString valueToText(double value) const;
    virtual void valueFormatChanged();

    virtual QSize minimumSizeHint() const { return QSize(32,32); }
    void rebuildDataBrushIfNeeded();

//    virtual void mouseMoveEvent(QMouseEvent *event);
//    virtual void mousePressEvent(QMouseEvent *event);
//    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    double m_min, m_max;//最小值,最大值
    double m_value;//当前值
    double m_startAngle;//起始角度
    BarStyle m_barStyle;//显示类型
    double m_outlinePenWidth, m_dataPenWidth;//外圆画笔宽度,数据圆画笔宽度(主要用在线条显示类型)
    QGradientStops m_gradientData;//渐变颜色(主要用在圆环和饼状显示类型)
    bool m_rebuildBrush;
    QString m_format;//文本显示格式
    int m_decimals;//小数点位数
    bool m_clockwise;//顺时针
    bool m_baseCircleVisible;//显示外圆
    bool m_dataCircleVisible;//显示数据圆
    bool m_centerCircleVisible;//显示内圆
    bool m_textVisible;//显示文字

    static const int UF_VALUE = 1;//文本格式-当前值
    static const int UF_PERCENT = 2;//文本格式-当前值百分比
    static const int UF_MAX = 4;//文本格式-最大值
    int m_updateFlags;

    QImage img;
    qreal roate_; //起始坐标系旋转角度
    qreal degree_; //鼠标移动角度
    bool mouse_down; //鼠标是否放下

};

#endif // ROUNDPROGRESSBAR_H
