#include "sliderwithlabel.h"
#include <QGridLayout>

namespace detector {
namespace view {

static int m_idCounter = 0;

SliderWithLabel::SliderWithLabel(QWidget *parent)
    : QWidget(parent)
    , m_id(m_idCounter++)
{
    m_label = new QLabel("0.00", this);
    m_slider = new QSlider(this);
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setRange(0, 100);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_slider, 3);
    mainLayout->addWidget(m_label, 1);
    connect(m_slider, &QSlider::valueChanged, this, &SliderWithLabel::onValueChanged);
}

int SliderWithLabel::id() const
{
    return m_id;
}

void SliderWithLabel::onValueChanged(int value)
{
    qreal valueReal = qreal(value) * 0.01;
    m_label->setText(QString::asprintf("%.2f", valueReal));
    emit valueChanged(m_id, valueReal);
}

}
}
