#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T22:08:56
#
#-------------------------------------------------

QT       += core gui
CONFIG += -std=c++17
MAKEFLAGS += CXX=g++-8 CXXFLAGS+=-std=c++17 CXXFLAGS+=-fPIC

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zlR
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        maingui.cpp \
    src/Data.cpp \
    src/DataRegion.cpp \
    src/DataSection.cpp \
    src/DataI.cpp \
    src/delegat/LEDelegate.cpp

HEADERS += \
        maingui.hpp \
    src/Data.hpp \
    src/DataRegion.hpp \
    src/DataSection.hpp \
    src/DataI.hpp \
    src/delegat/LEDelegate.hpp
