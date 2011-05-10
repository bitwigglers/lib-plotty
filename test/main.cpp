#include <QtGui/QApplication>
#include <plotter.h>

#include <cmath>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Plotter plotter;
	PlotSettings settings;
	settings.minY = - 5 * 360;
	settings.maxY = 5 * 360;
	settings.minX = 5 * -360;
	settings.maxX = 5 * 360;
	plotter.setPlotSettings(settings);

	QVector<QPointF> v1, v2, v3, v4, v5;
	double a = 50;
	for (int i = 0; i < 5 * 360; i+=10) {
		double alpha = i * 3.14159 / 180;
		double r1 = a * alpha;
		double r2 = 5*a * pow(alpha, 1.0 / 2.0);
		qDebug() << r2;

		v1 << QPointF(r1 * sin(alpha), r1 * cos(alpha));
		v2 << QPointF(r2 * sin(alpha), r2 * cos(alpha));
	}

	PlotCurve c1, c2, c3, c4, c5;
	c1.setData(v1);
	c1.setLineStyle(Qt::DashDotLine);
	c1.setPointStyle(PlotCurve::PointCircle);
	c1.setCurveStyle(PlotCurve::CurveSticks);
	c1.setColor(QColor(255, 0, 0, 127));
	c2.setData(v2);
	c2.setLineStyle(Qt::DashDotDotLine);
	c2.setPointStyle(PlotCurve::PointCircle);
	c2.setCurveStyle(PlotCurve::CurveStairCase);
	c2.setColor(QColor(255, 255, 0, 127));
	c3.setData(v3);
	c3.setLineStyle(Qt::DashLine);
	c3.setPointStyle(PlotCurve::PointTriangleRight);
	c3.setCurveStyle(PlotCurve::CurveBaseLineSticks);
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

	return app.exec();
}
