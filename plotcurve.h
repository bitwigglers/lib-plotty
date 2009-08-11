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

	Qt::PenStyle lineStyle();
	void setLineStyle (Qt::PenStyle style);

	QVector<QPointF> data();
	void setData(QVector<QPointF> data);

private:
	PlotCurvePrivate *d;
};

#endif // PLOTCURVE_H
