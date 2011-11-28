// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (widget.cpp) is part of AnAbAr.

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

#include "widget.h"

WidgetClient::WidgetClient(Client *client , QWidget *parent) :
        QWidget(parent)
{
    m_client=client;
    connect(m_client,SIGNAL(changed()),this,SLOT(updateSolde()));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    m_photo = new QLabel(this);
    m_photo->setPixmap(QPixmap(QString::fromUtf8("C://Qt/MonProjet/AnAbAr-build-desktop/inconnu.jpg")));
    m_photo->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_photo);

    m_surnom = new QLineEdit(this);
    m_surnom->setText(client->getSurnom());
    m_surnom->setAlignment(Qt::AlignCenter);
    m_surnom->setReadOnly(true);
    layout->addWidget(m_surnom);

    m_nom = new QLineEdit(this);
    m_nom->setText(client->getPrenom() + " " + client->getNom());
    m_nom->setAlignment(Qt::AlignCenter);
    m_nom->setReadOnly(true);
    layout->addWidget(m_nom);

    m_solde = new QDoubleSpinBox(this);
    m_solde->setWrapping(false);
    m_solde->setAlignment(Qt::AlignCenter);
    m_solde->setReadOnly(true);
    m_solde->setButtonSymbols(QAbstractSpinBox::NoButtons);
    m_solde->setMinimum(-10000);
    m_solde->setMaximum(10000);
    m_solde->setSingleStep(0.01);
    m_solde->setPrefix("Solde : ");
    m_solde->setSuffix(" " + QString(8364));
    m_solde->setValue((double)client->getSolde());
    layout->addWidget(m_solde);
}

void WidgetClient::updateSolde()
{
    m_solde->setValue((double)m_client->getSolde());
}

void WidgetClient::changerClient(Client *client)
{
    m_client=client;

    m_surnom->setText(m_client->getSurnom());
    m_nom->setText(m_client->getPrenom() + " " + m_client->getNom());
    m_solde->setValue((double)m_client->getSolde());
}

Client * WidgetClient::getClient() { return m_client; }

WidgetConso::WidgetConso(Conso *conso, QWidget *parent) :
        QWidget(parent)
{
    m_conso=conso;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    m_bouton = new QPushButton(conso->getNom(),this);
    QString tooltip = "prix : " + QString::number(conso->getPrix()) + ";" + QString::number(conso->getPrixExt()) + ";" + QString::number(conso->getPrixBar()) + ";" + QString::number(conso->getPrixBar()) ;
    m_bouton->setToolTip ( tooltip );
    layout->addWidget(m_bouton);
    connect(m_bouton,SIGNAL(clicked()),this,SLOT(clicked()));

    m_nombre = new QSpinBox(this);
    m_nombre->setMinimum(1);
    m_nombre->setMaximumWidth(40);
    layout->addWidget(m_nombre);
}

void WidgetConso::clicked() { emit clicked(m_conso, m_nombre->value()); }

WidgetBoutonClient::WidgetBoutonClient(Client *client, QWidget *parent) :
        QPushButton(parent)
{
    m_client=client;
    connect(this,SIGNAL(clicked()),this,SLOT(clicked()));

    m_photo = new QLabel(this);
    m_photo->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

    m_nom = new QLabel(this);
    m_nom->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

    if (client->isempty()) {
        this->setEnabled(false);
        this->setFlat(true);
        m_photo->hide();
        m_nom->hide();
    }
    else {
        m_nom->setText(client->getSurnom()[0].toUpper() + client->getSurnom().mid(1));
        QFileInfo fi("C:\\Qt\\MonProjet\\AnAbAr-build-desktop\\photos\\" + client->getPrenom() + "_" + client->getNom() + ".jpg");
        if (fi.exists())
            m_photo->setPixmap(QPixmap(fi.absoluteFilePath()));
        else
            m_photo->setPixmap(QPixmap("C:\\Qt\\MonProjet\\AnAbAr-build-desktop\\photos\\inconnu.jpg"));

        this->setEnabled(true);
        this->setFlat(false);
        m_photo->show();
        m_nom->show();
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_photo);
    layout->addWidget(m_nom);
    layout->setContentsMargins ( 6,6,6,6 );
    this->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Expanding );

}

void WidgetBoutonClient::clicked() { emit clicked(m_client); }

void WidgetBoutonClient::update(){
    if (m_client->isempty()) {
        this->setEnabled(false);
        this->setFlat(true);
        m_photo->hide();
        m_nom->hide();
    }
    else {
        m_nom->setText(m_client->getSurnom()[0].toUpper() + m_client->getSurnom().mid(1));
        QFileInfo fi("C:\\Qt\\MonProjet\\AnAbAr-build-desktop\\photos\\" + m_client->getPrenom() + "_" + m_client->getNom() + ".jpg");
        if (fi.exists())
            m_photo->setPixmap(QPixmap(fi.absoluteFilePath()));
        else
            m_photo->setPixmap(QPixmap("C:\\Qt\\MonProjet\\AnAbAr-build-desktop\\photos\\inconnu.jpg"));

        this->setEnabled(true);
        this->setFlat(false);
        m_photo->show();
        m_nom->show();
    }
}

QPushButtonPlus::QPushButtonPlus(QString texte_bouton, QWidget * parent, QString donnee) :
   QPushButton(texte_bouton, parent)
{
    m_donnee = donnee;
    connect(this,SIGNAL(clicked()),this,SLOT(clicked()));
}

void QPushButtonPlus::clicked()
{
    emit clicked(m_donnee);
}
