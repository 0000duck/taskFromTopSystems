#include <iostream>
#include <TopoDs_Shape.hxx>
#include <IVtkOCC_Shape.hxx>

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <IVtkTools_ShapeDataSource.hxx>
#include <BRepPrimAPI_MakeBox.hxx>

#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>


int main()
{
    BRepPrimAPI_MakeBox mkBox(1., 2., 3.);
    mkBox.Build();
    TopoDS_Shape aShape = mkBox.Shape();

    vtkSmartPointer<vtkRenderWindow>
        renwin = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderer>
        ren = vtkSmartPointer<vtkRenderer>::New();
    renwin->AddRenderer(ren);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera>
        istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    vtkSmartPointer<vtkRenderWindowInteractor>
        iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    
    iren->SetRenderWindow(renwin);
    iren->SetInteractorStyle(istyle);

    IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(aShape);
    vtkSmartPointer<IVtkTools_ShapeDataSource> DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
    DS->SetShape(aShapeImpl);

    vtkSmartPointer<vtkPolyDataMapper> Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    Mapper->SetInputConnection(DS->GetOutputPort());

    vtkSmartPointer<vtkActor> Actor = vtkSmartPointer<vtkActor>::New();

    Actor->SetMapper(Mapper);

    ren->AddActor(Actor);

    renwin->Render();
    iren->Start();

}