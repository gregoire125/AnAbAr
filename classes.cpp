// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (classes.cpp) is part of AnAbAr.

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

#include "classes.h"

Client::Client()
{
    m_empty=true;
}

Client::Client(QString prenom, QString nom, QString surnom, QString promo, QString statut, float solde, QString mail, QString historique) :
        m_prenom(prenom), m_nom(nom), m_surnom(surnom), m_promo(promo), m_statut(statut), m_solde(solde), m_mail(mail), m_historique(historique)
{
    m_empty=false;
}

void Client::changerClient(Client *client)
{
    m_prenom=client->m_prenom;
    m_nom=client->m_nom;
    m_empty=client->m_empty;
    m_surnom=client->m_surnom;
    m_promo=client->m_promo;
    m_statut=client->m_statut;
    m_solde=client->m_solde;
    m_mail=client->m_mail;
    m_historique=client->m_historique;

    emit changed();
}

QString Client::getPrenom(){ return m_prenom; }
QString Client::getNom(){ return m_nom; }
QString Client::getSurnom(){ return m_surnom; }
float Client::getSolde(){ return m_solde; }
bool Client::isempty(){ return m_empty; }

void Client::setSoldeConso(Conso *conso, int nombre)
{
    if ( m_statut=="client" )               m_solde -= conso->getPrix()*nombre;
    else if ( m_statut=="barman" )          m_solde -= conso->getPrixBar()*nombre;
    else if ( m_statut=="exterieur" )       m_solde -= conso->getPrixExt()*nombre;
    else if ( m_statut=="ancien" )          m_solde -= conso->getPrixAnc()*nombre;

    QString str=QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm");
    str += "\t" + conso->getNom() + "\t" + QString::number(m_solde) + "\n";
    m_historique = str + m_historique;

    QSqlQuery req;
    req.exec("UPDATE client SET solde = " + QString::number(m_solde) +" , historique = \"" + str + "\" || historique WHERE prenom=\""+m_prenom+"\" AND nom=\"" + m_nom + "\"");

    emit changed();
}

void Client::setSoldeBarman(Barman barman, float somme)
{
    m_solde += somme;

    QString str=QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm");
    str += "\t" + barman.getNom(); + "\t" + QString::number(m_solde) + "\n";
    m_historique = str + m_historique;

    QSqlQuery req;
    req.exec("UPDATE client SET solde = " + QString::number(m_solde) +" , historique = \"" + str + "\" || historique WHERE prenom=\""+m_prenom+"\" AND nom=\"" + m_nom + "\"");

    emit changed();
}

Conso::Conso(QString nom)
{
    m_nom=nom;

    QSqlQuery req;
    req.exec("SELECT prix,prix_bar,prix_ext,prix_anc FROM conso WHERE nom=\""+nom+"\"");
    if (req.next()) {
        m_prix = req.value(0).toFloat();
        m_prix_bar = req.value(1).toFloat();
        m_prix_ext = req.value(2).toFloat();
        m_prix_anc = req.value(3).toFloat();
    }
    else qDebug("fail2");
}

Conso::Conso(QString nom, float prix, float prix_bar, float prix_anc, float prix_ext) : m_nom(nom), m_prix(prix), m_prix_bar(prix_bar), m_prix_anc(prix_anc), m_prix_ext(prix_ext) {}

QString Conso::getNom(){ return m_nom; }
float Conso::getPrix() { return m_prix; }
float Conso::getPrixBar() { return m_prix_bar; }
float Conso::getPrixExt() { return m_prix_ext; }
float Conso::getPrixAnc() { return m_prix_anc; }


Barman::Barman(QString mdp){
    QSqlQuery req;
    QString mdp_hash(QCryptographicHash::hash(mdp.toAscii(),QCryptographicHash::Sha1).toHex());
    req.exec("SELECT nom FROM barman WHERE password=\""+mdp_hash+"\"");
    if (req.next())
        m_nom = req.value(0).toString();
}

QString Barman::getNom(){ return m_nom; }
