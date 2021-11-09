QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_fileparser.cpp \
    ../src/fileparser.cpp

HEADERS += \
    ../src/fileparser.h
