#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qmath.h>
#include "mplot.h"
#include "selwidget.h"
#include <QEvent>
#include "qwtchartzoom.h"
#include "qwheelzoomsvc.h"
#include "qaxiszoomsvc.h"
#include <QFont>
#include "qwt_text_label.h"
#include "qwt_plot_picker.h"
#include "qwt_picker.h"
#include "QDebug"


MPlot::MPlot(QWidget *parent):
    QwtPlot(parent)
{
    setAutoReplot(false);

    QFont font;
    font.setFamily("Times");
    font.setPointSize(8);
    setAxisFont(QwtPlot::yLeft,font);
    setAxisFont(QwtPlot::xBottom,font);

    canvas()->setCursor(Qt::ArrowCursor);
    isZoom = false;
    isSelWidget = false;
    setAutoReplot(true);

    // ¬ключить возможность перемещени¤ по графику
    d_panner = new QwtPlotPanner(canvas());
    //  лавиша, активирующа¤ перемещение
    d_panner->setMouseButton(Qt::LeftButton,Qt::ControlModifier);



    zoom = new QwtChartZoom(this);
    zoom->setRubberBandColor(Qt::cyan);
    zoom->isZoom = false;

    whlzmsvc = new QWheelZoomSvc();
    whlzmsvc->attach(zoom);
    whlzmsvc->isZoom = false;

    x1=0;
    x2=0;
    dx=0;
    xc=0;

    y1=0;
    y2=0;
    yc=0;
    dy=0;

    //√раницы маркера шума
    leftWum = 0;
    rightWum = 0;

    //√раницы маркера сигнала
    leftSig = 0;
    rightSig = 0;

    axzmsvc = new QAxisZoomSvc();
    axzmsvc->attach(zoom);
    axzmsvc->isZoom = false;
}

MPlot::~MPlot()
{

    if (grid)
        delete grid;

    if (!isSonogram)
    {
        if (blueFilledCurve)
            delete blueFilledCurve;
        if (purpleFilledCurve)
            delete purpleFilledCurve;
        if (redLineCurve)
            delete redLineCurve;
        if (greenLineCurve)
            delete greenLineCurve;
        if (yellowLineCurve)
            delete yellowLineCurve;
        if (magentaLineCurve)
            delete magentaLineCurve;
        if (cyanLineCurve)
            delete cyanLineCurve;
        if (whiteLineCurve)
            delete whiteLineCurve;
        if (blueLineCurve)
            delete blueLineCurve;
        if (grayLineCurve)
            delete grayLineCurve;
        if (blackLineCurve)
            delete blackLineCurve;
        if (greenDotsCurve)
            delete greenDotsCurve;

        if (yellowDotsCurve)
            delete yellowDotsCurve;

        if (redDotsCurve)
            delete redDotsCurve;

        if (yellowDotLineCurve)
            delete yellowDotLineCurve;
        if (redDotLineCurve)
            delete redDotLineCurve;
        if (greenDotLineCurve)
            delete greenDotLineCurve;
        if (grayPointsCurve)
            delete darkGrayPointsCurve;
        if (grayPointsCurve)
            delete grayPointsCurve;
        if (whitePointsCurve)
            delete whitePointsCurve;


        if (redSticksCurve)
            delete redSticksCurve;
        if (yellowSticksCurve)
            delete yellowSticksCurve;
        if (greenSticksCurve)
            delete greenSticksCurve;
    }
    else
    {

        if (spectrogramm)
            delete spectrogramm;
    }

    if (axzmsvc)
        delete axzmsvc;
    if (whlzmsvc)
        delete whlzmsvc;
    if (zoom)
        delete zoom;

    if (selWind)
        delete selWind;
    if (noiseMarker)
        delete noiseMarker;
    if (signalMarker)
        delete signalMarker;



}

