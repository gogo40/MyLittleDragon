/*
My Little Dragon

Inflation

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

