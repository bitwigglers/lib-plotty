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

QVector<QPointF> PlotCurve::data()
{
	return d->data;
}

void PlotCurve::setData(QVector<QPointF> data)
{
	d->data = data;
}

/************************************************/

PlotCurvePrivate::PlotCurvePrivate()
{
	lineStyle = Qt::SolidLine;
}
