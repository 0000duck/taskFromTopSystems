#include "makerPrimitive.h"


void MakerPrimitive::makePrimitive(Message& mes)
{
    switch (mes.typeShape_)
    {
    case Message::circle:
        makeCircle();
        break;
    case Message::square:
        makeSquare();
        break;
    case Message::triangle:
        makeTriangle();
        break;
    case Message::rectangle:
        makeRectangle();
        break;
    case Message::elips:
        makeElips();
        break;
    }

    push();
}

TopoDS_Shape MakerPrimitive::getShape() const
{
    return actualShape_;
}

void MakerPrimitive::makeCircle()
{
    gp_Ax2 ax(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 1));
    gp_Circ circlLine(ax, 50);
    BRepBuilderAPI_MakeEdge makerEdge(circlLine, 0, circlLine.Length());
    BRepBuilderAPI_MakeWire makerWire(makerEdge.Edge());

    actualShape_ = BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

void MakerPrimitive::makeSquare()
{
    int X = 20;

    gp_Pnt p1(X / 2, X / 2, 0);
    gp_Pnt p2(X / 2, - X / 2, 0);
    gp_Pnt p3(- X / 2, - X / 2, 0);
    gp_Pnt p4(- X / 2, X / 2, 0);

    BRepBuilderAPI_MakeWire makerWire;

    makerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

    actualShape_ = BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

void MakerPrimitive::makeTriangle()
{
    int X = 20;

    gp_Pnt p1(-X, 0, 0);
    gp_Pnt p2(X, 0, 0);
    gp_Pnt p3(0, X, 0);

    BRepBuilderAPI_MakeWire makerWire;

    makerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p3, p1).Edge());

    actualShape_ = BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

void MakerPrimitive::makeRectangle()
{
    int A = 20;
    int B = 10;

    gp_Pnt p1(A / 2, B / 2, 0);
    gp_Pnt p2(A / 2, -B / 2, 0);
    gp_Pnt p3(-A / 2, -B / 2, 0);
    gp_Pnt p4(-A / 2, B / 2, 0);


    BRepBuilderAPI_MakeWire makerWire;

    makerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

    actualShape_ = BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

void MakerPrimitive::makeElips()
{
    int A = 17;
    int B = 5;

    gp_Ax2 ax(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 1));
    gp_Elips elips(ax, A, B);

    BRepBuilderAPI_MakeEdge makerEdge(elips);
    BRepBuilderAPI_MakeWire makerWire(makerEdge.Edge());

    actualShape_ = BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

void MakerPrimitive::push()
{
    Message mes{
        Message::command::updateShape,
        Message::type_shape::none
    };
    actualShape_ = actualShape_;

    queue_.push(mes);
}

MakerPrimitive::MakerPrimitive(std::queue<Message>& queue): queue_(queue){}
