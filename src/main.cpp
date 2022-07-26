#include "Application.h"

int main(int argc, char *argv[])
{
    Application *app = new Application();
    int exit_code = app->run();
    delete app;
    return exit_code;
}
