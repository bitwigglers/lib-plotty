TARGET = plotter
TEMPLATE = app

INCLUDEPATH += ../lib

debug{
	LIBS += -L../lib/debug -lplotlib
}

release{
	LIBS += -L../lib/release -lplotlib
}

SOURCES += main.cpp
