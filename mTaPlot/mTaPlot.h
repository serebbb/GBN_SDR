#ifndef MTAPLOT_H
#define MTAPLOT_H
#include "mplot.h"
#include "QLineEdit"
#include "QGridLayout"
#include "QLabel"
#include "QSplitter"
#include <qwidget.h>
#include <QEvent>
#include <QWheelEvent>
#include "selwidget.h"
#include <QDateTime>

class TaPlot;

/*class MouseFilter : public QObject {
    Q_OBJECT
protected:
    virtual bool eventFilter(QObject*, QEvent*);

    void procMouseButtonPress(QMouseEvent *); // нажатие на кнопку мыши
    void procMouseMove(QMouseEvent *);// перемещение мыши
    void procMouseButtonRelease(QMouseEvent *);// отпускание кнопки мыши
    void procMouseButtonDblClick(QMouseEvent *);

    TaPlot * taPlot;     // указатель на объект класса MPlot (график)

    MPlot * qwtp;
    bool isLeftBtnPressed;   //индикатор нажатия левой клавиши мыши
    // положение курсора в момент начала выделения относительно канвы (в пикселах)
    int  scp_x, scp_y;
    // положение курсора в момент начала выделения относительно MPlot (в пикселах)
    int  spp_x, spp_y;
    // текущее положение курсора относительно MPlot
    int  curr_x, curr_y;
    // координаты канвы MPlot
    int  canv_x, canv_y;
    // размеры канвы MPlot
    int  canv_h, canv_w;
    bool ctrlPressed;


public:
    MouseFilter(TaPlot *qp);
    void setCtrlFalse();


signals:

    void resizedWidget();

};*/



class TaPlot : public QWidget
{

    Q_OBJECT

public:
    explicit TaPlot(QWidget * parent = 0);
    ~TaPlot();
    MPlot * plot;


    void setMeasurePanelVisible(bool ind);
    void setDataTimeEditsVisible(bool ind);
    void setBaseDateTime(QDateTime datatime);
    void addMenu(QAction * action);

    QRect plotRect;

    QLineEdit * editXl;
    QLineEdit * editXr;
    QLineEdit * editXc;
    QLineEdit * editXd;

    QLineEdit * editYl;
    QLineEdit * editYr;
    QLineEdit * editYc;
    QLineEdit * editYd;
    QSplitter * splitter;
    QVBoxLayout * layout;

    QLineEdit * dateTimeL;
    QLineEdit * dateTimeR;
    QLineEdit * dateTimeC;

    QDateTime  dataTimeBase;
    QDateTime  dataTimeBeg;
    QDateTime  dataTimeEnd;
    QDateTime  dataTimeInt;

private:

    SelWidget  * marker; //маркер выделения графиков

    QWidget     * measureWidget; //виджет, в которо размещены результаты измерений
    QHBoxLayout * measureLayout;

    QLabel * labelXl;
    QLabel * labelXr;
    QLabel * labelXc;
    QLabel * labelXd;

    QLabel * labelYl;
    QLabel * labelYr;
    QLabel * labelYc;
    QLabel * labelYd;

    QLabel * labelDTl;
    QLabel * labelDTr;
    QLabel * labelDTc;


    //MouseFilter * mFilter;



    QList <QAction *> menuList;

    void paintEvent(QPaintEvent *);




public slots:
    void  sendSignalTimesOnClick(float time);
    float getLeftPosOfMarker();
    float getRightPosOfMarker();
    float getDeltaXOfMarker();
    float getCenterXOfMarker();
    float getBottomPosOfMarker();
    float getTopPosOfMarker();
    float getDeltaYOfMarker();
    float getCenterYOfMarker();

    void resizedSelWidget();

    void removeMarkersOnWheeling();
    void removeMarkersOnWheeling(int,int);
    void setMinWidthMode(bool ind);
    void slotSendMarkerLimits();



    void setHorWheeleng();
signals:

    void selWidgetResized();
    void sendTimesOnClick(float time);
    void signalMarkerLimits(float left, float right);

};








#endif // MTAPLOT_H
