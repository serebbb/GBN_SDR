#ifndef SELWIDGET_H
#define SELWIDGET_H
#include <QWidget>
#include <QLabel>

class QPaintEvent;

class SelWidget : public QWidget

{
//    Q_OBJECT
public:
    SelWidget(QWidget * par, bool isSpectrogram);
    ~SelWidget();
    void setGeometryOwn(QRect rect);

    bool isXsel;
    bool isYsel;
    QLabel * widLeft;
    QLabel * widRight;
    QLabel * widBottom;
    QLabel * widTop;
    QLabel * widVerCent;
    QLabel * widHorCent;

    void hideLines();

protected:

    void resizeEvent(QResizeEvent *);
};

class NoiseMarker : public QWidget

{
//    Q_OBJECT
public:
    NoiseMarker(QWidget * par);
    ~NoiseMarker();
    bool isXsel;
    bool isYsel;

protected:

};

class SignalMarker : public QWidget

{
//    Q_OBJECT
public:
    SignalMarker(QWidget * par);
    ~SignalMarker();
    bool isXsel;
    bool isYsel;

protected:

};

#endif // SELWIDGET_H
