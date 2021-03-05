#ifndef MPLOT_H
#define MPLOT_H
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include "selwidget.h"
#include <QResizeEvent>
#include "qwtchartzoom.h"
#include "qwheelzoomsvc.h"
#include "qaxiszoomsvc.h"
#include "qwt_matrix_raster_data.h"
#include <qwt_plot_spectrogram.h>
//#include <qwt_double_range.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include "limits"
#include "qwt_plot_panner.h"
#include "qwt_series_data.h"
#include "qwt_plot_shapeitem.h"

class QwtPlotCurve;
class QwtPlotMarker;
class QwtChartZoom;
class QWheelZoomSvc;
class QAxisZoomSvc;
class QwtPlotPicker;

enum CurvesNames
{
    blueFilled     = 0,
    purpleFilled   = 1,
    redLine        = 2,
    greenLine      = 3,
    yellowLine     = 4,
    magentaLine    = 5,
    cyanLine       = 6,
    whiteLine      = 7,
    blueLine       = 8,
    grayLine       = 9,
    blackLine      = 10,
    greenDots      = 11,
    yellowDots     = 12,
    redDots        = 13,
    yellowDotLine  = 14,
    redDotLine     = 15,
    greenDotLine   = 16,
    darkGrayPoints = 17,
    grayPoints     = 18,
    whitePoints    = 19,

    redSticks      = 20,
    yellowSticks   = 21,
    greenSticks    = 22
};


#include <qwt_color_map.h>
//class ColorMap: public QwtLinearColorMap
//{
//public:
//    ColorMap():
//        QwtLinearColorMap( Qt::white, Qt::darkBlue )
//    {

//        addColorStop( 0.30, Qt::cyan );
//        addColorStop( 0.50, Qt::cyan );
//        addColorStop( 0.90, Qt::blue );
//        addColorStop( 0.95, Qt::darkBlue );
//    }
//};


class ColorMap: public QwtLinearColorMap
{
public:
    ColorMap():
        QwtLinearColorMap( Qt::darkBlue, Qt::red )
    {
        addColorStop( 0.33, Qt::blue );
        addColorStop( 0.5, Qt::cyan );
        addColorStop( 0.66, Qt::yellow );
    }
};

class SpectrogramData: public QwtMatrixRasterData
{
private:

    double m_minValue;
    double m_maxValue;

    struct structMinMax{
        double min;
        double max;
    };
    structMinMax m_RangeX;
    structMinMax m_RangeY;
    struct structXY{
        double x;
        double y;
    };
    structXY m_DataSize;
    structXY m_RealToArray;
    bool isNeedTransform;

public:
    QVector<double> matrix;

    SpectrogramData(): QwtMatrixRasterData()
    {
        m_RangeX.min = 0;
        m_RangeX.max = 1;
        m_RangeY.min = 0;
        m_RangeY.max = 1;
    }

    ~SpectrogramData()
    {

    }

    void clearData()
    {
        matrix.clear();
        setValueMatrix (matrix, 0);
    }

    double value(double x, double y) const
    {
        if (valueMatrix().isEmpty())
        {
            return -1;
        }

            int xpos = int((x - m_RangeX.min) / m_RealToArray.x);
            int ypos = int((y - m_RangeY.min) / m_RealToArray.y);
            int pos = arrPos(xpos, ypos);

        if (pos < valueMatrix().size() && pos >=0 )
            return valueMatrix()[pos];

        return 0 ;
    }

    void minMaxArrayValue(double * array, int size, double * minVal, double * maxVal)
    {
        *maxVal = std::numeric_limits<double>::max()*-1;
        *minVal = std::numeric_limits<double>::max();
        int delta = 1;
        if (size > 3000000)
            delta = size/3000000;
        for (int i = 0; i < size; i+=delta)
        {
            if (array[i] > *maxVal) *maxVal = array[i];
            if (array[i] < *minVal) *minVal = array[i];
        }
    }

    void setData(QVector<double> &matrixData, int colCnt)
    {
        matrix.resize(matrixData.size());
        memcpy(matrix.data(),matrixData.data(),sizeof(double));
        setValueMatrix (matrix, colCnt);
    }

    void setDataParams(int colCnt, double x_min, double x_max,double y_min, double y_max, bool isTransform)
    {
        if (matrix.isEmpty()       ||
            matrix.size() < colCnt ||
            x_min > x_max          ||
            y_min > y_max)
            return;

        isNeedTransform = isTransform;

        minMaxArrayValue(matrix.data(), matrix.size(), &m_minValue, &m_maxValue);

        if (!isNeedTransform)
        {
            setRangeX(x_min,x_max);
            setRangeY(y_min,y_max);
            setValueMatrix (matrix, colCnt);
            m_DataSize.y = numRows();
            m_DataSize.x = numColumns();
        }
        else
        {
            setRangeX(y_min,y_max);
            setRangeY(x_min,x_max);
            setValueMatrix (matrix, colCnt);
            m_DataSize.y = numColumns();
            m_DataSize.x = numRows();
        }


        m_RealToArray.x = (m_RangeX.max - m_RangeX.min) / (m_DataSize.x - 1);
        m_RealToArray.y = (m_RangeY.max - m_RangeY.min) / (m_DataSize.y - 1);
        setInterval( Qt::ZAxis, QwtInterval( m_minValue, m_maxValue ) );
    }

