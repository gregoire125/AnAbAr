// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (caisse.h) is part of AnAbAr.

// AnAbAr is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// AnAbAr is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Foobar. If not, see <http://www.gnu.org/licenses/>.

#ifndef CAISSE_H
#define CAISSE_H

#include <QtGui>
#include "classes.h"
#include "widget.h"
#include "database.h"

class Caisse : public QWidget
{
    Q_OBJECT
public:
    explicit Caisse(QMainWindow *parent = 0);

private:
    QMainWindow m_mainWindow;
    int m_nombrecolonne;
    int m_nombreligne;

    Client m_client;
    QString m_promo;

    WidgetClient * m_widgetClient;

    QVector<Conso*> listConso;
    QVector<WidgetConso*> listWidgetConso;

    QVector<Client*> listClient;
    QVector<WidgetBoutonClient*> listWidgetBoutonClient;

    QVector<QPushButtonPlus*> listPromo;

    QGroupBox *boxPage;
    QVBoxLayout *layoutBoxPage;
    QVector<QPushButtonPlus*> listPage;

signals:

public slots:
    void changerClient(Client *client);
    void changerPromo(QString promo);
    void changerPage(QString page);

    void changerSoldeConso(Conso* conso, int nombre);

};

#endif // CAISSE_H
