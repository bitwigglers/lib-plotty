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
	settings.minX = - 10;
	settings.maxX = 10;
	plotter.setPlotSettings(settings);

	QVector<QPointF> v1, v2, v3, v4, v5;

	double x = -10;
	while (x <= 10) {
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

		x += 0.1;
	}


	plotter.setCurveData(0, v1);
	plotter.setCurveData(1, v2);
	plotter.setCurveData(2, v3);
	plotter.setCurveData(3, v4);
	plotter.setCurveData(4, v5);

	plotter.setXUnit("s");
	plotter.setYUnit("V");
	plotter.show();

	return a.exec();
}
