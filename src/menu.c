#include "menu.h"

#include <stdlib.h>
#include "sprite.h"
#include <stdarg.h>


Menu *Menu_Create(int n, ...) {
  Menu *self;
  va_list valist;
  int i;

  self = (Menu *) malloc(sizeof(Menu));
  if (NULL == self) {
    return NULL;
  }

  self->number_of_sprites = n;
  self->sprites = (Sprite **) calloc(n, sizeof(Sprite *));
  self->current_sprite_index = 0;

  va_start(valist, n);
  for (i = 0; i < n; ++i) {
    self->sprites[i] = Sprite_Create(va_arg(valist, char *));
  }
  va_end(valist);

  return self;
}


void Menu_Destroy(Menu *self) {
  int i;
  if (NULL == self) {
    return;
  }

  for (i = 0; i < self->number_of_sprites; ++i) {
    Sprite_Destroy(self->sprites[i]);
  }
  free(self->sprites);
  free(self);
}


void Menu_Render(Menu *self) {
  Sprite_Render(self->sprites[self->current_sprite_index], 0.0, 0.0);
}


void Menu_NavigateDown(Menu *self) {
  ++ self->current_sprite_index;
  if (self->number_of_sprites == self->current_sprite_index) {
    self->current_sprite_index = 0;
  }
}

void Menu_NavigateUp(Menu *self) {
  -- self->current_sprite_index;
  if (-1 == self->current_sprite_index) {
    self->current_sprite_index = self->number_of_sprites - 1;
  }
}



