#include "eventLoop.h"

EventLoop::EventLoop(): cli(queue_), maker(queue_), win(queue_){}

void EventLoop::loop()
{
	while (true) {
		if (queue_.empty()) cli.processing();

		Message mes = queue_.front();
		
		switch (mes.command_)
		{
		case Message::exit:
			//win.exit();
			//return;
		case Message::makeShape:
			maker.makePrimitive(mes);
			break;
		case Message::updateShape:
			win.updateShape(maker.getShape());
			break;
		default:
			return;
		}

		queue_.pop();
	}
}
