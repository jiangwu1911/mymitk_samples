/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "QmitkRegisterClasses.h"
#include "QmitkRenderWindow.h"
#include "QmitkSliceWidget.h"

#include "mitkNodePredicateDataType.h"
#include "mitkProperties.h"
#include "mitkRenderingManager.h"
#include "mitkStandaloneDataStorage.h"

#include "mitkPointSet.h"
#include "mitkPointSetDataInteractor.h"

#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <itksys/SystemTools.hxx>
#include <mitkIOUtil.h>

int main(int argc, char *argv[]) {
    QApplication qtapplication(argc, argv);

    if (argc < 2) {
        fprintf(stderr, "Usage:   %s [filename1] [filename2] ...\n\n",
                itksys::SystemTools::GetFilenameName(argv[0]).c_str());
        return 1;
    }

    QmitkRegisterClasses();

    mitk::StandaloneDataStorage::Pointer ds = mitk::StandaloneDataStorage::New();

    int i;
    for (i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-testing") == 0)
            continue;

        mitk::StandaloneDataStorage::SetOfObjects::Pointer dataNodes = mitk::IOUtil::Load(argv[i], *ds);

        if (dataNodes->empty()) {
            fprintf(stderr, "Could not open file %s \n\n", argv[i]);
            exit(2);
        }
    }

    QWidget toplevelWidget;
    QGridLayout layout;
    layout.setSpacing(2);
    layout.setMargin(0);
    toplevelWidget.setLayout(&layout);

    QmitkRenderWindow renderWindow(&toplevelWidget);
    layout.addWidget(&renderWindow, 1, 1);

    renderWindow.GetRenderer()->SetDataStorage(ds);
    renderWindow.GetRenderer()->SetMapperID(mitk::BaseRenderer::Standard3D);
    renderWindow.GetRenderer()->GetVtkRenderer()->ResetCamera();

    QmitkSliceWidget view2(&toplevelWidget);
    layout.addWidget(&view2, 0, 0);
    view2.SetDataStorage(ds);
    mitk::DataStorage::SetOfObjects::ConstPointer rs = ds->GetSubset(mitk::TNodePredicateDataType<mitk::Image>::New());
    view2.SetData(rs->Begin(), mitk::SliceNavigationController::Axial);
    ds->Add(view2.GetRenderer()->GetCurrentWorldPlaneGeometryNode());

    QmitkSliceWidget view3(&toplevelWidget);
    layout.addWidget(&view3, 0, 1);
    view3.SetDataStorage(ds);
    view3.SetData(rs->Begin(), mitk::SliceNavigationController::Sagittal);
    ds->Add(view3.GetRenderer()->GetCurrentWorldPlaneGeometryNode());

    QmitkSliceWidget view4(&toplevelWidget);
    layout.addWidget(&view4, 1, 0);
    view4.SetDataStorage(ds);
    view4.SetData(rs->Begin(), mitk::SliceNavigationController::Frontal);
    ds->Add(view4.GetRenderer()->GetCurrentWorldPlaneGeometryNode());

    mitk::PointSet::Pointer pointSet = mitk::PointSet::New();
    mitk::DataNode::Pointer pointSetNode = mitk::DataNode::New();
    pointSetNode->SetData(pointSet);
    ds->Add(pointSetNode);

    mitk::PointSetDataInteractor::Pointer interactor = mitk::PointSetDataInteractor::New();
    interactor->LoadStateMachine("PointSet.xml");
    interactor->SetEventConfig("PointSetConfig.xml");
    interactor->SetDataNode(pointSetNode);

    toplevelWidget.resize(800, 480);
    toplevelWidget.show();

    return qtapplication.exec();
}
