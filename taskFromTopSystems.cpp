#include "windows.h"


#include "makerPrimitive.h"
#include "viewWndow.h"
#include "CLI.h"



int main()
{
    viewWndow win;
    makerPrimitive mak;

    bool status = true;

    CLI cli(status);

    bool getFig = false;
    while (cli.getStatus()) {
        cli.processing();
        if (!getFig) {
            getFig = !getFig;
            mak.setShape(1);
            win.addShape(mak.makePrimitiv());

            Sleep(5000);

            //win.clean();

            mak.setShape(3);
            win.addShape(mak.makePrimitiv());
            Sleep(5000);
            mak.setShape(4);
            win.addShape(mak.makePrimitiv());
        }
    }
}
