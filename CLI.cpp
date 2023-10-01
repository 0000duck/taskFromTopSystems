#include "CLI.h"

CLI::CLI(std::queue<Message>& queue) : queue_(queue) {};

void CLI::processing()
{
	while (true) {
		invitationMessage();

		std::cin >> buf;
		int i = stoi(buf);

		if (i == 6) {
			pushExit();
			return;
		}
		if (i >= 1 && i <= 5) {
			pushMake(i);
			return;
		}

		buf.clear();
	}
}

void CLI::pushMake(int i)
{
	Message mes{
		Message::command::makeShape,
		Message::type_shape(i),
	};

	queue_.push(mes);
}

void CLI::pushExit()
{
	Message mes{
		Message::command::exit,
		Message::type_shape::none,
	};

	queue_.push(mes);
}

void CLI::invitationMessage(){
	std::cout << "Enter the number of the shape you want to display:\n\
1 - circle\n\
2 - square\n\
3 - triangle\n\
4 - rectangle\n\
5 - ellipse\n\
input: ";
}
