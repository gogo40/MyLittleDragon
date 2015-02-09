/*
My Little Dragon

Main Window

Copyright (c) 2015, gogo40, Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or other
materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may
be used to endorse or promote products derived from this software without specific
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    add_item_dialog_(0),
    total_value_(0),
    month_inflation_(0),
    year_inflation_(0)
{
    ui_->setupUi(this);

    updateCities();

    add_item_dialog_.setMainWindow(this);
    add_item_dialog_.update();
    add_item_dialog_.hide();

    ui_->itemsTable->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction* menu_action_add_item;
    menu_action_add_item = new QAction("Adicionar item", this);
    ui_->itemsTable->addAction(menu_action_add_item);
    QObject::connect(menu_action_add_item, SIGNAL(triggered()),
                     this, SLOT(openAddItemDialog()));

    QAction* menu_action_remove_item;
    menu_action_remove_item = new QAction("Remover item", this);
    ui_->itemsTable->addAction(menu_action_remove_item);
    QObject::connect(menu_action_remove_item, SIGNAL(triggered()),
                     this, SLOT(removeItems()));


}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::openAddItemDialog()
{
    add_item_dialog_.show();
}

void MainWindow::calculateInflation()
{
    updateWeigths();
    updateMessage();
}

bool operator<(const QTableWidgetSelectionRange& a, const QTableWidgetSelectionRange& b)
{
    if (a.bottomRow() > b.bottomRow()) return false;
    if (a.bottomRow() < b.bottomRow()) return true;
    return a.topRow() < b.topRow();
}

void MainWindow::removeItems()
{
    QList<QTableWidgetSelectionRange> list = ui_->itemsTable->selectedRanges();


    std::sort(list.begin(), list.end());
    for (int i = list.size() - 1; i > -1; --i) {
        QTableWidgetSelectionRange& item = list[i];
        int bottom = item.bottomRow();
        int top = item.topRow();

        for (int j = bottom; j >= top; --j) {
            double v = 0;
            bool ok;

            v = ui_->itemsTable->item(j, 1)->text().toDouble(&ok);

            if (ok) {
                total_value_ -= v;
            }

            removeItem(ui_->itemsTable->item(j, 0)->text());

            ui_->itemsTable->removeRow(j);
        }
    }

    calculateInflation();
}

void MainWindow::addItem(const QString &item, double value)
{
    total_value_ += value;

    if (this->items_.find(item) != this->items_.end()) {
        QTableWidgetItem* label = this->items_table_[item][1];
        label->setText(QString::number(value));

        total_value_ -= this->items_[item];
        this->items_[item] = value;

        calculateInflation();
        return;
    }

    int rows = ui_->itemsTable->rowCount();
    this->items_[item] = value;

    ui_->itemsTable->setRowCount(rows + 1);

    std::vector<QTableWidgetItem*>& items = this->items_table_[item];

    QString city = ui_->cityList->currentText();

    items.resize(5);

    for (int i = 0; i < 5; ++i) {
        if (!ui_->itemsTable->item(rows, i))
            ui_->itemsTable->setItem(rows, i, new QTableWidgetItem);
    }

    ui_->itemsTable->item(rows, 0)->setText(item);
    ui_->itemsTable->item(rows, 1)->setText(QString::number(value));
    ui_->itemsTable->item(rows, 2)->setText("");
    ui_->itemsTable->item(rows, 3)->setText(InflationManager::getInflationMonthly(item, city));
    ui_->itemsTable->item(rows, 4)->setText(InflationManager::getInflationAnual(item, city));

    for (int i = 0; i < 5; ++i) items[i] = ui_->itemsTable->item(rows, i);

    calculateInflation();
}

void MainWindow::removeItem(const QString &item)
{
    this->items_.erase(item);
    this->items_table_.erase(item);
}

void MainWindow::updateInflation(const QString &)
{
    QString city = ui_->cityList->currentText();

    for (std::map<QString, std::vector<QTableWidgetItem*> >::iterator it = items_table_.begin();
         it != items_table_.end();
         ++it) {
        std::vector<QTableWidgetItem*>& items = it->second;

        QTableWidgetItem* name = items[0];
        QTableWidgetItem* month = items[3];
        QTableWidgetItem* year = items[4];

        month->setText(InflationManager::getInflationMonthly(name->text(), city));
        year->setText(InflationManager::getInflationAnual(name->text(), city));
    }

    calculateInflation();
}

void MainWindow::updateWeigths()
{
    month_inflation_ = 0;
    year_inflation_ = 0;

    for (std::map<QString, std::vector<QTableWidgetItem*> >::iterator it = items_table_.begin();
         it != items_table_.end();
         ++it) {
        std::vector<QTableWidgetItem*>& items = it->second;

        QTableWidgetItem* value = items[1];
        QTableWidgetItem* weigth = items[2];
        QTableWidgetItem* month = items[3];
        QTableWidgetItem* year = items[4];

        bool ok;
        double v = value->text().toDouble(&ok);

        if (ok && total_value_ > 0) {
            double w = v / total_value_;

            month_inflation_ += w * month->text().toDouble();
            year_inflation_ += w * year->text().toDouble();

            weigth->setText(QString::number(w));
        }
    }
}

void MainWindow::updateCities()
{
    QList<QString>& cities = InflationManager::getCities();

    ui_->cityList->clear();
    for (int i = 0; i < cities.size(); ++i) {
        ui_->cityList->addItem(cities[i]);
    }
}

void MainWindow::updateMessage()
{
    ui_->message->setText(QString(InflationManager::getDate()) + "\n"
                          "Gasto Total = R$ " + QString("%1").arg(total_value_, 2) + "\n" +
                          "Inflação (12 meses) = " + QString("%1").arg(year_inflation_, 2) + "%\n" +
                          "Inflação (mês) = " + QString("%1").arg(month_inflation_, 2) + "%\n");
}


ItemDialog::ItemDialog(QWidget *parent) :
    QWidget(parent)
{
    ui_.setupUi(this);
}

ItemDialog::~ItemDialog()
{
}

void ItemDialog::addItem()
{
    MainWindow* m_window = static_cast<MainWindow*>(main_window_);

    QList<QListWidgetItem*> list = ui_.itemList->selectedItems();

    for (int i = 0; i < list.size(); ++i) {
        double value = ui_.itemValue->value();
        QListWidgetItem* item = list[i];
        m_window->addItem(item->text(), value);
    }

    close();
}

void ItemDialog::update()
{
    QList<QString>& items = InflationManager::getItems();

    ui_.itemList->clear();

    for (int i = 0; i < items.size(); ++i) {
        ui_.itemList->addItem(items[i]);
    }
}

void ItemDialog::setMainWindow(QWidget * mw)
{
    main_window_ = mw;
}


