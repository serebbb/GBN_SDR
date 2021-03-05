#include "qwheelzoomsvc.h"

#ifdef Q_WS_WIN
//    #define L_SHIFT 42
#define R_SHIFT 54
#endif

#ifdef Q_WS_X11
//    #define L_SHIFT 50
#define R_SHIFT 62
#endif

// Конструктор
QWheelZoomSvc::QWheelZoomSvc() :
    QObject()
{
    isZoom = true;
    // назначаем коэффициент, определяющий изменение масштаба графика
    // при вращении колеса мыши
    sfact = 1.2;
    movingFix = false;
}

// Прикрепление интерфейса к менеджеру масштабирования
void QWheelZoomSvc::attach(QwtChartZoom *zm)
{
    // запоминаем указатель на менеджер масштабирования
    zoom = zm;
    // назначаем для графика обработчик событий (фильтр событий)
    zoom->plot()->installEventFilter(this);
    zoom->setRegim(QwtChartZoom::ctHorWheel);
}

// Задание коэффициента масштабирования графика
// при вращении колеса мыши (по умолчанию он равен 1.2)
void QWheelZoomSvc::setWheelFactor(double fact) {
    sfact = fact;
}

// Обработчик всех событий
bool QWheelZoomSvc::eventFilter(QObject *target,QEvent *event)
{

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
        curr_x = mEvent->pos().x();
        curr_y = mEvent->pos().y();
        movingFix = true;
    }

    // если событие произошло для графика, то
    if (target == zoom->plot() && isZoom)
    {
        // если произошло одно из событий от клавиатуры, то
        if (event->type() == QEvent::KeyPress ||
            event->type() == QEvent::KeyRelease)
            switchWheel(event); // вызываем соответствующий обработчик
        // если событие вызвано вращением колеса мыши, то
        if (event->type() == QEvent::Wheel)
        {
            procWheel(event);   // вызываем соответствующий обработчик
            zoom->updatePlot(); // обновляем график
            emit wheeled();
        }



    }
    // передаем управление стандартному обработчику событий
    return QObject::eventFilter(target,event);
}

// Обработчик нажатия/отпускания клавиши Ctrl или Shift
void QWheelZoomSvc::switchWheel(QEvent *event)
{
    // читаем режим масштабирования
    QwtChartZoom::QConvType ct = zoom->regim();
    // создаем указатель на событие от клавиатуры
    QKeyEvent *kEvent = static_cast<QKeyEvent *>(event);
    // переключаем режим в зависимости от клавиши
    switch (kEvent->key())
    {
        // клавиша Ctrl
        //    case Qt::Key_Control:
        //        // в зависимости от события
        //        switch (event->type())
        //        {
        //        // клавиша нажата
        //        case QEvent::KeyPress:
        //            // если не включен никакой другой режим,
        //            if (ct == QwtChartZoom::ctNone)
        //                // то включаем режим Wheel
        //                zoom->setRegim(QwtChartZoom::ctHorWheel);
        //             break;
        //        // клавиша отпущена
        //        case QEvent::KeyRelease:
        //            // если включен режим Wheel,
        //            if (ct == QwtChartZoom::ctHorWheel)
        //                // то выключаем его
        //                zoom->setRegim(QwtChartZoom::ctNone);
        //            break;
        //        // иначе ничего не делаем
        //        default: ;
        //        }
        //        break;


        case Qt::Key_Control:
            // в зависимости от события
            switch (event->type())
            {
                // клавиша нажата
                case QEvent::KeyPress:

#ifdef R_SHIFT
                    // платформа Win или X11
                    // если не включен никакой другой режим, то
                    if (ct == QwtChartZoom::ctNone)
                    {
                        // если нажат правый Shift,
                        if (kEvent->nativeScanCode() == R_SHIFT)
                            // то включаем режим ctHorWheel
                            zoom->setRegim(QwtChartZoom::ctWheel);
                        // иначе (нажат левый Shift) включаем режим ctVerWheel
                        else zoom->setRegim(QwtChartZoom::ctVerWheel);
                    }
#else
                    // неизвестная платформа
                    // если не включен никакой другой режим,
                    if (ct == QwtChartZoom::ctHorWheel)
                        // то включаем режим ctVerWheel
                        zoom->setRegim(QwtChartZoom::ctVerWheel);
#endif

                    break;
                    // клавиша отпущена
                case QEvent::KeyRelease:

#ifdef R_SHIFT
                    // платформа Win или X11
                    // если отпущен правый Shift,
                    if (kEvent->nativeScanCode() == R_SHIFT)
                    {
                        // если включен режим ctHorWheel,
                        if (ct == QwtChartZoom::ctWheel)
                            // то выключаем его
                            zoom->setRegim(QwtChartZoom::ctNone);
                    }
                    // иначе (отпущен левый Shift)
                    // если включен режим ctVerWheel,
                    else if (ct == QwtChartZoom::ctVerWheel)
                        // то выключаем его
                        zoom->setRegim(QwtChartZoom::ctNone);
#else
                    // неизвестная платформа
                    // если включен режим ctVerWheel,
                    if (ct == QwtChartZoom::ctVerWheel)
                        // то выключаем его
                        zoom->setRegim(QwtChartZoom::ctHorWheel);
#endif

                    break;
                    // иначе ничего не делаем
                default: ;
            }
            break;
            // для остальных ничего не делаем
        default:;

    }

}

