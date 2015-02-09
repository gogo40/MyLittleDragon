/*
My Little Dragon

Inflation

(c) 2015, Escrito por Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
*/

#ifndef INFLATION_H
#define INFLATION_H

#include <map>
#include <vector>

#include <QString>
#include <QList>

class Inflation {
public:
    Inflation();
    ~Inflation();

    QString& getInflationAnual(const QString& item, const QString& city);
    QString& getNationalInflationAnual(const QString& item);

    QString& getInflationMonthly(const QString& item, const QString& city);
    QString& getNationalInflationMonthly(const QString& item);

    QList<QString>& getItems();
    QList<QString>& getCities();

    const QString& getCity(int i) const;

    int numberCities();
    int numberItems();

    void clear();
    void init();

    void addCity(const QString& city);
    void addItem(const QString& item);
    void addItem(const QString& item, const QString& city, const QString& month, const QString& year);

private:
    std::map<QString, std::map<QString, QString> > anual_;
    std::map<QString, std::map<QString, QString> > monthly_;

    QList<QString> items_;
    QList<QString> cities_;
};

class InflationManager {
public:
    InflationManager();
    ~InflationManager();

    static void clear();
    static void init();

    static QString& getInflationAnual(const QString& item, const QString& city);
    static QString& getNationalInflationAnual(const QString& item);

    static QString& getInflationMonthly(const QString& item, const QString& city);
    static QString& getNationalInflationMonthly(const QString& item);

    static QList<QString>& getItems();
    static QList<QString>& getCities();

    static const char* getDate();

private:
    static Inflation inflation_;
};

#endif // INFLATION_H

