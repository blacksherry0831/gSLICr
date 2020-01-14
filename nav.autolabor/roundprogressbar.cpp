#include "roundprogressbar.h"
#include <QPainter>
#include <QTransform>

RoundProgressBar::RoundProgressBar(QWidget *parent) :
    QWidget(parent),

    m_min(0),
    m_max(100),
    m_value(25),
    m_startAngle(0),//数据条起始角度0
    m_barStyle(StyleDonut),
    m_outlinePenWidth(1),  //;//外圆画笔宽度
    m_dataPenWidth(1),
    m_rebuildBrush(false),
    m_format("%p%"),
    m_decimals(1),//设置小数位为1
    m_clockwise(true), //顺时针
    m_baseCircleVisible(true),
    m_dataCircleVisible(true),
    m_centerCircleVisible(true),
    m_textVisible(true),
    m_updateFlags(UF_PERCENT),  //文本格式-当前值百分比

    img("E:/qt/test/dial.png"),
    roate_(0),
    degree_(0),
    mouse_down(false)
{

}

RoundProgressBar::~RoundProgressBar()
{
}

void RoundProgressBar::setStartAngle(double angle)
{
    if (angle != m_startAngle)
    {
        m_startAngle = angle;
        update();
    }
}

void RoundProgressBar::setBarStyle(RoundProgressBar::BarStyle style)
{
    if (style != m_barStyle)
    {
        m_barStyle = style;
        update();
    }
}

void RoundProgressBar::setOutlinePenWidth(double penWidth)
{
    if (penWidth != m_outlinePenWidth)
    {
        m_outlinePenWidth = penWidth;
        update();
    }
}

void RoundProgressBar::setDataPenWidth(double penWidth)
{
    if (penWidth != m_dataPenWidth)
    {
        m_dataPenWidth = penWidth;

        update();
    }
}

void RoundProgressBar::setDataColors(const QGradientStops &stopPoints)
{
    if (stopPoints != m_gradientData)
    {
        m_gradientData = stopPoints;
        m_rebuildBrush = true;
        update();
    }
}

void RoundProgressBar::setFormat(const QString &format)
{
    if (format != m_format)
    {
        m_format = format;
        valueFormatChanged();
    }
}

void RoundProgressBar::setDecimals(int count)
{
    if (count >= 0 && count != m_decimals)
    {
        m_decimals = count;
        valueFormatChanged();
    }
}

void RoundProgressBar::setClockwise(bool clockwise)
{
    if(clockwise != m_clockwise)
    {
        m_clockwise = clockwise;
        update();
    }
}

void RoundProgressBar::setRange(double min, double max)
{
    m_min = min;
    m_max = max;
    if (m_max < m_min)
        qSwap(m_max, m_min);
    if (m_value < m_min)
        m_value = m_min;
    else if (m_value > m_max)
        m_value = m_max;
    update();
}

void RoundProgressBar::setValue(int val)
{
    setValue((double)val);
}

void RoundProgressBar::setValue(double val)
{
    if (m_value != val)
    {
        if (val < m_min)
            m_value = m_min;
        else if (val > m_max)
            m_value = m_max;
        else
            m_value = val;
        update();
    }
}

void RoundProgressBar::setBaseCircleVisible(bool visible)
{
    if(visible != m_baseCircleVisible)
    {
        m_baseCircleVisible = visible;
        update();
    }
}

void RoundProgressBar::setDataCircleVisible(bool visible)
{
    if(visible != m_dataCircleVisible)
    {
        m_dataCircleVisible = visible;
        update();
    }
}

void RoundProgressBar::setCenterCircleVisible(bool visible)
{
    if(visible != m_centerCircleVisible)
    {
        m_centerCircleVisible = visible;
        update();
    }
}

void RoundProgressBar::setTextVisible(bool visible)
{
    if(visible != m_textVisible)
    {
        m_textVisible = visible;
        update();
    }
}

void RoundProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    double outerRadius = qMin(width(), height()); //;获取长宽的最小值
    QRectF baseRect(1, 1, outerRadius-2, outerRadius-2); //画矩形

    QImage buffer(outerRadius, outerRadius, QImage::Format_ARGB32_Premultiplied); //图像存储使用一个自左乘32位ARGB格式

    QPainter p(&buffer);
    p.setRenderHint(QPainter::Antialiasing); //反走样

    //data brush
    rebuildDataBrushIfNeeded(); //设置数据条颜色填充 渐变

    // background
    drawBackground(p, buffer.rect()); //填充背景色

    // base circle
    if(m_baseCircleVisible)
        drawBase(p, baseRect);  //画外圆

    // data circle 画数据条
    double delta = (m_max - m_min) / (m_value - m_min);
    if(m_dataCircleVisible)
        drawValue(p, baseRect, m_value, delta);  //当前数据值 画数据条

    // center circle
    double innerRadius(0);
    QRectF innerRect;
    calculateInnerRect(baseRect, outerRadius, innerRect, innerRadius); //内圆的外接框计算
    if(m_centerCircleVisible)
        drawInnerBackground(p, innerRect); //画内圆

    // text
    if(m_textVisible)
        drawText(p, innerRect, innerRadius, m_value); //显示文字

    // finally draw the bar
    p.end();

    QTransform transform;
    transform.translate((width()-outerRadius)/2, (height()-outerRadius)/2); //平移坐标系
    QPainter painter(this);
    painter.setTransform(transform);
    painter.fillRect(baseRect, palette().background());
    painter.drawImage(0,0, buffer); //画出整体布局
}

void RoundProgressBar::drawBackground(QPainter &p, const QRectF &baseRect)
{
    p.fillRect(baseRect, palette().background());
}

void RoundProgressBar::drawBase(QPainter &p, const QRectF &baseRect)
{
    switch (m_barStyle)
    {
    case StyleDonut:
        p.setPen(QPen(palette().shadow().color(), m_outlinePenWidth));
        p.setBrush(palette().base());
        p.drawEllipse(baseRect);  //画矩形的内接圆
        break;
    case StylePie:
        p.setPen(QPen(palette().base().color(), m_outlinePenWidth));
        p.setBrush(palette().base());
        p.drawEllipse(baseRect);
        break;
    case StyleLine:
        p.setPen(QPen(palette().base().color(), m_outlinePenWidth));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(baseRect.adjusted(m_outlinePenWidth/2, m_outlinePenWidth/2, -m_outlinePenWidth/2, -m_outlinePenWidth/2));

        p.setPen(QPen(palette().background(),  m_outlinePenWidth));
        p.drawArc(
            baseRect.adjusted(m_outlinePenWidth/2, m_outlinePenWidth/2, -m_outlinePenWidth/2, -m_outlinePenWidth/2),
            180 * 16,
            180 * 16); //绘制下半圆弧
        break;
    default:
        break;
    }
}

void RoundProgressBar::drawValue(QPainter &p, const QRectF &baseRect, double value, double delta)
{
    if (value == m_min)
        return;
    // for Line style
    if (m_barStyle == StyleLine)
    {
        p.setPen(QPen(palette().highlight().color(), m_dataPenWidth));
        p.setBrush(Qt::NoBrush);
        if (value == m_max)
        {
            //dx1为相对于原始矩形左上角x坐标的偏移值，dy1为相对于原始矩形左上角y坐标的偏移值，负值表示在矩形外，正值表示在矩形内；
            //dx2和dy2分别是相对于右下角x坐标和y坐标的偏移值，负值表示在矩形内，正值表示在矩形外，正好相反！这点需要注意一下！
            p.drawEllipse(baseRect.adjusted(m_outlinePenWidth/2, m_outlinePenWidth/2, -m_outlinePenWidth/2, -m_outlinePenWidth/2));
        }
        else
        {
            double arcLength = 360.0 / delta;  //根据value 调整所填的范围
            p.drawArc(
                baseRect.adjusted(m_outlinePenWidth/2, m_outlinePenWidth/2, -m_outlinePenWidth/2, -m_outlinePenWidth/2),
                m_startAngle * 16,
                m_clockwise?-arcLength * 16:arcLength * 16); //绘制圆弧
        }

        return;
    }
    // for Pie and Donut styles
    QPainterPath dataPath;
    dataPath.setFillRule(Qt::WindingFill);

    // pie segment outer
    if (value == m_max)
    {
        dataPath.addEllipse(baseRect);
    }
    else
    {
        double arcLength = 360.0 / delta;
        dataPath.moveTo(baseRect.center());
        dataPath.arcTo(baseRect, m_startAngle, m_clockwise?-arcLength:arcLength);
        dataPath.lineTo(baseRect.center());
    }

    p.setBrush(palette().highlight());
    p.setPen(QPen(palette().shadow().color(), m_dataPenWidth));
    p.drawPath(dataPath);
}

