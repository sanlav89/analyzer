#pragma once

#include <QWidget>

#include <QSlider>
#include <QLabel>

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

    static int m_idCounter;

signals:
    void valueChanged(int, qreal);

private slots:
    void onValueChanged(int value);

};
