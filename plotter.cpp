
#include <QtGui>

#include "plotter.h"

Plotter::Plotter(QWidget *parent)
    : QWidget(parent)
{
	d = new PlotterPrivate();

	rubberBand = NULL;

	setBackgroundRole(QPalette::Dark);
	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setFocusPolicy(Qt::StrongFocus);

	zoomInButton = new QToolButton(this);
	zoomInButton->setIcon(QIcon(":/images/zoomin.png"));
	zoomInButton->adjustSize();
	connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));

	zoomOutButton = new QToolButton(this);
	zoomOutButton->setIcon(QIcon(":/images/zoomout.png"));
	zoomOutButton->adjustSize();
	connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

	setPlotSettings(PlotSettings());
}

void Plotter::setPlotSettings(const PlotSettings &settings)
{
	zoomStack.clear();
	zoomStack.append(settings);
	curZoom = 0;
	zoomInButton->hide();
	zoomOutButton->hide();
	refreshPixmap();
}

void Plotter::zoomOut()
{
	if (curZoom > 0) {
		--curZoom;
		zoomOutButton->setEnabled(curZoom > 0);
		zoomInButton->setEnabled(true);
		zoomInButton->show();
		refreshPixmap();
	}
}

void Plotter::zoomIn()
{
	if (curZoom < zoomStack.count() - 1) {
		++curZoom;
		zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
		zoomOutButton->setEnabled(true);
		zoomOutButton->show();
		refreshPixmap();
	}
}

void Plotter::setCurveData(int id, const QVector<QPointF> &data)
{
	curveMap[id] = data;
	refreshPixmap();
}

void Plotter::clearCurve(int id)
{
	curveMap.remove(id);
	refreshPixmap();
}

QSize Plotter::minimumSizeHint() const
{
	return QSize(6 * Margin, 4 * Margin);
}

QSize Plotter::sizeHint() const
{
	return QSize(12 * Margin, 8 * Margin);
}

void Plotter::paintEvent(QPaintEvent *)
{
	QStylePainter painter(this);
	painter.drawPixmap(0, 0, pixmap);

	if (hasFocus()) {
		QStyleOptionFocusRect option;
		option.initFrom(this);
		option.backgroundColor = palette().dark().color();
		painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
	}
}

void Plotter::resizeEvent(QResizeEvent *)
{
	int x = width() - (zoomInButton->width() + zoomOutButton->width() + 10);
	zoomInButton->move(x, 5);
	zoomOutButton->move(x + zoomInButton->width() + 5, 5);
	refreshPixmap();
}

void Plotter::mousePressEvent(QMouseEvent *event)
{
	QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);

	if (event->button() == Qt::LeftButton) {
		if (rect.contains(event->pos())) {
			rubberBandOrigin = event->pos();
			if (!rubberBand)
				rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
			rubberBand->setGeometry(QRect(rubberBandOrigin, QSize()));
			rubberBand->show();
			setCursor(Qt::CrossCursor);
		}
	}
	else if (event->button() == Qt::RightButton)
		zoomOut();
}

void Plotter::mouseMoveEvent(QMouseEvent *event)
{
	QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
	rubberBand->setGeometry(QRect(rubberBandOrigin, event->pos()).normalized().intersected(rect));
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		unsetCursor();

		QRect rect = rubberBand->geometry().normalized();
		if (rect.width() < 4 || rect.height() < 4)
			return;

		rubberBand->hide();

		rect.translate(-Margin, -Margin);

		PlotSettings prevSettings = zoomStack[curZoom];
		PlotSettings settings;
		double dx = prevSettings.spanX() / (width() - 2 * Margin);
		double dy = prevSettings.spanY() / (height() - 2 * Margin);

		settings.minX = prevSettings.minX + dx * rect.left();
		settings.maxX = prevSettings.minX + dx * rect.right();
		settings.minY = prevSettings.maxY - dy * rect.bottom();
		settings.maxY = prevSettings.maxY - dy * rect.top();
		settings.adjust();

		zoomStack.resize(curZoom + 1);
		zoomStack.append(settings);
		zoomIn();
	}
}

void Plotter::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Plus:
		zoomIn();
		break;
	case Qt::Key_Minus:
		zoomOut();
		break;
	case Qt::Key_Left:
		zoomStack[curZoom].scroll(-1, 0);
		refreshPixmap();
		break;
	case Qt::Key_Right:
		zoomStack[curZoom].scroll(+1, 0);
		refreshPixmap();
		break;
	case Qt::Key_Down:
		zoomStack[curZoom].scroll(0, -1);
		refreshPixmap();
		break;
	case Qt::Key_Up:
		zoomStack[curZoom].scroll(0, +1);
		refreshPixmap();
		break;
	default:
		QWidget::keyPressEvent(event);
	}
}

