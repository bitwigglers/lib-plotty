#ifndef PLOTTERPRIVATE_H
#define PLOTTERPRIVATE_H

#include <QString>

class PlotterPrivate
{
	PlotterPrivate();
	QString xUnit;
	QString yUnit;

	bool useAntiAliasing;

	friend class Plotter;
};

#endif // PLOTTERPRIVATE_H
