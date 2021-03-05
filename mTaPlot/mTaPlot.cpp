#include "mTaPlot.h"


TaPlot::TaPlot(QWidget * par)
{

    layout = new QVBoxLayout;
    setLayout(layout);
    layout->addSpacing(0);

    plot = new MPlot(this);
    plot->show();
    plot->setMinimumHeight(50);

    splitter = new QSplitter;
    layout->addWidget(splitter);

    splitter->setOrientation(Qt::Vertical);
    setMouseTracking(true);
    plot->setMouseTracking(true);
    plot->canvas()->setMouseTracking(true);

    splitter->addWidget(plot);
    measureWidget = new QWidget;
    splitter->addWidget(measureWidget);

    measureLayout = new QHBoxLayout;
    measureWidget->setLayout(measureLayout);

    labelDTl = new QLabel;
    labelDTl->setMaximumWidth(30);
    labelDTr = new QLabel;
    labelDTr->setMaximumWidth(30);
    labelDTc = new QLabel;
    labelDTc->setMaximumWidth(30);

    labelXl = new QLabel;
    labelXl->setMaximumWidth(30);
    labelXc = new QLabel;
    labelXc->setMaximumWidth(30);
    labelXr = new QLabel;
    labelXr->setMaximumWidth(30);
    labelXd = new QLabel;
    labelXd->setMaximumWidth(30);

    labelYl = new QLabel;
    labelYl->setMaximumWidth(30);
    labelYr = new QLabel;
    labelYr->setMaximumWidth(30);
    labelYc = new QLabel;
    labelYc->setMaximumWidth(30);
    labelYd = new QLabel;
    labelYd->setMaximumWidth(30);

    editXl = new QLineEdit;
    editXl->setMaximumWidth(500);
    editXl->setReadOnly(true);
    editXr = new QLineEdit;
    editXr->setMaximumWidth(500);
    editXr->setReadOnly(true);
    editXc = new QLineEdit;
    editXc->setMaximumWidth(500);
    editXc->setReadOnly(true);
    editXd = new QLineEdit;
    editXd->setMaximumWidth(500);
    editXd->setReadOnly(true);


    editYl = new QLineEdit;
    editYl->setMaximumWidth(500);
    editYl->setReadOnly(true);
    editYr = new QLineEdit;
    editYr->setMaximumWidth(500);
    editYr->setReadOnly(true);
    editYc = new QLineEdit;
    editYc->setMaximumWidth(500);
    editYc->setReadOnly(true);
    editYd = new QLineEdit;
    editYd->setMaximumWidth(500);
    editYd->setReadOnly(true);



    dateTimeR = new QLineEdit;
    dateTimeR->setMaximumWidth(500);
    dateTimeL = new QLineEdit;
    dateTimeL->setMaximumWidth(500);
    dateTimeC = new QLineEdit;
    dateTimeC->setMaximumWidth(500);

    dateTimeR->setMinimumWidth(10);
    dateTimeL->setMinimumWidth(10);
    dateTimeC->setMinimumWidth(10);

    measureLayout->addWidget(labelXl,0,Qt::AlignRight);
    labelXl->setText("x1:");
    measureLayout->addWidget(editXl,1,Qt::AlignLeft);

    measureLayout->addWidget(labelXr,0,Qt::AlignRight);
    labelXr->setText("x2:");
    measureLayout->addWidget(editXr,1,Qt::AlignLeft);

    measureLayout->addWidget(labelXd,0,Qt::AlignRight);
    labelXd->setText("dx:");
    measureLayout->addWidget(editXd,1,Qt::AlignLeft);

    measureLayout->addWidget(labelXc,0,Qt::AlignRight);
    labelXc->setText("xc:");
    measureLayout->addWidget(editXc,1,Qt::AlignLeft);

    measureLayout->addWidget(labelYl,0,Qt::AlignRight);
    labelYl->setText("y1:");
    measureLayout->addWidget(editYl,1,Qt::AlignLeft);

    measureLayout->addWidget(labelYr,0,Qt::AlignRight);
    labelYr->setText("y2:");
    measureLayout->addWidget(editYr,1,Qt::AlignLeft);

    measureLayout->addWidget(labelYd,0,Qt::AlignRight);
    labelYd->setText("dy:");
    measureLayout->addWidget(editYd,1,Qt::AlignLeft);

    measureLayout->addWidget(labelYc,0,Qt::AlignRight);
    labelYc->setText("yc:");
    measureLayout->addWidget(editYc,1,Qt::AlignLeft);

    measureLayout->addWidget(labelDTl,0,Qt::AlignRight);
    labelDTl->setText("Beg");
    measureLayout->addWidget(dateTimeL,1,Qt::AlignLeft);

    measureLayout->addWidget(labelDTr,0,Qt::AlignRight);
    labelDTr->setText("End");
    measureLayout->addWidget(dateTimeR,1,Qt::AlignLeft);

    measureLayout->addWidget(labelDTc,0,Qt::AlignRight);
    labelDTc->setText("Int");
    measureLayout->addWidget(dateTimeC,1,Qt::AlignLeft);

//    mFilter = new MouseFilter(this);
//    installEventFilter(mFilter);
//    connect(mFilter,SIGNAL(resizedWidget()),this,SLOT(resizedSelWidget()));

    connect(plot->whlzmsvc,SIGNAL(wheeled()),this,SLOT(removeMarkersOnWheeling()));
    connect(plot->d_panner,SIGNAL(panned(int,int)),this,SLOT(removeMarkersOnWheeling(int,int)));

}


