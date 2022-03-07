#pragma once

#include "types.h"
#include <QWidget>

namespace view {

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual void updateSpectrum(const spectrum_t &spectrum) = 0;
    virtual void updateNuclides(const nuclides_t &nuclides) = 0;
    virtual void updateActivities(const activities_t &activities) = 0;
    virtual void updateEnergyScale(const enpoly_t &enpoly) = 0;
    virtual void updateStatusMsg(const std::string &msg) = 0;
    virtual void setStartedButtonsState() = 0;
    virtual void setPausedButtonsState() = 0;

signals:
    void startButtonClicked();
    void pauseButtonClicked();
    void clearButtonClicked();
};

}

