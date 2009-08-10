
#include "plotter.h"
#include "plotterplugin.h"

#include <QtPlugin>

PlotterPlugin::PlotterPlugin(QObject *parent)
        : QObject(parent)
{
    initialized = false;
}

void PlotterPlugin::initialize(QDesignerFormEditorInterface *)
{
    if (initialized)
        return;

    initialized = true;
}

bool PlotterPlugin::isInitialized() const
{
    return initialized;
}

QWidget *PlotterPlugin::createWidget(QWidget *parent)
{
	return new Plotter(parent);
}

QString PlotterPlugin::name() const
{
    return "Plotter";
}

QString PlotterPlugin::group() const
{
    return "bitwigglers.org";
}

QIcon PlotterPlugin::icon() const
{
    return QIcon();
}

QString PlotterPlugin::toolTip() const
{
    return "";
}

QString PlotterPlugin::whatsThis() const
{
    return "";
}

bool PlotterPlugin::isContainer() const
{
    return false;
}

QString PlotterPlugin::domXml() const
{
    return "<widget class=\"Plotter\" name=\"plotter\">\n"
           " <property name=\"geometry\">\n"
           "  <rect>\n"
           "   <x>0</x>\n"
           "   <y>0</y>\n"
           "   <width>400</width>\n"
           "   <height>300</height>\n"
           "  </rect>\n"
           " </property>\n"
           " <property name=\"toolTip\" >\n"
           "  <string>Battery Meter</string>\n"
           " </property>\n"
           " <property name=\"whatsThis\" >\n"
           "  <string>a plotter widget</string>\n"
           " </property>\n"
           " </widget>\n";
}

QString PlotterPlugin::includeFile() const
{
    return "plotter.h";
}

Q_EXPORT_PLUGIN2(customwidgetplugin, PlotterPlugin)
