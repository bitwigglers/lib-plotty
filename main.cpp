#include <QtGui/QApplication>
#include "plotter.h"

#include <cmath>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	Plotter plotter;
	PlotSettings settings;
	settings.minY = -1;
	settings.maxY = 1;
	settings.minX = - 10;
	settings.maxX = 10;
	plotter.setPlotSettings(settings);

	QVector<QPointF> vector;
	double x = -10;
	while (x <= 10) {
		vector.append(QPointF(x, sin(x)));
		x += 0.1;
	}
	plotter.setCurveData(0, vector);
	plotter.show();

	return a.exec();
}