void MPlot::installPlot(bool isSpectorgram)
{
    isSonogram =isSpectorgram;
    if (!isSonogram)
    {
        setCanvasBackground(QColor(Qt::black));

        QColor c1,c2;

        blueFilledCurve = new QwtPlotCurve();
        blueFilledCurve->setStyle( QwtPlotCurve::Lines );
        c1 = Qt::cyan;
        c1.setAlpha( 100 );
        c2 = Qt::blue;
        c2.setAlpha( 200 );
        QLinearGradient gradCurvBluFilled(0, height()+height(), 0, 0);
        gradCurvBluFilled.setSpread(QGradient::PadSpread);
        gradCurvBluFilled.setColorAt(1,c1);
        gradCurvBluFilled.setColorAt(0,c2);
        blueFilledCurve->setPen(QPen(QColor(Qt::white)));
        blueFilledCurve->setYAxis(QwtPlot::yLeft);
        blueFilledCurve->setBaseline(-1000);
        blueFilledCurve->setBrush(gradCurvBluFilled);
        blueFilledCurve->attach(this);

        purpleFilledCurve = new QwtPlotCurve();
        purpleFilledCurve->setStyle( QwtPlotCurve::Lines );
        c1 = QColor(255,192,203);
        c1.setAlpha( 100 );
        c2 = QColor(160,32,240);
        c2.setAlpha( 200 );
        QLinearGradient gradCurvPurFilled(0, height()+height(), 0, 0);
        gradCurvPurFilled.setSpread(QGradient::PadSpread);
        gradCurvPurFilled.setColorAt(1,c1);
        gradCurvPurFilled.setColorAt(0,c2);
        purpleFilledCurve->setPen(QPen(QColor(Qt::white)));
        purpleFilledCurve->setYAxis(QwtPlot::yLeft);
        purpleFilledCurve->setBaseline(-1000);
        purpleFilledCurve->setBrush(gradCurvPurFilled);
        purpleFilledCurve->attach(this);

        whiteLineCurve = new QwtPlotCurve();
        whiteLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        whiteLineCurve->setPen(QPen(Qt::white));
        whiteLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        whiteLineCurve->setYAxis(QwtPlot::yLeft);
        whiteLineCurve->attach(this);

        redLineCurve = new QwtPlotCurve();
        redLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        redLineCurve->setPen(QPen(Qt::red));
        redLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        redLineCurve->setYAxis(QwtPlot::yLeft);
        redLineCurve->attach(this);

        greenLineCurve = new QwtPlotCurve();
        greenLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        greenLineCurve->setPen(QPen(Qt::green));
        greenLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        greenLineCurve->setYAxis(QwtPlot::yLeft);
        greenLineCurve->attach(this);

        yellowLineCurve = new QwtPlotCurve();
        yellowLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        yellowLineCurve->setPen(QPen(Qt::yellow));
        yellowLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        yellowLineCurve->setYAxis(QwtPlot::yLeft);
        yellowLineCurve->attach(this);

        magentaLineCurve = new QwtPlotCurve();
        magentaLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        magentaLineCurve->setPen(QPen(Qt::magenta));
        magentaLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        magentaLineCurve->setYAxis(QwtPlot::yLeft);
        magentaLineCurve->attach(this);

        cyanLineCurve = new QwtPlotCurve();
        cyanLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        cyanLineCurve->setPen(QPen(Qt::cyan));
        cyanLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        cyanLineCurve->setYAxis(QwtPlot::yLeft);
        cyanLineCurve->attach(this);


        blueLineCurve = new QwtPlotCurve();
        blueLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        blueLineCurve->setPen(QPen(Qt::blue));
        blueLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        blueLineCurve->setYAxis(QwtPlot::yLeft);
        blueLineCurve->attach(this);

        grayLineCurve = new QwtPlotCurve();
        grayLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        grayLineCurve->setPen(QPen(Qt::gray));
        grayLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        grayLineCurve->setYAxis(QwtPlot::yLeft);
        grayLineCurve->attach(this);


        blackLineCurve = new QwtPlotCurve();
        blackLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        blackLineCurve->setPen(QPen(Qt::black));
        blackLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        blackLineCurve->setYAxis(QwtPlot::yLeft);
        blackLineCurve->attach(this);

        greenDotsCurve = new QwtPlotCurve();
        greenDotsCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        greenDotsCurve->setPen(QPen(Qt::green,5,Qt::DotLine));
        greenDotsCurve->setStyle(QwtPlotCurve::Dots);
        greenDotsCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        greenDotsCurve->setYAxis(QwtPlot::yLeft);
        greenDotsCurve->attach(this);

        yellowDotsCurve = new QwtPlotCurve();
        yellowDotsCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        yellowDotsCurve->setPen(QPen(Qt::yellow,5,Qt::DotLine));
        yellowDotsCurve->setStyle(QwtPlotCurve::Dots);
        yellowDotsCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        yellowDotsCurve->setYAxis(QwtPlot::yLeft);
        yellowDotsCurve->attach(this);

        redDotsCurve = new QwtPlotCurve();
        redDotsCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        redDotsCurve->setPen(QPen(Qt::red,5,Qt::DotLine));
        redDotsCurve->setStyle(QwtPlotCurve::Dots);
        redDotsCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        redDotsCurve->setYAxis(QwtPlot::yLeft);
        redDotsCurve->attach(this);

        yellowDotLineCurve = new QwtPlotCurve();
        yellowDotLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        yellowDotLineCurve->setPen(QPen(Qt::yellow,0.8,Qt::DotLine));
        yellowDotLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        yellowDotLineCurve->setYAxis(QwtPlot::yLeft);
        yellowDotLineCurve->attach(this);

        redDotLineCurve = new QwtPlotCurve();
        redDotLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        redDotLineCurve->setPen(QPen(Qt::red,0.8,Qt::DotLine));
        redDotLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        redDotLineCurve->setYAxis(QwtPlot::yLeft);
        redDotLineCurve->attach(this);

        greenDotLineCurve = new QwtPlotCurve();
        greenDotLineCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        greenDotLineCurve->setPen(QPen(Qt::green,0.8,Qt::DotLine));
        greenDotLineCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
        greenDotLineCurve->setYAxis(QwtPlot::yLeft);
        greenDotLineCurve->attach(this);

        darkGrayPointsCurve = new QwtPlotCurve();
        darkGrayPointsCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        darkGrayPointsCurve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush,QPen(Qt::darkGray), QSize(1, 1) ) );
        darkGrayPointsCurve->setStyle(QwtPlotCurve::NoCurve);
        darkGrayPointsCurve->attach(this);

        grayPointsCurve = new QwtPlotCurve();
        grayPointsCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        grayPointsCurve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush,QPen(Qt::gray), QSize(1, 1) ) );
        grayPointsCurve->setStyle(QwtPlotCurve::NoCurve);
        grayPointsCurve->attach(this);

        whitePointsCurve = new QwtPlotCurve();
        whitePointsCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        whitePointsCurve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush,QPen(Qt::white), QSize(2, 2) ) );
        whitePointsCurve->setStyle(QwtPlotCurve::NoCurve);
        whitePointsCurve->attach(this);

        redSticksCurve = new QwtPlotCurve();
        redSticksCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        redSticksCurve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::red,
                                                QPen(Qt::red), QSize(5, 5) ) );
        redSticksCurve->setPen(QColor(Qt::red));
        redSticksCurve->setStyle(QwtPlotCurve::Sticks);
        redSticksCurve->attach(this);

        yellowSticksCurve = new QwtPlotCurve;
        yellowSticksCurve = new QwtPlotCurve();
        yellowSticksCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        yellowSticksCurve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::yellow,
                                                   QPen(Qt::yellow), QSize(5, 5) ) );
        yellowSticksCurve->setPen(QColor(Qt::yellow));
        yellowSticksCurve->setStyle(QwtPlotCurve::Sticks);
        yellowSticksCurve->attach(this);


        greenSticksCurve = new QwtPlotCurve;
        greenSticksCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
        greenSticksCurve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::green,
                                                  QPen(Qt::green), QSize(5, 5) ) );
        greenSticksCurve->setPen(QColor(Qt::green));
        greenSticksCurve->setStyle(QwtPlotCurve::Sticks);
        greenSticksCurve->attach(this);
        // grid
        grid = new QwtPlotGrid;
        grid->enableXMin(false);
        grid->setPen(QPen(Qt::darkGray, 0, Qt::DashLine));
        grid->attach(this);

    }
    else
    {
        specData = new SpectrogramData();
        spectrogramm = new QwtPlotSpectrogram;
        spectrogramm->setColorMap(new ColorMap);
        spectrogramm->attach(this);
        spectrogramm->setData(specData);
        setCanvasBackground(QColor(Qt::darkCyan));

        grid = new QwtPlotGrid;
        grid->enableXMin(true);
        grid->setPen(QPen(Qt::white, 0, Qt::DashLine));
        grid->attach(this);
        //        rightAxis = axisWidget(QwtPlot::yRight);
        //        rightAxis->setColorBarEnabled(true);;
        //        setAxisFont(QwtPlot::yRight,font);
        //        enableAxis(QwtPlot::yRight);
    }



    //делаем доступным маркер
    selWidgetEnabled(true);
    //делаем доступным зум
    zoomEnabled(true);




}

