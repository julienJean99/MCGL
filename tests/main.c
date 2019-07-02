
/* // */
/* // This document created by Julien JEAN */
/* // For project : window */
/* // */
/* // Thu 21 Feb 22:19:55 CET 2019 */
/* // test */
/* // */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "modular/new.h"
#include "modular/list.h"
#include "modular/string.h"
#include "class/mc_window.h"
#include "class/drawable/point.h"
#include "class/drawable/line.h"
#include "class/drawable/cercle.h"
#include "class/drawable/text.h"
#include "class/drawable/image.h"
#include "class/event/hook.h"

void drawList(
    listArgs *arg)
{
    mc_window *window = va_arg(arg->args, mc_window*);

    window->draw(window, arg->obj);
}

void pointerPosition(
    mc_mouseMouvment *mouvment)
{
    mc_cercle *cercle = mouvment->param;

    cercle->x = mouvment->x;
    cercle->y = mouvment->y;
}

void enlargeCercle(mc_cercle *cercle)
{
    cercle->rad += 3;
}

void reduceCercle(mc_cercle *cercle)
{
    cercle->rad -= 3;
    if (cercle->rad < 0) {
        cercle->rad = 0;
    }
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
                          new(mc_Text, "Test", "-*-fixed-*-*-*-10-*"),
                          new(mc_Image,
                              "tests/asset/iconfinder_firefox_png_148659.png",
                              150, 350));
        window->setHook(
            window,
            mouse,
            mouvment,
            &pointerPosition,
            drawbleList->at(drawbleList, 2));
        window->setHook(
            window,
            mouse,
            clickR,
            press,
            &reduceCercle,
            drawbleList->at(drawbleList, 2));
        window->setHook(
            window,
            mouse,
            clickR,
            hold,
            &reduceCercle,
            drawbleList->at(drawbleList, 2));
        window->setHook(
            window,
            mouse,
            clickL,
            press,
            &enlargeCercle,
            drawbleList->at(drawbleList, 2));
        window->setHook(
            window,
            mouse,
            clickL,
            hold,
            &enlargeCercle,
            drawbleList->at(drawbleList, 2));

    }
    drawbleList->loop(drawbleList, &drawList, window);
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
