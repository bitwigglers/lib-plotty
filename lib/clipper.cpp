/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

//#include "qwt_math.h"
#include "clipper.h"

enum Edge
{
    Left,
    Top,
    Right,
    Bottom,
    NEdges
};

class PolygonClipper: public QRect
{
public:
    PolygonClipper(const QRect &r);

    QPolygon clipPolygon(const QPolygon &) const;

private:
    void clipEdge(Edge, const QPolygon &, QPolygon &) const;
    bool insideEdge(const QPoint &, Edge edge) const;
    QPoint intersectEdge(const QPoint &p1,
                         const QPoint &p2, Edge edge) const;

    void addPoint(QPolygon &, uint pos, const QPoint &point) const;
};

class PolygonClipperF: public QRectF
{
public:
    PolygonClipperF(const QRectF &r);
    QPolygonF clipPolygon(const QPolygonF &) const;

private:
    void clipEdge(Edge, const QPolygonF &, QPolygonF &) const;
    bool insideEdge(const QPointF &, Edge edge) const;
    QPointF intersectEdge(const QPointF &p1,
                          const QPointF &p2, Edge edge) const;

    void addPoint(QPolygonF &, uint pos, const QPointF &point) const;
};

PolygonClipper::PolygonClipper(const QRect &r):
    QRect(r)
{
}

inline void PolygonClipper::addPoint(
    QPolygon &pa, uint pos, const QPoint &point) const
{
    if ( uint(pa.size()) <= pos )
        pa.resize(pos + 5);

    pa.setPoint(pos, point);
}

//! Sutherland-Hodgman polygon clipping
QPolygon PolygonClipper::clipPolygon(const QPolygon &pa) const
{
    if ( contains( pa.boundingRect() ) )
        return pa;

    QPolygon cpa(pa.size());

    clipEdge((Edge)0, pa, cpa);

    for ( uint edge = 1; edge < NEdges; edge++ )
    {
        const QPolygon rpa = cpa;
        clipEdge((Edge)edge, rpa, cpa);
    }

    return cpa;
}

bool PolygonClipper::insideEdge(const QPoint &p, Edge edge) const
{
    switch(edge)
    {
    case Left:
        return p.x() > left();
    case Top:
        return p.y() > top();
    case Right:
        return p.x() < right();
    case Bottom:
        return p.y() < bottom();
    default:
        break;
    }

    return false;
}

QPoint PolygonClipper::intersectEdge(const QPoint &p1,
                                     const QPoint &p2, Edge edge ) const
{
    int x=0, y=0;
    double m = 0;

    const double dy = p2.y() - p1.y();
    const double dx = p2.x() - p1.x();

    switch ( edge )
    {
    case Left:
        x = left();
        m = double(qAbs(p1.x() - x)) / qAbs(dx);
        y = p1.y() + int(dy * m);
        break;
    case Top:
        y = top();
        m = double(qAbs(p1.y() - y)) / qAbs(dy);
        x = p1.x() + int(dx * m);
        break;
    case Right:
        x = right();
        m = double(qAbs(p1.x() - x)) / qAbs(dx);
        y = p1.y() + int(dy * m);
        break;
    case Bottom:
        y = bottom();
        m = double(qAbs(p1.y() - y)) / qAbs(dy);
        x = p1.x() + int(dx * m);
        break;
    default:
        break;
    }

    return QPoint(x,y);
}

void PolygonClipper::clipEdge(Edge edge,
                              const QPolygon &pa, QPolygon &cpa) const
{
    if ( pa.count() == 0 )
    {
        cpa.resize(0);
        return;
    }

    unsigned int count = 0;

    QPoint p1 = pa.point(0);
    if ( insideEdge(p1, edge) )
        addPoint(cpa, count++, p1);

    const uint nPoints = pa.size();
    for ( uint i = 1; i < nPoints; i++ )
    {
        const QPoint p2 = pa.point(i);
        if ( insideEdge(p2, edge) )
        {
            if ( insideEdge(p1, edge) )
                addPoint(cpa, count++, p2);
            else
            {
                addPoint(cpa, count++, intersectEdge(p1, p2, edge));
                addPoint(cpa, count++, p2);
            }
        }
        else
        {
            if ( insideEdge(p1, edge) )
                addPoint(cpa, count++, intersectEdge(p1, p2, edge));
        }
        p1 = p2;
    }
    cpa.resize(count);
}

