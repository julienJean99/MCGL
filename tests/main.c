
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

int update(
    mc_window *window)
{
    static mc_point *point = NULL;
    static mc_line *line = NULL;
    static mc_cercle *cercle = NULL;
    static mc_text *text = NULL;
    static mc_image *image = NULL;

    point = (point == NULL) ? new(mc_Point, 100, 100) : point;
    line = (line == NULL) ? new(mc_Line, 20, 20, 30, 40) : line;
    cercle = (cercle == NULL) ? new(mc_Cercle, 20, 20, 30) : cercle;
    text = (text == NULL) ? new(mc_Text, "Test", "-*-fixed-*-*-*-20-*") : text;
    image = (image == NULL) ? new(mc_Image,
                                  "tests/asset/iconfinder_firefox_png_148659.png",
                                  10, 10) : image;

    window->draw(window, point);
    window->draw(window, line);
    window->draw(window, cercle);
    window->draw(window, text);
    window->draw(window, image);
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