void MPlot::setSpectrogramParams(int colCnt, double x_min, double x_max,double y_min, double y_max, bool isTranstform)
{

    specData->setDataParams(colCnt,x_min, x_max, y_min, y_max, isTranstform);
    plotLayout()->setAlignCanvasToScales(true);
    if (!isTranstform)
    {
        setAxisScale(QwtPlot::yLeft, y_min, y_max);
        setAxisScale(QwtPlot::xBottom, x_min, x_max);
        xMin = x_min;
        xMax = x_max;
        yMin = y_min;
        yMax = y_max;
    }
    else
    {
        setAxisScale(QwtPlot::yLeft, x_min, x_max);
        setAxisScale(QwtPlot::xBottom, y_min, y_max);
        xMin = x_min;
        xMax = y_max;
        yMin = x_min;
        yMax = x_max;
    }
}

void MPlot::showDataQV64f(const QVector<double> &xSamples,
                          const QVector<double> &ySamples,
                          CurvesNames curveName)
{
    if (xSamples.size()==ySamples.size() && xSamples.size()>0)
    {
        switch(curveName)
        {
            case blueFilled:
                blueFilledCurve->setSamples(xSamples, ySamples);
                xMin = blueFilledCurve->minXValue();
                xMax = blueFilledCurve->maxXValue();
                break;

            case purpleFilled:
                purpleFilledCurve->setSamples(xSamples, ySamples);
                xMin = purpleFilledCurve->minXValue();
                xMax = purpleFilledCurve->maxXValue();
                break;

            case redLine:
                redLineCurve->setSamples(xSamples, ySamples);
                xMin = redLineCurve->minXValue();
                xMax = redLineCurve->maxXValue();
                break;

            case greenLine:
                greenLineCurve->setSamples(xSamples, ySamples);
                xMin = greenLineCurve->minXValue();
                xMax = greenLineCurve->maxXValue();
                break;

            case yellowLine:
                yellowLineCurve->setSamples(xSamples, ySamples);
                xMin = yellowLineCurve->minXValue();
                xMax = yellowLineCurve->maxXValue();
                break;

            case magentaLine:
                magentaLineCurve->setSamples(xSamples, ySamples);
                xMin = magentaLineCurve->minXValue();
                xMax = magentaLineCurve->maxXValue();
                break;

            case cyanLine:
                cyanLineCurve->setSamples(xSamples, ySamples);
                xMin = cyanLineCurve->minXValue();
                xMax = cyanLineCurve->maxXValue();
                break;

            case blackLine:
                blackLineCurve->setSamples(xSamples, ySamples);
                xMin = blackLineCurve->minXValue();
                xMax = blackLineCurve->maxXValue();
                break;

            case whiteLine:
                whiteLineCurve->setSamples(xSamples, ySamples);
                xMin = whiteLineCurve->minXValue();
                xMax = whiteLineCurve->maxXValue();
                break;

            case blueLine:
                blueLineCurve->setSamples(xSamples, ySamples);
                xMin = blueLineCurve->minXValue();
                xMax = blueLineCurve->maxXValue();
                break;

            case grayLine:
                grayLineCurve->setSamples(xSamples, ySamples);
                xMin = grayLineCurve->minXValue();
                xMax = grayLineCurve->maxXValue();
                break;

            case greenDots:
                greenDotsCurve->setSamples(xSamples, ySamples);
                xMin = greenDotsCurve->minXValue();
                xMax = greenDotsCurve->maxXValue();
                break;

            case redDots:
                redDotsCurve->setSamples(xSamples, ySamples);
                xMin = redDotsCurve->minXValue();
                xMax = redDotsCurve->maxXValue();
                break;

            case yellowDots:
                yellowDotsCurve->setSamples(xSamples, ySamples);
                xMin = yellowDotsCurve->minXValue();
                xMax = yellowDotsCurve->maxXValue();
                break;

            case yellowDotLine:
                yellowDotLineCurve->setSamples(xSamples, ySamples);
                xMin = yellowDotLineCurve->minXValue();
                xMax = yellowDotLineCurve->maxXValue();
                break;

            case redDotLine:
                redDotLineCurve->setSamples(xSamples, ySamples);
                xMin = redDotLineCurve->minXValue();
                xMax = redDotLineCurve->maxXValue();
                break;

            case greenDotLine:
                greenDotLineCurve->setSamples(xSamples, ySamples);
                xMin = greenDotLineCurve->minXValue();
                xMax = greenDotLineCurve->maxXValue();
                break;

            case darkGrayPoints:
                darkGrayPointsCurve->setSamples(xSamples, ySamples);
                xMin = darkGrayPointsCurve->minXValue();
                xMax = darkGrayPointsCurve->maxXValue();
                break;

            case grayPoints:
                grayPointsCurve->setSamples(xSamples, ySamples);
                xMin = grayPointsCurve->minXValue();
                xMax = grayPointsCurve->maxXValue();
                break;

            case whitePoints:
                whitePointsCurve->setSamples(xSamples, ySamples);
                xMin = whitePointsCurve->minXValue();
                xMax = whitePointsCurve->maxXValue();
                break;

            case greenSticks:
                greenSticksCurve->setSamples(xSamples, ySamples);
                xMin = greenSticksCurve->minXValue();
                xMax = greenSticksCurve->maxXValue();
                break;

            case yellowSticks:
                yellowSticksCurve->setSamples(xSamples, ySamples);
                xMin = yellowSticksCurve->minXValue();
                xMax = yellowSticksCurve->maxXValue();
                break;

            case redSticks:
                redSticksCurve->setSamples(xSamples, ySamples);
                xMin = redSticksCurve->minXValue();
                xMax = redSticksCurve->maxXValue();


        }
        //        xMin = std::numeric_limits<double>::max();
        //        xMax = std::numeric_limits<double>::min();
        //        for ( int p_1 = 0; p_1<xSamples.size();p_1++){
        //            if (xMin > xSamples[p_1])
        //                xMin = xSamples[p_1];
        //            if (xMax < xSamples[p_1])
        //                xMax = xSamples[p_1];
        //        }
        //        xMin = xSamples[0];
        //        xMax = xSamples[xSamples.size()-1];
        //        qDebug() << "xMin " << xMin;
        //        qDebug() << "xMax " << xMax;
        setAxisScale(xBottom,xMin,xMax);

    }
}

