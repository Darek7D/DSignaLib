include(../tests.pri)

SOURCES += tst_filterfir.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release/ -ldsignal
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/debug/ -ldsignal
else:unix: LIBS += -L$$OUT_PWD/../../src/ -ldsignal

INCLUDEPATH += $$PWD/../../src/
DEPENDPATH += $$PWD/../../src/
