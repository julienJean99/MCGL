
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
#include "class/drawable/line.h"
#include "class/drawable/cercle.h"
#include "class/drawable/text.h"
#include "class/drawable/image.h"
#include "modular/list.h"

void *drawList(
    Drawable *obj,
    va_list *arg)
{
    mc_window *window = va_arg(*arg, mc_window*);
    window->draw(window, obj);
    return (NULL);
}

int update(
    mc_window *window)
{
    static list_t *drawbleList = NULL;

    if (!drawbleList) {
        drawbleList = new(List_t, 5, 5,
                          new(mc_Point, 100, 100),
                          new(mc_Line, 20, 20, 30, 40),
                          new(mc_Cercle, 20, 20, 30),
                          new(mc_Text, "Test", "-*-fixed-*-*-*-20-*"),
                          new(mc_Image,
                              "tests/asset/iconfinder_firefox_png_148659.png",
                              150, 350));
    }
    delete(drawbleList->map(drawbleList, (mapFunc*)&drawList, window));
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
