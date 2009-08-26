/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_CLIPPER_H
#define QWT_CLIPPER_H

//#include "qwt_global.h"
//#include "qwt_array.h"
//#include "qwt_polygon.h"
//#include "qwt_double_rect.h"
//#include "qwt_double_interval.h"

#include <QPolygon>
#include <QPolygonF>
#include <QRect>
#include <QRectF>

/*!
  \brief Some clipping algos
*/

class Clipper
{
public:
	static QPolygon clipPolygon(const QRect &, const QPolygon &);
	static QPolygonF clipPolygonF(const QRectF &, const QPolygonF &);
};

#endif
