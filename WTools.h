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

    QNetworkAccessManager * netManager() const;




private:
    WTools();
    static WTools * mInstance;
    QNetworkAccessManager * mNetManager;

    QString mHost;
    QString mPrefix;



};

#endif // WTOOLS_H
