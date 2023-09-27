
#include <thread>

#include "makerPrimitive.h"
//#include "viewWndow.h"
#include "CLI.h"

int main()
{
    viewWndow win;
    makerPrimitive mak;
    CLI cli(&win, &mak);

    std::thread t1(&CLI::processing, &cli);
    t1.detach();

    win.run();


}
