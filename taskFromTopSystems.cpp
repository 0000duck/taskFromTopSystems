#include "makerPrimitive.h"
#include "viewWndow.h"
#include "CLI.h"

int main()
{
    CLI cli;
    makerPrimitive mak;
    viewWndow win;

    while (cli.getStatus()) {
        cli.processing();
        win.clean();
        mak.setShape(cli.getNumberFigure());

        win.addShape(mak.makePrimitiv());
        win.run();
    }
}

