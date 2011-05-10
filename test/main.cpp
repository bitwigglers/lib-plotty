#include <QtGui/QApplication>
#include <plotter.h>

#include <cmath>
#include <QDebug>
#include <QTimer>
#include <QGradient>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Plotter plotter;

        QLinearGradient gradient(plotter.geometry().topLeft(), plotter.geometry().bottomRight());
        gradient.setColorAt(0, Qt::lightGray);
        gradient.setColorAt(1, Qt::darkGray);
        QBrush brush(gradient);
        QPalette palette = plotter.palette();
        palette.setBrush(QPalette::Dark, brush);
        plotter.setPalette(palette);

	PlotSettings settings;
        settings.minY = -2;
        settings.maxY = 2;
        settings.minX = -2 * M_PI;
        settings.maxX = 2 * M_PI;
	plotter.setPlotSettings(settings);

        QVector<QPointF> v1, v2, v3, v4;
        float f = settings.minX;
        while (f <= settings.maxX) {
            v1 << QPointF(f, -1 + sin(f));
            v2 << QPointF(f, 0 + sin(f));
            v3 << QPointF(f, 0.5 * cos(f));
            f += M_PI/8;
        }

        f = settings.minX;
        while (f <= settings.maxX) {
            v4 << QPointF(f, 0.75 + sin(f) + 1.0/3.0 * sin(3*f) + 1.0/5.0 * sin(5*f));
            f += M_PI/100;
        }

        PlotCurve c1, c2, c3, c4;
	c1.setData(v1);
	c1.setLineStyle(Qt::DashDotLine);
	c1.setPointStyle(PlotCurve::PointCircle);
	c1.setCurveStyle(PlotCurve::CurveSticks);
        c1.setColor(QColor(255, 0, 0, 255));
        plotter.setCurveData(0, &c1);

        c2.setData(v2);
	c2.setLineStyle(Qt::DashDotDotLine);
	c2.setPointStyle(PlotCurve::PointCircle);
	c2.setCurveStyle(PlotCurve::CurveStairCase);
        c2.setColor(QColor(255, 255, 0, 255));
        plotter.setCurveData(1, &c2);

        c3.setData(v3);
        c3.setPointStyle(PlotCurve::PointBox);
        c3.setCurveStyle(PlotCurve::CurveBaseLineSticks);
	c3.setColor(QColor(0, 255, 0, 127));
        plotter.setCurveData(2, &c3);

        c4.setData(v4);
        c4.setColor(QColor(0, 0, 255, 255));
        plotter.setCurveData(3, &c4);

        plotter.setXUnit("t");
        plotter.setYUnit("sin(t)");

        plotter.show();

	return app.exec();
}
