#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

class CLI
{
private:
	int numberFigure_;
	bool status_ = true;
public:
	void processing();

	int getNumberFigure() const;
	bool getStatus() const;
};

