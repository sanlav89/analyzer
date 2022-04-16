#include "modelingwidget.h"
#include <QGroupBox>
#include <QGridLayout>
#include <view/sliderwithlabel.h>

namespace detector {
namespace view {

ModelingWidget::ModelingWidget(const utils::names_t &names, QWidget *parent)
    : QWidget{parent}
{
    std::vector<SliderWithLabel *> sliders(names.size());
    QGroupBox *slidersGB = new QGroupBox(this);
    QGridLayout *slidersLayout = new QGridLayout(slidersGB);
    for (auto i = 0u; i < names.size(); i++) {
        sliders[i] = new SliderWithLabel(this);
        slidersLayout->addWidget(new QLabel(names[i].c_str(), this), i, 0, 1, 1);
        slidersLayout->addWidget(sliders[i], i, 1, 1, 4);
        connect(sliders[i], &SliderWithLabel::valueChanged, this, &ModelingWidget::activityChanged);
    }

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(slidersGB);
    setLayout(mainLayout);
}

}
}
