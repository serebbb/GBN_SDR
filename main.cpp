#include "mainwindow.h"
#include <QApplication>
#include "mysettings.h"
#include "QDebug"
#include <QStyleFactory>

void loadStyleSheets()
{
    QFile f("qdarkstyle/mystyle.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
}

int main(int argc, char *argv[])
{
    App a(argc, argv, "MyCompany", "Client");
    qApp->setStyle(QStyleFactory::create("fusion"));

//    QPalette palette;
//        palette.setColor(QPalette::Window, QColor(53,53,53));
//        palette.setColor(QPalette::WindowText, Qt::white);
//        palette.setColor(QPalette::Base, QColor(25,25,25));
//        palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
//        palette.setColor(QPalette::ToolTipBase, Qt::white);
//        palette.setColor(QPalette::ToolTipText, Qt::black);
//        palette.setColor(QPalette::Text, Qt::white);
//        palette.setColor(QPalette::Button, QColor(0x40, 0x40, 0x40));
//        palette.setColor(QPalette::Button, Qt::blue);
//        palette.setColor(QPalette::ButtonText, Qt::white);
//        palette.setColor(QPalette::BrightText, Qt::red);

//        palette.setColor(QPalette::Light, QColor(53,53,53).lighter(125).lighter());
//        palette.setColor(QPalette::Mid, QColor(53,53,53).lighter(125));
//        palette.setColor(QPalette::Dark, QColor(53,53,53).lighter(125).darker());

//        palette.setColor(QPalette::Link, QColor(0,0xa0,0xa0));
//        palette.setColor(QPalette::LinkVisited, QColor(0,0xa0,0xa0).lighter());
//        palette.setColor(QPalette::Highlight, QColor(0xff, 0x8c, 0x00));
//        palette.setColor(QPalette::HighlightedText, Qt::black);
//        qApp->setPalette(palette);

    MainWindow w;
    loadStyleSheets();
    w.show();

    return a.exec();
}

