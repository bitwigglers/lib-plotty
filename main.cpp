#include <QtGui/QApplication>
#include "plotter.h"

#include <cmath>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Plotter plotter;
	PlotSettings settings;
	settings.minY = -2;
	settings.maxY = 2;
	settings.minX = -2 * M_PI;
	settings.maxX = 2 * M_PI;
	plotter.setPlotSettings(settings);

	QVector<QPointF> v1, v2, v3, v4, v5;

	for (int i = -360; i < 360; i+=10) {
		double x = i * M_PI / 180;
		double y = sin(x);
		v1.append(QPointF(x, y));
		y += 1.0/3.0 * sin(3.0 * x);
		v2.append(QPointF(x, y));
		y += 1.0/5.0 * sin(5.0 * x);
		v3.append(QPointF(x, y));
		y += 1.0/7.0 * sin(7.0 * x);
		v4.append(QPointF(x, y));
		y += 1.0/9.0 * sin(9.0 * x);
		v5.append(QPointF(x, y));
	}

	PlotCurve c1, c2, c3, c4, c5;
	c1.setData(v1);
	c1.setLineStyle(Qt::DashDotLine);
	c1.setPointStyle(PlotCurve::PointCircle);
	c1.setCurveStyle(PlotCurve::CurveSticks);
	c1.setColor(QColor(255, 0, 0, 127));
	c2.setData(v2);
	c2.setLineStyle(Qt::DashDotDotLine);
	c2.setPointStyle(PlotCurve::PointTriangleUp);
	c2.setCurveStyle(PlotCurve::CurveStairCase);
	c2.setColor(QColor(255, 255, 0, 127));
	c3.setData(v3);
	c3.setLineStyle(Qt::DashLine);
	c3.setPointStyle(PlotCurve::PointTriangleRight);
	c3.setCurveStyle(PlotCurve::CurveOriginSticks);
	c3.setColor(QColor(0, 255, 0, 127));
	c4.setData(v4);
	c4.setLineStyle(Qt::DotLine);
	c4.setPointStyle(PlotCurve::PointTriangleDown);
	c4.setColor(QColor(0, 0, 255, 255));
	c5.setData(v5);
	c5.setPointStyle(PlotCurve::PointTriangleLeft);
	c5.setColor(QColor(255, 0, 255, 127));
	//plotter.setAntiAliasing(false);
	plotter.setCurveData(0, &c1);
	plotter.setCurveData(1, &c2);
	plotter.setCurveData(2, &c3);
	plotter.setCurveData(3, &c4);
	plotter.setCurveData(4, &c5);

	plotter.setXUnit("s");
	plotter.setYUnit("V");
	plotter.show();

	return a.exec();
}
