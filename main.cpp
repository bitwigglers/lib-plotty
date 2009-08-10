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

	QVector<QPointF> vector;
	double x = -10;
	while (x <= 10) {
		vector.append(QPointF(x, sin(x) + 0.333 * sin (3 * x) + 0.2 *sin(5*x)));
		x += 0.1;
	}
	plotter.setCurveData(0, vector);
	plotter.setXUnit("s");
	plotter.setYUnit("V");
	plotter.show();

	return a.exec();
}
