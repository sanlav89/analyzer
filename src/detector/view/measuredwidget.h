#pragma once

#include <QWidget>
#include <QListWidget>
#include <utils/types.h>

namespace detector {
namespace view {

class MeasuredWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MeasuredWidget(const utils::names_t &names,QWidget *parent = nullptr);

signals:
    void nameChanged(const std::string &name);

private slots:
    void onItemClicked(QListWidgetItem *item);

};

}
}
