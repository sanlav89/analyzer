#include "measuredwidget.h"
#include <QGroupBox>
#include <QGridLayout>

namespace detector {
namespace view {

MeasuredWidget::MeasuredWidget(const utils::names_t &names, QWidget *parent)
    : QWidget{parent}
{
    QListWidget *listWidget = new QListWidget(this);
    for (const auto &name : names) {
        QListWidgetItem *item = new QListWidgetItem(name.c_str(), listWidget);
        listWidget->addItem(item);
    }
    connect(listWidget, &QListWidget::itemClicked, this, &MeasuredWidget::onItemClicked);

    QGroupBox *listWidgetGB = new QGroupBox(this);
    QGridLayout *listWidgetLayout = new QGridLayout(listWidgetGB);
    listWidgetLayout->addWidget(listWidget);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(listWidgetGB);
    setLayout(mainLayout);
}

void MeasuredWidget::onItemClicked(QListWidgetItem *item)
{
    emit nameChanged(item->text().toStdString());
}

}
}
