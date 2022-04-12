#include "sprite.h"

#include <windows.h>
#include "gl.h"
#include "glaux.h"

Sprite *Sprite_Create(char const *filename) {
  Sprite *self;
  AUX_RGBImageRec *image;
  int num_of_pixels, i, j;

  self = (Sprite *) malloc(sizeof(Sprite));
  image = auxDIBImageLoad(filename);

  if (NULL == self || NULL == image) {
    return NULL;
  }


  self->width = image->sizeX;
  self->height = image->sizeY;
  num_of_pixels = self->width * self->height;
  self->pixel_data = (int *) calloc(num_of_pixels, sizeof(int));


  for (i = 0, j = 0; i < num_of_pixels; ++i, j += 3) {
    int rgb = 0;

    rgb = ((rgb << 8) | image->data[j+2]);
    rgb = ((rgb << 8) | image->data[j+1]);
    rgb = ((rgb << 8) | image->data[j+0]);

    self->pixel_data[i] = 255;
    self->pixel_data[i] = ((self->pixel_data[i] << 24) | rgb);
  }

  free(image->data);
  free(image);
  return self;
}

void Sprite_Destroy(Sprite *self) {
  free(self->pixel_data);
  free(self);
}


void Sprite_Render(Sprite *self, double x, double y) {
  glRasterPos2f(0.0f, 0.0f);
  glBitmap(0, 0, 0.0f, 0.0f, (GLfloat) x, (GLfloat) y, NULL);
  glDrawPixels(self->width, self->height, GL_RGBA, GL_UNSIGNED_BYTE, self->pixel_data);
}


