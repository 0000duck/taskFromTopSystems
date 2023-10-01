#include "viewWindow.h"

ViewWndow::ViewWndow(std::queue<Message>& queue): queue_(queue)
{
	renderWindowDisplay3D_ = vtkSmartPointer<vtkRenderWindow>::New();
	renDisplay3D_ = vtkSmartPointer<vtkRenderer>::New();

	irenDisplay3D_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	styleDisplay3D_ = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

	std::thread viewTread([=] {this->run(this); });
	viewTread.detach();
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

	timerCallback_->updateActor(actor);
}

void ViewWndow::exit()
{
	//irenDisplay3D->UnRegister(irenDisplay3D);
	//irenDisplay3D->TerminateApp(); //
}

unsigned long __stdcall ViewWndow::run(void* param)
{
	this->timerCallback_ = vtkSmartPointer<vtkMyCallback>::New();

	this->renderWindowDisplay3D_->SetSize(600, 400);
	this->renderWindowDisplay3D_->AddRenderer(renDisplay3D_);
	this->renderWindowDisplay3D_->Render();

	this->irenDisplay3D_->SetRenderWindow(renderWindowDisplay3D_);
	this->irenDisplay3D_->SetInteractorStyle(styleDisplay3D_);
	this->irenDisplay3D_->Initialize();
	
	this->irenDisplay3D_->AddObserver(vtkCommand::TimerEvent, timerCallback_);
	this->irenDisplay3D_->CreateRepeatingTimer(100);

	irenDisplay3D_->Start();

	return 0;
}
