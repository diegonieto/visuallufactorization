#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T15:07:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LU_factorization
TEMPLATE = app


SOURCES += main.cpp\
        lu_main_window.cpp

HEADERS  += lu_main_window.h \
    Matrix.hpp \
    NumericMatrix.hpp \
    Squarematrix.hpp

FORMS    += lu_main_window.ui
