#
#  BugLot Tool
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = BugLot
TEMPLATE = app

SOURCES += access.cpp \
    CrunchLogC_Arm.cpp \
    Drivers/ClickableLabel.cpp \
    Drivers/IAnimationShow.cpp \
	ISettings.cpp \
    ITimePerform.cpp \
    figurewidget.cpp \
    legenditem.cpp \
		  main.cpp\
		   mainwindow.cpp \
		 ../qcustomplot.cpp \
	CrunchLog.cpp \
	CDecorator.cpp

HEADERS  += access.h \
        Drivers/ClickableLabel.h \
        Drivers/IAnimationShow.h \
        CrunchLogC_Arm.h \
	ISettings.h \
    ITimePerform.h \
    figurewidget.h \
    legenditem.h \
		  mainwindow.h \
		 ../qcustomplot.h \
	CrunchLog.h \
	CDecorator.h

FORMS    += access.ui \
			figurewidget.ui \
			legenditem.ui \
			mainwindow.ui

INCLUDEPATH += $$PWD/..

RESOURCES += \
	img.qrc

DISTFILES +=

QMAKE_CXXFLAGS += -O0
