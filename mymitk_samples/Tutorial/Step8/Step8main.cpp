/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "QmitkRegisterClasses.h"
#include "Step8.h"

#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <itksys/SystemTools.hxx>

int main(int argc, char *argv[]) {
    QApplication qtapplication(argc, argv);

    if (argc < 2) {
        fprintf(stderr, "Usage:   %s [filename1] [filename2] ...\n\n",
                itksys::SystemTools::GetFilenameName(argv[0]).c_str());
        return 1;
    }

    // Register Qmitk-dependent global instances
    QmitkRegisterClasses();

    Step8 mainWidget(argc, argv, nullptr);
    mainWidget.Initialize();

    if (QString(argv[1]).toInt() > 0) {
        WId wid = WId(QString(argv[1]).toInt());
        QWindow *window = QWindow::fromWinId(wid);

        mainWidget.setProperty("_q_embedded_native_parent_handle", QVariant(wid));
        mainWidget.winId();
        mainWidget.windowHandle()->setParent(window);
    }

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rect = screen->geometry();
    rect.height();

    int windowWidth = 1024;
    int windowHeight = 768;
    mainWidget.resize(windowWidth, windowHeight);
    mainWidget.show();
    mainWidget.move((rect.width() - windowWidth) / 2, (rect.height() - windowHeight) / 2);

    return qtapplication.exec();
}
/**
\example Step8main.cpp
*/
