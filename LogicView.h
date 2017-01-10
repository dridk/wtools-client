#ifndef LOGICVIEW_H
#define LOGICVIEW_H
#include <QtWidgets>
#include "LogicModel.h"
#include "LogicDelegate.h"
#include "Request.h"

class LogicView : public QTreeView
{
    Q_OBJECT
public:
    LogicView(QWidget * parent = Q_NULLPTR);
    void contextMenuEvent(QContextMenuEvent* event);
    QString query();
public Q_SLOTS:
    void load();

protected Q_SLOTS:
    void received(const QJsonDocument& json);




private:
    LogicModel * mModel;
    LogicDelegate * mDelegate;
    Request mRequest;
};

#endif // LOGICVIEW_H
