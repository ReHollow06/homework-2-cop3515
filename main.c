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
#include <math.h>
#define NUM_FILES 3

void arrayOut(int *numArray, int size);
void arrayOutFormatted(int *numArray, int size, const char *stringFormat);
bool hasEvenParity(int *binArray, int binArraySize, int parityBit);
void decToBinArray(int dataVal, int *binArray, int binArraySize);


void arrayOut(int *numArray, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%d", numArray[i]);
  }
}

void arrayOutFormatted(int *numArray, int size, const char *stringFormat)
{
  for (int i = 0; i < size; i++)
  {
    printf(stringFormat, numArray[i]);
  }
}

bool hasEvenParity(int *binArray, int binArraySize, int parityBit)
{
  int numOnes = parityBit;
  for (int i = 0; i < binArraySize; i++)
  {
    if (binArray[i] == 1)
    {
      numOnes++;
    }
  }

  if (numOnes % 2 == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void decToBinArray(int dataVal, int *binArray, int binArraySize)
{
  for (int i = binArraySize - 1; dataVal > 0; i--)
  {
    binArray[i] = dataVal % 2;
    dataVal /= 2;
  }
}


int main(void)
{
  FILE *dataFiles[NUM_FILES];
  dataFiles[0] = fopen("White House Transmission Data - Parity.txt", "r");
  dataFiles[1] = fopen("White House Transmission Data - Checksum.txt", "r");
  dataFiles[2] = fopen("White House Transmission Data - 2D Parity.txt", "r");

  // File open test
  for (int i = 0; i < NUM_FILES; i++) // checks for null pointers in all files
  {
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

  // PART 1 PARITY CHECK
  // printf("\n\n** Part 1 - Parity Check Processing\n\n\n");
  
  // int lineNumberParity = 1;
  // while (!feof(dataFiles[0]))
  // {  

  //   int dataBytes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  //   int parityByte = 0;
  //   int parityBitArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  //   fscanf(dataFiles[0], "%3d%4d%4d%4d%4d%4d%4d%4d%4d", &dataBytes[0], &dataBytes[1], &dataBytes[2], &dataBytes[3], &dataBytes[4], &dataBytes[5], &dataBytes[6], &dataBytes[7], &parityByte);

  //   decToBinArray(parityByte, parityBitArray, 8);

  //   printf("Transmission line number: %d\n\n\n", lineNumberParity);
  //   printf("Data stream:\n");
  //   arrayOutFormatted(dataBytes, 8, "%d ");
  //   printf("\n\n");
  //   printf("Parity Byte: %d\n\n", parityByte);

  //   for (int i = 0; i < 8; i++)
  //   {
  //     int dataValBin[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  //     decToBinArray(dataBytes[i], dataValBin, 8);
  //     printf("Data Item: %d, Binary: ", dataBytes[i]);
  //     arrayOut(dataValBin, 8);
  //     printf(", Parity Bit: %d", parityBitArray[i]);
  //     printf("\n");

  //     if (hasEvenParity(dataValBin, 8, parityBitArray[i]))
  //     {
  //       printf("No error in transmission byte %d\n", i + 1);
  //     }
  //     else
  //     {
  //       printf("Error in transmission byte %d\n", i + 1);
  //     }
    
  //     printf("\n\n");
  //   }
  //   printf("\n");
  //   lineNumberParity++;
  //   // printf("Continue?:");
  //   // char input;
  //   // scanf("%c", &input);
  // }

  // PART 2 CHECKSUM

  for (int k = 0; k < NUM_FILES; k++)
  { // closes all files in file array
    fclose(dataFiles[k]);
  }
  return 0;
}