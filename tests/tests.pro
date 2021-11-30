QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    ../src/fileparser.cpp \
    ../src/translator.cpp \
    ../src/word.cpp \
    ../src/dictionary.cpp \
    ../src/outputgenerator.cpp \
    tst_fileparser.cpp \
    tst_translator.cpp \
    tst_outputgenerator.cpp

HEADERS += \
    ../src/fileparser.h \
    ../src/translator.h \
    ../src/word.h \
    ../src/dictionary.h \
    ../src/outputgenerator.h \
    tst_fileparser.h \
    tst_translator.h \
    tst_outputgenerator.h
