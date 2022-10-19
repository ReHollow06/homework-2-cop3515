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

int decToBin(int decNum);
int binToDec(int binNum);
void arrayOut(int *numArray, int size);
void arrayOutFormatted(int *numArray, int size, const char *stringFormat);
bool hasEvenParity(int *binArray, int binArraySize, int parityBit);
void decToBinArray(int dataVal, int *binArray, int binArraySize);
int sumArray(int *numArray, int size);

int decToBin(int decNum)
{ // converts decimal number to binary
  int binaryNumArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int binaryNum = 0;
  int i = 0;
  int placeCount = 1000000000;
  while (decNum != 0)
  {
    binaryNumArray[i++] = decNum % 2;
    decNum /= 2;
  }

  for (int j = 10; j > 0; j--)
  {
    binaryNum += binaryNumArray[j - 1] * placeCount;
    placeCount /= 10;
  }

  return binaryNum;
}

int binToDec(int binNum)
{
  int decNum = 0;
  int placeCount = 0;
  int rem;

  while (binNum != 0)
  {
    rem = binNum % 10;
    binNum /= 10;
    decNum += rem * (int)pow((double)2, (double)placeCount);
    placeCount++;
  }

  return decNum;
}

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
  for (int i = 0; i < binArraySize; i++)
  {
    binArray[i] = 0;
  }

  for (int i = binArraySize - 1; dataVal > 0; i--)
  {
    binArray[i] = dataVal % 2;
    dataVal /= 2;
  }
}

int sumArray(int *numArray, int size)
{
  int sum = 0;

  for (int i = 0; i < size; i++)
  {
    sum += numArray[i];
  }

  return sum;
}

