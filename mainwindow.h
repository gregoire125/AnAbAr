// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (mainwindow.h) is part of AnAbAr.

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

/// \file mainwindow.h
/// \brief MainWindow class header.
/// \author Grégoire Lemoult
/// \author Aniss Bendjoudi
/// \version 1.3
/// \date 26 november 2011

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtSql/QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=0);
    ~MainWindow();

private:
    QSqlDatabase *database;
    QMenu *menu_file;
    QAction *action_quit;
    void setup_menu();
};

#endif // MAINWINDOW_H
