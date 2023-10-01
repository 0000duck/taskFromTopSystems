#pragma once

#include "TopoDS_Shape.hxx"
#include <Standard_Handle.hxx>


struct Message {
    enum command {
        exit = 0,
        makeShape,
        updateShape,
    } command_;
    enum type_shape {
        circle = 1,
        square,
        triangle,
        rectangle,
        elips,
        none
    } typeShape_;
};
