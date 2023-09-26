#include "viewWndow.h"

viewWndow::viewWndow()
{
	renwin_ = vtkSmartPointer<vtkRenderWindow>::New();
	ren_ = vtkSmartPointer<vtkRenderer>::New();

	renwin_->AddRenderer(ren_);

	istyle_ = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	iren_->SetRenderWindow(renwin_);
	iren_->SetInteractorStyle(istyle_);
}

void viewWndow::addShape(TopoDS_Shape shape)
{
	IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(shape);
	vtkSmartPointer<IVtkTools_ShapeDataSource>
		DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
	DS->SetShape(aShapeImpl);

	vtkSmartPointer<vtkPolyDataMapper> Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	
	Mapper->SetInputConnection(DS->GetOutputPort());
	
	actor_ = vtkSmartPointer<vtkActor>::New();;

	actor_->SetMapper(Mapper);
	ren_->AddActor(actor_);


}

void viewWndow::run()
{
	renwin_->Render();
	iren_->Start();

	//ren_->AddActor(actor_);

}

void viewWndow::start()
{
	iren_->Enable();
}

void viewWndow::clean()
{
	iren_->Disable();
	ren_->RemoveActor(actor_);
}