void Plotter::wheelEvent(QWheelEvent *event)
{
	int numDegrees = event->delta() / 8;
	int numTicks = numDegrees / 15;

	if (event->orientation() == Qt::Horizontal)
		zoomStack[curZoom].scroll(numTicks, 0);
	else
		zoomStack[curZoom].scroll(0, numTicks);

	refreshPixmap();
}

void Plotter::refreshPixmap()
{
	pixmap = QPixmap(size());
	pixmap.fill(this, 0, 0);

	QPainter painter(&pixmap);
	painter.initFrom(this);
	drawGrid(&painter);
	drawCurves(&painter);
	update();
}

void Plotter::drawGrid(QPainter *painter)
{
	QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);

	if (!rect.isValid())
		return;

	PlotSettings settings = zoomStack[curZoom];
	QPen quiteDark = palette().dark().color().light();
	QPen light = palette().light().color();

	//draw x grid and labels
	for (int i = 0; i <= settings.numXTicks; ++i) {
		int x = rect.left() + (i * (rect.width() - 1) / settings.numXTicks);
		double label = settings.minX + (i * settings.spanX() / settings.numXTicks);

		painter->setPen(quiteDark);
		painter->drawLine(x, rect.top(), x, rect.bottom());
		painter->setPen(light);
		painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
		painter->drawText(x - 50, rect.bottom() + 5, 100, 15, Qt::AlignHCenter | Qt::AlignTop, QString::number(label));
	}

	//draw unit string for x axis
	int unitXPos = rect.right() - 0.5 * rect.width() / settings.numXTicks;
	painter->drawText(unitXPos - 50, rect.bottom() + 5, 100, 15, Qt::AlignHCenter | Qt::AlignTop, d->xUnit);

	//draw y grid and labels
	for (int j = 0; j <= settings.numYTicks; ++j) {
		int y = rect.bottom() - (j * (rect.height() - 1) / settings.numYTicks);
		double label = settings.minY + (j * settings.spanY() / settings.numYTicks);

		painter->setPen(quiteDark);
		painter->drawLine(rect.left(), y, rect.right(), y);
		painter->setPen(light);
		painter->drawLine(rect.left() - 5, y, rect.left(), y);
		painter->drawText(rect.left() - Margin, y - 10, Margin - 5, 20, Qt::AlignRight | Qt::AlignVCenter, QString::number(label));
	}
	// draw unit string for y axis
	int unitYPos = rect.top() + 0.5 * rect.height() / settings.numYTicks;
	painter->drawText(rect.left() - Margin, unitYPos - 10, Margin - 5, 20, Qt::AlignRight | Qt::AlignVCenter, d->yUnit);

	painter->drawRect(rect.adjusted(0, 0, -1, -1));
}

void Plotter::drawCurves(QPainter *painter)
{
	static const QColor colorForIds[6] = {
		Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow};

	PlotSettings settings = zoomStack[curZoom];
	QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
	if (!rect.isValid())
		return;

	painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

	QMapIterator<int, QVector<QPointF> > i(curveMap);
	while (i.hasNext()) {
		i.next();

		int id = i.key();
		const QVector<QPointF> &data = i.value();
		QPolygonF polyline(data.count());

		for (int j = 0; j < data.count(); ++j) {
			double dx = data[j].x() - settings.minX;
			double dy = data[j].y() - settings.minY;
			double x = rect.left() + (dx * (rect.width() - 1) / settings.spanX());
			double y = rect.bottom() - (dy *(rect.height() - 1) / settings.spanY());
			polyline[j] = QPointF(x, y);
		}
		painter->setPen(colorForIds[uint(id) % 6]);
		painter->drawPolyline(polyline);
	}
}

QString Plotter::xUnit()
{
	return d->xUnit;
}

void Plotter::setXUnit(QString unit)
{
	d->xUnit = unit;
	update();
}

void Plotter::unsetXUnit()
{
	d->xUnit = "";
	update();
}

QString Plotter::yUnit()
{
	return d->yUnit;
}

void Plotter::setYUnit(QString unit)
{
	d->yUnit = unit;
	update();
}

void Plotter::unsetYUnit()
{
	d->yUnit = "";
	update();
}









