/*******************************************************************************
 * Name            : read_input.cc
 * Project         : fcal
 * Module          : scanner
 * Description     : Implementation of input reader utility
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * ReadInputFromFile() - Do the actual reading of the file into the buffer
 *
 * RETURN:
 *     char* - The buffer, or NULL if an error occurred.
 **/
char *ReadInputFromFile(const char *filename) {
  FILE *in_fp;
  in_fp = fopen(filename, "r");

  if (in_fp == NULL) {
    printf("File \"%s\" not found.\n", filename);
    fflush(stdout);
    return NULL;
  }

  // Determine the size of the file, used to allocate the char buffer.
  struct stat filestatus;
  stat(filename, &filestatus);

  int filesize = filestatus.st_size + 1;  // +1 for terminating null char

  // Allocate space for the character buffer.
  char *buffer = new char[filesize];

  int index = 0;
  char ch = getc(in_fp);

  while (ch != EOF) {
    buffer[index] = ch;
    index++;
    ch = getc(in_fp);
  }
  buffer[index] = '\0';

  return buffer;
} /* ReadInputFromFile() */


/**
 * ReadInput() - Read a file into a char buffer. The calling function is
 * responsible for disposing of the return memory.
 *
 * RETURN:
 *     char* - The buffer, or NULL if an error occurred.
 **/
char *ReadInput(int argc, char **argv) {
  // Verify that a file name is provided and that the file exists.
  // Use some new C++ stream features.
  if (argc <= 1) {
    //        printf ("Usage: %s <filename>\n", argv[0]) ;
    return NULL;
  } else {
    return ReadInputFromFile(argv[1]);
  }
} /* ReadInput() */

} /* namespace scanner */
} /* namespace fcal */
