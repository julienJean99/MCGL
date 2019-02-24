
/* // */
/* // This document created by Julien JEAN */
/* // For project : window */
/* // */
/* // Thu 21 Feb 22:19:55 CET 2019 */
/* // test */
/* // */

#include <unistd.h>
#include <stdio.h>
#include "class/mc_window.h"
#include "modular/new.h"
#include "class/drawable/point.h"

int update(mc_window *window)
{
    static mc_point *point = NULL;

    if (point == NULL) {
        point = new(mc_Point, 10, 10);
    }
    if (point == NULL) {
        return (-1);
    }
    window->draw(window, (struct mc_drawable *)point);
    return (0);
}

int main()
{
    mc_window *window = new(mc_Window, 300, 500);
    int ret = 0;

    if (!window) {
        printf("Oops\n");
        return (84);
    }
    window->setLoop(window, (loop)&update);
    ret = window->open(window);
    delete(window);
    return (ret);
}
