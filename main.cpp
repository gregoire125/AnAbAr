// Copyright 2011 Grégoire Lemoult and Aniss Bendjoudi.

// This file (main.cpp) is part of AnAbAr.

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

/// \file main.cpp
/// \brief AnAbAr: account management software.
/// \author Grégoire Lemoult
/// \author Aniss Bendjoudi
/// \version 1.3
/// \date 26 november 2011

#include <QApplication>
#include "mainwindow.h"

/// \fn int main(int argc, char *argv[])
/// \brief Main software entry point.
/// \param argc Number of input arguments including the software name and path.
/// \param argv Input arguments as an array of strings.
/// \return Status code of the 'exec' method from the QApplication class.
int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    MainWindow window;

    window.show();

    return application.exec();
}
