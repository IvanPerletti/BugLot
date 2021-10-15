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
    ilegenditemwidget.cpp \
		  main.cpp\
		   mainwindow.cpp \
		 ../qcustomplot.cpp \
	CrunchLog.cpp \
	CDecorator.cpp \
    qlegendwidgetitem.cpp

HEADERS  += access.h \
    CrunchLogC_Arm.h \
	ISettings.h \
    ITimePerform.h \
    ilegenditemwidget.h \
		  mainwindow.h \
		 ../qcustomplot.h \
	CrunchLog.h \
	CDecorator.h \
    qlegendwidgetitem.h

FORMS    += access.ui \
			mainwindow.ui

INCLUDEPATH += $$PWD/..

RESOURCES += \
	img.qrc

DISTFILES +=
