// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (caisse.cpp) is part of AnAbAr.

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

#include "caisse.h"

Caisse::Caisse(QMainWindow *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    QSplitter *splitter = new QSplitter(this);
    layout->addWidget(splitter);
    splitter->setChildrenCollapsible( false );
        QWidget *widgetGauche = new QWidget(this);
        QVBoxLayout *layout_gauche = new QVBoxLayout(widgetGauche);
        splitter->addWidget(widgetGauche);
        QWidget *widgetCentre = new QWidget(this);
        QGridLayout *layout_centre = new QGridLayout(widgetCentre);
        splitter->addWidget(widgetCentre);
        QWidget *widgetDroite = new QWidget(this);
        QVBoxLayout *layout_droite = new QVBoxLayout(widgetDroite);
        splitter->addWidget(widgetDroite);


    // On construit le tableau avec tous les bouton clients
    m_promo="125";
    m_nombrecolonne=3;
    m_nombreligne=1;
    listClient = getListClient(m_promo,m_nombreligne * m_nombrecolonne);

    //On construit le layout de gauche en commencant par l'affichage du client en cours
    m_widgetClient = new WidgetClient(listClient[0],this);
    layout_gauche->addWidget(m_widgetClient);

    for (int i=0; i<m_nombreligne * m_nombrecolonne ; i++) {
        listWidgetBoutonClient.push_back(new WidgetBoutonClient(listClient[i],this));
        connect(listWidgetBoutonClient[i],SIGNAL(clicked(Client*)),this,SLOT(changerClient(Client*)));
        connect(listClient[i],SIGNAL(changed()),listWidgetBoutonClient[i],SLOT(update()));
        layout_centre->addWidget(listWidgetBoutonClient[i],i/m_nombrecolonne,i%m_nombrecolonne);
    }

    // On construit la liste des consommations
    listConso = getListConso();
    for (int i=0; i<listConso.size(); i++)
    {
        listWidgetConso.push_back(new WidgetConso(listConso[i],this));
        connect(listWidgetConso[i],SIGNAL(clicked(Conso*,int)),this,SLOT(changerSoldeConso(Conso*,int)));
        layout_gauche->addWidget(listWidgetConso[i]);
    }

    // On construit les boutons de pages et de promo

    QGroupBox *boxPromo = new QGroupBox("Promotion",this);
    QVBoxLayout *layoutBoxPromo = new QVBoxLayout(boxPromo);
    layout_droite->addWidget(boxPromo);
    listPromo = getListPromo(this);
    for (int i=0; i<listPromo.size(); i++) {
        layoutBoxPromo->addWidget(listPromo[i]);
        connect(listPromo[i],SIGNAL(clicked(QString)),this,SLOT(changerPromo(QString)));
    }

    boxPage = new QGroupBox("Promo " + m_promo ,this);
    layoutBoxPage = new QVBoxLayout(boxPage);
    layout_droite->addWidget(boxPage);
    listPage = getListPage(this, m_promo, m_nombreligne * m_nombrecolonne);
    for (int i=0; i<listPage.size(); i++) {
        layoutBoxPage->addWidget(listPage[i]);
        connect(listPage[i],SIGNAL(clicked(QString)),this,SLOT(changerPage(QString)));
    }

}

void Caisse::changerClient(Client *client)
{
    m_widgetClient->changerClient(client);
}

void Caisse::changerPromo(QString promo)
{
    m_promo=promo;

    QVector<Client*> newListClient = getListClient(promo,m_nombreligne*m_nombrecolonne);
    for (int i=0; i<m_nombreligne * m_nombrecolonne ; i++) {
        listClient[i]->changerClient(newListClient[i]);
        delete(newListClient[i]);
    }

    this->changerClient(listClient[0]);

    boxPage->setTitle("Promo " + m_promo);
    QVector<QPushButtonPlus*> newListPage = getListPage(this,m_promo,m_nombreligne*m_nombrecolonne);
    int i=0;
    while ( i<newListPage.size() || i<listPage.size() ){
        if (i<newListPage.size() && i<listPage.size()){
            listPage[i]->setText(newListPage[i]->text());
        }
        else if ( i<listPage.size() ) {
            listPage[i]->close();
        }
        else if ( i<newListPage.size()) {
            listPage.push_back(new QPushButtonPlus(newListPage[i]->text(),this,QString::number(i)));
            layoutBoxPage->addWidget(listPage[i]);
            connect(listPage[i],SIGNAL(clicked(QString)),this,SLOT(changerPage(QString)));
        }
        i++;
    }
    listPage.resize(newListPage.size());
}

void Caisse::changerPage(QString page)
{
    QVector<Client*> newListClient = getListClient(m_promo,m_nombreligne*m_nombrecolonne,m_nombreligne*m_nombrecolonne*page.toInt());
    for (int i=0; i<m_nombreligne * m_nombrecolonne ; i++) {
        listClient[i]->changerClient(newListClient[i]);
    }
    this->changerClient(listClient[0]);
}

void Caisse::changerSoldeConso(Conso* conso, int nombre)
{

}
