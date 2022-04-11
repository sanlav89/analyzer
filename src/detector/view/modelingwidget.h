#pragma once

#include <QGroupBox>
#include <utils/types.h>

namespace detector {
namespace view {

class ModelingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelingWidget(const utils::names_t &names, QWidget *parent = nullptr);

signals:
    void activityChanged(int id, qreal value);
};

}
}
