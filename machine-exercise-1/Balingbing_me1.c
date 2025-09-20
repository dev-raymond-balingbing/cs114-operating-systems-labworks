// # Name: RAYMOND C. BALINGBING
// # Bloc: BSCS 3B

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void posix_api_v1_up();
void std_lib_v2_up();

int main() {
  // std_lib_v2_up();
  posix_api_v1_up();
  return 0;
}

void posix_api_v1_up() {
  char src_in[100];
  printf("Enter source file: ");
  scanf("%s", src_in);
  
 int src_fd = open(src_in, O_RDONLY); // opening file using posix
  if (src_fd == -1) {
    perror("POSIX FILE OPEN ERROR - src");
    return;
  }
  
  char des_in2[100];
  printf("Enter destination file for POSIX API: ");
  scanf("%s", des_in2);
  
  int des_fd = open(des_in2, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR); // Create the file or open it with writing mode only
  if(des_fd == -1) { // This catches the error if the file does not exists
    perror("POSIX FILE OPEN ERROR - des");
    return;
  }
  
  char *contents = malloc(1); // buffer to hold the entire content
  if(!contents) {
    perror("MEMORY ALLOC ERROR");
    return;
  }
  
  contents[0] = '\0'; // initialize as empty string

  size_t cap = 10; // starting capacity of line buffer
  char *str = malloc(cap);
  if(!str) {
    perror("MEMORY ALLOC ERROR");
    free(contents);
    return;
  }

  size_t curr_len = 0;
  char substr[12]; // temporary read buffer
  ssize_t substr_sz;

  while((substr_sz = read(src_fd, substr, sizeof(substr))) > 0) {
    for(ssize_t i = 0; i < substr_sz; i++) {
      if(curr_len + 1 >= cap) {
        char *temp = realloc(str, cap + curr_len + 1);
        if(!temp) {
          free(str);
          free(contents);
          perror("MEMORY REALLOC ERROR");
          return;
        }
        str = temp;
        cap += curr_len + 1;
      }

      str[curr_len++] = substr[i];

      if(substr[i] == '\n') {
        str[curr_len] = '\0';

        // Resize contents to fit new line
        char *temp2 = realloc(contents, strlen(contents) + strlen(str) + 1);
        if(!temp2) {
          free(str);
          free(contents);
          perror("MEMORY REALLOC ERROR TO CONTENTS");
          return;
        }
        contents = temp2;

        strcat(contents, str);
        curr_len = 0; // reset for next line
      }
    }
  }

  // Write final contents to destination file
  if(write(des_fd, contents, strlen(contents)) < 0) {
    perror("WRITE ERROR");
  }

  free(str);
  free(contents);
}

void std_lib_v2_up() {
  char src_in[100];
  printf("Enter source file: ");
  scanf("%s", src_in);
  
  FILE *src = fopen(src_in, "r"); // opening file using standard lib
  if(src == NULL) {
    perror("STANDARD LIBRARY FILE OPEN ERROR - src");
    return;
  }
  
  char des_in[100];
  printf("Enter destination file for C Standard Library: ");
  scanf("%s", des_in);
  
  FILE *des = fopen(des_in, "w");
  if(src == NULL) {
    perror("STANDARD LIBRARY FILE OPEN ERROR - des");
    return;
  }
  
  char *contents = malloc(sizeof(char)); // this is where the whole content of the src file will be temporarily stored
  if(!contents) { // check for memory allocation error
    perror("MEMORY ALLOC ERROR");
    return;
  }

  size_t cap = 10; // initial size of the str that will hold each line of text from the file
  char *str = malloc(cap); // the str variable that will hold each line of text from the file; the previous value will be reset when reading the new line
  if(!str) { // check for memory allocation error
    perror("MEMORY ALLOC ERROR");
    return;
  }
  
  size_t curr_len = 0; // the current length of the str variable; this will be reset after reading a line of text from the file
  char substr[12]; // the substring variable that will hold each substring in the src file with a size of 12 characters; the contents of this will be appended to the str to build the whole line of text
  size_t substr_sz; // the actual size that was read in the file; could be less than 12
  
  while((substr_sz = fread(substr, 1, sizeof(substr), src)) > 0) { // will scan the wole file until end of file and will read a string from each line in the file with a length of 12 characters
    for(size_t i = 0; i < substr_sz; i++) { // will scan the substring that was read using fread()
      if(curr_len + 1 >= cap) { // will check if the character length of the str exceeded the initial length of it 
        // cap *= 2; // this will adjust the cap length of the str variable
        char *temp = realloc(str, cap + curr_len + 1); // allocating new memory edit
        if(!temp) { // checking for memory reallocation error
          free(str);
          perror("MEMORY REALLOC ERROR");
          return;
        }
        str = temp; // assigning the new memory address to the original str varaible
      }
      str[curr_len++] = substr[i]; // appending every character in the substring to the str varaible to build the a line of text from the src file
      
      if(substr[i] == '\n') { // checking if a new character is encoutered; if yes then terminate the str variable to concatenate it to the contents variable to build the whole content of the src file
        str[curr_len] = '\0'; // terminating the str variable
        // printf("Line: %s", str);
        contents = realloc(contents, strlen(contents) + strlen(str)); // new memory size of contents
        //perror("MEMORY REALLOC ERROR TO CONTENTS");
        strcat(contents, str); // building the contents of a file by appending every line of text from the src file using the str variable
        // printf("Contents:\n%s\n\n", contents);
        curr_len = 0; // reseting the length of str variable so that the previous value of the str value will be overwrittn by the new/next line of text from the src file
      }
    }
  }
  
  fprintf(des, "%s", contents);
  
  free(str);
  free(contents);
  
  
  
}