TaPlot::~TaPlot()
{

}


void TaPlot::setMeasurePanelVisible(bool isVis)
{
    QList<int> sizes1;
    sizes1.append(100);
    sizes1.append(0);

    QList<int> sizes2;
    sizes2.append(100);
    sizes2.append(20);
    if (isVis)
    {
        splitter->setSizes(sizes2);
    }
    else
    {
        splitter->setSizes(sizes1);
    }

}
void TaPlot::setDataTimeEditsVisible(bool ind)
{
    labelDTl->setVisible(ind);
    labelDTr->setVisible(ind);
    labelDTc->setVisible(ind);
    dateTimeL->setVisible(ind);
    dateTimeR->setVisible(ind);
    dateTimeC->setVisible(ind);
}

void TaPlot::setBaseDateTime(QDateTime datatime)
{
    dataTimeBase = datatime;

}

void TaPlot::paintEvent(QPaintEvent * ev)
{

    QRect currRect = ev->rect();//plot->geometry();
    if (plotRect.right() !=currRect.right() ||
        plotRect.left()  !=currRect.left() ||
        plotRect.top()   !=currRect.top() ||
        plotRect.bottom()!=currRect.bottom())
    {
        removeMarkersOnWheeling();
    }

    plotRect = plot->geometry();

}

void TaPlot::setHorWheeleng()
{
   plot->zoom->setRegim(QwtChartZoom::ctHorWheel);
   //mFilter->setCtrlFalse();
}



void TaPlot::sendSignalTimesOnClick(float time)
{

    emit sendTimesOnClick(time);
}

float TaPlot::getLeftPosOfMarker()
{
    return plot->x1;
}

float TaPlot::getRightPosOfMarker()
{
    return plot->x2;
}

float TaPlot::getDeltaXOfMarker()
{
    return plot->dx;
}

float TaPlot::getCenterXOfMarker()
{
    return plot->xc;
}


float TaPlot::getBottomPosOfMarker()
{
    return plot->y1;
}

float TaPlot::getTopPosOfMarker()
{
    return plot->y2;
}

float TaPlot::getDeltaYOfMarker()
{
    return plot->dy;
}

float TaPlot::getCenterYOfMarker()
{
    return plot->yc;
}

void TaPlot::resizedSelWidget()
{
    emit selWidgetResized();
}

