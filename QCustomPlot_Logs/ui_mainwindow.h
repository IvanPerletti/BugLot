/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *LoadFile;
    QLabel *qlFileName;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *SaveButton;
    QLabel *SaveLabel;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButtonProcess;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *PulisciButton;
    QLabel *qlTestoFinito;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_15;
    QTextEdit *textEdit;
    QSpacerItem *horizontalSpacer_2;
    QPlainTextEdit *FinishTextEdit;
    QLabel *label;
    QWidget *tab_1;
    QHBoxLayout *horizontalLayout_14;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_12;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QSlider *hsInfInterval;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_9;
    QSlider *hsSupInterval;
    QPushButton *pushButtonZoom;
    QCustomPlot *customPlot;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditInterval;
    QLabel *label_3;
    QLineEdit *lineEditMin;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonZoomRange;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_2;
    QTimeEdit *timeEdit;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButtonZoomLeft;
    QPushButton *pushButtonZoomMeno;
    QPushButton *pushButtonZoomPiu;
    QPushButton *pushButtonZoomRight;
    QLabel *label_time;
    QPushButton *pushButtonDiretta;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QDial *dial;
    QLCDNumber *lcdNumber;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(846, 638);
        MainWindow->setStyleSheet(QLatin1String("QLabel{\n"
"font: 11pt;\n"
"}\n"
"\n"
"QToolTip\n"
"{\n"
"     border: 1px solid black;\n"
"     background-color: #ffa02f;\n"
"     padding: 1px;\n"
"     border-radius: 3px;\n"
"     opacity: 100;\n"
"}\n"
"\n"
"QWidget\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QWidget:item:hover\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:item:selected\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QMenuBar::item\n"
"{\n"
"    background: transparent;\n"
"}\n"
"\n"
"QMenuBar::item:selected\n"
"{\n"
"    background: transparent;\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QMenuBar::item:pressed\n"
"{\n"
"    background: #444;\n"
"    border: 1px solid #000;\n"
"    background-color: QLinearGradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:1 #212121,\n"
"        stop"
                        ":0.4 #343434/*,\n"
"        stop:0.2 #343434,\n"
"        stop:0.1 #ffaa00*/\n"
"    );\n"
"    margin-bottom:-1px;\n"
"    padding-bottom:1px;\n"
"}\n"
"\n"
"QMenu\n"
"{\n"
"    border: 1px solid #000;\n"
"}\n"
"\n"
"QMenu::item\n"
"{\n"
"    padding: 2px 20px 2px 20px;\n"
"font-size: 12px;\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:disabled\n"
"{\n"
"    color: #404040;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QAbstractItemView\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0.1 #646464, stop: 1 #5d5d5d);\n"
"}\n"
"\n"
"QWidget:focus\n"
"{\n"
"    /*border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);*/\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0 #646464, stop: 1 #5d5d5d);\n"
"    padding: 1px;\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radiu"
                        "s: 3px;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 3px;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"    selection-background-color: #ffaa00;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QComboBox:hover,QPushButton:ho"
                        "ver\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"\n"
"QComboBox:on\n"
"{\n"
"    padding-top: 3px;\n"
"    padding-left: 4px;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"    selection-background-color: #ffaa00;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView\n"
"{\n"
"    border: 2px solid darkgray;\n"
"    selection-background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QComboBox::drop-down\n"
"{\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"\n"
"     border-left-width: 0px;\n"
"     border-left-color: darkgray;\n"
"     border-left-style: solid; /* just a single line */\n"
"     border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"     border-bottom-right-radius: 3px;\n"
" }\n"
"\n"
""
                        "QComboBox::down-arrow\n"
"{\n"
"     image: url(:/down_arrow.png);\n"
"}\n"
"\n"
"QGroupBox:focus\n"
"{\n"
"border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QTextEdit:focus\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"     border: 1px solid #222222;\n"
"     background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"     height: 7px;\n"
"     margin: 0px 16px 0 16px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #f"
                        "fa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"      subcontrol-position: right;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"      width: 7px;\n"
"      margin: 16px 0 16px 0;\n"
"      border: 1px solid #222222;\n"
"}\n"
"\n"
"QScr"
                        "ollBar::handle:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      height: 14px;\n"
"      subcontrol-position: bottom;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7801a, stop: 1 #ffa02f);\n"
"      height: 14px;\n"
"      subcontrol-position: top;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      backg"
                        "round: white;\n"
"}\n"
"\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QPlainTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QHeaderView::section\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050, stop: 0.6 #434343, stop:1 #656565);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"}\n"
"\n"
"QCheckBox:disabled\n"
"{\n"
"color: #414141;\n"
"}\n"
"\n"
"QDockWidget::title\n"
"{\n"
"    text-align: center;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button, QDockWidget::float-button\n"
"{\n"
"    text-align: center;\n"
"    spacing: 1px; /* spacing between items in the tool bar */\n"
"    backgrou"
                        "nd-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button:hover, QDockWidget::float-button:hover\n"
"{\n"
"    background: #242424;\n"
"}\n"
"\n"
"QDockWidget::close-button:pressed, QDockWidget::float-button:pressed\n"
"{\n"
"    padding: 1px -1px -1px 1px;\n"
"}\n"
"\n"
"QMainWindow::separator\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #4c4c4c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QMainWindow::separator:hover\n"
"{\n"
"\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QToolBar::handl"
                        "e\n"
"{\n"
"     spacing: 3px; /* spacing between items in the tool bar */\n"
"     background: url(:/images/handle.png);\n"
"}\n"
"\n"
"QMenu::separator\n"
"{\n"
"    height: 2px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    margin-left: 10px;\n"
"    margin-right: 5px;\n"
"}\n"
"\n"
"QProgressBar\n"
"{\n"
"    border: 2px solid grey;\n"
"    border-radius: 3px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk\n"
"{\n"
"    background-color: #d7801a;\n"
"    width: 2.15px;\n"
"    margin: 0.5px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    color: #b1b1b1;\n"
"    border: 1px solid #444;\n"
"    border-bottom-style: none;\n"
"    background-color: #323232;\n"
"    padding-left: 10px;\n"
"    padding-right: 10px;\n"
"    padding-top: 3px;\n"
"    padding-bottom: 2px;\n"
"    margin-right: -1px;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #444"
                        ";\n"
"    top: 1px;\n"
"}\n"
"\n"
"QTabBar::tab:last\n"
"{\n"
"    margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"    border-top-right-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:first:!selected\n"
"{\n"
" margin-left: 0px; /* the last selected tab has nothing to overlap with on the right */\n"
"\n"
"\n"
"    border-top-left-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected\n"
"{\n"
"    color: #b1b1b1;\n"
"    border-bottom-style: solid;\n"
"    margin-top: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:.4 #343434);\n"
"}\n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    margin-bottom: 0px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected:hover\n"
"{\n"
"    /*border-top: 2px solid #ffaa00;\n"
"    padding-bottom: 3px;*/\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 "
                        "#212121, stop:0.4 #343434, stop:0.2 #343434, stop:0.1 #ffaa00);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked, QRadioButton::indicator:unchecked{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked\n"
"{\n"
"    background-color: qradialgradient(\n"
"        cx: 0.5, cy: 0.5,\n"
"        fx: 0.5, fy: 0.5,\n"
"        radius: 1.0,\n"
"        stop: 0.25 #ffaa00,\n"
"        stop: 0.3 #323232\n"
"    );\n"
"}\n"
"\n"
"QTimeEdit\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 3px;\n"
"    padding: 3px;\n"
"    font-size: 14px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QTimeEdit:pressed\n"
"{\n"
"    background-color: QL"
                        "inearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    width: 9px;\n"
"    height: 9px;\n"
"}\n"
"\n"
"QRadioButton::indicator\n"
"{\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QRadioButton::indicator:hover, QCheckBox::indicator:hover\n"
"{\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    image:url(:/images/checkbox.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:disabled, QRadioButton::indicator:disabled\n"
"{\n"
"    border: 1px solid #444;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setMinimumSize(QSize(0, 600));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_7 = new QVBoxLayout(tab);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        LoadFile = new QPushButton(tab);
        LoadFile->setObjectName(QStringLiteral("LoadFile"));
        LoadFile->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_5->addWidget(LoadFile);

        qlFileName = new QLabel(tab);
        qlFileName->setObjectName(QStringLiteral("qlFileName"));
        qlFileName->setStyleSheet(QStringLiteral(""));

        horizontalLayout_5->addWidget(qlFileName);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        SaveButton = new QPushButton(tab);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        SaveButton->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_6->addWidget(SaveButton);

        SaveLabel = new QLabel(tab);
        SaveLabel->setObjectName(QStringLiteral("SaveLabel"));

        horizontalLayout_6->addWidget(SaveLabel);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        pushButtonProcess = new QPushButton(tab);
        pushButtonProcess->setObjectName(QStringLiteral("pushButtonProcess"));
        pushButtonProcess->setEnabled(false);
        pushButtonProcess->setMinimumSize(QSize(200, 0));
        pushButtonProcess->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_11->addWidget(pushButtonProcess);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_4);

        PulisciButton = new QPushButton(tab);
        PulisciButton->setObjectName(QStringLiteral("PulisciButton"));
        PulisciButton->setMinimumSize(QSize(200, 0));
        PulisciButton->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_11->addWidget(PulisciButton);


        verticalLayout_7->addLayout(horizontalLayout_11);

        qlTestoFinito = new QLabel(tab);
        qlTestoFinito->setObjectName(QStringLiteral("qlTestoFinito"));

        verticalLayout_7->addWidget(qlTestoFinito);

        verticalSpacer_3 = new QSpacerItem(15, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_7->addItem(verticalSpacer_3);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        horizontalLayout_15->addWidget(textEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_2);

        FinishTextEdit = new QPlainTextEdit(tab);
        FinishTextEdit->setObjectName(QStringLiteral("FinishTextEdit"));

        horizontalLayout_15->addWidget(FinishTextEdit);


        verticalLayout_7->addLayout(horizontalLayout_15);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_7->addWidget(label);

        tabWidget->addTab(tab, QString());
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        horizontalLayout_14 = new QHBoxLayout(tab_1);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        groupBox = new QGroupBox(tab_1);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(800, 300));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        hsInfInterval = new QSlider(groupBox);
        hsInfInterval->setObjectName(QStringLiteral("hsInfInterval"));
        hsInfInterval->setMaximum(100);
        hsInfInterval->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(hsInfInterval);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        hsSupInterval = new QSlider(groupBox);
        hsSupInterval->setObjectName(QStringLiteral("hsSupInterval"));
        hsSupInterval->setMaximum(100);
        hsSupInterval->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(hsSupInterval);


        verticalLayout->addLayout(horizontalLayout_9);


        horizontalLayout_10->addLayout(verticalLayout);

        pushButtonZoom = new QPushButton(groupBox);
        pushButtonZoom->setObjectName(QStringLiteral("pushButtonZoom"));
        pushButtonZoom->setMinimumSize(QSize(70, 30));

        horizontalLayout_10->addWidget(pushButtonZoom);


        verticalLayout_5->addLayout(horizontalLayout_10);


        verticalLayout_6->addLayout(verticalLayout_5);

        customPlot = new QCustomPlot(groupBox);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setMinimumSize(QSize(0, 400));

        verticalLayout_6->addWidget(customPlot);


        horizontalLayout_7->addLayout(verticalLayout_6);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(200, 0));
        groupBox_2->setMaximumSize(QSize(240, 16777215));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEditInterval = new QLineEdit(groupBox_2);
        lineEditInterval->setObjectName(QStringLiteral("lineEditInterval"));
        lineEditInterval->setMinimumSize(QSize(80, 0));
        lineEditInterval->setMaximumSize(QSize(16777215, 23));

        gridLayout_2->addWidget(lineEditInterval, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 23));
        label_3->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        lineEditMin = new QLineEdit(groupBox_2);
        lineEditMin->setObjectName(QStringLiteral("lineEditMin"));
        lineEditMin->setEnabled(true);
        lineEditMin->setMinimumSize(QSize(80, 0));
        lineEditMin->setMaximumSize(QSize(16777215, 23));

        gridLayout_2->addWidget(lineEditMin, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(16777215, 23));

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(65, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        pushButtonZoomRange = new QPushButton(groupBox_2);
        pushButtonZoomRange->setObjectName(QStringLiteral("pushButtonZoomRange"));
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        pushButtonZoomRange->setFont(font);
        pushButtonZoomRange->setStyleSheet(QLatin1String("\n"
"font: 75 12pt \"MS Shell Dlg 2\";"));

        verticalLayout_3->addWidget(pushButtonZoomRange);

        verticalSpacer_6 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_6);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        timeEdit = new QTimeEdit(groupBox_2);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setMinimumSize(QSize(150, 20));
        timeEdit->setMaximumSize(QSize(150, 20));

        verticalLayout_3->addWidget(timeEdit);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        pushButtonZoomLeft = new QPushButton(groupBox_2);
        pushButtonZoomLeft->setObjectName(QStringLiteral("pushButtonZoomLeft"));
        pushButtonZoomLeft->setMinimumSize(QSize(50, 30));

        horizontalLayout_8->addWidget(pushButtonZoomLeft);

        pushButtonZoomMeno = new QPushButton(groupBox_2);
        pushButtonZoomMeno->setObjectName(QStringLiteral("pushButtonZoomMeno"));
        pushButtonZoomMeno->setMinimumSize(QSize(40, 30));
        pushButtonZoomMeno->setStyleSheet(QStringLiteral("font: 75 11pt \"MS Shell Dlg 2\";"));

        horizontalLayout_8->addWidget(pushButtonZoomMeno);

        pushButtonZoomPiu = new QPushButton(groupBox_2);
        pushButtonZoomPiu->setObjectName(QStringLiteral("pushButtonZoomPiu"));
        pushButtonZoomPiu->setMinimumSize(QSize(40, 30));
        pushButtonZoomPiu->setStyleSheet(QStringLiteral("font: 75 11pt \"MS Shell Dlg 2\";"));

        horizontalLayout_8->addWidget(pushButtonZoomPiu);

        pushButtonZoomRight = new QPushButton(groupBox_2);
        pushButtonZoomRight->setObjectName(QStringLiteral("pushButtonZoomRight"));
        pushButtonZoomRight->setMinimumSize(QSize(50, 30));

        horizontalLayout_8->addWidget(pushButtonZoomRight);


        verticalLayout_3->addLayout(horizontalLayout_8);

        label_time = new QLabel(groupBox_2);
        label_time->setObjectName(QStringLiteral("label_time"));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_time->setFont(font1);

        verticalLayout_3->addWidget(label_time);

        pushButtonDiretta = new QPushButton(groupBox_2);
        pushButtonDiretta->setObjectName(QStringLiteral("pushButtonDiretta"));

        verticalLayout_3->addWidget(pushButtonDiretta);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        dial = new QDial(groupBox_2);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setEnabled(true);
        dial->setMinimumSize(QSize(100, 100));
        dial->setMaximumSize(QSize(100, 100));
        dial->setToolTipDuration(-1);
        dial->setMinimum(-100);
        dial->setMaximum(100);
        dial->setSingleStep(40);
        dial->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(dial);

        lcdNumber = new QLCDNumber(groupBox_2);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setMaximumSize(QSize(80, 40));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setFrameShadow(QFrame::Raised);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout->addWidget(lcdNumber);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_7->addWidget(groupBox_2);


        horizontalLayout_12->addWidget(groupBox);


        horizontalLayout_13->addLayout(horizontalLayout_12);


        horizontalLayout_14->addLayout(horizontalLayout_13);

        tabWidget->addTab(tab_1, QString());

        verticalLayout_4->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QCustomPlot plot examples", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        LoadFile->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Load file to be processed</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LoadFile->setText(QApplication::translate("MainWindow", "Load file", Q_NULLPTR));
        qlFileName->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        SaveButton->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Select file to be used as output-preprocessed file</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        SaveButton->setText(QApplication::translate("MainWindow", "SaveButton", Q_NULLPTR));
        SaveLabel->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        pushButtonProcess->setText(QApplication::translate("MainWindow", "process", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        PulisciButton->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Clean current processing and start with another one</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PulisciButton->setText(QApplication::translate("MainWindow", "Clean All", Q_NULLPTR));
        qlTestoFinito->setText(QString());
#ifndef QT_NO_TOOLTIP
        textEdit->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Here will be showed preview of the Load File</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        FinishTextEdit->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Here will be showed preview of the Procesed File to be plot</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "FL Tool rev 1.0.0.1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Plot", Q_NULLPTR));
        pushButtonZoom->setText(QApplication::translate("MainWindow", "Zoom", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Tools", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEditInterval->setToolTip(QApplication::translate("MainWindow", "Interval Time [ms]", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEditInterval->setText(QApplication::translate("MainWindow", "1000", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "min Extrem", Q_NULLPTR));
        lineEditMin->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "interval", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButtonZoomRange->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Click to plot current time set</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButtonZoomRange->setText(QApplication::translate("MainWindow", "Process", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Time Edit", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        timeEdit->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Starting time HH:MM:SS to be displayed</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        timeEdit->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", Q_NULLPTR));
        pushButtonZoomLeft->setText(QApplication::translate("MainWindow", "<<", Q_NULLPTR));
        pushButtonZoomMeno->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        pushButtonZoomPiu->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        pushButtonZoomRight->setText(QApplication::translate("MainWindow", ">>", Q_NULLPTR));
        label_time->setText(QString());
        pushButtonDiretta->setText(QApplication::translate("MainWindow", "ON AIR", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "Graph", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
