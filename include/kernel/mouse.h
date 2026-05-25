#ifndef MOUSE_H
#define MOUSE_H

#include "../include/types.h"

void mouse_init();
void mouse_handle();
int mouse_get_x();
int mouse_get_y();
int mouse_button_left();
int mouse_button_right();

#endif