void MPlot::showDataQV32f(const QVector<float> &xSamples,
                          const QVector<float> &ySamples,
                          CurvesNames curveName)
{    
    QVector<double> xSamples64(xSamples.size());
    QVector<double> ySamples64(ySamples.size());

    for (int i = 0; i < ySamples.size(); i++)
    {
        xSamples64[i] = xSamples[i];
        ySamples64[i] = ySamples[i];
    }
    showDataQV64f(xSamples64,ySamples64, curveName);
}

void MPlot::showData( const double *xData,
                      const double *yData,
                      int size,
                      CurvesNames curveName)
{
    if (size>0)
    {
        switch(curveName)
        {
            case blueFilled:
                blueFilledCurve->setSamples(xData, yData, size);
                xMin = blueFilledCurve->minXValue();
                xMax = blueFilledCurve->maxXValue();
                break;

            case purpleFilled:
                purpleFilledCurve->setSamples(xData, yData, size);
                xMin = purpleFilledCurve->minXValue();
                xMax = purpleFilledCurve->maxXValue();
                break;

            case redLine:
                redLineCurve->setSamples(xData, yData, size);
                xMin = redLineCurve->minXValue();
                xMax = redLineCurve->maxXValue();
                break;

            case greenLine:
                greenLineCurve->setSamples(xData, yData, size);
                xMin = greenLineCurve->minXValue();
                xMax = greenLineCurve->maxXValue();
                break;

            case yellowLine:
                yellowLineCurve->setSamples(xData, yData, size);
                xMin = yellowLineCurve->minXValue();
                xMax = yellowLineCurve->maxXValue();
                break;

            case magentaLine:
                magentaLineCurve->setSamples(xData, yData, size);
                xMin = magentaLineCurve->minXValue();
                xMax = magentaLineCurve->maxXValue();
                break;

            case cyanLine:
                cyanLineCurve->setSamples(xData, yData, size);
                xMin = cyanLineCurve->minXValue();
                xMax = cyanLineCurve->maxXValue();
                break;

            case blackLine:
                blackLineCurve->setSamples(xData, yData, size);
                xMin = blackLineCurve->minXValue();
                xMax = blackLineCurve->maxXValue();
                break;

            case whiteLine:
                whiteLineCurve->setSamples(xData, yData, size);
                xMin = whiteLineCurve->minXValue();
                xMax = whiteLineCurve->maxXValue();
                break;

            case blueLine:
                blueLineCurve->setSamples(xData, yData, size);
                xMin = blueLineCurve->minXValue();
                xMax = blueLineCurve->maxXValue();
                break;

            case grayLine:
                grayLineCurve->setSamples(xData, yData, size);
                xMin = grayLineCurve->minXValue();
                xMax = grayLineCurve->maxXValue();
                break;

            case greenDots:
                greenDotsCurve->setSamples(xData, yData, size);
                xMin = greenDotsCurve->minXValue();
                xMax = greenDotsCurve->maxXValue();
                break;


            case redDots:
                redDotsCurve->setSamples(xData, yData, size);
                xMin = redDotsCurve->minXValue();
                xMax = redDotsCurve->maxXValue();
                break;

            case yellowDots:
                yellowDotsCurve->setSamples(xData, yData, size);
                xMin = yellowDotsCurve->minXValue();
                xMax = yellowDotsCurve->maxXValue();
                break;

            case yellowDotLine:
                yellowDotLineCurve->setSamples(xData, yData, size);
                xMin = yellowDotLineCurve->minXValue();
                xMax = yellowDotLineCurve->maxXValue();
                break;

            case redDotLine:
                redDotLineCurve->setSamples(xData, yData, size);
                xMin = redDotLineCurve->minXValue();
                xMax = redDotLineCurve->maxXValue();
                break;

            case greenDotLine:
                greenDotLineCurve->setSamples(xData, yData, size);
                xMin = greenDotLineCurve->minXValue();
                xMax = greenDotLineCurve->maxXValue();
                break;

            case darkGrayPoints:
                darkGrayPointsCurve->setSamples(xData, yData, size);
                xMin = darkGrayPointsCurve->minXValue();
                xMax = darkGrayPointsCurve->maxXValue();
                break;

            case grayPoints:
                grayPointsCurve->setSamples(xData, yData, size);
                xMin = grayPointsCurve->minXValue();
                xMax = grayPointsCurve->maxXValue();
                break;

            case whitePoints:
                whitePointsCurve->setSamples(xData, yData, size);
                xMin = whitePointsCurve->minXValue();
                xMax = whitePointsCurve->maxXValue();
                break;



            case greenSticks:
                greenSticksCurve->setSamples(xData, yData, size);
                xMin = greenSticksCurve->minXValue();
                xMax = greenSticksCurve->maxXValue();
                break;

            case yellowSticks:
                yellowSticksCurve->setSamples(xData, yData, size);
                xMin = yellowSticksCurve->minXValue();
                xMax = yellowSticksCurve->maxXValue();
                break;

            case redSticks:
                redSticksCurve->setSamples(xData, yData, size);
                xMin = redSticksCurve->minXValue();
                xMax = redSticksCurve->maxXValue();


        }
        setAxisScale(xBottom,xMin,xMax);
    }
}

