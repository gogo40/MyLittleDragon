/*
My Little Dragon

Main Window

(c) 2015, Escrito por Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

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

void MainWindow::removeItems()
{
    QList<QTableWidgetSelectionRange> list = ui_->itemsTable->selectedRanges();

    for (int i = list.size() - 1; i > -1; --i) {
        QTableWidgetSelectionRange& item = list[i];
        int bottom = item.bottomRow();
        int top = item.topRow();

        for (int j = bottom; j >= top; --j) {
            QLabel* label = static_cast<QLabel*>(ui_->itemsTable-> cellWidget(j, 0));
            QLabel* value = static_cast<QLabel*>(ui_->itemsTable-> cellWidget(j, 1));

            double v = 0;
            bool ok;
            v = value->text().toDouble(&ok);

            if (ok) {
                total_value_ -= v;
            }

            removeItem(label->text());

            ui_->itemsTable->removeRow(j);
        }
    }

    calculateInflation();
}

void MainWindow::addItem(const QString &item, double value)
{
    total_value_ += value;

    if (this->items_.find(item) != this->items_.end()) {
        QLabel* label = static_cast<QLabel*>(this->items_table_[item][1]);
        label->setText(QString::number(value));
        total_value_ -= this->items_[item];
        this->items_[item] = value;

        calculateInflation();
        return;
    }

    int rows = ui_->itemsTable->rowCount();
    this->items_[item] = value;

    ui_->itemsTable->setRowCount(rows + 1);

    std::vector<QWidget*>& items = this->items_table_[item];

    QString city = ui_->cityList->currentText();

    items.resize(5);

    ui_->itemsTable->setCellWidget(rows, 0, new QLabel(item));
    ui_->itemsTable->setCellWidget(rows, 1, new QLabel(QString::number(value)));
    ui_->itemsTable->setCellWidget(rows, 2, new QLabel(""));
    ui_->itemsTable->setCellWidget(rows, 3, new QLabel(InflationManager::getInflationMonthly(item, city)));
    ui_->itemsTable->setCellWidget(rows, 4, new QLabel(InflationManager::getInflationAnual(item, city)));

    for (int i = 0; i < 5; ++i) items[i] = ui_->itemsTable->cellWidget(rows, i);

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

    for (std::map<QString, std::vector<QWidget*> >::iterator it = items_table_.begin();
         it != items_table_.end();
         ++it) {
        std::vector<QWidget*>& items = it->second;

        QLabel* name = static_cast<QLabel*>(items[0]);
        QLabel* month = static_cast<QLabel*>(items[3]);
        QLabel* year = static_cast<QLabel*>(items[4]);

        month->setText(InflationManager::getInflationMonthly(name->text(), city));
        year->setText(InflationManager::getInflationAnual(name->text(), city));
    }

    calculateInflation();
}

void MainWindow::updateWeigths()
{
    month_inflation_ = 0;
    year_inflation_ = 0;

    for (std::map<QString, std::vector<QWidget*> >::iterator it = items_table_.begin();
         it != items_table_.end();
         ++it) {
        std::vector<QWidget*>& items = it->second;

        QLabel* value = static_cast<QLabel*>(items[1]);
        QLabel* weigth = static_cast<QLabel*>(items[2]);
        QLabel* month = static_cast<QLabel*>(items[3]);
        QLabel* year = static_cast<QLabel*>(items[4]);

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
                          "Gasto Total = R$ " + QString::number(total_value_) + "\n" +
                          "Inflação (12 meses) = " + QString::number(year_inflation_) + "%\n" +
                          "Inflação (mês) = " + QString::number(month_inflation_) + "%\n");
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


