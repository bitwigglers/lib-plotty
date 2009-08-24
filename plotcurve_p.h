#ifndef PLOTCURVE_P_H
#define PLOTCURVE_P_H

#endif // PLOTCURVE_P_H

class PlotCurvePrivate
{
public:
	PlotCurvePrivate();
	Qt::PenStyle lineStyle;
	PlotCurve::PointStyle pointStyle;
	PlotCurve::CurveStyle curveStyle;
	QColor color;
	QVector<QPointF> data;
	double baseLine;
};
