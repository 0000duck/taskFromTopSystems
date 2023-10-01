#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include <functional>

#include "message.h"


class CLI
{
public:
	CLI(std::queue<Message>& queue);

	void processing();
private:
	CLI() = delete;

	void invitationMessage();
	void pushMake(int i);
	void pushExit();
public:

private:
	std::queue<Message>& queue_;

	std::string buf;
};