void RoundProgressBar::calculateInnerRect(const QRectF &/*baseRect*/, double outerRadius, QRectF &innerRect, double &innerRadius)
{
    // for Line and Expand styles
    if (m_barStyle == StyleLine)
    {
        innerRadius = outerRadius - m_outlinePenWidth; //算内圆半径
    }
    else    // for Pie and Donut styles
    {
        innerRadius = outerRadius * 0.75;
    }

    double delta = (outerRadius - innerRadius) / 2;
    innerRect = QRectF(delta, delta, innerRadius, innerRadius);
}

void RoundProgressBar::drawInnerBackground(QPainter &p, const QRectF &innerRect)
{
    if (m_barStyle == StyleDonut)
    {
        p.setBrush(palette().alternateBase());
        p.drawEllipse(innerRect);
    }
//    p.save();
//    img=img.scaled(innerRect.width()/2,innerRect.height()/2,Qt::KeepAspectRatio);
//    p.setRenderHint(QPainter::SmoothPixmapTransform);
//    p.drawImage(0,0,img);
//    p.restore();

}

void RoundProgressBar::drawText(QPainter &p, const QRectF &innerRect, double innerRadius, double value)
{
    if (m_format.isEmpty())
        return;
    // !!! to revise
    QFont f(font());
    f.setPixelSize(10);
    QFontMetricsF fm(f);
    double maxWidth = fm.width(valueToText(m_max));
    double delta = innerRadius / maxWidth;
    double fontSize = f.pixelSize() * delta * 0.75;
    f.setPixelSize(fontSize);
    p.setFont(f);

    QRectF textRect(innerRect);
    p.setPen(palette().text().color());
    p.drawText(textRect, Qt::AlignCenter, valueToText(value));
}

QString RoundProgressBar::valueToText(double value) const
{
    QString textToDraw(m_format);

    if (m_updateFlags & UF_VALUE)
        textToDraw.replace("%v", QString::number(value, 'f', m_decimals));

    if (m_updateFlags & UF_PERCENT)
    {
        double procent = (value - m_min) / (m_max - m_min) * 100.0;
        textToDraw.replace("%p", QString::number(procent, 'f', m_decimals));
    }

    if (m_updateFlags & UF_MAX)
        textToDraw.replace("%m", QString::number(m_max - m_min + 1, 'f', m_decimals));

    return textToDraw;
}

void RoundProgressBar::valueFormatChanged()
{
    m_updateFlags = 0;

    if (m_format.contains("%v"))
        m_updateFlags |= UF_VALUE;

    if (m_format.contains("%p"))
        m_updateFlags |= UF_PERCENT;

    if (m_format.contains("%m"))
        m_updateFlags |= UF_MAX;

    update();
}

void RoundProgressBar::rebuildDataBrushIfNeeded()
{
    if (!m_rebuildBrush)
        return;
    if (m_gradientData.isEmpty()) //渐变颜色范围和颜色参数
        return;
    if (m_barStyle == StyleLine)
        return;
    m_rebuildBrush = false;

    QPalette p(palette()); //调色板
    QConicalGradient dataBrush(QPointF(0.5,0.5), m_startAngle); //前两个参数 cx 和 cy 组成角度渐变的中心点，第三个参数是渐变的起始角度
    dataBrush.setCoordinateMode(QGradient::StretchToDeviceMode); //设置渐变模式
    // invert colors
    for (int i = 0; i < m_gradientData.count(); i++)
        dataBrush.setColorAt(1.0 - m_gradientData.at(i).first, m_gradientData.at(i).second);
    p.setBrush(QPalette::Highlight, dataBrush);
    setPalette(p); //设置本控件的调色板
}
