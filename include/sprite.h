#ifndef SPRITE_H_873216
#define SPRITE_H_873216

typedef struct {
  int width;
  int height;
  int *pixel_data;
} Sprite;


Sprite *Sprite_Create(char const *filename);
void Sprite_Destroy(Sprite *self);
void Sprite_Render(Sprite *self, double x, double y);

#endif /* SPRITE_H_873216 */
