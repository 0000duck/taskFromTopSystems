#pragma once

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <IVtkTools_ShapeDataSource.hxx>
#include <BRepPrimAPI_MakeBox.hxx>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>

#include <TopoDs_Shape.hxx>
#include <IVtkOCC_Shape.hxx>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRendererCollection.h>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

#include <iostream>

namespace {

	// Callback for the interaction.
	class vtkMyCallback : public vtkCommand
	{
		mutable std::recursive_mutex g_lock;

	public:
		static vtkMyCallback* New()
		{
			return new vtkMyCallback;
		}

		void Execute(vtkObject* caller, unsigned long, void*) override
		{

			//std::cout << "Execute called" << std::endl;

			vtkRenderWindowInteractor* renderer = reinterpret_cast<vtkRenderWindowInteractor*>(caller);
			if (clean_) {
				std::lock_guard<std::recursive_mutex> g_l(this->g_lock);
				std::cout << "Execute called::Clean" << std::endl;
				renderer->GetRenderWindow()->GetRenderers()->RemoveAllItems();

				clean_ = !clean_;
			}
			if (statusAddShape_) {
				std::lock_guard<std::recursive_mutex> g_l(this->g_lock);
				std::cout << "Execute called::Add" << std::endl;
				vtkSmartPointer<vtkRenderer> ptr_renderer = vtkSmartPointer<vtkRenderer>::New();

				renderer->GetRenderWindow()->GetRenderers()->RemoveAllItems();
				ptr_renderer->AddActor(this->actor_);

				renderer->GetRenderWindow()->AddRenderer(ptr_renderer);
				renderer->GetRenderWindow()->Render();

				statusAddShape_ = !statusAddShape_;
			}
		};
		
		void addShape(vtkSmartPointer<vtkActor> actor) {
			std::lock_guard<std::recursive_mutex> g_l(this->g_lock);
			std::cout << "addShape call" << std::endl;

			this->actor_ = actor;
			statusAddShape_ = true;
		};

		void Clean() {
			std::lock_guard<std::recursive_mutex> g_l(this->g_lock);
			std::cout << "clean call" << std::endl;

			clean_ = true;
		};

		vtkMyCallback() : g_lock() {};
	private:
		std::atomic_bool clean_ = false;
		std::atomic_bool statusAddShape_ = false;

		vtkSmartPointer<vtkActor> actor_;
		
		
	};
} // namespace


class viewWndow
{
public:

private:
	vtkSmartPointer<vtkRenderWindow> renderwindowDisplay3D;
	vtkSmartPointer<vtkRenderer> renDisplay3D;

	vtkSmartPointer<vtkRenderWindowInteractor> irenDisplay3D;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> styleDisplay3D;

	vtkSmartPointer<vtkMyCallback> timerCallback;
public:
	viewWndow();
	void addShape(TopoDS_Shape shape);
	void clean();



private:
	unsigned long __stdcall run(void* param);
};

