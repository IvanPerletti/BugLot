#ifndef CDECORATOR_H
#define CDECORATOR_H
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QApplication>
#include <QFileDialog>
#include "../../qcustomplot.h"

class CDecorator
{
	public:
	CDecorator();
	void cleanGraph(QCustomPlot *customPlot);
    bool buildGraph(QCustomPlot *customPlot, QFile *file);
	private:
	typedef enum {
		TIME                 	 = 	0  ,
		I_PID_SDCAL_STP      	 = 	1  ,
		I_PID_APPOPEN        	 = 	2  ,
		I_PID_READY          	 = 	3  ,
		I_PID_PULSE_MODE     	 = 	4  ,
		O_PID_HCF_MODE       	 = 	5  ,
		I_GEN_REQ_FL_HCF     	 = 	6  ,
		I_GEN_PREP_RAD       	 = 	7  ,
		I_GEN_COM_REQ        	 = 	8  ,
		I_GEN_READY          	 = 	9  ,
		I_GEN_REQ_RAD        	 = 	10 ,
		O_PID_CFL            	 = 	11 ,
		O_PREP_PID           	 = 	12 ,
		O_CRAD_PID           	 = 	13 ,
		I_PID_EXP_RX         	 = 	14 ,
		O_PID_DOSE_ADJ       	 = 	15 ,
		O_GEN_READY_ACQ_FL   	 = 	16 ,
		O_READY_ACQ_RAD_HCF  	 = 	17 ,
		I_GEN_EXON           	 = 	18 ,
		O_PID_EXON           	 = 	19 ,
		MC_STATUS             	 = 	20 ,
		I_CNS_PREP           	 = 	21 ,
		I_CNS_FL             	 = 	22 ,
		I_CNS_RAD            	 = 	23 ,
		O_TAB_x              	 = 	24 ,
		O_TAB_FL             	 = 	25 ,
		O_TAB_PREP           	 = 	26 ,
		O_TAB_RAD            	 = 	27 ,
		O_TAB_EN             	 = 	28 ,
		GEN_STAT             	 = 	29 ,
		DLL_GE_STAT          	 = 	30 ,
		GEN_REQ_BIT          	=	31	,
		GEN_XRAY_ON_BIT      	=	32	,
		PREPARATION_BIT_EXT  	=	33	,
		FLUORO_BIT_EXT       	=	34	,
		EXPOSURE_BIT_EXT     	=	35	,
		CONS1_PREP_HW         	=	36	,
		CONS1_RAD_HW          	=	37	,
		CONS1_FL_HW           	=	38	,
		LOGICAL_MODE            =	39	,
	} enumIO;
	QRect qrAxisDim;

    void addSignalToPlot(QVector<double> qvTime,
							QString qStrLegend,
                            QVector <QVector <double> > qvMyVect,
                            QVector<double> &qvDataArranged,
							int iDataIdx,
							QCustomPlot *customPlot);
	QVector<QString> buildLegend();
	void addGraph(QPen pen, QVector<double> qvDataArranged, QVector<double> qvTime, QString qStrLegend, QCustomPlot *customPlot);
};
extern CDecorator cDecorator;
#endif // CDECORATOR_H
