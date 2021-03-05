#include "spinWidget.h"

SmWidget::SmWidget(QWidget * par,QColor acolor): QWidget(par)
{
    QPalette pallete;
    pallete.setColor(backgroundRole(),acolor);
    setPalette(pallete);

    setAutoFillBackground(true);
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect;
    effect->setOpacity(0.3);
    setGraphicsEffect(effect);
    resize(QSize(0,0));
}

MLabel::MLabel(QWidget * par): parent(par)
{
    QString str;
    str.setNum(0);
    QFont font;
    font.setPointSize(20);
   // font.setFamily("Gulim");
   // font.setFamily("FangSong");
    font.setFamily("Arial Unicode MC");
  //  font.setBold(true);
    setFixedWidth(18);
    setFixedHeight(26);
    setText(str);
    setFont(font);
    setAlignment(Qt::AlignCenter);
    widH = new SmWidget(this,Qt::red);
    widL = new SmWidget(this,Qt::blue);
    this->setMouseTracking(true);
}

MLabel::~MLabel()
{
    if (widH)
        delete widH;
    if (widL)
        delete widL;
}
void MLabel::sendUpdateFromFilter()
{
    emit sendNumUpdate(true);
}
void MLabel::setFontTone(bool isBlack)
{
    QColor color2 = Qt::gray;
    QColor color1 = Qt::black;
    if (isBlack)
        setStyleSheet(QString("color: %1").arg(color1.name()));
    else
        setStyleSheet(QString("color: %1").arg(color2.name()));
}

void MLabel::setWidType(WidType wid)
{
    if (wid == HIGTH)
    {
        widH->setGeometry(0,0,width(),height()/2);
        widH->resize(width(),height()/2);
        widH->show();
        widL->resize(0,0);
    }
    if (wid == LOW)
    {
        widL->setGeometry(0,height()/2,width(),height()/2);
        widL->resize(width(),height()/2);
        widL->show();
        widH->resize(0,0);
    }
    if (wid == NONE)
    {
        widH->resize(0,0);
        widL->resize(0,0);
    }

}
void MLabel::mousePressEvent(QMouseEvent *ev)
{
    if (ev->y() <= height()/2)
    {
        QString str = text();
        int num = str.toInt();
        num = ++num%10;
        setText(str.setNum(num));
    }
    else if (ev->y() > height()/2)
    {
        QString str = text();
        int num = str.toInt();
        if (--num==-1) num = 9;
        setText(str.setNum(num));
    }
    emit sendNumUpdate(true);
}


