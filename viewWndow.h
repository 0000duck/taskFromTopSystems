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

#include <thread>
#include <mutex>
#include <condition_variable>



class viewWndow
{
public:

private:
	std::mutex m;
	std::condition_variable cv;


	bool open_window = true;
	bool ready = true;

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

	void close();
};

