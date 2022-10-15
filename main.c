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
bool hasEvenParity(int binNum, int parityBit);
bool checksum(int sumDataItems, int checksumVal);

int decToBin(int decNum)
{ // converts decimal number to binary
  int binaryNumArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

bool hasEvenParity(int binNum, int parityBit)
{
  int numOnes = parityBit;
  while (binNum != 0)
  {
    if (binNum % 10 == 1)
    {
      numOnes++;
    }
    else
    {
      numOnes += 0;
    }
    binNum /= 10;
  }

  printf("numOnes (including parity bit): %d\n", numOnes);

  if (numOnes % 2 == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool checksum(int sumDataItems, int checksumVal)
{
  int totalSum = sumDataItems + checksumVal;
  int complement = ~totalSum;
  printf("Sum after adding checksum = %d, binary = %d\n", totalSum, decToBin(totalSum));
  printf("Sum after complement = %d\n", complement);

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

  // PART 1 - PARITY CHECK PROCESSING
  // printf("** Part 1 - Parity Check Processing\n\n\n");

  // while (!feof(dataFiles[0])) // runs through file until it reaches the end
  // {
  //   int dataBytes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  //   int parityByte = 0;
  //   int parityBitArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  //   fscanf(dataFiles[0], "%3d%4d%4d%4d%4d%4d%4d%4d%4d", &dataBytes[0], &dataBytes[1], &dataBytes[2], &dataBytes[3], &dataBytes[4], &dataBytes[5], &dataBytes[6], &dataBytes[7], &parityByte);
  //   int parityByteBin = decToBin(parityByte);

  //   for (int i = 8; i > 0; i--) // splits up parity byte into a bit array
  //   {
  //     parityBitArray[i - 1] = parityByteBin % 10;
  //     parityByteBin /= 10;
  //   }

  //   printf("\nData stream:");

  //   for (int i = 0; i < 8; i++)
  //   {
  //     printf(" %d", dataBytes[i]);
  //   }
  //   printf("\n\nParity Byte: %d", parityByte);
  //   printf("\n\n");

  //   for (int i = 0; i < 8; i++) // iterates through data items and checks for parity
  //   {
  //     int binData = decToBin(dataBytes[i]);
  //     printf("Data Item: %d, Binary: %d, Parity Bit: %d\n", dataBytes[i], binData, parityBitArray[i]);
  //     if (hasEvenParity(binData, parityBitArray[i]) == true)
  //     {
  //       printf("No error in transmission byte: %d", dataBytes[i]);
  //     }
  //     else
  //     {
  //       printf("Error in transmission byte: %d", dataBytes[i]);
  //     }

  //     printf("\n\n");
  //   }
  // }

  // PART 1 - PARITY CHECK PROCESSING END

  printf("\n\n\n");

  // PART 2 - CHECKSUM PROCESSING
  printf("** Part 2 - Checksum Processing\n\n\n");

  int dataBytes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int sumDataBytes = 0;
  int sumDataBytesBin = 0;
  int checksumVal = 0;
  int checksumValBin = 0;

  fscanf(dataFiles[1], "%4d%4d%4d%4d%4d%4d%4d%4d%4d", &dataBytes[0], &dataBytes[1], &dataBytes[2], &dataBytes[3], &dataBytes[4], &dataBytes[5], &dataBytes[6], &dataBytes[7], &checksumVal);

  printf("\nData stream:");

  for (int i = 0; i < 8; i++)
  {
    printf(" %d", dataBytes[i]);
  }

  printf("\nChecksum: %d\n\n", checksumVal);

  for (int i = 0; i < 8; i++)
  {
    int binData = decToBin(dataBytes[i]);
    printf("parityData[i] = %d, binary = %d\n\n", dataBytes[i], binData);
    sumDataBytes += dataBytes[i];
  }

  sumDataBytesBin = decToBin(sumDataBytes);
  checksumValBin = decToBin(checksumVal);
  printf("Sum of data items = %d, binary = %d\n\n", sumDataBytes, sumDataBytesBin);
  printf("Checksum value = %d, binary = %d\n\n", checksumVal, checksumValBin);

  if (checksum(sumDataBytes, checksumVal) == true)
  {
    printf("Checksum: No errors in transmission\n\n");
  }
  else
  {
    printf("Checksum: Errors in transmission\n\n");
  }
  


  for (int k = 0; k < NUM_FILES; k++)
  { // closes all files in file array
    fclose(dataFiles[k]);
  }
  return 0;
}