void MPlot::showDataOneQV32(QVector<float> &vector, CurvesNames  curveName)
{
    if (vector.size()>0)
    {
        QVector<double> times(vector.size());
        QVector<double> ampls(vector.size());
        for (int i = 0; i <  vector.size(); i++)
        {
            times[i]=i;
            ampls[i]=double(vector[i]);
        }

        showDataQV64f(times, ampls,curveName);
    }
}


void MPlot::showData32f_2os(const float *xData,
                            const float *yData,
                            unsigned int size,
                            int num)
{

    if (size>0 && xData!=nullptr && yData!=nullptr)
    {
        QVector<double> times(size);
        QVector<double> ampls(size);
        for (unsigned int i = 0; i <  size; i++)
        {
            times[i]=xData[i];
            ampls[i]=yData[i];
        }
        showDataQV64f(times, ampls,CurvesNames(num));
    }

}


void MPlot::showData32f_1os(const float *yData,
                            int size,
                            int num)
{
    if (size>0 && yData!=0)
    {
        QVector<double> times(size);
        QVector<double> ampls(size);
        for (int i = 0; i <  size; i++)
        {
            times[i]=i;
            ampls[i]=yData[i];
        }

        showDataQV64f(times, ampls,CurvesNames(num));
    }
}

void MPlot::showData64f_1os(double *yData,
                            int size,
                            int num)
{
    if (size>0 && yData!=0)
    {
        QVector<double> times(size);
        QVector<double> ampls(size);
        for (int i = 0; i <  size; i++)
        {
            times[i]=i;
            ampls[i]=yData[i];
        }

        showDataQV64f(times, ampls,CurvesNames(num));
    }
}

