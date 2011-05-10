#ifndef PLOTTER_H
#define PLOTTER_H

#include <QMap>
#include <QWidget>
#include <cmath>

#include "plotsettings.h"
#include "plotcurve.h"

class QPixmap;
class QRubberBand;
class QTimer;
class QToolButton;
class QWidget;

class PlotterPrivate;

class Plotter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString xUnit READ xUnit WRITE setXUnit RESET unsetXUnit)
    Q_PROPERTY(QString yUnit READ yUnit WRITE setYUnit RESET unsetYUnit)

    Q_PROPERTY(uint margin READ margin WRITE setMargin)

    Q_PROPERTY(bool antiAliasing READ antiAliasing WRITE setAntiAliasing)

public:
    Plotter(QWidget *parent = 0);
    ~Plotter();

    void setPlotSettings(const PlotSettings &settings);
    void setCurveData(int id, PlotCurve *curve);
    void clearCurve(int id);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    QString xUnit();
    void setXUnit(QString unit);
    void unsetXUnit();

    QString yUnit();
    void setYUnit(QString unit);
    void unsetYUnit();

    bool antiAliasing();
    void setAntiAliasing(bool);

    uint margin();
    void setMargin(uint);

public slots:
    void zoomIn();
    void zoomOut();
    void updatePlot();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void refreshPixmap();
    void drawGrid(QPainter *painter);
    void drawCurves(QPainter *painter);
    void drawPoint(QPainter *painter, QPointF center, PlotCurve::PointStyle style = PlotCurve::PointNone);

    QPolygonF clipPolyline(QRectF r, QPolygonF poly);

    QToolButton *zoomInButton;
    QToolButton *zoomOutButton;
    QMap<int, PlotCurve*> curveMap;
    QVector<PlotSettings> zoomStack;
    int curZoom;

    QRubberBand *rubberBand;
    QPoint rubberBandOrigin;

    QPixmap pixmap;

    PlotterPrivate *d;

    int rotAngle;
};


#endif // PLOTTER_H
