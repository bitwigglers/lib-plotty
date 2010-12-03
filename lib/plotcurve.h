#ifndef PLOTCURVE_H
#define PLOTCURVE_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QColor>

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
	enum CurveStyle{CurveNormal, CurveSticks, CurveBaseLineSticks, CurveStairCase};

	Qt::PenStyle lineStyle();
	void setLineStyle (Qt::PenStyle style);
	PlotCurve::PointStyle pointStyle();
	void setPointStyle (PlotCurve::PointStyle style);
	PlotCurve::CurveStyle curveStyle();
	void setCurveStyle (PlotCurve::CurveStyle style);
	QColor& color() const;
	void setColor(const QColor &color);
	double baseLine();
	void setBaseLine(double y);

	QVector<QPointF> data();
	void setData(QVector<QPointF> data);

private:
	PlotCurvePrivate *d;
};

#endif // PLOTCURVE_H
