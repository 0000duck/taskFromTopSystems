#include "viewWindow.h"

ViewWndow::ViewWndow(std::queue<Message>& queue): queue_(queue)
{
	renderwindowDisplay3D = vtkSmartPointer<vtkRenderWindow>::New();
	renDisplay3D = vtkSmartPointer<vtkRenderer>::New();

	irenDisplay3D = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	styleDisplay3D = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

	t1 = std::thread(([=] {this->run(this); }));
	t1.detach();
}


void ViewWndow::updateShape(TopoDS_Shape temp)
{
	IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(temp);
	vtkSmartPointer<IVtkTools_ShapeDataSource>
		DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
	DS->SetShape(aShapeImpl);

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	
	mapper->SetInputConnection(DS->GetOutputPort());
	
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();;

	actor->SetMapper(mapper);

	timerCallback->updateActor(actor);
}

void ViewWndow::exit()
{
	irenDisplay3D->UnRegister(irenDisplay3D);
	irenDisplay3D->TerminateApp();
}

// нормально
unsigned long __stdcall ViewWndow::run(void* param)
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
