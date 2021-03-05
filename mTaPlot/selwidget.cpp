#include "selwidget.h"
#include "QGraphicsOpacityEffect"
#include <QPainter>
#include <QPalette>
#include "QDebug"

SelWidget::SelWidget(QWidget * par, bool isSpectrogram): QWidget(par)
{
    isXsel = false;
    isYsel = false;

    QPalette pallete;
    if (!isSpectrogram)
        pallete.setColor(backgroundRole(),Qt::yellow);
    else
        pallete.setColor(backgroundRole(),Qt::blue);
    setPalette(pallete);

    setAutoFillBackground(true);
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect;
    effect->setOpacity(0.25);
    setGraphicsEffect(effect);
    resize(QSize(0,0));

    QPalette palleteLine;

    if (!isSpectrogram)
        palleteLine.setBrush(QPalette::Background,QBrush(Qt::yellow,Qt::SolidPattern));
    else
        palleteLine.setBrush(QPalette::Background,QBrush(Qt::blue,Qt::SolidPattern));// rgb(255, 129, 3)255, 160, 0  QColor(255, 215, 0)

    widLeft = new QLabel(par);
    widLeft->setAutoFillBackground(true);
    widLeft->setPalette(palleteLine);
    widLeft->resize(QSize(0,0));
    widLeft->show();

    widRight = new QLabel(par);
    widRight->setAutoFillBackground(true);
    widRight->setPalette(palleteLine);
    widRight->resize(QSize(0,0));
    widRight->show();

    widBottom = new QLabel(par);
    widBottom->setAutoFillBackground(true);
    widBottom->setPalette(palleteLine);
    widBottom->resize(QSize(0,0));
    widBottom->show();

    widTop = new QLabel(par);
    widTop->setAutoFillBackground(true);
    widTop->setPalette(palleteLine);
    widTop->resize(QSize(0,0));
    widTop->show();

    widVerCent = new QLabel(par);
    widVerCent->setAutoFillBackground(true);
    widVerCent->setPalette(palleteLine);
    widVerCent->resize(QSize(0,0));
    widVerCent->show();

    widHorCent = new QLabel(par);
    widHorCent->setAutoFillBackground(true);
    widHorCent->setPalette(palleteLine);
    widHorCent->resize(QSize(0,0));
    widHorCent->show();

}

SelWidget::~SelWidget()
{
    if (widLeft)
        delete widLeft;

    if (widRight)
        delete widRight;

    if (widBottom)
        delete widBottom;

    if (widTop)
        delete widTop;

    if (widVerCent)
        delete widVerCent;

    if (widHorCent)
        delete widHorCent;

}

void SelWidget::setGeometryOwn(QRect rect)
{


    if (isXsel == false && isYsel == false)
    {
        widLeft-> setGeometry(rect.x(),rect.y(),2,rect.height());
        widRight->setGeometry(rect.x()+rect.width()-2,rect.y(),2,rect.height());
        widBottom->setGeometry(rect.x(),rect.y(),rect.width(),2);
        widTop->setGeometry(rect.x(),rect.y()+rect.height()-2,rect.width(),2);
        widVerCent->setGeometry(rect.x()+rect.width()/2,rect.y(),2,rect.height());
        widHorCent->setGeometry(rect.x(),rect.y()+rect.height()/2,rect.width(),2);
    }

    if (isXsel == true)
    {
        widLeft-> setGeometry(rect.x(),rect.y(),2,rect.height());
        widRight->setGeometry(rect.x()+rect.width()-2,rect.y(),2,rect.height());
        widBottom->setGeometry(0,0,0,0);
        widTop->setGeometry(0,0,0,0);
        widVerCent->setGeometry(rect.x()+rect.width()/2,rect.y(),2,rect.height());
        widHorCent->setGeometry(0,0,0,0);
    }

    if (isYsel == true)
    {
        widLeft-> setGeometry(0,0,0,0);
        widRight->setGeometry(0,0,0,0);
        widBottom->setGeometry(rect.x(),rect.y(),rect.width(),2);
        widTop->setGeometry(rect.x(),rect.y()+rect.height()-2,rect.width(),2);
        widVerCent->setGeometry(0,0,0,0);
        widHorCent->setGeometry(rect.x(),rect.y()+rect.height()/2,rect.width(),2);
    }
    setGeometry(rect);

}

void SelWidget::hideLines()
{
    widLeft->setGeometry(0,0,0,0);
    widRight->setGeometry(0,0,0,0);
    widBottom->setGeometry(0,0,0,0);
    widTop->setGeometry(0,0,0,0);
    widVerCent->setGeometry(0,0,0,0);
    widHorCent->setGeometry(0,0,0,0);
}

void SelWidget::resizeEvent(QResizeEvent * ev )
{
   QRect rect = geometry();

    if (isXsel == false && isYsel == false)
    {
        widLeft-> setGeometry(rect.x(),rect.y(),2,rect.height());
        widRight->setGeometry(rect.x()+rect.width()-2,rect.y(),2,rect.height());
        widBottom->setGeometry(rect.x(),rect.y(),rect.width(),2);
        widTop->setGeometry(rect.x(),rect.y()+rect.height()-2,rect.width(),2);
        widVerCent->setGeometry(rect.x()+rect.width()/2,rect.y(),2,rect.height());
        widHorCent->setGeometry(rect.x(),rect.y()+rect.height()/2,rect.width(),2);
    }

    if (isXsel == true)
    {
        widLeft-> setGeometry(rect.x(),rect.y(),2,rect.height());
        widRight->setGeometry(rect.x()+rect.width()-2,rect.y(),2,rect.height());
        widBottom->setGeometry(0,0,0,0);
        widTop->setGeometry(0,0,0,0);
        widVerCent->setGeometry(rect.x()+rect.width()/2,rect.y(),2,rect.height());
        widHorCent->setGeometry(0,0,0,0);
    }

    if (isYsel == true)
    {
        widLeft-> setGeometry(0,0,0,0);
        widRight->setGeometry(0,0,0,0);
        widBottom->setGeometry(rect.x(),rect.y(),rect.width(),2);
        widTop->setGeometry(rect.x(),rect.y()+rect.height()-2,rect.width(),2);
        widVerCent->setGeometry(0,0,0,0);
        widHorCent->setGeometry(rect.x(),rect.y()+rect.height()/2,rect.width(),2);
    }
    QWidget::resizeEvent(ev);
}



NoiseMarker::NoiseMarker(QWidget * par): QWidget(par)
{
    isXsel = false;
    isYsel = false;

    QPalette pallete;
    pallete.setColor(backgroundRole(),Qt::gray);
    setPalette(pallete);

    setAutoFillBackground(true);
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect;
    effect->setOpacity(0.5);
    setGraphicsEffect(effect);
    resize(QSize(0,0));
}

NoiseMarker::~NoiseMarker()
{

}

SignalMarker::SignalMarker(QWidget * par): QWidget(par)
{
    isXsel = false;
    isYsel = false;

    QPalette pallete;
    pallete.setColor(backgroundRole(),QColor(0, 206, 209));
    setPalette(pallete);

    setAutoFillBackground(true);
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect;
    effect->setOpacity(0.5);
    setGraphicsEffect(effect);
    resize(QSize(0,0));
}

SignalMarker::~SignalMarker()
{

}


