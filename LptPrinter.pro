QT += widgets
CONFIG += c++11

SOURCES += \
    main.cpp \
    printerwidget.cpp \
    printersettingdlg.cpp \
    printerparam.cpp \
    printerhandler.cpp

HEADERS += \
    printerwidget.h \
    macrostrings.h \
    printersettingdlg.h \
    printerparam.h \
    printerhandler.h

RC_FILE = printer.rc

RESOURCES += \
    res.qrc

TRANSLATIONS = printer.ts

DISTFILES += \
    okicode.txt
