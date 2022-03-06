#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "iview.h"
#include "graph.h"

namespace view {

class View : public QWidget, public IView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

    void updateSpectrum(const spectrum_t &spectrum) override;
    void updateNuclides(const nuclides_t &nuclides) override;
    void updateActivities(const activities_t &activities) override;
    void updateState() override;

private:

    enum State {
        Started,
        Paused
    };

    Graph *m_graph;
    QPushButton *m_startBtn;
    QPushButton *m_pauseBtn;
    QPushButton *m_clearBtn;
    QLabel *m_statusLbl;

    int m_state;

signals:

private slots:
    void onStartBtn();
    void onPauseBtn();
    void onClearBtn();

};

}

#endif // GRAPH_H
