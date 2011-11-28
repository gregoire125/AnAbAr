// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (widget.h) is part of AnAbAr.

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

#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include "classes.h"

class WidgetClient : public QWidget
{
    Q_OBJECT
public:
    WidgetClient(Client *client, QWidget *parent);

    Client * getClient();

private:
    Client *m_client;
    QLabel *m_photo;
    QLineEdit *m_surnom;
    QLineEdit *m_nom;
    QDoubleSpinBox *m_solde;

public slots:
    void updateSolde();
    void changerClient(Client *client);
};

class WidgetBoutonClient : public QPushButton
{
    Q_OBJECT
public:
    WidgetBoutonClient(Client *client, QWidget *parent);

private:
    Client *m_client;
    QLabel *m_photo;
    QLabel *m_nom;

signals:
    void clicked(Client *client);

public slots:
    void clicked();
    void update();
};

class WidgetConso : public QWidget
{
    Q_OBJECT
public:
    WidgetConso(Conso *conso, QWidget *parent);

private:
    Conso *m_conso;
    QPushButton *m_bouton;
    QSpinBox *m_nombre;

signals:
    void clicked(Conso * conso, int nombre);

public slots:
    void clicked();

};

class QPushButtonPlus : public QPushButton
{

    Q_OBJECT
public:
    QPushButtonPlus( QString texte_bouton, QWidget * parent, QString donnee );

private:
    QString m_donnee;

signals:
    void clicked(QString donnee);

public slots:
    void clicked();

};

#endif // WIDGET_H
