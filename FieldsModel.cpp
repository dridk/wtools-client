#include "FieldsModel.h"
#include <QDebug>
#include <QApplication>
#include "qfonticon.h"

FieldsModel::FieldsModel(QObject *parent)
    :QStandardItemModel(parent)
{

    connect(&mRequest,SIGNAL(jsonReceived(QJsonDocument)), this,SLOT(received(QJsonDocument)));

}

QStringList FieldsModel::fields() const
{

    QStringList out;

    for (int i=0; i< rowCount(); ++i)
    {
        QStandardItem * rootItem = item(i);

        if (rootItem->hasChildren())
        {
            for (int j=0; j<rootItem->rowCount(); ++j)
            {
                QStandardItem * fieldItem = rootItem->child(j);
                if (fieldItem->checkState() == Qt::Checked)
                    out.append(rootItem->text()+QString(".") + fieldItem->text());
            }
        }
    }
    return out;

}

void FieldsModel::load()
{

    mRequest.get(Request::makeRequest("projects/projet1/fields/"));

}

void FieldsModel::received(const QJsonDocument &json)
{

    if (json.object().value("success").toBool() == true)
    {

        clear();

        for ( QJsonValue obj : json.object().value("results").toArray())
        {
            QString dbName = obj.toObject().value("name").toString();
            QStandardItem * rootItem = new QStandardItem;
            rootItem->setText(dbName);
            rootItem->setIcon(QFontIcon::icon(0xf1c0, qApp->palette("QWidget").highlight().color()));

            for (QJsonValue field : obj.toObject().value("fields").toArray())
            {
                QStandardItem * fieldItem = new QStandardItem();
                fieldItem->setText(field.toObject().value("name").toString());
                fieldItem->setToolTip(field.toObject().value("comment").toString());
                fieldItem->setCheckable(true);
                fieldItem->setIcon(QFontIcon::icon(0xf06e, qApp->palette("QWidget").text().color()));

                rootItem->appendRow(fieldItem);

            }



            appendRow(rootItem);




        }



    }



}
