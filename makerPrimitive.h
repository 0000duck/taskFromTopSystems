#pragma once

#include <TopoDs_Shape.hxx>
#include <TopoDS_Vertex.hxx>

#include <IVtkOCC_Shape.hxx>

#include <gp_Circ.hxx>
#include <gp_Elips.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>

// класс реализующий один из выбранных прмиитивов

class makerPrimitive
{
public:

private:
	bool status_;

	int numberFigure_;

public:
	makerPrimitive() : status_(false), numberFigure_(-1){};

	bool isDone();
	
	void setShape(int i);
	
	TopoDS_Shape makePrimitiv();
private:
	TopoDS_Shape makeCircle();
	TopoDS_Shape makeSquare();
	TopoDS_Shape makeTriangle();
	TopoDS_Shape makerRectangle();
	TopoDS_Shape makerElips();

};

