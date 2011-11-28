// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (mainwindow.cpp) is part of AnAbAr.

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

/// \file mainwindow.cpp
/// \brief MainWindow class source code.
/// \author Grégoire Lemoult
/// \author Aniss Bendjoudi
/// \version 1.3
/// \date 26 november 2011

#include "mainwindow.h"
#include "database.h"
#include "caisse.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("AnAbAr - C++"));

    // Menu
    setup_menu();

    // Database connection ... or die
    database=new QSqlDatabase;
    if(createConnection(database))
        setCentralWidget(new Caisse(this));
    else
        exit(1);
}

MainWindow::~MainWindow()
{
    delete database;
}

void MainWindow::setup_menu()
{
    menu_file=menuBar()->addMenu(tr("&Fichier"));
    action_quit=menu_file->addAction(tr("&Quitter"));
    connect(action_quit,SIGNAL(triggered()),qApp,SLOT(quit()));
    action_quit->setShortcut(QKeySequence("Ctrl+Q"));
}
