TARGET = plotter
TEMPLATE = app

INCLUDEPATH += ../lib
qtAddLibrary(plotty)

debug{
    LIBS += -L../lib/debug/
}

release {
    LIBS += -L../lib/release/
}

SOURCES += main.cpp
