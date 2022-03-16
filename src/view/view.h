#pragma once

#include "utils/types.h"
#include <QWidget>

namespace view {

using namespace utils;

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual void setStartedButtonsState() = 0;
    virtual void setPausedButtonsState() = 0;

signals:
    void startButtonClicked();
    void pauseButtonClicked();
    void clearButtonClicked();
};

}

