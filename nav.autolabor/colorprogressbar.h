#ifndef COLORPROGRESSBAR_H
#define COLORPROGRESSBAR_H

#include <QWidget>

#ifdef MSC
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT ColorProgressBar: public QWidget
#else
class ColorProgressBar : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(double Min READ getMin WRITE setMin)
    Q_PROPERTY(double Max READ getMax WRITE setMax)
    Q_PROPERTY(double Value READ getValue WRITE setValue)
    Q_PROPERTY(QColor BarBackGroundColor READ getBarBackGroundColor WRITE setBarBackGroundColor)
    Q_PROPERTY(QColor BarSplitLineColor READ getBarSplitLineColor WRITE setBarSplitLineColor)
    Q_PROPERTY(QColor BarColor READ getBarColor WRITE setBarColor)
    Q_PROPERTY(int Decimal READ getDecimal WRITE setDecimal)
    Q_PROPERTY(int BarSplitLineDelta READ getBarSplitLineDelta WRITE setBarSplitLineDelta)
    Q_PROPERTY(bool ShowBarSplitLine READ getShowBarSplitLine WRITE setShowBarSplitLine)
    Q_PROPERTY(int Space READ getSpace WRITE setSpace)

public:
    ColorProgressBar(QWidget *parent = 0);
    ~ColorProgressBar();

    double getMin() const { return m_min; }  //获取min
    void setMin(double min) { m_min = min; } //设置min
    double getMax() const { return m_max; }  //获取max
    void setMax(double max) { m_max = max; } //设置max
    QColor getBarBackGroundColor() const { return m_barBackGroundColor; } //获背景色
    void setBarBackGroundColor(QColor color);  //设置背景色
    QColor getBarSplitLineColor() { return m_barSplitLineColor; } //获bar线条色
    void setBarSplitLineColor(QColor color); //设置bar线条色
    QColor getBarColor() const { return m_barColor; } //获bar色
    void setBarColor(QColor color);  //设置bar色
    int getDecimal() const { return m_decimal; } //获小数
    void setDecimal(int decimal);  //设小数
    int getBarSplitLineDelta() const { return m_barSplitLineDelta; } //获分割线刻度
    void setBarSplitLineDelta(int delta); //设分割线刻度
    bool getShowBarSplitLine() const { return m_showBarSplitLine; } //获展示的分割线
    void setShowBarSplitLine(bool show); //设展示的分割线
    int getSpace() const { return m_space; } //获空格值
    void setSpace(int space); //设空格值

public slots:
    double getValue() const { return m_value; }
    void setValue(double value);
    void setValue(int value);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void drawBackGround(QPainter& p, const QRectF& barRect, const QRectF& textRect);
    virtual void drawData(QPainter& p, const QRectF& barRect);
    virtual void drarBarSplitLine(QPainter& p, const QRectF& barRect);
    virtual void drawText(QPainter& p, const QRectF& textRect);
    QSize sizeHint() const { return QSize(300, 30); }

private:
    double m_min,m_max,m_value;
    QColor m_barBackGroundColor;//背景颜色
    QColor m_barSplitLineColor;//背景分割线颜色
    int m_barSplitLineDelta;//背景分割线间距
    bool m_showBarSplitLine;//是否显示背景分割线
    QColor m_barColor;
    int m_decimal;
    int m_space;//间隔

    int m_valueWidth;//数值宽度
    int m_xRadius;
    int m_yRadius;
};

#endif // COLORPROGRESSBAR_H
