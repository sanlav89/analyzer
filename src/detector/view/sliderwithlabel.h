#pragma once

#include <QWidget>

#include <QSlider>
#include <QLabel>

namespace detector {
namespace view {

class SliderWithLabel : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWithLabel(QWidget *parent = nullptr);

    int id() const;

private:
    int m_id;
    QLabel *m_label;
    QSlider *m_slider;

signals:
    void valueChanged(int, qreal);

private slots:
    void onValueChanged(int value);

};

}
}
