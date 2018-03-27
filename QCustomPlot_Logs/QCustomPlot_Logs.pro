#
#  QCustomPlot_Logs
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = QCustomPlot_Logs
TEMPLATE = app

SOURCES += access.cpp \
		  main.cpp\
		   mainwindow.cpp \
		 ../qcustomplot.cpp \
	CrunchLog.cpp

HEADERS  += access.h \
		  mainwindow.h \
		 ../qcustomplot.h \
	CrunchLog.h


FORMS    += access.ui \
			mainwindow.ui


