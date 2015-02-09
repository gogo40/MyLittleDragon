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

#include "inflation.h"
#include <QMessageBox>

//////////////////////////////////////////////////////////
///RAW DATA
//////////////////////////////////////////////////////////

#include "raw_data.txt"

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

Inflation InflationManager::inflation_;




Inflation::Inflation()
{

}

Inflation::~Inflation()
{

}

QString& Inflation::getInflationAnual(const QString &item, const QString &city)
{
    return this->anual_[item][city];
}

QString& Inflation::getNationalInflationAnual(const QString &item)
{
    return this->monthly_[item]["NACIONAL"];
}

QString& Inflation::getInflationMonthly(const QString &item, const QString &city)
{
    return this->monthly_[item][city];
}

QString& Inflation::getNationalInflationMonthly(const QString &item)
{
    return this->monthly_[item]["NACIONAL"];
}

QList<QString> &Inflation::getItems()
{
    return this->items_;
}

QList<QString> &Inflation::getCities()
{
    return this->cities_;
}

const QString& Inflation::getCity(int i) const
{
    return this->cities_.at(i);
}

int Inflation::numberCities()
{
    return this->cities_.size();
}

int Inflation::numberItems()
{
    return this->items_.size();
}

void Inflation::clear()
{
    this->items_.clear();
    this->cities_.clear();
    this->monthly_.clear();
    this->anual_.clear();
}

void Inflation::init()
{
    clear();

    for (const char** c = _g_cities; *c; ++c) {
        addCity(*c);
    }

    for (const char** i = _g_items; *i; ++i) {
        addItem(*i);
    }

    int n_cities = numberCities();
    int n_items = numberItems();

    for (int i = 0; i < n_items; ++i) {
        QString item(_g_monthly[i * (n_cities + 1)]);
        for (int j = 0; j < n_cities; ++j) {
            int p = i * (n_cities + 1) + j + 1;
            QString city(_g_cities[j]);
            QString value(_g_monthly[p]);
            this->monthly_[item][city] = value;
        }
    }

    for (int i = 0; i < n_items; ++i) {
        QString item(_g_anual[i * (n_cities + 1)]);
        for (int j = 0; j < n_cities; ++j) {
            int p = i * (n_cities + 1) + j + 1;
            QString city(_g_cities[j]);
            QString value(_g_anual[p]);
            this->anual_[item][city] = value;
        }
    }
}

void Inflation::addCity(const QString &city)
{
    this->cities_.push_back(city);
}

void Inflation::addItem(const QString &item)
{
    this->items_.push_back(item);
}

void Inflation::addItem(const QString &item, const QString &city, const QString &month, const QString &year)
{
    this->monthly_[item][city] = month;
    this->anual_[item][city] = year;
}


InflationManager::InflationManager()
{

}

InflationManager::~InflationManager()
{

}

void InflationManager::clear()
{
    inflation_.clear();
}

void InflationManager::init()
{
    inflation_.init();
}

QString& InflationManager::getInflationAnual(const QString &item, const QString &city)
{
    return inflation_.getInflationAnual(item, city);
}

QString& InflationManager::getNationalInflationAnual(const QString &item)
{
    return inflation_.getNationalInflationAnual(item);
}

QString& InflationManager::getInflationMonthly(const QString &item, const QString &city)
{
    return inflation_.getInflationMonthly(item, city);
}

QString& InflationManager::getNationalInflationMonthly(const QString &item)
{
    return inflation_.getNationalInflationMonthly(item);
}

QList<QString> &InflationManager::getItems()
{
    return inflation_.getItems();
}

QList<QString> &InflationManager::getCities()
{
    return inflation_.getCities();
}

const char *InflationManager::getDate()
{
    return g_month_year;
}
