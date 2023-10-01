#pragma once

#include <queue>
#include <string>

#include "CLI.h"
#include "makerPrimitive.h"
#include "viewWindow.h"
#include "message.h"


class EventLoop
{
public:
    EventLoop();
    void loop();
private:
    
public:

private:
    std::queue<Message> queue_;

    CLI cli_;
    MakerPrimitive maker_;
    ViewWndow win_;
};