    void setRangeX(const double min, const double max)
    {
        m_RangeX.min = min;
        m_RangeX.max = max;
        setInterval( Qt::XAxis, QwtInterval( m_RangeX.min, m_RangeX.max ) );
    }

    void setRangeY(const double min, const double max)
    {
        m_RangeY.min = min;
        m_RangeY.max = max;
        setInterval( Qt::YAxis, QwtInterval( m_RangeY.min, m_RangeY.max  ) );
    }

    int arrPos(const int x, const int y) const
    {
        int pos = 0;
        if (!isNeedTransform)
            pos = x + m_DataSize.x * y;
        else
            pos = y + m_DataSize.y * x;
        return pos;

    }

};



class MPlot: public QwtPlot
{

    Q_OBJECT

public:
    MPlot(QWidget * parent);
    ~MPlot();

    void installPlot(bool isSpectorgram);

    void setSpectrogramParams(int colCnt,
                              double x_min,
                              double x_max,
                              double y_min,
                              double y_max,
                              bool isTranstform);



    void setVisibleCurve(bool ind, CurvesNames curveName);
    void clearCurve(CurvesNames curveName);
    void clearAll();
    void clearAllReplot();
    void setNoiseMarker();
    void setSignalMarker();
    void setNoiseMarker(QRect rect);
    void setSignalMarker(QRect rect, int xl, int xr);
    void setSignalMarker(float centFreq, float bandWith);
    void setSignalMarker(float centFreq, float bandWith, float begTime, float time);
    QRect getNoiseMarkerPos();
    QRect getSigMarkerPos();
    void clearSigWumMarkers();
    void selWidgetEnabled(bool indW);
    void resetZoom();
    void zoomEnabled(bool indZ);
    void clearMarker();

    QwtPlotSpectrogram * spectrogramm;
    SpectrogramData    * specData;
    QwtScaleWidget     * rightAxis;
    QwtInterval          zInterval;

    bool isSonogram;
    bool isZoom;   
    bool isSelWidget;

    QwtChartZoom  * zoom;
    QWheelZoomSvc * whlzmsvc;
    QAxisZoomSvc  * axzmsvc;
    QwtPlotPanner * d_panner;

    SelWidget    * selWind;
    NoiseMarker  * noiseMarker;
    SignalMarker * signalMarker;


    float x1;
    float x2;
    float dx;
    float xc;

    float y1;
    float y2;
    float yc;
    float dy;

    QRect rectSelW;
    QRect rectWum;
    QRect rectSig;

    //√раницы маркера шума
    double leftWum;
    double rightWum;

    //√раницы маркера сигнала
    double leftSig;
    double rightSig;

    //√раницы отображаемого графика
    double xMin;
    double xMax;
    double yMin;
    double yMax;

private:

    QwtPlotGrid * grid;

    QwtPlotCurve *blueFilledCurve;
    QwtPlotCurve *purpleFilledCurve;
    QwtPlotCurve *redLineCurve;
    QwtPlotCurve *greenLineCurve;
    QwtPlotCurve *yellowLineCurve;
    QwtPlotCurve *magentaLineCurve;
    QwtPlotCurve *cyanLineCurve;
    QwtPlotCurve *whiteLineCurve;
    QwtPlotCurve *blueLineCurve;
    QwtPlotCurve *grayLineCurve;
    QwtPlotCurve *blackLineCurve;
    QwtPlotCurve *greenDotsCurve;
    QwtPlotCurve *yellowDotsCurve;
    QwtPlotCurve *redDotsCurve;
    QwtPlotCurve *yellowDotLineCurve;
    QwtPlotCurve *redDotLineCurve;
    QwtPlotCurve *greenDotLineCurve;
    QwtPlotCurve *darkGrayPointsCurve;
    QwtPlotCurve *grayPointsCurve;
    QwtPlotCurve *whitePointsCurve;

    QwtPlotCurve *redSticksCurve;
    QwtPlotCurve *yellowSticksCurve;
    QwtPlotCurve *greenSticksCurve;

protected:
    void resizeEvent(QResizeEvent * ev);

public slots:

    void showDataQV64f(const QVector<double> &xSamples,
                       const QVector<double> &ySamples,
                       CurvesNames curveName);
    void showDataQV32f(const QVector<float> &time,
                       const QVector<float> &values,
                       CurvesNames    curveName);

    void showData( const double *xData,
                   const double *yData,
                   int size,
                   CurvesNames curveName);

    void showDataOneQV32(QVector<float> &vector,
                         CurvesNames    curveName);
    void showData32f_2os(const float *xData,
                     const float *yData,
                         unsigned int size,
                     int num);
    void showData32f_1os(const float *yData,
                     int size,
                     int num);

    void showData64f_1os(double *yData,
                     int size,
                     int num);

};


#endif // MPLOT_H
