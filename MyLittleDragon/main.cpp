/*
My Little Dragon

Main

(c) 2015, Escrito por Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    InflationManager::init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
