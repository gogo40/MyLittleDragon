/*
My Little Dragon

Main Window

(c) 2015, Escrito por Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <ui_itemdialog.h>

#include "inflation.h"

class ItemDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ItemDialog(QWidget *parent = 0);
    ~ItemDialog();

public slots:
    void addItem();
    void update();
    void setMainWindow(QWidget*);

private:
    Ui::ItemDialog ui_;
    QWidget* main_window_;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openAddItemDialog();
    void calculateInflation();
    void removeItems();

    void addItem(const QString& item, double value);
    void removeItem(const QString& item);
    void updateInflation(const QString&);
    void updateWeigths();

    void updateCities();
    void updateMessage();

private:
    Ui::MainWindow *ui_;
    ItemDialog add_item_dialog_;

    std::map<QString, double> items_;
    std::map<QString, std::vector<QWidget*> > items_table_;

    double total_value_;
    double month_inflation_;
    double year_inflation_;
};

#endif // MAINWINDOW_H
