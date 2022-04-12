#ifndef MENU_H_728314
#define MENU_H_728314

#include "sprite.h"
#include <stdarg.h>

typedef struct {
  Sprite **sprites;
  int number_of_sprites;
  int current_sprite_index;
} Menu;

Menu *Menu_Create(int n, ...);
void Menu_Destroy(Menu *self);

void Menu_Render(Menu *self);
void Menu_NavigateUp(Menu *self);
void Menu_NavigateDown(Menu *self);

#endif /* MENU_H_728314 */