void MPlot::setVisibleCurve(bool ind,CurvesNames curveName)
{
    switch(curveName)
    {
        case blueFilled:
            blueFilledCurve->setVisible(ind);
            break;

        case purpleFilled:
            purpleFilledCurve->setVisible(ind);
            break;

        case redLine:
            redLineCurve->setVisible(ind);
            break;

        case greenLine:
            greenLineCurve->setVisible(ind);
            break;

        case yellowLine:
            yellowLineCurve->setVisible(ind);
            break;

        case magentaLine:
            magentaLineCurve->setVisible(ind);
            break;

        case cyanLine:
            cyanLineCurve->setVisible(ind);
            break;

        case whiteLine:
            whiteLineCurve->setVisible(ind);
            break;

        case blueLine:
            blueLineCurve->setVisible(ind);
            break;

        case grayLine:
            grayLineCurve->setVisible(ind);
            break;

        case blackLine:
            blackLineCurve->setVisible(ind);
            break;

        case greenDots:
            greenDotsCurve->setVisible(ind);
            break;

        case redDots:
            redDotsCurve->setVisible(ind);
            break;

        case yellowDots:
            yellowDotsCurve->setVisible(ind);
            break;

        case yellowDotLine:
            yellowDotLineCurve->setVisible(ind);
            break;

        case redDotLine:
            redDotLineCurve->setVisible(ind);
            break;

        case greenDotLine:
            greenDotLineCurve->setVisible(ind);
            break;

        case darkGrayPoints:
            darkGrayPointsCurve->setVisible(ind);
            break;

        case grayPoints:
            grayPointsCurve->setVisible(ind);
            break;

        case whitePoints:
            whitePointsCurve->setVisible(ind);
            break;


        case greenSticks:
            greenSticksCurve->setVisible(ind);
            break;

        case yellowSticks:
            yellowSticksCurve->setVisible(ind);
            break;

        case redSticks:
            redSticksCurve->setVisible(ind);
    }
}

