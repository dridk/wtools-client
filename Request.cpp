#include "Request.h"
#include <QDebug>
Request::Request(QObject *parent) : QObject(parent)
{

}

QNetworkReply * Request::get(const QNetworkRequest &request)
{
    mLoading = true;
    QNetworkReply * reply = WTools::i()->netManager()->get(request);
    connect(reply, SIGNAL(finished()), this,SLOT(received()));
}

QNetworkReply * Request::put(const QNetworkRequest &request, const QByteArray &data)
{
    mLoading = true;
    QNetworkReply * reply = WTools::i()->netManager()->put(request, data);
    connect(reply, SIGNAL(finished()), this,SLOT(received()));

}

QNetworkReply * Request::post(const QNetworkRequest &request, const QByteArray &data)
{
    mLoading = true;

    QNetworkReply * reply = WTools::i()->netManager()->post(request,data);
    connect(reply, SIGNAL(finished()), this,SLOT(received()));

}

QNetworkReply * Request::deleteResource(const QNetworkRequest &request)
{
    mLoading = true;
    QNetworkReply * reply = WTools::i()->netManager()->deleteResource(request);
    connect(reply, SIGNAL(finished()), this,SLOT(received()));
}

QNetworkRequest Request::makeRequest(const QString &resource)
{
    QUrl url;
    url.setHost(WTools::i()->host());
    url.setPath(WTools::i()->prefix() + resource);
    url.setScheme("http");

    qDebug()<<url;

    QNetworkRequest request(url);
    return request;
}

const QJsonDocument &Request::json() const
{
    return mJson;
}

void Request::received()
{
    mLoading = false;
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    if (reply)
    {
       mJson = QJsonDocument::fromJson(reply->readAll());
       emit jsonReceived(mJson);
    }



}
