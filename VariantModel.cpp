#include "VariantModel.h"

VariantModel::VariantModel(QObject * parent )
    :QAbstractListModel(parent)
{



}

int VariantModel::rowCount(const QModelIndex &parent) const
{
    return mData.count();
}

int VariantModel::columnCount(const QModelIndex &parent) const
{
    if (mData.count() > 0 )
        return mData.first().count();

    return 0;


}

QVariant VariantModel::data(const QModelIndex &index, int role) const
{

    if ( !index.isValid())
        return QVariant();

    if ( mData.count()<=0)
        return QVariant();


    if (role == Qt::DisplayRole)
    {
        QVariantList item = mData.at(index.row());
        return item.at(index.column());

    }



    return QVariant();


}

QVariant VariantModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {

        if (orientation == Qt::Horizontal)
        {

            if (section < mFields.count())
            {
                return mFields.at(section);
            }



        }


    }

    return QVariant();

}

void VariantModel::setFields(const QStringList &fields)
{
    mFields = fields;
}

void VariantModel::setQuery(const QString &query)
{
    mQuery = query;
}

void VariantModel::exportCsv(const QString &filename)
{

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);

        for (int r = 0; r < rowCount(); ++r)
        {
            QStringList list;
            QStringList header;


            for (int c=0; c<columnCount(); ++c)
            {

                if (r == 0)
                    header.append(headerData(c,Qt::Horizontal,Qt::DisplayRole).toString());


                list.append(data(index(r,c), Qt::DisplayRole).toString());
            }

            if (r == 0)
                stream<<header.join(";")<<'\n';

            stream<<list.join(";");
            stream<<'\n';
        }


    }


    file.close();


}

void VariantModel::load()
{
    if (mFields.isEmpty())
        return;

    QNetworkRequest request = Request::makeRequest("projects/projet1/select/");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject data;
    QJsonArray fields;

    for (QString f: mFields)
        fields.append(f);


    data["fields"] = fields;
    data["query"] =  mQuery;




    QJsonDocument doc(data);

    QNetworkReply * reply = WTools::i()->netManager()->post(request, doc.toJson());

    qDebug()<<request.url();

    connect(reply,SIGNAL(finished()), this,SLOT(received()));

}

void VariantModel::received()
{
    beginResetModel();

    mData.clear();

    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    QTextStream reader(reply->readAll());
    QString line ;

    while (reader.readLineInto(&line))
    {
        QStringList row =line.split(QChar::Tabulation);
        QVariantList item;
        for (QString value : row)
            item.append(value.simplified());

        mData.append(item);


    }



    endResetModel();



}
