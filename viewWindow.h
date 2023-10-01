#pragma once

#include <thread>
#include <mutex>
#include <queue>

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <IVtkTools_ShapeDataSource.hxx>
#include <BRepPrimAPI_MakeBox.hxx>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkRendererCollection.h>

#include <TopoDs_Shape.hxx>
#include <IVtkOCC_Shape.hxx>

#include "message.h"


class vtkMyCallback : public vtkCommand
{
public:
	static vtkMyCallback* New()
	{
		return new vtkMyCallback;
	}

	void Execute(vtkObject* caller, unsigned long, void*) override
	{
		if (statusAddShape_) {
			vtkRenderWindowInteractor* renderer = reinterpret_cast<vtkRenderWindowInteractor*>(caller);
			std::lock_guard<std::mutex> g_l(this->g_lock);
			vtkSmartPointer<vtkRenderer> ptr_renderer = vtkSmartPointer<vtkRenderer>::New();

			renderer->GetRenderWindow()->GetRenderers()->RemoveAllItems();
			ptr_renderer->AddActor(this->actor_);

			renderer->GetRenderWindow()->AddRenderer(ptr_renderer);
			renderer->GetRenderWindow()->Render();

			statusAddShape_ = !statusAddShape_;
		}
	};
	
	void updateActor(vtkSmartPointer<vtkActor> actor) {
		std::lock_guard<std::mutex> g_l(this->g_lock);

		this->actor_ = actor;
		statusAddShape_ = true;
	};


	vtkMyCallback() : g_lock() {};
private:
	bool statusAddShape_ = false;
	bool stateExit_ = false;
	mutable std::mutex g_lock;

	vtkSmartPointer<vtkActor> actor_;
};


class ViewWndow
{
public:
	ViewWndow(std::queue<Message>& queue);
	void updateShape(TopoDS_Shape temp);
	void exit();
private:
	ViewWndow() = delete;

	unsigned long __stdcall run(void* param);
public:

private:

	vtkSmartPointer<vtkRenderWindow> renderWindowDisplay3D_;
	vtkSmartPointer<vtkRenderer> renDisplay3D_;

	vtkSmartPointer<vtkRenderWindowInteractor> irenDisplay3D_;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> styleDisplay3D_;

	vtkSmartPointer<vtkMyCallback> timerCallback_;

	std::queue<Message>& queue_;
};

