#include "viewWndow.h"

viewWndow::viewWndow()
{
	renderwindowDisplay3D = vtkSmartPointer<vtkRenderWindow>::New();
	renDisplay3D = vtkSmartPointer<vtkRenderer>::New();

	irenDisplay3D = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	styleDisplay3D = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

	std::thread t1([&] {this->run(this); });
	t1.detach();
}


void viewWndow::addShape(TopoDS_Shape shape)
{
	IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(shape);
	vtkSmartPointer<IVtkTools_ShapeDataSource>
		DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
	DS->SetShape(aShapeImpl);

	vtkSmartPointer<vtkPolyDataMapper> Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	
	Mapper->SetInputConnection(DS->GetOutputPort());
	
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();;

	actor->SetMapper(Mapper);

	timerCallback->addShape(actor);
}

// нормально
unsigned long __stdcall viewWndow::run(void* param)
{
	this->timerCallback = vtkSmartPointer<vtkMyCallback>::New();

	this->renderwindowDisplay3D->SetSize(600, 400);
	this->renderwindowDisplay3D->AddRenderer(renDisplay3D);
	this->renderwindowDisplay3D->Render();

	this->irenDisplay3D->SetRenderWindow(renderwindowDisplay3D);
	this->irenDisplay3D->SetInteractorStyle(styleDisplay3D);

	this->irenDisplay3D->Initialize();

	
	this->irenDisplay3D->AddObserver(vtkCommand::TimerEvent, timerCallback);

	this->irenDisplay3D->CreateRepeatingTimer(100);

	irenDisplay3D->Start();

	return 0;
}

void viewWndow::clean()
{
	timerCallback->Clean();
}