void TaPlot::removeMarkersOnWheeling()
{
    plot->rectSelW.setTop(plot->transform(QwtPlot::yLeft,plot->y2));
    plot->rectSelW.setBottom(plot->transform(QwtPlot::yLeft,plot->y1));
    plot->rectSelW.setLeft(plot->transform(QwtPlot::xBottom,plot->x1));
    plot->rectSelW.setRight(plot->transform(QwtPlot::xBottom,plot->x2));
    plot->selWind->setGeometryOwn(plot->rectSelW);

    plot->rectSig.setLeft(plot->transform(QwtPlot::xBottom,plot->leftSig));
    plot->rectSig.setRight(plot->transform(QwtPlot::xBottom,plot->rightSig));
    plot->rectSig.setBottom(plot->geometry().height());
    plot->signalMarker->setGeometry(plot->rectSig);

    plot->rectWum.setLeft(plot->transform(QwtPlot::xBottom,plot->leftWum));
    plot->rectWum.setRight(plot->transform(QwtPlot::xBottom,plot->rightWum));
    plot->rectWum.setBottom(plot->geometry().height());
    plot->noiseMarker->setGeometry(plot->rectWum);

}
void TaPlot::removeMarkersOnWheeling(int,int)
{
    plot->rectSelW.setTop(plot->transform(QwtPlot::yLeft,plot->y2));
    plot->rectSelW.setBottom(plot->transform(QwtPlot::yLeft,plot->y1));
    plot->rectSelW.setLeft(plot->transform(QwtPlot::xBottom,plot->x1));
    plot->rectSelW.setRight(plot->transform(QwtPlot::xBottom,plot->x2));
    plot->selWind->setGeometryOwn(plot->rectSelW);

    plot->rectSig.setLeft(plot->transform(QwtPlot::xBottom,plot->leftSig));
    plot->rectSig.setRight(plot->transform(QwtPlot::xBottom,plot->rightSig));
    plot->rectSig.setBottom(plot->geometry().height());
    plot->signalMarker->setGeometry(plot->rectSig);

    plot->rectWum.setLeft(plot->transform(QwtPlot::xBottom,plot->leftWum));
    plot->rectWum.setRight(plot->transform(QwtPlot::xBottom,plot->rightWum));
    plot->rectWum.setBottom(plot->geometry().height());
    plot->noiseMarker->setGeometry(plot->rectWum);

}


void TaPlot::setMinWidthMode(bool ind)
{
    labelYl->setVisible(!ind);
    labelYr->setVisible(!ind);
    labelYc->setVisible(!ind);
    labelYd->setVisible(!ind);
    editYl->setVisible(!ind);
    editYr->setVisible(!ind);
    editYc->setVisible(!ind);
    editYd->setVisible(!ind);
}

void TaPlot::slotSendMarkerLimits()
{
    emit signalMarkerLimits(getLeftPosOfMarker(),getRightPosOfMarker());
}

