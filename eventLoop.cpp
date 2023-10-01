#include "eventLoop.h"

EventLoop::EventLoop(): cli_(queue_), maker_(queue_), win_(queue_){}

void EventLoop::loop()
{
	while (true) {
		if (queue_.empty()) cli_.processing();

		Message mes = queue_.front();
		
		switch (mes.command_)
		{
		case Message::exit:
			//win.exit();
			//return;
		case Message::makeShape:
			maker_.makePrimitive(mes);
			break;
		case Message::updateShape:
			win_.updateShape(maker_.getShape());
			break;
		default:
			return;
		}

		queue_.pop();
	}
}
