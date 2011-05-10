CONFIG += designer \
    plugin \
    release
TARGET = $$qtLibraryTarget($$TARGET)
TEMPLATE = lib
QTDIR_build:DESTDIR = $$QT_BUILD_TREE/plugins/designer
INCLUDEPATH += ../
DEPENDPATH += ../
HEADERS = plotter.h \
    plotsettings.h \
	plotter_p.h \
    plotterplugin.h
SOURCES = plotter.cpp \
    plotsettings.cpp \
	plotterplugin.cpp
RESOURCES += plotter.qrc \
    plotterplugin.qrc
target.path = $$[QT_INSTALL_PLUGINS]/designer
sources.files = $$SOURCES \
    $$HEADERS \
    *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/designer/plotterplugin
INSTALLS += target \
    sources
