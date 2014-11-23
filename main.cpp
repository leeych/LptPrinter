#include <QApplication>
#include <QTranslator>
#include "printerwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    translator.load(":/widgets.qm");
    QTranslator custom_translator;
    custom_translator.load(":/printer.qm");
    app.installTranslator(&translator);
    app.installTranslator(&custom_translator);

    PrinterWidget widget;
    widget.show();
    return app.exec();
}
