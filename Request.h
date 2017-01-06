#ifndef REQUEST_H
#define REQUEST_H
#include <QObject>
#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include "WTools.h"

class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);

    QNetworkReply * get(const QNetworkRequest& request);
    QNetworkReply * post(const QNetworkRequest& request,const QByteArray& data = QByteArray() );
    QNetworkReply * put(const QNetworkRequest& request, const QByteArray& data = QByteArray());
    QNetworkReply * deleteResource(const QNetworkRequest& request);

    static QNetworkRequest makeRequest(const QString& resource) ;

    const QJsonDocument& json() const;

signals :
    void jsonReceived(const QJsonDocument& json);


protected Q_SLOTS:
    void received();

private:
    bool mLoading = false;
    QJsonDocument mJson;


};

#endif // REQUEST_H
