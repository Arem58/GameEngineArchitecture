#include "print.h"

#include "Pong.h"

int main()
{
    Pong pong = Pong("pong", 800, 600);

    pong.run();
}