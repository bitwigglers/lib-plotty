TARGET = plotter
TEMPLATE = app

INCLUDEPATH += ../lib

debug{
	LIBS += -L../lib/debug -lplotty
}

release{
	LIBS += -L../lib/release -lplotty
}

SOURCES += main.cpp
