#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <math.h>
#include <stdlib.h>

const char *ans_img_s = "answer_img_small";
const char *ans_img_l = "answer_img_large";

float sigmoid(float x);
void matrix_print(int mat_x, int mat_y, const float mat[]);
void matrix_multiplication(int mat_w_x, int mat_w_y, int mat_n_x, int mat_n_y,
                           float mat_w[], float mat_n[], float mat_r[]);

int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "Usage: %s <file> <mode>\n", argv[0]);
    return 1;
  }

  char *file = argv[1];
  char *dir = argv[2];
  if (strcmp(dir, "ais") == 0) {
    *dir = *ans_img_s;
  } else if (strcmp(dir, "ail") == 0) {
    *dir = *ans_img_l;
  }
  int width, height, channels;
  char path[99];

  snprintf(path, sizeof path, "%s/%s", dir, file);

  unsigned char *pixels = stbi_load(path, &width, &height, &channels, 1);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int index = y * width + x;
      printf("%3d ", pixels[index]);
    }
    putchar('\n');
  }
}

float sigmoid(float x) {
  return 1.0f / (1.0f + expf(-x));
} // simple sigmoid interpretation 1/(1+e^-x)

void matrix_print(int mat_x, int mat_y, const float mat[]) {
  for (int row = 0; row < mat_y; row++) {
    printf("[");
    for (int col = 0; col < mat_x; col++) {
      printf("%s%8.3f", col == 0 ? "" : " ", mat[row * mat_x + col]);
    }
    printf("]\n");
  }
}

void matrix_multiplication(int mat_w_x, int mat_w_y, int mat_n_x, int mat_n_y,
                           float mat_w[], float mat_n[], float mat_r[]) {
  // error checking
  if (mat_w_x != mat_n_y) {
    exit(1);
  }
  // Row-major arrays: mat_r needs mat_w_y * mat_n_x elements
  // and must not overlap either input array.
  for (int row = 0; row < mat_w_y; row++) {
    for (int col = 0; col < mat_n_x; col++) {
      float cell = 0.0f;
      for (int k = 0; k < mat_w_x; k++) {
        cell += mat_w[row * mat_w_x + k] * mat_n[k * mat_n_x + col];
      }
      mat_r[row * mat_n_x + col] = cell;
    }
  }
}
