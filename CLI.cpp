#include "CLI.h"

CLI::CLI(viewWndow* ptr, makerPrimitive* ptr_maker)
{
	ptr_ = ptr;
	ptr_maker_ = ptr_maker;
}

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
			ptr_maker_->setShape(numberFigure_);
			ptr_->addShape(ptr_maker_->makePrimitiv());
			break;
		case 2:
			numberFigure_ = 2;
			ptr_maker_->setShape(numberFigure_);
			ptr_->addShape(ptr_maker_->makePrimitiv());
			break;
		case 3:
			numberFigure_ = 3;
			ptr_maker_->setShape(numberFigure_);
			ptr_->addShape(ptr_maker_->makePrimitiv());
			break;
		case 4:
			numberFigure_ = 4;
			ptr_maker_->setShape(numberFigure_);
			ptr_->addShape(ptr_maker_->makePrimitiv());
			break;
		case 5:
			numberFigure_ = 5;
			ptr_maker_->setShape(numberFigure_);
			ptr_->addShape(ptr_maker_->makePrimitiv());
			break;
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
