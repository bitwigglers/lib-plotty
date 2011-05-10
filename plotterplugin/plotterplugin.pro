CONFIG += designer plugi

TARGET = $$qtLibraryTarget($$TARGET)
TEMPLATE = lib

INCLUDEPATH += ../lib

qtAddLibrary(plotty)
debug{
    LIBS += -L../lib/debug/
}

release {
    LIBS += -L../lib/release/
}

QTDIR_build:DESTDIR = $$QT_BUILD_TREE/plugins/designer
INCLUDEPATH += ../
DEPENDPATH += ../
HEADERS = plotterplugin.h
SOURCES = plotterplugin.cpp
RESOURCES += plotterplugin.qrc

target.path = $$[QT_INSTALL_PLUGINS]/designer
sources.files = $$SOURCES \
    $$HEADERS \
    *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/designer/plotterplugin
INSTALLS += target \
    sources
