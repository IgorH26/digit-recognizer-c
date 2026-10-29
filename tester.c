#include <dirent.h>
#include <stdio.h>
const char *folder_path = "answer_img_small/0";
int main(void) {
  DIR *dir = opendir(folder_path);
  if (dir == NULL) {
    perror(folder_path);
    return 1;
  }

  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.')
      continue; // skip "." and ".."

    printf("Filename: %s\n", entry->d_name);
    
    char file_path[512];
    snprintf(file_path, sizeof file_path, "%s/%s", folder_path, entry->d_name);

    // Pass file_path to stbi_load(...)
  }

  closedir(dir);
}
