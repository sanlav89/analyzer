#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "view.h"
#include "graph.h"
#include "observer.h"

namespace view {

class MainWidget : public View, public Observer
{
    Q_OBJECT
public:
    explicit MainWidget(View *parent = nullptr);

    void updateSpectrum(const spectrum_t &spectrum) override;
    void updateNuclides(const nuclides_t &nuclides) override;
    void updateEnergyScale(const enpoly_t &enpoly) override;
    void updateStatusMsg(const std::string &msg) override;
    void setStartedButtonsState() override;
    void setPausedButtonsState() override;

private:

    Graph *m_graph;
    QPushButton *m_startBtn;
    QPushButton *m_pauseBtn;
    QPushButton *m_clearBtn;
    QLabel *m_statusLbl;

};

}

#endif // GRAPH_H
