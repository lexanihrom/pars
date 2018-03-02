#include "networkmanagerdemowidget.h"

#include <QNetworkReply>
#include <QFile>
#include <QApplication>
#include <QElapsedTimer>
#include <QTime>

NetworkManagerDemoWidget::NetworkManagerDemoWidget( QObject* parent ) :
    QObject( parent ),
    timer(new QElapsedTimer())
{
    timer->start();
    connect( &m_manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( onFinished( QNetworkReply* ) ) );
    m_manager.get(QNetworkRequest( QUrl( "http://www.idei66.ru/shop/00001976/page_count/50/" )));
}

NetworkManagerDemoWidget::~NetworkManagerDemoWidget() {
}

void NetworkManagerDemoWidget::onFinished( QNetworkReply* reply ) {
    if( reply->error() == QNetworkReply::NoError ) {
        QString data = QString::fromUtf8( reply->readAll() );
        QRegExp iconsRegExp("data-e-link-name=\"([^\"]+).*data-e-link-price=\"([^\"]+)\"");
        iconsRegExp.setMinimal(true);
        QString text;
        int lastPos = 0;
        while ((lastPos = iconsRegExp.indexIn(data, lastPos)) != -1) {
            lastPos += iconsRegExp.matchedLength();
            QString qwe = iconsRegExp.cap(1) + "," + iconsRegExp.cap(2);
            text.append(qwe + "\n");
        }
        QFile fileOut("file1.csv");
        if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream writeStream(&fileOut);
            writeStream << text << "\n" << timer->elapsed();
            fileOut.close();
        }
    }
    QApplication::quit();
}