SpinWidget::SpinWidget(QWidget * par): parent(par)
{
    QHBoxLayout * layout = new QHBoxLayout;

    layout->setSpacing(0);
    currNumb = 0;
    num10 = new MLabel(this);
    tochka9 = new QLabel;
    num9 = new MLabel(this);
    num8 = new MLabel(this);
    num7 = new MLabel(this);
    tochka6 = new QLabel;
    num6 = new MLabel(this);
    num5 = new MLabel(this);
    num4 = new MLabel(this);
    tochka3 = new QLabel;
    num3 = new MLabel(this);
    num2 = new MLabel(this);
    num1 = new MLabel(this);

    QColor color = Qt::gray;
    tochka9->setStyleSheet(QString("color: %1").arg(color.name()));
    tochka6->setStyleSheet(QString("color: %1").arg(color.name()));
    tochka3->setStyleSheet(QString("color: %1").arg(color.name()));

    num10->installEventFilter(new MouseFilter(num10));
    num9->installEventFilter(new MouseFilter(num9));
    num8->installEventFilter(new MouseFilter(num8));
    num7->installEventFilter(new MouseFilter(num7));
    num6->installEventFilter(new MouseFilter(num6));
    num5->installEventFilter(new MouseFilter(num5));
    num4->installEventFilter(new MouseFilter(num4));
    num3->installEventFilter(new MouseFilter(num3));
    num2->installEventFilter(new MouseFilter(num2));
    num1->installEventFilter(new MouseFilter(num1));

    layout->addWidget(num10);
    layout->addWidget(tochka9);
    layout->addWidget(num9);
    layout->addWidget(num8);
    layout->addWidget(num7);
    layout->addWidget(tochka6);
    layout->addWidget(num6);
    layout->addWidget(num5);
    layout->addWidget(num4);
    layout->addWidget(tochka3);
    layout->addWidget(num3);
    layout->addWidget(num2);
    layout->addWidget(num1);
    setLayout(layout);

    QFont font;
    font.setPointSize(20);
    tochka9->setFixedWidth(5);
    tochka9->setFixedHeight(24);
    tochka9->setText(".");
    tochka9->setFont(font);

    tochka9->setAlignment(Qt::AlignCenter);

    tochka6->setFixedWidth(5);
    tochka6->setFixedHeight(24);
    tochka6->setText(".");
    tochka6->setFont(font);
    tochka6->setAlignment(Qt::AlignCenter);

    tochka3->setFixedWidth(5);
    tochka3->setFixedHeight(24);
    tochka3->setText(".");
    tochka3->setFont(font);
    tochka3->setAlignment(Qt::AlignCenter);

    QObject::connect(num10,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num9,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num8,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num7,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num6,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num5,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num4,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num3,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num2,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    QObject::connect(num1,SIGNAL(sendNumUpdate(bool)),this,SLOT(updateNumber(bool)),Qt::QueuedConnection);
    updateNumber(false);

    this->setMouseTracking(true);
}

SpinWidget::~SpinWidget()
{
    if (num10)
        delete num10;
    if (tochka9)
        delete tochka9;
    if (num9)
        delete num9;
    if (num8)
        delete num8;
    if (num7)
        delete num7;
    if (tochka6)
        delete tochka6;
    if (num6)
        delete num6;
    if (num5)
        delete num5;
    if (num4)
        delete num4;
    if (tochka3)
        delete tochka3;
    if (num3)
        delete num3;
    if (num2)
        delete num2;
    if (num1)
        delete num1;
}

void SpinWidget::updateNumber(bool isSignal)
{
    currNumb = (qint64(num10->text().toInt())*1000000000+
               qint64(num9 ->text().toInt())*100000000+
               qint64(num8 ->text().toInt())*10000000+
               qint64(num7 ->text().toInt())*1000000+
               qint64(num6 ->text().toInt())*100000+
               qint64(num5 ->text().toInt())*10000+
               qint64(num4 ->text().toInt())*1000+
               qint64(num3 ->text().toInt())*100+
               qint64(num2 ->text().toInt())*10+
               qint64(num1 ->text().toInt()));
    updateFontTone();
    if (isSignal)
        emit sendNumChanged();
}
void SpinWidget::updateFontTone()
{
    if (currNumb == 0)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(false);
        num7->setFontTone(false);
        num6->setFontTone(false);
        num5->setFontTone(false);
        num4->setFontTone(false);
        num3->setFontTone(false);
        num2->setFontTone(false);
        num1->setFontTone(false);
    }
    else if(currNumb < 10)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(false);
        num7->setFontTone(false);
        num6->setFontTone(false);
        num5->setFontTone(false);
        num4->setFontTone(false);
        num3->setFontTone(false);
        num2->setFontTone(false);
        num1->setFontTone(true);
    }
    else if (currNumb < 100)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(false);
        num7->setFontTone(false);
        num6->setFontTone(false);
        num5->setFontTone(false);
        num4->setFontTone(false);
        num3->setFontTone(false);
        num2->setFontTone(true);
        num1->setFontTone(true);
    }
    else if (currNumb < 1000)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(false);
        num7->setFontTone(false);
        num6->setFontTone(false);
        num5->setFontTone(false);
        num4->setFontTone(false);
        num3->setFontTone(true);
        num2->setFontTone(true);
        num1->setFontTone(true);
    }
    else if (currNumb < 10000)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(false);
        num7->setFontTone(false);
        num6->setFontTone(false);
        num5->setFontTone(false);
        num4->setFontTone(true);
        num3->setFontTone(true);
        num2->setFontTone(true);
        num1->setFontTone(true);
    }
    else if (currNumb < 100000)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(false);
        num7->setFontTone(false);
        num6->setFontTone(false);
        num5->setFontTone(true);
        num4->setFontTone(true);
        num3->setFontTone(true);
        num2->setFontTone(true);
        num1->setFontTone(true);
    }
    else if (currNumb < 1000000)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(false);
        num7->setFontTone(false);
        num6->setFontTone(true);
        num5->setFontTone(true);
        num4->setFontTone(true);
        num3->setFontTone(true);
        num2->setFontTone(true);
        num1->setFontTone(true);
    }
    else if (currNumb < 10000000)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(false);
        num7->setFontTone(true);
        num6->setFontTone(true);
        num5->setFontTone(true);
        num4->setFontTone(true);
        num3->setFontTone(true);
        num2->setFontTone(true);
        num1->setFontTone(true);
    }
    else if (currNumb < 100000000)
    {
        num10->setFontTone(false);
        num9->setFontTone(false);
        num8->setFontTone(true);
        num7->setFontTone(true);
        num6->setFontTone(true);
        num5->setFontTone(true);
        num4->setFontTone(true);
        num3->setFontTone(true);
        num2->setFontTone(true);
        num1->setFontTone(true);
    }
    else if (currNumb <= 999999999)
    {
        num10->setFontTone(false);
        num9->setFontTone(true);
        num8->setFontTone(true);
        num7->setFontTone(true);
        num6->setFontTone(true);
        num5->setFontTone(true);
        num4->setFontTone(true);
        num3->setFontTone(true);
        num2->setFontTone(true);
        num1->setFontTone(true);
    }
    else
    {
        num10->setFontTone(true);
        num9->setFontTone(true);
        num8->setFontTone(true);
        num7->setFontTone(true);
        num6->setFontTone(true);
        num5->setFontTone(true);
        num4->setFontTone(true);
        num3->setFontTone(true);
        num2->setFontTone(true);
        num1->setFontTone(true);

    }
   // qDebug() << currNumb;
}

