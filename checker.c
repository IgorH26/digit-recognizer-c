#include <stdio.h>
#include <string.h>
// Compile stb_image's implementation in this source file only.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <dirent.h>
#include <math.h>
#include <stdlib.h>

const char *ans_img_s = "answer_img_small";
const char *ans_img_l = "answer_img_large";
const int short_files = 12;

float sigmoid(float x);
void matrix_print(int mat_x, int mat_y, const float mat[]);
void matrix_multiplication(int mat_w_x, int mat_w_y, int mat_n_x, int mat_n_y,
                           float mat_w[], float mat_n[], float mat_r[]);

int main(int argc, char *argv[]) {
  // Each 28 x 28 digit supplies 784 grayscale values for the future network.
  // TODO: normalize the pixel values and use them as the network's input
  // vector.
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <dir>\n", argv[0]);
    return 1;
  }

  char *folder_path = argv[1];
  // TODO: assign the directory pointer for these aliases; dereferencing it
  // currently replaces only the first character of the argument.

  int width, height, channels;

  // TODO: loop for each image in folder / each file.
  int images[short_files][784];
  int img_index = 0;
  DIR *dir = opendir(folder_path);
  if (dir == NULL) {
    perror(folder_path);
    return 1;
  }
  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.')
      continue; // skip "." and ".."

    char path[99];
    snprintf(path, sizeof path, "%s/%s", folder_path, entry->d_name);

    // Request one grayscale byte per pixel (0 = black, 255 = white).
    unsigned char *pixels = stbi_load(path, &width, &height, &channels, 1);
    if (pixels == NULL) {
      fprintf(stderr, "Failed to load image: %s\n", path);
      return 1;
    }
    if (height != 28 || width != 28) {
      // Reject images that do not match the expected digit input dimensions.
      stbi_image_free(pixels);
      exit(2);
    }
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        // Rows are stored consecutively: skip y full rows, then move x pixels.
        int index = y * width + x;
        images[img_index][index] = pixels[index];
      }
    }
    img_index++;
    stbi_image_free(pixels);
  }

  closedir(dir);
  float average_img_grc[784] = {0};

  if (img_index == 0) {
    fprintf(stderr, "No images loaded\n");
    return 1;
  }

  // Add the same pixel from every image.
  for (int cur_img = 0; cur_img < img_index; cur_img++) {
    for (int pixel = 0; pixel < 784; pixel++) {
      average_img_grc[pixel] += images[cur_img][pixel] / short_files;
    }
  }
  /*      ////IMAGE OUTPUT MAKER FOR VISUALISATION////
          // Divide each pixel total by the number of images.
          unsigned char png_pixels[28 * 28];

          for (int i = 0; i < 28 * 28; i++) {
            png_pixels[i] = (unsigned char)(average_img_grc[i] + 0.5f);
          }

          if (!stbi_write_png("average.png", 28, 28, 1, png_pixels, 28)) {
            fprintf(stderr, "Could not write average.png\n");
            return 1;
          }
  */
}

// Squash a neuron's weighted input toward 0 or 1 using 1 / (1 + e^(-x)).
float sigmoid(float x) { return 1.0f / (1.0f + expf(-x)); }

// Print a flat row-major array with mat_x columns and mat_y rows.
void matrix_print(int mat_x, int mat_y, const float mat[]) {
  for (int row = 0; row < mat_y; row++) {
    printf("[");
    for (int col = 0; col < mat_x; col++) {
      printf("%s%8.3f", col == 0 ? "" : " ", mat[row * mat_x + col]);
    }
    printf("]\n");
  }
}

// Multiply W (mat_w_y rows, mat_w_x columns) by N (mat_n_y rows, mat_n_x
// columns).
void matrix_multiplication(int mat_w_x, int mat_w_y, int mat_n_x, int mat_n_y,
                           float mat_w[], float mat_n[], float mat_r[]) {
  // W's column count must equal N's row count to form each dot product.
  if (mat_w_x != mat_n_y) {
    exit(1);
  }
  // Row-major arrays: mat_r needs mat_w_y * mat_n_x elements
  // and must not overlap either input array.
  for (int row = 0; row < mat_w_y; row++) {
    for (int col = 0; col < mat_n_x; col++) {
      // Each output cell is the dot product of one row of W and one column of
      // N.
      float cell = 0.0f;
      for (int k = 0; k < mat_w_x; k++) {
        cell += mat_w[row * mat_w_x + k] * mat_n[k * mat_n_x + col];
      }
      mat_r[row * mat_n_x + col] = cell;
    }
  }
}
