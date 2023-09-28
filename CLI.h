#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

class CLI
{
private:

	int numberFigure_;
	bool& status_;
public:
	CLI(bool& status);

	void processing();

	int getNumberFigure() const;
	bool getStatus() const;
};
