#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T22:08:56
#
#-------------------------------------------------

QT       += core gui
CONFIG += -std=c++17
MAKEFLAGS += CXX=g++-8 CXXFLAGS+=-std=c++17 CXXFLAGS+=-fPIC

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

GIT_VERSION = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

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
    src/delegat/LEDelegate.cpp \
    src/validator/ValidateHex.cpp \
    src/validator/ValidateRWX.cpp \
    src/validator/ValidateSize.cpp \
    src/validator/ValidateName.cpp \
    src/delegat/TypeDelegate.cpp \
    src/delegat/RegDelegate.cpp \
    src/delegat/BTypeDelegate.cpp \
    src/DataDefs.cpp \
    src/Macro.cpp \
    src/OtherShitSolver.cpp

HEADERS += \
        maingui.hpp \
    src/Data.hpp \
    src/DataRegion.hpp \
    src/DataSection.hpp \
    src/DataI.hpp \
    src/delegat/LEDelegate.hpp \
    src/validator/ValidateHex.hpp \
    src/validator/ValidateRWX.hpp \
    src/validator/ValidateSize.hpp \
    src/validator/ValidateName.hpp \
    src/delegat/TypeDelegate.hpp \
    src/delegat/RegDelegate.hpp \
    src/delegat/BTypeDelegate.hpp \
    src/DataDefs.hpp \
    ver.h \
    src/Macro.hpp \
    src/OtherShitSolver.hpp

RESOURCES += \
    res.qrc
