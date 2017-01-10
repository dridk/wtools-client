#include "LogicDelegate.h"

LogicDelegate::LogicDelegate(QObject *parent)
    :QItemDelegate(parent)
{


}

QWidget *LogicDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<Q_FUNC_INFO<<"create editor ";

    const LogicModel * lModel = qobject_cast<const LogicModel*>(index.model());

    if (lModel->itemFromIndex(index)->type() == LogicModel::LogicType)
    {
        QComboBox * box = new QComboBox(parent);
        box->setMaximumWidth(200);

        for (Operator o : LogicModel::logicOperators())
            box->addItem(o.name.toUpper());


        return box;
    }

    if (lModel->itemFromIndex(index)->type() == LogicModel::ConditionType)
    {
        ConditionItem * item = dynamic_cast<ConditionItem*>(lModel->itemFromIndex(index));
        ConditionWidget * box = new ConditionWidget(item->value().type(), parent);
        box->setFieldNames(mFieldNames);
        return box;
    }

    return QItemDelegate::createEditor(parent, option, index);

}

void LogicDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug()<<Q_FUNC_INFO<<"set editor data";


    const LogicModel * lModel = qobject_cast<const LogicModel*>(index.model());

    if (lModel->itemFromIndex(index)->type() == LogicModel::LogicType){
        QComboBox * box = qobject_cast<QComboBox*>(editor);
        box->setCurrentText(index.data().toString());
    }

    if (lModel->itemFromIndex(index)->type() == LogicModel::ConditionType){

        ConditionWidget * box = qobject_cast<ConditionWidget*>(editor);
        QString key = index.data(ConditionItem::KeyRole).toString();
        QString op = index.data(ConditionItem::OperatorRole).toString();
        QVariant val = index.data(ConditionItem::ValueRole);
        box->setValue(key, op, val);
    }



    QItemDelegate::setEditorData(editor, index);

}

void LogicDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    qDebug()<<Q_FUNC_INFO<<"set model data";

    LogicModel * lModel = qobject_cast<LogicModel*>(model);


    if (lModel->itemFromIndex(index)->type() == LogicModel::LogicType){
        QComboBox * box = qobject_cast<QComboBox*>(editor);
        model->setData(index, box->currentText());
        return;
    }

    if (lModel->itemFromIndex(index)->type() == LogicModel::ConditionType){
        ConditionWidget * box = qobject_cast<ConditionWidget*>(editor);
        ConditionItem * item = dynamic_cast<ConditionItem*>(lModel->itemFromIndex(index));

        item->setValue(box->key(), box->conditionOperator(),box->value());


        return;
    }

    QItemDelegate::setModelData(editor,model, index);

}

QSize LogicDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    qDebug()<<"size ";
    QSize size = QItemDelegate::sizeHint(option, index);
    size.setHeight(30);
    return size;


}

void LogicDelegate::setFieldNames(const QStringList &fields)
{
    mFieldNames = fields;
}




