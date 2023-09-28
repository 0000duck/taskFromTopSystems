#include "makerPrimitive.h"

bool makerPrimitive::isDone()
{
    return status_;
}

void makerPrimitive::setShape(int i)
{
    if (i > 5 || i < 1) {
        status_ = false;
        return;
    }

    status_ = true;
    numberFigure_ = i;
}

TopoDS_Shape makerPrimitive::makePrimitiv()
{
    if (status_ == false) return TopoDS_Shape();

    switch (numberFigure_)
    {
    case 1: return makeCircle();
    case 2: return makeSquare();
    case 3: return makeTriangle();
    case 4: return makerRectangle();
    case 5: return makerElips();
    }
}

TopoDS_Shape makerPrimitive::makeCircle()
{
    gp_Ax2 ax(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 1));
    gp_Circ circlLine(ax, 50);
    BRepBuilderAPI_MakeEdge makerEdge(circlLine, 0, circlLine.Length());
    BRepBuilderAPI_MakeWire makerWire(makerEdge.Edge());

    return BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

TopoDS_Shape makerPrimitive::makeSquare()
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

    return BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

TopoDS_Shape makerPrimitive::makeTriangle()
{
    int X = 20;

    gp_Pnt p1(-X, 0, 0);
    gp_Pnt p2(X, 0, 0);
    gp_Pnt p3(0, X, 0);

    BRepBuilderAPI_MakeWire makerWire;

    makerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    makerWire.Add(BRepBuilderAPI_MakeEdge(p3, p1).Edge());

    return BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

TopoDS_Shape makerPrimitive::makerRectangle()
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

    return BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}

TopoDS_Shape makerPrimitive::makerElips()
{
    int A = 17;
    int B = 5;

    gp_Ax2 ax(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 1));
    gp_Elips elips(ax, A, B);

    BRepBuilderAPI_MakeEdge makerEdge(elips);
    BRepBuilderAPI_MakeWire makerWire(makerEdge.Edge());

    return BRepBuilderAPI_MakeFace(makerWire.Wire()).Shape();
}