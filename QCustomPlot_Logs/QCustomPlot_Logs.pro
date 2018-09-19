#
#  File Logger Tool
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = FileLoggerTool
TEMPLATE = app

SOURCES += access.cpp \
		  main.cpp\
		   mainwindow.cpp \
		 ../qcustomplot.cpp \
	CrunchLog.cpp \
	CDecorator.cpp

HEADERS  += access.h \
		  mainwindow.h \
		 ../qcustomplot.h \
	CrunchLog.h \
	CDecorator.h


FORMS    += access.ui \
			mainwindow.ui

RESOURCES += \
	img.qrc

DISTFILES +=
