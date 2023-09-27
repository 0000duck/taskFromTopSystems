#pragma once
#include "viewWndow.h"
#include "makerPrimitive.h"

#include <iostream>
#include <string>
#include <cstdlib>

class CLI
{
private:
	viewWndow* ptr_;
	makerPrimitive* ptr_maker_;

	int numberFigure_;
	bool status_ = true;
public:
	CLI(viewWndow* ptr, makerPrimitive* ptr_maker);

	void processing();

	int getNumberFigure() const;
	bool getStatus() const;
};

