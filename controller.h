#pragma once

#include <QObject>
#include "view.h"

using namespace view;

namespace ctrl {

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(View *view, QObject *parent = nullptr);

private:
    View *m_view;

signals:

private slots:
    void onStartBtn();
    void onPauseBtn();
    void onClearBtn();

};

}
