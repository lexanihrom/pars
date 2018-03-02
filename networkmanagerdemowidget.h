#ifndef NETWORKMANAGERDEMOWIDGET_H
#define NETWORKMANAGERDEMOWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
class QElapsedTimer;
class NetworkManagerDemoWidget : public QObject {
    Q_OBJECT

public:
    explicit NetworkManagerDemoWidget(QObject* parent = 0);
    ~NetworkManagerDemoWidget();
private slots:
    void onFinished(QNetworkReply* reply);
private:
    QNetworkAccessManager m_manager;
    QElapsedTimer *timer;
};

#endif // NETWORKMANAGERDEMOWIDGET_H
