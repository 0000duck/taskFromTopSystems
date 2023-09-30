#pragma once

#include <queue>

#include <TopoDs_Shape.hxx>
#include <TopoDS_Vertex.hxx>

#include <IVtkOCC_Shape.hxx>

#include <gp_Circ.hxx>
#include <gp_Elips.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>

#include "message.h"

// класс реализующий один из выбранных прмиитивов
class MakerPrimitive
{
public:
	MakerPrimitive(std::queue<Message>& queue_);
	
	void makePrimitive(Message& mes);

	TopoDS_Shape getShape() const;
private:
	MakerPrimitive() = delete;

	void makeCircle();
	void makeSquare();
	void makeTriangle();
	void makeRectangle();
	void makeElips();

	void push();
public:

private:
	std::queue<Message>& queue_;

	TopoDS_Shape actualShape_;
};

