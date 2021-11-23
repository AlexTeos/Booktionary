QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_fileparser.cpp \
    ../src/fileparser.cpp \
    ../src/translator.cpp \
    main.cpp \
    tst_translator.cpp\
    ../src/word.cpp

HEADERS += \
    ../src/fileparser.h\
    ../src/translator.h\
    ../src/word.h\
    tst_fileparser.h\
    tst_translator.h
