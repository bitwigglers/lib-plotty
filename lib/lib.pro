TARGET = plotty
TEMPLATE = lib
SOURCES += plotter.cpp \
    plotsettings.cpp \
    plotcurve.cpp \
    clipper.cpp
HEADERS += plotter.h \
    plotter_p.h \
    plotsettings.h \
    plotcurve.h \
    plotcurve_p.h \
    clipper.h

RESOURCES += plotter.qrc