// Применение изменений по вращении колеса мыши
void QWheelZoomSvc::applyWheel(QEvent *event,bool ax,bool ay)
{
    // приводим тип QEvent к QWheelEvent
    QWheelEvent *wEvent = static_cast<QWheelEvent *>(event);
    // если вращается вертикальное колесо мыши
    if (wEvent->orientation() == Qt::Vertical)
    {
        // определяем угол поворота колеса мыши
        // (значение 120 соответствует углу поворота 15°)
        int wd = wEvent->delta();
        // вычисляем масштабирующий множитель
        // (во сколько раз будет увеличен/уменьшен график)
        double kw = sfact*wd/120;
        if (wd != 0)    // если колесо вращалось, то
        {
            // фиксируем исходные границы графика (если этого еще не было сделано)
            zoom->fixBounds();
            // получаем указатель на график
            QwtPlot *plt = zoom->plot();
            if (ax) // если задано масштабирование по горизонтали
            {
                // получаем карту основной горизонтальной шкалы
                QwtScaleMap sm = plt->canvasMap(zoom->masterH());
                // определяем центр отображаемого на шкале x интервала
                double center = (sm.s1()+sm.s2())/2;
                double mouse = center;

                if (movingFix)
                    mouse = plt->invTransform(QwtPlot::xBottom,curr_x);//mySerg

                double koef = 0;
                // и полуширину интервала
                double dx = (sm.s2()-sm.s1())/2;
                // в зависимости от знака угла поворота колеса мыши
                // уменьшаем полуширину отображаемых интервалов в kw раз
                if (wd > 0)
                {
                    dx /= kw;
                    koef  =1/kw;
                }
                // или увеличиваем полуширину отображаемых интервалов в -kw раз
                else
                {
                    dx *= -kw;
                    koef = -kw;
                }
                // устанавливаем новые левую и правую границы шкалы для оси x

                double left = 0, right = 0;

                right = mouse + (sm.s2() - mouse)  *koef;
                left  = mouse - (mouse   - sm.s1())*koef;

                zoom->isb_x->set(left,right);
            }
            if (ay) // если задано масштабирование по вертикали
            {
                // получаем карту основной вертикальной шкалы
                QwtScaleMap sm = plt->canvasMap(zoom->masterV());
                // определяем центр отображаемого на шкале y интервала


                double center = (sm.s1()+sm.s2())/2;
                double mouse = center;

                if (movingFix)
                    mouse = plt->invTransform(QwtPlot::yLeft,curr_y);//mySerg

                double koef = 0;

                // и полуширину интервала
                double dy = (sm.s2()-sm.s1())/2;
                // в зависимости от знака угла поворота колеса мыши
                // уменьшаем полуширину отображаемых интервалов в kw раз
                if (wd > 0)
                {
                    dy /= kw;
                    koef = 1/kw;
                }
                // увеличиваем полуширину отображаемых интервалов в -kw раз
                else
                {
                    dy *= -kw;
                    koef = -kw;
                }
                // устанавливаем новые нижнюю и верхнюю границы вертикальной шкалы

                double top = 0, bottom = 0;
                top     = mouse + (sm.s2() - mouse)   * koef;
                bottom  = mouse - (mouse   - sm.s1()) * koef;

                zoom->isb_y->set(bottom,top);
            }
            // перестраиваем график (синхронно с остальными)
            plt->replot();

        }
    }
}

// Обработчик вращения колеса мыши
void QWheelZoomSvc::procWheel(QEvent *event)
{
    // в зависимости от включенного режима вызываем
    // масштабирование с соответствующими параметрами
    switch (zoom->regim())
    {
        // Wheel - была нажата клавиша Ctrl -
        // масштабирование по обеим осям
        case QwtChartZoom::ctWheel: applyWheel(event,true,true); break;
            //VerWheel - была нажата левая клавиша Shift -
            // масштабирование только по вертикальной оси
        case QwtChartZoom::ctVerWheel: applyWheel(event,false,true); break;
            // HorWheel - была нажата правая клавиша Shift -
            // масштабирование только по горизонтальной оси
        case QwtChartZoom::ctHorWheel: applyWheel(event,true,false); break;
            // для прочих режимов ничего не делаем
        default: ;
    }
}
