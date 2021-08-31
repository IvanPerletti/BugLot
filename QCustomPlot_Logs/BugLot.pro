#
#  BugLot Tool
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = BugLot
TEMPLATE = app

SOURCES += access.cpp \
    CrunchLogC_Arm.cpp \
	ISettings.cpp \
    ITimePerform.cpp \
		  main.cpp\
		   mainwindow.cpp \
		 ../qcustomplot.cpp \
	CrunchLog.cpp \
	CDecorator.cpp

HEADERS  += access.h \
    CrunchLogC_Arm.h \
	ISettings.h \
    ITimePerform.h \
		  mainwindow.h \
		 ../qcustomplot.h \
	CrunchLog.h \
	CDecorator.h

FORMS    += access.ui \
			mainwindow.ui

RESOURCES += \
	img.qrc

DISTFILES +=