int numComplement(int num)
{
  if (num <= 255)
  {
    unsigned char num_u_char = (unsigned char)num;
    unsigned char complement = ~num_u_char;
    return complement;
  }
  else if (num > 255 && num <= 1023)
  {
    int numBin = decToBin(num);
    int numBinComplement = 0;
    int complement = 0;
    int numBinBitArray[10];
    int numBinBitArrayComp[10];
    int index = 9;
    int placeCount = 1000000000;

    for (int i = 0; i < 10; i++)
    {
      numBinBitArray[i] = 0;
      numBinBitArrayComp[i] = 0;
    }

    while (numBin != 0)
    {
      numBinBitArray[index] = numBin % 10;
      numBin /= 10;
      index--;
    }

    for (int i = 0; i < 10; i++) // complementing binary bit array
    {
      switch (numBinBitArray[i])
      {
      case 0:
        numBinBitArrayComp[i] = 1;
        break;
      case 1:
        numBinBitArrayComp[i] = 0;
        break;
      default:
        break;
      }
    }

    // DEBUG
    //  for (int i = 0; i < 10; i++)
    //  {
    //    printf("%d", numBinBitArray[i]);
    //  }

    // printf(" ");

    // for (int i = 0; i < 10; i++)
    // {
    //   printf("%d", numBinBitArrayComp[i]);
    // }

    for (int i = 10; i > 0; i--)
    {
      numBinComplement += numBinBitArrayComp[i - 1] * placeCount;
      placeCount /= 10;
    }

    complement = binToDec(numBinComplement);
    return complement;
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
  printf("\n\n** Part 1 - Parity Check Processing\n\n\n");

  int lineNumberParity = 1;
  while (!feof(dataFiles[0]))
  {

    int dataBytes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int parityByte = 0;
    int parityBitArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    fscanf(dataFiles[0], "%3d%4d%4d%4d%4d%4d%4d%4d%4d", &dataBytes[0], &dataBytes[1], &dataBytes[2], &dataBytes[3], &dataBytes[4], &dataBytes[5], &dataBytes[6], &dataBytes[7], &parityByte);

    decToBinArray(parityByte, parityBitArray, 8);

    printf("==> Transmission line number: %d\n\n\n", lineNumberParity);
    printf("Data stream:\n");
    arrayOutFormatted(dataBytes, 8, "%d ");
    printf("\n\n");
    printf("Parity Byte: %d\n\n", parityByte);

    for (int i = 0; i < 8; i++) // loops through dataBytes and checks parity
    {
      int dataValBin[8] = {0, 0, 0, 0, 0, 0, 0, 0};
      decToBinArray(dataBytes[i], dataValBin, 8);
      printf("Data Item: %d, Binary: ", dataBytes[i]);
      arrayOut(dataValBin, 8);
      printf(", Parity Bit: %d", parityBitArray[i]);
      printf("\n");

      if (hasEvenParity(dataValBin, 8, parityBitArray[i]))
      {
        printf("No error in transmission byte %d\n", i + 1);
      }
      else
      {
        printf("Error in transmission byte %d\n", i + 1);
      }

      printf("\n\n");
    }
    printf("\n");
    lineNumberParity++;
    // printf("Continue?:");
    // char input;
    // scanf("%c", &input);
  }

  // PART 2 CHECKSUM
  printf("** Part 2 - Checksum Processing\n\n\n");
  int lineNumberChecksum = 1;
  while (!feof(dataFiles[1]))
  {

    int dataBytes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int checksumVal = 0;
    int sumDataBytes = 0;
    int finalSum = 0;

    fscanf(dataFiles[1], "%4d%4d%4d%4d%4d%4d%4d%4d%4d", &dataBytes[0], &dataBytes[1], &dataBytes[2], &dataBytes[3], &dataBytes[4], &dataBytes[5], &dataBytes[6], &dataBytes[7], &checksumVal);
    printf("==> Transmission line number: %d\n\nData stream:\n", lineNumberChecksum);
    arrayOutFormatted(dataBytes, 8, "%d ");
    printf("\n");
    printf("Checksum: %d\n\n", checksumVal);

    sumDataBytes = sumArray(dataBytes, 8);
    finalSum = sumDataBytes + checksumVal;

    if (finalSum <= 255)
    {
      int sumDataBytesBin[8];
      int checksumValBin[8];
      int finalSumBin[8];
      decToBinArray(sumDataBytes, sumDataBytesBin, 8);
      decToBinArray(checksumVal, checksumValBin, 8);
      decToBinArray(finalSum, finalSumBin, 8);
      for (int i = 0; i < 8; i++)
      {
        int dataValBin[8];
        decToBinArray(dataBytes[i], dataValBin, 8);
        printf("parityData[i]: %d, Binary: ", dataBytes[i]);
        arrayOut(dataValBin, 8);
        printf("\n\n");
      }

      printf("Sum of data items: %d, Binary: ", sumDataBytes);
      arrayOut(sumDataBytesBin, 8);
      printf("\n\n");
      printf("Checksum value: %d, Binary: ", checksumVal);
      arrayOut(checksumValBin, 8);
      printf("\n\n\n");
      printf("Sum after adding checksum: %d, Binary: ", finalSum);
      arrayOut(finalSumBin, 8);
      printf("\n");
      printf("Sum after complement: %d, Binary ", numComplement(finalSum));
      int finalSumCompBin[8];
      decToBinArray(numComplement(finalSum), finalSumCompBin, 8);
      arrayOut(finalSumCompBin, 8);
      printf("\n\n");

      if (numComplement(finalSum) == 0)
      {
        printf("Checksum: No errors in transmission\n\n\n");
      }
      else
      {
        printf("Checksum: Errors in transmission\n\n\n");
      }
    }
    else if (finalSum > 255 && finalSum <= 1023)
    {
      int sumDataBytesBin[10];
      int checksumValBin[10];
      int finalSumBin[10];
      decToBinArray(sumDataBytes, sumDataBytesBin, 10);
      decToBinArray(checksumVal, checksumValBin, 10);
      decToBinArray(finalSum, finalSumBin, 10);
      for (int i = 0; i < 8; i++)
      {
        int dataValBin[10];
        decToBinArray(dataBytes[i], dataValBin, 10);
        printf("parityData[i]: %d, Binary: ", dataBytes[i]);
        arrayOut(dataValBin, 10);
        printf("\n\n\n");
      }

      printf("Sum of data items: %d, Binary: ", sumDataBytes);
      arrayOut(sumDataBytesBin, 10);
      printf("\n\n");
      printf("Checksum value: %d, Binary: ", checksumVal);
      arrayOut(checksumValBin, 10);
      printf("\n\n\n");
      printf("Sum after adding checksum: %d, Binary: ", finalSum);
      arrayOut(finalSumBin, 10);
      printf("\n");
      printf("Sum after complement: %d, Binary ", numComplement(finalSum));
      int finalSumCompBin[10];
      decToBinArray(numComplement(finalSum), finalSumCompBin, 10);
      arrayOut(finalSumCompBin, 10);
      printf("\n\n");

      if (numComplement(finalSum) == 0)
      {
        printf("Checksum: No errors in transmission\n\n\n");
      }
      else
      {
        printf("Checksum: Errors in transmission\n\n\n");
      }
    }
    
    lineNumberChecksum++;
  }

  for (int k = 0; k < NUM_FILES; k++)
  { // closes all files in file array
    fclose(dataFiles[k]);
  }
  return 0;
}