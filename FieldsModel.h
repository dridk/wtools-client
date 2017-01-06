#ifndef FIELDSMODEL_H
#define FIELDSMODEL_H
#include <QStandardItemModel>
#include "Request.h"
class FieldsModel : public QStandardItemModel
{
    Q_OBJECT
public:
    FieldsModel(QObject *parent = Q_NULLPTR);

    QStringList fields() const;


public Q_SLOTS:
    void load();

protected Q_SLOTS:
    void received(const QJsonDocument& json);


private:
    Request mRequest;

};

#endif // FIELDSMODEL_H