bool SpinWidget::setNumber(int number)
{
    if (number < 0)
        return false;

    QString str;
    int sum;
    int razr10 = (int)floor(double(number)/1000000000.);
    num10->setText(str.setNum(razr10));
    sum = razr10*1000000000;

    int razr9 = number - sum;
    razr9 = (int)floor(double(razr9)/100000000.);
    num9->setText(str.setNum(razr9));
    sum += razr9*100000000;

    int razr8 = number - sum;
    razr8 = (int)floor(double(razr8)/10000000.);
    num8->setText(str.setNum(razr8));
    sum += razr8*10000000;

    int razr7 = number - sum;
    razr7 = (int)floor(double(razr7)/1000000.);
    num7->setText(str.setNum(razr7));
    sum += razr7*1000000;

    int razr6 = number - sum;
    razr6 = (int)floor(double(razr6)/100000.);
    num6->setText(str.setNum(razr6));
    sum += razr6*100000;

    int razr5 = number - sum;
    razr5 = (int)floor(double(razr5)/10000.);
    num5->setText(str.setNum(razr5));
    sum += razr5*10000;

    int razr4 = number - sum;
    razr4 = (int)floor(double(razr4)/1000.);
    num4->setText(str.setNum(razr4));
    sum += razr4*1000;

    int razr3 = number - sum;
    razr3 = (int)floor(double(razr3)/100.);
    num3->setText(str.setNum(razr3));
    sum += razr3*100;

    int razr2 = number - sum;
    razr2 = (int)floor(double(razr2)/10.);
    num2->setText(str.setNum(razr2));
    sum += razr2*10;

    int razr1 = number - sum;
    num1->setText(str.setNum(razr1));
    updateNumber(false);
    return true;
}

int SpinWidget::getNumber()
{
    return currNumb;
}

