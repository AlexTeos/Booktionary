QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../src/translatorcache.cpp \
    main.cpp \
    ../src/dictionarymodel.cpp \
    ../src/inputparser.cpp \
    ../src/translator.cpp \
    ../src/word.cpp \
    ../src/outputgenerator.cpp \
    tst_inputparser.cpp \
    tst_translator.cpp \
    tst_outputgenerator.cpp \
    tst_translatorcache.cpp

HEADERS += \
    ../src/dictionarymodel.h \
    ../src/inputparser.h \
    ../src/translator.h \
    ../src/translatorcache.h \
    ../src/word.h \
    ../src/outputgenerator.h \
    tst_inputparser.h \
    tst_translator.h \
    tst_outputgenerator.h \
    tst_translatorcache.h
