// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (database.cpp) is part of AnAbAr.

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

#include "database.h"
#include "mainwindow.h"
#include "classes.h"

bool createConnection( QSqlDatabase *db )
{
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("AnAbAr_db.db");
    if (!db->open()) {
        QMessageBox::critical(0, qApp->tr("Impossible d'ouvrir la base de données"),
            qApp->tr("Connexion à la base de données impossible, vérifiez que le chemin d'accès au fichier est correct ou que vous disposez des droits suffisants."), QMessageBox::Cancel,
                     QMessageBox::NoButton);
        return false;
    }
    else {
        return true;
    }
}

QVector<Conso *> getListConso()
{
    QVector<Conso*> listConso;

    QSqlQuery req;
    req.exec("SELECT nom,prix,prix_bar,prix_anc,prix_ext FROM conso");
    int i=0;
    while (req.next()) {
        listConso.push_back(new Conso(req.value(0).toString(), req.value(1).toFloat(), req.value(2).toFloat(), req.value(3).toFloat(), req.value(4).toFloat() ));
        i++;
    }

    return listConso;
}

QVector<Client*> getListClient(QString promo,int size, int offset)
{
    QVector<Client*> listClient;

    QSqlQuery req;
    req.exec("SELECT prenom,nom,surnom,promo,statut,solde,mail,historique FROM client WHERE promo=\"" + promo + "\" ORDER BY surnom LIMIT " + QString::number(offset) + "," + QString::number(size+offset));
    int i=0;
    while (req.next()) {
        listClient.push_back(new Client(req.value(0).toString(),
                                        req.value(1).toString(),
                                        req.value(2).toString(),
                                        req.value(3).toString(),
                                        req.value(4).toString(),
                                        req.value(5).toFloat(),
                                        req.value(6).toString(),
                                        req.value(7).toString()  ));
        i++;
    }

    while (i<size) {
        listClient.push_back(new Client());
        i++;
    }

    return listClient;
}

QVector<QPushButtonPlus*> getListPromo(QWidget *parent)
{
    QVector<QPushButtonPlus*> listPromo;

    QSqlQuery req;
    req.exec("SELECT DISTINCT promo FROM client ORDER BY promo");
    int i=0;
    while (req.next()) {
        listPromo.push_back(new QPushButtonPlus( req.value(0).toString() , parent , req.value(0).toString()));
        i++;
    }

    return listPromo;
}

QVector<QPushButtonPlus*> getListPage(QWidget *parent, QString promo, int size)
{
    QVector<QPushButtonPlus*> listPage;

    QSqlQuery req;
    req.exec("SELECT surnom FROM client WHERE promo=\"" + promo + "\" ORDER BY surnom");
    int i=0;
    int j=0;
    QString nom1, nom2;
    while (req.next()) {
        nom2 = req.value(0).toString();
        //nom2 = req.value(0).toString();
        if (i%size==0) {
            nom1 = req.value(0).toString();
        }
        else if (i%size==size-1) {
            listPage.push_back(new QPushButtonPlus(nom1 + " / " +nom2 , parent, QString::number(j)));
            j++;
        }
        i++;
    }
    if ((i-1)%size!=size-1){
        if (nom1!=nom2)
            listPage.push_back(new QPushButtonPlus(nom1 + " / " +nom2 , parent, QString::number(j)));
        else
            listPage.push_back(new QPushButtonPlus(nom1 , parent, QString::number(j)));
    }

    return listPage;
}
