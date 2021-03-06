#include "plotcurve.h"
#include "plotcurve_p.h"

PlotCurve::PlotCurve()
{
    d = new PlotCurvePrivate();
}

PlotCurve::~PlotCurve()
{
    delete d;
}

Qt::PenStyle PlotCurve::lineStyle()
{
    return d->lineStyle;
}

void PlotCurve::setLineStyle(Qt::PenStyle style)
{
    d->lineStyle = style;
}

PlotCurve::PointStyle PlotCurve::pointStyle()
{
    return d->pointStyle;
}

void PlotCurve::setPointStyle(PlotCurve::PointStyle style)
{
    d->pointStyle = style;
}

PlotCurve::CurveStyle PlotCurve::curveStyle()
{
    return d->curveStyle;
}

void PlotCurve::setCurveStyle(PlotCurve::CurveStyle style)
{
    d->curveStyle = style;
}

QVector<QPointF> PlotCurve::data()
{
    return d->data;
}

void PlotCurve::setData(QVector<QPointF> data)
{
    d->data = data;
}

QColor& PlotCurve::color() const
{
    return d->color;
}

void PlotCurve::setColor(const QColor &color)
{
    d->color = color;
}

double PlotCurve::baseLine()
{
    return d->baseLine;
}

void PlotCurve::setBaseLine(double y)
{
    d->baseLine = y;
}

/************************************************/

PlotCurvePrivate::PlotCurvePrivate()
{
    lineStyle = Qt::SolidLine;
    pointStyle = PlotCurve::PointNone;
    curveStyle = PlotCurve::CurveNormal;
    color = Qt::red;
    baseLine = 0.0;
}
