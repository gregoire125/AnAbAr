// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (database.h) is part of AnAbAr.

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

#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include "classes.h"
#include "widget.h"
#include <QtSql/QSqlQuery>

bool createConnection( QSqlDatabase *db );

QVector<Conso*> getListConso();

QVector<Client*> getListClient(QString promo,int size, int offset=0);

QVector<QPushButtonPlus*> getListPromo(QWidget *parent);

QVector<QPushButtonPlus*> getListPage(QWidget *parent, QString promo, int size);


#endif // DATABASE_H
