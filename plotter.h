#ifndef PLOTTER_H
#define PLOTTER_H

#include <QMap>
#include <QPixmap>
#include <QVector>
#include <QWidget>

#include <QTimer>
#include <cmath>

class QToolButton;
class PlotSettings;
class PlotterPrivate;

class Plotter : public QWidget
{
    Q_OBJECT
	Q_PROPERTY(QString xUnit READ xUnit WRITE setXUnit RESET unsetXUnit)

public:
	Plotter(QWidget *parent = 0);

	void setPlotSettings(const PlotSettings &settings);
	void setCurveData(int id, const QVector<QPointF>&data);
	void clearCurve(int id);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	QString xUnit();
	void setXUnit(QString unit);
	void unsetXUnit();
	QString yUnit();
	void setYUnit(QString unit);
	void unsetYUnit();

public slots:
	void zoomIn();
	void zoomOut();
	void updatePlot() {refreshPixmap();}

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void wheelEvent(QWheelEvent *event);

private:
	void updateRubberBandRegion();
	void refreshPixmap();
	void drawGrid(QPainter *painter);
	void drawCurves(QPainter *painter);

	enum {Margin = 50};

	QToolButton *zoomInButton;
	QToolButton *zoomOutButton;
	QMap<int, QVector<QPointF> > curveMap;
	QVector<PlotSettings> zoomStack;
	int curZoom;
	bool rubberBandIsShown;
	QRect rubberBandRect;
	QPixmap pixmap;

	PlotterPrivate *d;
};

class PlotSettings
{
public:
	PlotSettings();

	void scroll(int dx, int dy);
	void adjust();
	double spanX() const {return maxX - minX;}
	double spanY() const {return maxY - minY;}

	double minX;
	double maxX;
	int numXTicks;
	double minY;
	double maxY;
	int numYTicks;

private:
	static void adjustAxis(double &min, double &max, int &numTicks);
};

class PlotterPrivate
{
	PlotterPrivate();
	QString xUnit;
	QString yUnit;
	friend class Plotter;
};

#endif // PLOTTER_H