void TaPlot::addMenu(QAction * action)
{
    if (action !=0 )
    {
        if (menuList.isEmpty())
            this->setContextMenuPolicy(Qt::ActionsContextMenu);
        menuList.append(action);
        this->addAction(action);
    }

}
/*
MouseFilter::MouseFilter(TaPlot *qp): taPlot(qp)
{
    isLeftBtnPressed = false;
    qwtp = taPlot->plot;
    ctrlPressed = false;
}

void MouseFilter::setCtrlFalse()
{
    ctrlPressed = false;
}

bool MouseFilter::eventFilter(QObject *obj, QEvent *event)
{

    if (qwtp->isSelWidget == true )
    {

        if ( event->type() == QEvent::KeyPress)
        {
            QKeyEvent *mEvent = static_cast<QKeyEvent *>(event);
            if (mEvent->key()==Qt::Key_Control)
            {
                ctrlPressed = true;
            }
        }

        if ( event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *mEvent = static_cast<QKeyEvent *>(event);
            if (mEvent->key()==Qt::Key_Control)
            {
                ctrlPressed = false;
            }
        }

        if (ctrlPressed!=true)
        {

            if ( event->type() == QEvent::MouseButtonPress   ||
                 event->type() == QEvent::MouseMove          ||
                 event->type() == QEvent::MouseButtonRelease ||
                 event->type() == QEvent::MouseButtonDblClick)
            {
                QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
                if (event->type() == QEvent::MouseButtonPress)
                    procMouseButtonPress(mEvent);             // нажата кнопка мыши
                else if (event->type() == QEvent::MouseMove)
                    procMouseMove(mEvent);                   // событие перемещения мыши
                else if (event->type() == QEvent::MouseButtonRelease)
                    procMouseButtonRelease(mEvent);         // отпущена кнопка мыши
                else if (event->type() == QEvent::MouseButtonDblClick)
                    procMouseButtonDblClick(mEvent);
            }
        }
    }

    return QObject::eventFilter(obj, event);    // передаем управление стандартному обработчику
}

// (private:) обработчик нажатия на кнопку мыши
void MouseFilter::procMouseButtonPress(QMouseEvent *mEvent)
{
    if (qwtp->isSelWidget ==true)
    {
        //taPlot->layout->geometry().x()+ taPlot->splitter->geometry().x()+
        //taPlot->layout->geometry().y()+ taPlot->splitter->geometry().y()+
        canv_x =taPlot->layout->geometry().x()+ taPlot->splitter->geometry().x()+taPlot->geometry().x()+qwtp->canvas()->geometry().x();
        canv_y =taPlot->layout->geometry().y()+ taPlot->splitter->geometry().y()+taPlot->geometry().y()+qwtp->canvas()->geometry().y();
        canv_h = qwtp->canvas()->geometry().height();
        canv_w = qwtp->canvas()->geometry().width();

        // определяем  положение курсора относительно канвы QwtPlot в момент начала выделения
        scp_x = mEvent->pos().x() - canv_x;
        scp_y = mEvent->pos().y() - canv_y;
        // определяем  положение курсора относительно MPlot в момент начала выделения
        spp_x = mEvent->pos().x();
        spp_y = mEvent->pos().y();

        if (scp_x >= 0 &&
            scp_x <= canv_w &&
            scp_y >= 0 &&
            scp_y <= canv_h &&
            mEvent -> button() == Qt::LeftButton)
        {
            QRect rectSelWid;
            qwtp->selWind->setGeometryOwn(rectSelWid);
            isLeftBtnPressed = true;
            qwtp->selWind->setVisible(true);
            if (qwtp->selWind->isXsel==true && qwtp->selWind->isYsel==false)
            {
                qwtp->selWind->move(QPoint(scp_x,0));
                //qwtp->selWind->resize(QSize(1,canv_h));
            }
            if (qwtp->selWind->isXsel==false && qwtp->selWind->isYsel==true)
            {
                qwtp->selWind->move(QPoint(0,scp_y));
                //qwtp->selWind->resize(QSize(canv_w,1));
            }
            if (qwtp->selWind->isXsel==false && qwtp->selWind->isYsel==false)
            {
                qwtp->selWind->move(QPoint(scp_x,scp_y));
                //qwtp->selWind->resize(QSize(1,1));
            }


            int l_pos,r_pos,c_pos, top_pos, bottom_pos, cup_pos;
            l_pos = qwtp->selWind->geometry().x();
            r_pos = qwtp->selWind->geometry().width()+l_pos;
            c_pos = (l_pos+r_pos)/2;
            top_pos = qwtp->selWind->geometry().y();
            bottom_pos = qwtp->selWind->geometry().height()+top_pos;
            cup_pos = (top_pos+bottom_pos)/2;

            QString str;
            float x1,x2,dx,xc,y1,y2,yc,dy;
            x1=qwtp->invTransform(QwtPlot::xBottom,l_pos);
            x2=qwtp->invTransform(QwtPlot::xBottom,r_pos);
            xc=qwtp->invTransform(QwtPlot::xBottom,c_pos);
            y2=qwtp->invTransform(QwtPlot::yLeft,top_pos);
            y1=qwtp->invTransform(QwtPlot::yLeft,bottom_pos);
            yc=qwtp->invTransform(QwtPlot::yLeft,cup_pos);
            dy=y2-y1;
            dx=x2-x1;
            qwtp->x1 = x1;
            qwtp->x2 = x2;
            qwtp->xc = xc;
            qwtp->dx = dx;
            qwtp->y1 = y1;
            qwtp->y2 = y2;
            qwtp->yc = yc;
            qwtp->dy = dy;

            taPlot->editXl->setText((str.setNum(x1,'f',3)));
            taPlot->editXr->setText((str.setNum(x2,'f',3)));
            taPlot->editXc->setText((str.setNum(xc,'f',3)));
            taPlot->editXd->setText((str.setNum(dx,'f',3)));
            taPlot->editYl->setText((str.setNum(y1,'f',3)));
            taPlot->editYr->setText((str.setNum(y2,'f',3)));
            taPlot->editYc->setText((str.setNum(yc,'f',3)));
            taPlot->editYd->setText((str.setNum(dy,'f',3)));

            taPlot->dataTimeBeg = taPlot->dataTimeBase.addSecs(round(x1*3600.));
            taPlot->dataTimeEnd = taPlot->dataTimeBase.addSecs(round(x2*3600.));

            int days = (int)trunc(dx/24);
            int h =   int(dx-days*24);
            int m =   int((dx-days*24-h)*60);

            QTime time;
            time.setHMS(h,m,0,0);

            QString interv;
            interv = interv.setNum(days);
            interv = interv + " дн. ";

            interv = interv + time.toString("hh:mm");

            taPlot->dateTimeL->setText(taPlot->dataTimeBeg.toString("dd.MM.yy hh:mm"));
            taPlot->dateTimeR->setText(taPlot->dataTimeEnd.toString("dd.MM.yy hh:mm"));
            taPlot->dateTimeC->setText(interv);

            emit taPlot->sendSignalTimesOnClick(x1);
        }
        else
            isLeftBtnPressed = false;
    }
}


void MouseFilter::procMouseMove(QMouseEvent * mEvent) // перемещение мыши
{
    if (qwtp->isSelWidget == true )
    {
        curr_x = mEvent->pos().x();
        curr_y = mEvent->pos().y();
        if (isLeftBtnPressed)
        {

            QRect rectSelWid = qwtp->selWind->geometry();
            if (qwtp->selWind->isXsel==true && qwtp->selWind->isYsel==false)
            {
                if (curr_x > spp_x)
                {
                    //qwtp->selWind->resize(QSize(curr_x - spp_x,canv_h));
                    rectSelWid.setRight(rectSelWid.left()+curr_x - spp_x);
                    rectSelWid.setBottom(rectSelWid.top()+canv_h);
                }
                else
                {
                    //qwtp->selWind->move(curr_x-canv_x,0);
                    //qwtp->selWind->resize(QSize(spp_x-curr_x,canv_h));
                    rectSelWid.setLeft(curr_x-canv_x);
                    rectSelWid.setTop(0);
                    rectSelWid.setRight(rectSelWid.left()+spp_x-curr_x);
                    rectSelWid.setBottom(rectSelWid.top()+canv_h);
                }
            }
            if (qwtp->selWind->isXsel==false && qwtp->selWind->isYsel==true)
            {
                if (curr_y > spp_y)
                {
                    //qwtp->selWind->resize(QSize(canv_w,curr_y - spp_y));
                    rectSelWid.setRight(rectSelWid.left()+canv_w);
                    rectSelWid.setBottom(rectSelWid.top()+curr_y - spp_y);
                }
                else
                {
                    //                    qwtp->selWind->move(0,curr_y-canv_y);
                    //                    qwtp->selWind->resize(QSize(canv_w,spp_y-curr_y));

                    rectSelWid.setLeft(0);
                    rectSelWid.setTop(curr_y-canv_y);
                    rectSelWid.setRight(rectSelWid.left()+canv_w);
                    rectSelWid.setBottom(rectSelWid.top()+spp_y-curr_y);
                }
            }
            if (qwtp->selWind->isXsel==false && qwtp->selWind->isYsel==false)
            {
                if (curr_x > spp_x && curr_y > spp_y)
                {
                    //                    qwtp->selWind->move(QPoint(scp_x,scp_y));
                    //                    qwtp->selWind->resize(QSize(curr_x - spp_x,curr_y - spp_y));

                    rectSelWid.setLeft(scp_x);
                    rectSelWid.setTop(scp_y);
                    rectSelWid.setRight(rectSelWid.left()+curr_x - spp_x);
                    rectSelWid.setBottom(rectSelWid.top()+curr_y - spp_y);

                }

                if (curr_x < spp_x && curr_y > spp_y)
                {
                    //                    qwtp->selWind->move(curr_x-canv_x,scp_y);
                    //                    qwtp->selWind->resize(QSize(spp_x-curr_x,curr_y-spp_y));

                    rectSelWid.setLeft(curr_x-canv_x);
                    rectSelWid.setTop(scp_y);
                    rectSelWid.setRight(rectSelWid.left()+spp_x-curr_x);
                    rectSelWid.setBottom(rectSelWid.top()+curr_y-spp_y);
                }

                if (curr_x > spp_x && curr_y < spp_y)
                {
                    //                    qwtp->selWind->move(spp_x-canv_x,curr_y-canv_y);
                    //                    qwtp->selWind->resize(QSize(curr_x-spp_x,spp_y-curr_y));

                    rectSelWid.setLeft(spp_x-canv_x);
                    rectSelWid.setTop(curr_y-canv_y);
                    rectSelWid.setRight(rectSelWid.left()+curr_x-spp_x);
                    rectSelWid.setBottom(rectSelWid.top()+spp_y-curr_y);
                }

                if (curr_x < spp_x && curr_y < spp_y)
                {

                    //                    qwtp->selWind->move(curr_x-canv_x,curr_y-canv_y);
                    //                    qwtp->selWind->resize(QSize(spp_x-curr_x,spp_y-curr_y));

                    rectSelWid.setLeft(curr_x-canv_x);
                    rectSelWid.setTop(curr_y-canv_y);
                    rectSelWid.setRight(rectSelWid.left()+spp_x-curr_x);
                    rectSelWid.setBottom(rectSelWid.top()+spp_y-curr_y);

                }
            }

            if (rectSelWid.height() < 10 && rectSelWid.width() < 10)
            {
                rectSelWid.setWidth(0);
                rectSelWid.setHeight(0);
            }

            qwtp->selWind->setGeometryOwn(rectSelWid);

            int l_pos,r_pos,c_pos, top_pos, bottom_pos, cup_pos;
            l_pos = qwtp->selWind->geometry().x();
            r_pos = qwtp->selWind->geometry().width()+l_pos;
            c_pos = (l_pos+r_pos)/2;
            top_pos = qwtp->selWind->geometry().y();
            bottom_pos = qwtp->selWind->geometry().height()+top_pos;
            cup_pos = (top_pos+bottom_pos)/2;

            QString str;
            float x1,x2,dx,xc,y1,y2,yc,dy;
            x1=qwtp->invTransform(QwtPlot::xBottom,l_pos);
            x2=qwtp->invTransform(QwtPlot::xBottom,r_pos);
            xc=qwtp->invTransform(QwtPlot::xBottom,c_pos);
            y2=qwtp->invTransform(QwtPlot::yLeft,top_pos);
            y1=qwtp->invTransform(QwtPlot::yLeft,bottom_pos);
            yc=qwtp->invTransform(QwtPlot::yLeft,cup_pos);
            dy=y2-y1;
            dx=x2-x1;
            qwtp->x1 = x1;
            qwtp->x2 = x2;
            qwtp->xc = xc;
            qwtp->dx = dx;
            qwtp->y1 = y1;
            qwtp->y2 = y2;
            qwtp->yc = yc;
            qwtp->dy = dy;

            taPlot->editXl->setText((str.setNum(x1,'f',3)));
            taPlot->editXr->setText((str.setNum(x2,'f',3)));
            taPlot->editXc->setText((str.setNum(xc,'f',3)));
            taPlot->editXd->setText((str.setNum(dx,'f',3)));
            taPlot->editYl->setText((str.setNum(y1,'f',3)));
            taPlot->editYr->setText((str.setNum(y2,'f',3)));
            taPlot->editYc->setText((str.setNum(yc,'f',3)));
            taPlot->editYd->setText((str.setNum(dy,'f',3)));

            taPlot->dataTimeBeg = taPlot->dataTimeBase.addSecs(round(x1*3600.));
            taPlot->dataTimeEnd = taPlot->dataTimeBase.addSecs(round(x2*3600.));

            int days = (int)trunc(dx/24);
            int h =   int(dx-days*24);
            int m =   int((dx-days*24-h)*60);

            QTime time;
            time.setHMS(h,m,0,0);

            QString interv;
            interv = interv.setNum(days);
            interv = interv + " дн. ";

            interv = interv + time.toString("hh:mm");

            taPlot->dateTimeL->setText(taPlot->dataTimeBeg.toString("dd.MM.yy hh:mm"));
            taPlot->dateTimeR->setText(taPlot->dataTimeEnd.toString("dd.MM.yy hh:mm"));
            taPlot->dateTimeC->setText(interv);

            //emit taPlot->sendSignalTimesOnClick(x1);

            emit resizedWidget();
        }
    }
}

void MouseFilter::procMouseButtonRelease(QMouseEvent *) // отпускание кнопки мыши
{
    isLeftBtnPressed = false;
}

void MouseFilter::procMouseButtonDblClick(QMouseEvent *)
{
    qwtp->resetZoom();
    qwtp->selWind->setGeometry(0,0,0,0);
}
*/
