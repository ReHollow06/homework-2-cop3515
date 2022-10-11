/*
 * COP 3515 – Fall Semester 2022
 *
 * Homework #2: Spotting The Hacker
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define NUM_FILES 3

int decToBin(int decNum);
bool hasEvenParity(int binNum);

int main(void)
{
  FILE *dataFiles[NUM_FILES];
  dataFiles[0] = fopen("White House Transmission Data - Parity.txt", "r");
  dataFiles[1] = fopen("White House Transmission Data - 2D Parity.txt", "r");
  dataFiles[2] = fopen("White House Transmission Data - Checksum.txt", "r");

  // File open test
  for (int i = 0; i < NUM_FILES; i++)
  { // checks for null pointers in all files
    if (dataFiles[i] == NULL)
    {
      printf("Couldn't open file %d\n", i + 1);
      return i + 1;
    }
    else
    {
      //printf("file %d open\n", i + 1);
      continue;
    }
  }

  return 0;
}