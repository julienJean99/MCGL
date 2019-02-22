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

int update(__attribute__((unused)) mc_window *this)
{
    return (4);
}

int main()
{
    mc_window *window = new(mc_Window, 300, 500);
    int ret = 0;

    if (!window) {
        printf("Oops\n");
        return (84);
    }
    window->setLoop(window, (loop)update);
    ret = window->open(window);
    delete(window);
    return (ret);
}
