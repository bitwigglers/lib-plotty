#ifndef PLOTCURVE_H
#define PLOTCURVE_H

#include <QObject>
#include <QVector>
#include <QPointF>

class PlotCurvePrivate;

class PlotCurve : public QObject
{
	Q_OBJECT
	Q_PROPERTY(Qt::PenStyle lineStyle READ lineStyle WRITE setLineStyle)

public:
    PlotCurve();
	~PlotCurve();

	enum PointStyle{PointNone, PointCircle, PointCross, PointXCross, PointDiamond, PointBox,
					PointTriangleUp, PointTriangleRight, PointTriangleDown, PointTriangleLeft};

	Qt::PenStyle lineStyle();
	void setLineStyle (Qt::PenStyle style);
	PlotCurve::PointStyle pointStyle();
	void setPointStyle (PlotCurve::PointStyle style);

	QVector<QPointF> data();
	void setData(QVector<QPointF> data);

private:
	PlotCurvePrivate *d;
};

#endif // PLOTCURVE_H
