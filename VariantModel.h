#ifndef VARIANTMODEL_H
#define VARIANTMODEL_H
#include <QAbstractListModel>
#include <QDebug>
#include <QtCore>
#include "WTools.h"
#include "Request.h"
class VariantModel : public QAbstractListModel
{
    Q_OBJECT
public:
    VariantModel(QObject * parent = Q_NULLPTR);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void setFields(const QStringList& fields);

public Q_SLOTS:
    void load();

protected Q_SLOTS:
    void received();

private:
    QList<QVariantList> mData;
    QStringList mFields;

};

#endif // VARIANTMODEL_H
