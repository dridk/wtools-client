#include "WTools.h"
#include <QDebug>
WTools  * WTools::mInstance = Q_NULLPTR;

WTools *WTools::i()
{
    if (mInstance == Q_NULLPTR)
        mInstance = new WTools();

    return mInstance;
}



const QString &WTools::host() const
{
    return mHost;
}

const QString &WTools::prefix() const
{
    return mPrefix;
}

QNetworkAccessManager *WTools::netManager() const
{
    return mNetManager;
}


WTools::WTools()
    :QObject(0)
{
    mNetManager = new QNetworkAccessManager;
    mHost   = "193.54.252.69";
    mPrefix = "/sacha/api/";

}