void MPlot::clearCurve(CurvesNames curveName)
{
    if (!isSonogram)
    {
        QVector<double> x;
        QVector<double> y;
        switch(curveName)
        {
            case blueFilled:
                blueFilledCurve->setSamples(x,y);
                break;

            case purpleFilled:
                purpleFilledCurve->setSamples(x,y);
                break;

            case redLine:
                redLineCurve->setSamples(x,y);
                break;

            case greenLine:
                greenLineCurve->setSamples(x,y);
                break;

            case yellowLine:
                yellowLineCurve->setSamples(x,y);
                break;

            case magentaLine:
                magentaLineCurve->setSamples(x,y);
                break;

            case cyanLine:
                cyanLineCurve->setSamples(x,y);
                break;

            case whiteLine:
                whiteLineCurve->setSamples(x,y);
                break;

            case blueLine:
                blueLineCurve->setSamples(x,y);
                break;

            case grayLine:
                grayLineCurve->setSamples(x,y);
                break;

            case blackLine:
                blackLineCurve->setSamples(x,y);
                break;

            case greenDots:
                greenDotsCurve->setSamples(x,y);
                break;

            case redDots:
                redDotsCurve->setSamples(x,y);
                break;

            case yellowDots:
                yellowDotsCurve->setSamples(x,y);
                break;

            case yellowDotLine:
                yellowDotLineCurve->setSamples(x,y);
                break;

            case redDotLine:
                redDotLineCurve->setSamples(x,y);
                break;

            case greenDotLine:
                greenDotLineCurve->setSamples(x,y);
                break;

            case darkGrayPoints:
                darkGrayPointsCurve->setSamples(x,y);
                break;

            case grayPoints:
                grayPointsCurve->setSamples(x,y);
                break;

            case whitePoints:
                whitePointsCurve->setSamples(x,y);
                break;


            case greenSticks:
                greenSticksCurve->setSamples(x,y);
                break;

            case yellowSticks:
                yellowSticksCurve->setSamples(x,y);
                break;

            case redSticks:
                redSticksCurve->setSamples(x,y);
        }
    }

}

void MPlot::clearAll()
{
    if (!isSonogram)
    {
        QVector<double> x;
        QVector<double> y;
        blueFilledCurve->setSamples(x,y);
        purpleFilledCurve->setSamples(x,y);
        redLineCurve->setSamples(x,y);
        greenLineCurve->setSamples(x,y);
        yellowLineCurve->setSamples(x,y);
        magentaLineCurve->setSamples(x,y);
        cyanLineCurve->setSamples(x,y);
        whiteLineCurve->setSamples(x,y);
        blueLineCurve->setSamples(x,y);
        grayLineCurve->setSamples(x,y);
        blackLineCurve->setSamples(x,y);
        greenDotsCurve->setSamples(x,y);
        yellowDotsCurve->setSamples(x,y);
        redDotsCurve->setSamples(x,y);
        yellowDotLineCurve->setSamples(x,y);
        redDotLineCurve->setSamples(x,y);
        greenDotLineCurve->setSamples(x,y);
        darkGrayPointsCurve->setSamples(x,y);
        grayPointsCurve->setSamples(x,y);
        whitePointsCurve->setSamples(x,y);

        greenSticksCurve->setSamples(x,y);
        yellowSticksCurve->setSamples(x,y);
        redSticksCurve->setSamples(x,y);
    }
    else
    {
        specData->clearData();
    }
    if (selWind)
    {
        signalMarker->setGeometry(0,
                                  0,
                                  0,
                                  0);
        noiseMarker->setGeometry(0,
                                 0,
                                 0,
                                 0);
    }
}

void MPlot::clearAllReplot()
{
    clearAll();
    replot();
}



void MPlot::setNoiseMarker()
{
    if (selWind)
    {
        noiseMarker->isXsel = true;
        noiseMarker->setGeometry(selWind->geometry().x(),
                                 0,
                                 selWind->geometry().width(),
                                 geometry().height());
        rectWum  = noiseMarker->geometry();
        leftWum  = invTransform(QwtPlot::xBottom,rectWum.x());
        rightWum = invTransform(QwtPlot::xBottom,rectWum.x()+rectWum.width());

    }
}

