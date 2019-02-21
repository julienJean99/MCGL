/* // */
/* // This document created by Julien JEAN */
/* // For project : window */
/* // */
/* // Thu 21 Feb 22:19:55 CET 2019 */
/* // test */
/* // */

#include <stdio.h>
#include "class/mc_window.h"
#include "modular/new.h"

void update(__attribute__((unused)) mc_window *this, int *ret)
{
    printf("Loop\n");
    *ret = 4;
}

int main()
{
    mc_window *window = new(mc_Window, 300, 500);

    if (!window) {
        printf("Oops\n");
        return (84);
    }
    window->setLoop(window, (loop)update);
    return (*(int *)window->open(window));
}
