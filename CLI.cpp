#include "CLI.h"

void CLI::processing()
{
	std::string buf;
	while (true) {
		std::cin >> buf;
		int i = atoi(buf.c_str());

		switch (i)
		{
		case 1:
			numberFigure_ = 1;
			return;
		case 2:
			numberFigure_ = 2;
			return;
		case 3:
			numberFigure_ = 3;
			return;
		case 4:
			numberFigure_ = 4;
			return;
		case 5:
			numberFigure_ = 5;
			return;
		case 0:
			status_ = false;
			return;
		default:
			break;
		}

	}
}

int CLI::getNumberFigure() const
{
	return numberFigure_;
}

bool CLI::getStatus() const
{
	return status_;
}
