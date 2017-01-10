#include "LogicView.h"

LogicView::LogicView(QWidget * parent)
    :QTreeView(parent)
{
    mModel = new LogicModel;
    mDelegate = new LogicDelegate;

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);

    setDragDropMode(QAbstractItemView::InternalMove);
    //setDragDropMode(QAbstractItemView::DragDrop);




    setModel(mModel);
    setItemDelegate(mDelegate);

    setUniformRowHeights(true);

    connect(&mRequest,SIGNAL(jsonReceived(QJsonDocument)), this,SLOT(received(QJsonDocument)));



}

void LogicView::contextMenuEvent(QContextMenuEvent *event)
{


    QStandardItem * item = mModel->itemFromIndex(currentIndex());



    if (item)
    {



        QMenu menu;
        QAction * groupAction = menu.addAction("Create groups");
        QAction * condiAction = menu.addAction("Create Condition");
        menu.addSeparator();
        QAction * delAction = menu.addAction("Remove");


        if ( item->type() == LogicModel::ConditionType)
        {
            menu.removeAction(groupAction);
            menu.removeAction(condiAction);
        }


        QAction * choice = menu.exec(event->globalPos());




        if (choice == groupAction)
            mModel->createGroup(item);

        if (choice == condiAction)
            mModel->createCondition(item);

        if (choice == delAction)
        {
            if (item->parent())
            {
                item->parent()->removeRow(item->row());
            }

        }



    }
}

QString LogicView::query()
{
    return mModel->makeQuery();
}

void LogicView::load()
{
    mRequest.get(Request::makeRequest("projects/projet1/fields/"));

}

void LogicView::received(const QJsonDocument &json)
{
    QStringList fields;
    if (json.object().value("success").toBool() == true)
    {
        for ( QJsonValue obj : json.object().value("results").toArray())
        {
            QString dbName = obj.toObject().value("name").toString();

            for (QJsonValue field : obj.toObject().value("fields").toArray())
            {
                QString item = dbName+"."+field.toObject().value("name").toString();
                fields.append(item);
            }
        }
    }

    mDelegate->setFieldNames(fields);

}