PolygonClipperF::PolygonClipperF(const QRectF &r):
    QRectF(r)
{
}

inline void PolygonClipperF::addPoint(QPolygonF &pa, uint pos, const QPointF &point) const
{
    if ( uint(pa.size()) <= pos )
        pa.resize(pos + 5);

    pa[(int)pos] = point;
}

//! Sutherland-Hodgman polygon clipping
QPolygonF PolygonClipperF::clipPolygon(const QPolygonF &pa) const
{
    if ( contains( pa.boundingRect()) )
        return pa;

    QPolygonF cpa(pa.size());

    clipEdge((Edge)0, pa, cpa);

    for ( uint edge = 1; edge < NEdges; edge++ )
    {
        const QPolygonF rpa = cpa;
        clipEdge((Edge)edge, rpa, cpa);
    }

    return cpa;
}

bool PolygonClipperF::insideEdge(const QPointF &p, Edge edge) const
{
    switch(edge)
    {
    case Left:
        return p.x() > left();
    case Top:
        return p.y() > top();
    case Right:
        return p.x() < right();
    case Bottom:
        return p.y() < bottom();
    default:
        break;
    }

    return false;
}

QPointF PolygonClipperF::intersectEdge(const QPointF &p1,
                                       const QPointF &p2, Edge edge ) const
{
    double x=0.0, y=0.0;
    double m = 0;

    const double dy = p2.y() - p1.y();
    const double dx = p2.x() - p1.x();

    switch ( edge )
    {
    case Left:
        x = left();
        m = double(qAbs(p1.x() - x)) / qAbs(dx);
        y = p1.y() + int(dy * m);
        break;
    case Top:
        y = top();
        m = double(qAbs(p1.y() - y)) / qAbs(dy);
        x = p1.x() + int(dx * m);
        break;
    case Right:
        x = right();
        m = double(qAbs(p1.x() - x)) / qAbs(dx);
        y = p1.y() + int(dy * m);
        break;
    case Bottom:
        y = bottom();
        m = double(qAbs(p1.y() - y)) / qAbs(dy);
        x = p1.x() + int(dx * m);
        break;
    default:
        break;
    }

    return QPointF(x,y);
}

void PolygonClipperF::clipEdge(Edge edge,
                               const QPolygonF &pa, QPolygonF &cpa) const
{
    if ( pa.count() == 0 )
    {
        cpa.resize(0);
        return;
    }

    unsigned int count = 0;

    QPointF p1 = pa[0];
    if ( insideEdge(p1, edge) )
        addPoint(cpa, count++, p1);

    const uint nPoints = pa.size();
    for ( uint i = 1; i < nPoints; i++ )
    {
        const QPointF p2 = pa[(int)i];
        if ( insideEdge(p2, edge) )
        {
            if ( insideEdge(p1, edge) )
                addPoint(cpa, count++, p2);
            else
            {
                addPoint(cpa, count++, intersectEdge(p1, p2, edge));
                addPoint(cpa, count++, p2);
            }
        }
        else
        {
            if ( insideEdge(p1, edge) )
                addPoint(cpa, count++, intersectEdge(p1, p2, edge));
        }
        p1 = p2;
    }
    cpa.resize(count);
}

QPolygon Clipper::clipPolygon(
    const QRect &clipRect, const QPolygon &polygon)
{
    PolygonClipper clipper(clipRect);
    return clipper.clipPolygon(polygon);
}

QPolygonF Clipper::clipPolygonF(
    const QRectF &clipRect, const QPolygonF &polygon)
{
    PolygonClipperF clipper(clipRect);
    return clipper.clipPolygon(polygon);
}
