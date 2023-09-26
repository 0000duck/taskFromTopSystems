#pragma once

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

#include <TopoDs_Shape.hxx>
#include <IVtkOCC_Shape.hxx>


class viewWndow
{
public:

private:
	vtkSmartPointer<vtkRenderWindow> renwin_;
	vtkSmartPointer<vtkRenderer> ren_;

	vtkSmartPointer<vtkRenderWindowInteractor> iren_;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> istyle_;

	vtkSmartPointer<vtkActor> actor_;
public:
	viewWndow();

	void addShape(TopoDS_Shape shape);
	void run();
	void clean();
};

