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

int decToBin(int decNum){ // converts decimal number to binary 
  int binaryNumArray[8] = {0,0,0,0,0,0,0,0};
  int binaryNum = 0;
  int i = 0;
  int placeCount = 10000000;
  while (decNum != 0)
  {
    binaryNumArray[i++] = decNum % 2;
    decNum /= 2;
  }

  for (int j = 8; j > 0; j--)
  {
    binaryNum += binaryNumArray[j - 1] * placeCount;
    placeCount /= 10;
  }

  return binaryNum;
}

bool hasEvenParity(int binNum, int parityBit){
  return true;
}

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
      // printf("file %d open\n", i + 1);
      continue;
    }
  }

  // PART 1 - PARITY CHECK PROCESSING

  printf("** Part 1 - Parity Check Processing\n\n\n");
  int dataBytes[8];
  int parityByte[8] = {0,0,0,0,0,0,0,0};
  // fscanf(dataFiles[0], "%3d%4d%4d%4d%4d%4d%4d%4d%4d", &dataBytes[0], &dataBytes[1], &dataBytes[2], &dataBytes[3], &dataBytes[4], &dataBytes[5], &dataBytes[6], &dataBytes[7], &parityByte);
  // for (int i = 0; i < 8; i++)
  // {
  //   printf("%d", dataBytes[i]);
  // }
  // printf("\n");
  // printf("%d", parityByte);

  while (!feof(dataFiles[0]))
  {
    printf("line\n");
  }
  

  for (int k = 0; k < NUM_FILES; k++) { // closes all files in file array
    fclose(dataFiles[k]);
  }
  return 0;
}