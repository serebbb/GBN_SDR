#ifndef SPINWIDGET_H
#define SPINWIDGET_H
#pragma once
#include <QWidget>
#include "QLabel"
#include "QHBoxLayout"
#include "qmath.h"
#include <QtGui/qevent.h>
#include "QDebug"
#include "QGraphicsOpacityEffect"
#include <QPainter>
#include <QPalette>


class QPaintEvent;

class SmWidget : public QWidget
{
public:
    SmWidget(QWidget * par,QColor acolor);
protected:

};

class MLabel : public QLabel
{
    Q_OBJECT

public:
    MLabel(QWidget * par);
    ~MLabel();
    enum WidType
    {HIGTH,LOW,NONE};

   void mousePressEvent(QMouseEvent *ev);
   void setWidType(WidType wid);
   void sendUpdateFromFilter();
   void setFontTone(bool isBlack);
private:
    SmWidget * widH;
    SmWidget * widL;
    QWidget*parent;
signals:
    void sendNumUpdate(bool isSignal);

};


class SpinWidget : public QWidget
{
    Q_OBJECT

public:
    SpinWidget(QWidget * par);
    ~SpinWidget();

    void mouseMoveEvent(QMouseEvent * event);

private:
    MLabel * num10;
    QLabel * tochka9;
    MLabel * num9;
    MLabel * num8;
    MLabel * num7;
    QLabel * tochka6;
    MLabel * num6;
    MLabel * num5;
    MLabel * num4;
    QLabel * tochka3;
    MLabel * num3;
    MLabel * num2;
    MLabel * num1;
    qint64 currNumb;
    QWidget * parent;
public slots:
    bool setNumber(int number);
    int getNumber();
    void updateNumber(bool isSignal);
    void updateFontTone();
signals:
    void sendNumChanged();
};

class MouseFilter : public QObject {
protected:
    virtual bool eventFilter(QObject*, QEvent*);

public:
    MouseFilter(QObject* pobj = 0);

};




#endif // SPINWIDGET_H
