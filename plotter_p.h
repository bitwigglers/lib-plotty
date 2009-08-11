#ifndef PLOTTERPRIVATE_H
#define PLOTTERPRIVATE_H

#include <QString>

class PlotterPrivate
{
public:
	PlotterPrivate();
	QString xUnit;
	QString yUnit;

	bool useAntiAliasing;
	uint margin;
};

#endif // PLOTTERPRIVATE_H