void SpinWidget::mouseMoveEvent(QMouseEvent * event)
{

    int x =  event->pos().x();
    int y =  event->pos().y();

    if (x >= num10->x() &&
        x < num10->x()+num10->width() &&
        y >= num10->y() &&
        y < num10->y()+num10->height())
    {
        if (y <= height()/2)
        {
            num10->setWidType(MLabel::HIGTH);
        }
        else
        {
            num10->setWidType(MLabel::LOW);
        }
    }
    else
        num10->setWidType(MLabel::NONE);

    if (x >= num9->x() &&
        x < num9->x()+num9->width() &&
        y >= num9->y() &&
        y < num9->y()+num9->height())
    {
        if (y <= height()/2)
        {
            num9->setWidType(MLabel::HIGTH);
        }
        else
        {
            num9->setWidType(MLabel::LOW);
        }
    }
    else
        num9->setWidType(MLabel::NONE);

    if (x >= num8->x() &&
        x < num8->x()+num8->width() &&
        y >= num8->y() &&
        y < num8->y()+num8->height())
    {
        if (y <= height()/2)
        {
            num8->setWidType(MLabel::HIGTH);
        }
        else
        {
            num8->setWidType(MLabel::LOW);
        }
    }
    else
        num8->setWidType(MLabel::NONE);


    if (x >= num7->x() &&
        x < num7->x()+num7->width() &&
        y >= num7->y() &&
        y < num7->y()+num7->height())
    {
        if (y <= height()/2)
        {
            num7->setWidType(MLabel::HIGTH);
        }
        else
        {
            num7->setWidType(MLabel::LOW);
        }
    }
    else
        num7->setWidType(MLabel::NONE);

    if (x >= num6->x() &&
        x < num6->x()+num6->width() &&
        y >= num6->y() &&
        y < num6->y()+num6->height())
    {
        if (y <= height()/2)
        {
            num6->setWidType(MLabel::HIGTH);
        }
        else
        {
            num6->setWidType(MLabel::LOW);
        }
    }
    else
        num6->setWidType(MLabel::NONE);

    if (x >= num5->x() &&
        x < num5->x()+num5->width() &&
        y >= num5->y() &&
        y < num5->y()+num5->height())
    {
        if (y <= height()/2)
        {
            num5->setWidType(MLabel::HIGTH);
        }
        else
        {
            num5->setWidType(MLabel::LOW);
        }
    }
    else
        num5->setWidType(MLabel::NONE);

    if (x >= num4->x() &&
        x < num4->x()+num4->width() &&
        y >= num4->y() &&
        y < num4->y()+num4->height())
    {
        if (y <= height()/2)
        {
            num4->setWidType(MLabel::HIGTH);
        }
        else
        {
            num4->setWidType(MLabel::LOW);
        }
    }
    else
        num4->setWidType(MLabel::NONE);

    if (x >= num3->x() &&
        x < num3->x()+num3->width() &&
        y >= num3->y() &&
        y < num3->y()+num3->height())
    {
        if (y <= height()/2)
        {
            num3->setWidType(MLabel::HIGTH);
        }
        else
        {
            num3->setWidType(MLabel::LOW);
        }
    }
    else
        num3->setWidType(MLabel::NONE);

    if (x >= num2->x() &&
        x < num2->x()+num2->width() &&
        y >= num2->y() &&
        y < num2->y()+num2->height())
    {
        if (y <= height()/2)
        {
            num2->setWidType(MLabel::HIGTH);
        }
        else
        {
            num2->setWidType(MLabel::LOW);
        }
    }
    else
        num2->setWidType(MLabel::NONE);

    if (x >= num1->x() &&
        x <= num1->x()+num1->width() &&
        y >= num1->y() &&
        y <= num1->y()+num1->height())
    {
        if (y <= height()/2)
        {
            num1->setWidType(MLabel::HIGTH);
        }
        else
        {
            num1->setWidType(MLabel::LOW);
        }
    }
    else
        num1->setWidType(MLabel::NONE);
}

MouseFilter::MouseFilter(QObject* pobj)
    : QObject(pobj)
{
}
bool MouseFilter::eventFilter(QObject* pobj, QEvent* pe)
{
    if (pe->type() == QEvent::Wheel)
    {
        if (((QWheelEvent*)pe)->delta()>0)
        {
            QString str = ((MLabel*)pobj)->text();
            int num = str.toInt();
            num = ++num%10;
            ((MLabel*)pobj)->setText(str.setNum(num));
            ((MLabel*)pobj)->sendUpdateFromFilter();
        }
        else
        {
            QString str = ((MLabel*)pobj)->text();
            int num = str.toInt();
            if (--num==-1) num = 9;
            ((MLabel*)pobj)->setText(str.setNum(num));
            ((MLabel*)pobj)->sendUpdateFromFilter();
        }

        return true;
    }
    return false;
}

