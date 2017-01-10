#ifndef WTOOLS_H
#define WTOOLS_H
#include <QtNetwork>
#include <QtCore>
#include <QJsonDocument>

class WTools : public QObject
{
    Q_OBJECT
public :
    static WTools * i();


    const QString& host() const;
    const QString& prefix() const;
    int port() const;

    QNetworkAccessManager * netManager() const;




private:
    WTools();
    static WTools * mInstance;
    QNetworkAccessManager * mNetManager;

    QString mHost;
    QString mPrefix;
    int mPort;



};

#endif // WTOOLS_H
