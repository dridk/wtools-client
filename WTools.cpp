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

int WTools::port() const
{
    return mPort;
}

QNetworkAccessManager *WTools::netManager() const
{
    return mNetManager;
}


WTools::WTools()
    :QObject(0)
{
    mNetManager = new QNetworkAccessManager;
    mHost   = "med-laennec.univ-brest.fr";
    mPrefix = "/sacha/api/";
    mPort   = 80;

}
