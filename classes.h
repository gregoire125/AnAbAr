// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (classes.h) is part of AnAbAr.

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

#ifndef CLASSES_H
#define CLASSES_H

#include <QtGui>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class Conso
{
public:
    Conso(QString nom);
    Conso(QString nom, float m_prix, float m_prix_bar, float m_prix_anc, float m_prix_ext);

    QString getNom();
    float getPrix();
    float getPrixBar();
    float getPrixExt();
    float getPrixAnc();

private:
    QString m_nom;
    float m_prix;
    float m_prix_bar;
    float m_prix_anc;
    float m_prix_ext;

};

class Barman
{
public:
    Barman(QString mdp);

    QString getNom();

private:
    QString m_nom;
};

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    Client(QString prenom, QString nom, QString surnom, QString promo, QString statut, float solde, QString mail, QString historique);

    QString getPrenom();
    QString getNom();
    QString getSurnom();
    float getSolde();
    bool isempty();

private:
    bool m_empty;

    QString m_prenom;
    QString m_nom;
    QString m_surnom;
    QString m_promo;
    QString m_statut;
    float m_solde;
    QString m_mail;
    QString m_historique;

signals:
    void changed();

public slots:
    void setSoldeConso(Conso *conso , int nombre);
    void setSoldeBarman(Barman barman, float somme);
    void changerClient(Client *client);
};

#endif // CLASSES_H
