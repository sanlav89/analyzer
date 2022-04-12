#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <view/viewinfoupdater.h>
#include <view/spectrumnuclides.h>
#include <utils/graph/spectrumonly.h>

namespace analyzer {
namespace view {

class MainWidget : public QWidget, public ViewInfoUpdater
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

    void updateSpectrum(const utils::spectrum_t &spectrum) override;
    void updateNuclides(const utils::nuclides_t &nuclides) override;
    void updateEnergyScale(const utils::poly_t &enpoly) override;
    void updateStatusMsg(const std::string &msg) override;
    void setStartedButtonsState();
    void setPausedButtonsState();

private:

    SpectrumNuclides *m_graph;
    QPushButton *m_startBtn;
    QPushButton *m_pauseBtn;
    QPushButton *m_clearBtn;
    QLabel *m_statusLbl;

signals:
    void startButtonClicked();
    void pauseButtonClicked();
    void clearButtonClicked();

};

}
}