void MPlot::setNoiseMarker(QRect rect)
{
    if (selWind)
    {
        noiseMarker->isXsel = true;
        noiseMarker->setGeometry(rect);
        rectWum = rect;
    }
}

void MPlot::setSignalMarker()
{
    if (selWind)
    {
        signalMarker->isXsel = true;
        signalMarker->setGeometry(selWind->geometry().x(),
                                  0,
                                  selWind->geometry().width(),
                                  geometry().height());
        rectSig = signalMarker->geometry();
        leftSig  = invTransform(QwtPlot::xBottom,rectSig.x());
        rightSig = invTransform(QwtPlot::xBottom,rectSig.x()+rectSig.width());
    }
}

void MPlot::setSignalMarker(QRect rect, int xl, int xr)
{
    if (selWind)
    {
        signalMarker->isXsel = true;
        signalMarker->setGeometry(rect);
        rectSig  = rect;
        leftSig  = xl;
        rightSig = xr;
    }
}

void MPlot::setSignalMarker(float centFreq, float bandWith)
{
    int leftXpos = transform(QwtPlot::xBottom, centFreq-bandWith/2);
    int rightXpos = transform(QwtPlot::xBottom, centFreq+bandWith/2);

    leftSig  = centFreq - bandWith/2;
    rightSig = centFreq + bandWith/2;

    rectSig.setRect(leftXpos,0,rightXpos-leftXpos,height());
    signalMarker->isXsel = true;
    signalMarker->setGeometry(rectSig);
}

void MPlot::setSignalMarker(float centFreq, float bandWith, float begTime, float time)
{
    int leftXpos = transform(QwtPlot::xBottom, centFreq-bandWith/2);
    int rightXpos = transform(QwtPlot::xBottom, centFreq+bandWith/2);
    int topPos = transform(QwtPlot::yLeft, begTime + time);
    int bottomPos = transform(QwtPlot::yLeft, begTime );

    rectSig.setRect(leftXpos,topPos,rightXpos-leftXpos,bottomPos-topPos);
    selWind->setGeometryOwn(rectSig);
}

QRect MPlot::getNoiseMarkerPos()
{
    return rectWum;
}

QRect MPlot::getSigMarkerPos()
{
    return rectSig;
}

void MPlot::clearSigWumMarkers()
{
    signalMarker->resize(0,0);
    noiseMarker->resize(0,0);
    rectWum = noiseMarker->geometry();
    leftWum = 0;
    rightWum = 0;
    rectSig = signalMarker->geometry();
    leftSig = 0;
    rightSig = 0;

}

void MPlot::selWidgetEnabled(bool indW)
{
    if (indW)
    {
        selWind = new SelWidget(canvas(),isSonogram);
        selWind->setGeometry(0,0,0,0);
        //selWind->show();

        signalMarker = new SignalMarker(canvas());
        //signalMarker->sshowData32f_2oshow();
        signalMarker->resize(0,0);

        noiseMarker = new NoiseMarker(canvas());
        //noiseMarker->show();
        noiseMarker->resize(0,0);

        isSelWidget = true;
    }
    else
    {
        if (isSelWidget == true)
        {
            selWind->setGeometry(0,0,0,0);
            noiseMarker->setGeometry(0,0,0,0);
            signalMarker->setGeometry(0,0,0,0);
            isSelWidget = false;
        }
    }
}

void MPlot::resetZoom()
{
    if (isSonogram)
    {
        setAxisScale(QwtPlot::yLeft, yMin, yMax);
        setAxisScale(QwtPlot::xBottom, xMin, xMax);
    }
    else
    {
        setAxisScale(QwtPlot::xBottom, xMin, xMax);
        setAxisAutoScale(QwtPlot::yLeft,true);
    }
    clearSigWumMarkers();

}

void MPlot::zoomEnabled(bool indZ)
{
    if (indZ)
    {
        //  zoom->isZoom = true;
        whlzmsvc->isZoom = true;
        axzmsvc->isZoom = true;
        isZoom = true;
    }
    else
    {
        // zoom->isZoom = false;
        whlzmsvc->isZoom = false;
        axzmsvc->isZoom = false;
        isZoom = false;
    }
}

void MPlot::clearMarker()
{
    selWind->setGeometry(0,0,0,0);
    selWind->resize(0,0);
    rectSelW = selWind->geometry();
    clearSigWumMarkers();
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}

void MPlot::resizeEvent(QResizeEvent * ev)
{
    QFrame::resizeEvent(ev);
    updateLayout();
    zoom->updatePlot();
}
