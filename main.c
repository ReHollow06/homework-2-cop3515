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
bool hasEvenParity(int binNum, int parityBit);
bool checksum(int sumDataItems, int checksumVal);
bool has2DParity();
int numComplement(int num);

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
    decNum += rem * (int) pow((double) 2, (double) placeCount);
    placeCount++;
  }

  return decNum;
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

  // printf("numOnes (including parity bit): %d\n", numOnes);

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
  int complement = numComplement(totalSum);
  printf("Sum after adding checksum = %d, binary = %d\n", totalSum, decToBin(totalSum));
  printf("Sum after complement = %u\n", complement);
  if (complement == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

int numComplement(int num)
{
  if (num <= 255)
  {
    unsigned char num_u_char = (unsigned char) num;
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

    //DEBUG
    // for (int i = 0; i < 10; i++) 
    // {
    //   printf("%d", numBinBitArray[i]);
    // }
    
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

  // PART 1 - PARITY CHECK PROCESSING
  printf("** Part 1 - Parity Check Processing\n\n\n");

  while (!feof(dataFiles[0])) // runs through file until it reaches the end
  {
    int dataBytes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int parityByte = 0;
    int parityBitArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    fscanf(dataFiles[0], "%3d%4d%4d%4d%4d%4d%4d%4d%4d", &dataBytes[0], &dataBytes[1], &dataBytes[2], &dataBytes[3], &dataBytes[4], &dataBytes[5], &dataBytes[6], &dataBytes[7], &parityByte);
    int parityByteBin = decToBin(parityByte);

    for (int i = 8; i > 0; i--) // splits up parity byte into a bit array
    {
      parityBitArray[i - 1] = parityByteBin % 10;
      parityByteBin /= 10;
    }

    printf("\nData stream:");

    for (int i = 0; i < 8; i++)
    {
      printf(" %d", dataBytes[i]);
    }
    printf("\n\nParity Byte: %d", parityByte);
    printf("\n\n");

    for (int i = 0; i < 8; i++) // iterates through data items and checks for parity
    {
      int binData = decToBin(dataBytes[i]);
      printf("Data Item: %d, Binary: %d, Parity Bit: %d\n", dataBytes[i], binData, parityBitArray[i]);
      if (hasEvenParity(binData, parityBitArray[i]) == true)
      {
        printf("No error in transmission byte: %d", dataBytes[i]);
      }
      else
      {
        printf("Error in transmission byte: %d", dataBytes[i]);
      }

      printf("\n\n");
    }
  }

  // PART 1 - PARITY CHECK PROCESSING END

  printf("\n\n\n");

  // PART 2 - CHECKSUM PROCESSING
  printf("** Part 2 - Checksum Processing\n\n\n");

  while (!feof(dataFiles[1]))
  {
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
  }
  printf("\n\n\n");

  // PART 3 - 2D PARITY CHECK
  // printf("** Part 3 - Two Dimensional Parity check\n\n\n");

  // printf("==> Processing Transmission Block 1\n\n\n");

  // int dataBytes[8][8];
  // int parityBytes[8][2];
  // int vertParityBitArray[8];
  // int vertParityByteBin;
  // int horiParityBitArray[8];
  // int horiParityByteBin;

  // for (int i = 0; i < 8; i++)
  // {
  //   fscanf(dataFiles[2], "%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d", &dataBytes[i][0], &dataBytes[i][1], &dataBytes[i][2], &dataBytes[i][3], &dataBytes[i][4], &dataBytes[i][5], &dataBytes[i][6], &dataBytes[i][7], &parityBytes[i][0], &parityBytes[i][1]);
  // }

  // printf("Data streams: \n");

  // for (int i = 0; i < 8; i++) // outputs data streams being checked
  // {
  //   for (int j = 0; j < 8; j++)
  //   {
  //     printf("%d ", dataBytes[i][j]);
  //   }
  //   printf("[V: %d] [H: %d]", parityBytes[i][0], parityBytes[i][1]);
  //   printf("\n");
  // }

  // printf("\n");

  // for (int i = 0; i < 8; i++)
  // {
  //   int numValuesPassed = 0;
  //   printf("** Vertical processing transmission line %d\n", i);
  //   for (int j = 0; j < 8; j++)
  //   {
  //     printf("Value %d = %d, %d\n", j + 1, dataBytes[j][i], decToBin(dataBytes[j][i]));
  //   }
  //   printf("\n");
  //   printf("Parity Byte = %d", parityBytes[i][0]);
  //   vertParityByteBin = decToBin(parityBytes[i][0]);
  //   printf("\n");

  //   for (int j = 0; j < 8; j++)
  //   {
  //     for (int k = 8; k > 0; k--) // splits up parity byte into a bit array
  //     {
  //       vertParityBitArray[k - 1] = vertParityByteBin % 10;
  //       vertParityByteBin /= 10;
  //       //printf("%d ", vertParityByteBin);
  //     }

  //     int binVal = decToBin(dataBytes[j][i]);
      
  //     if (hasEvenParity(binVal, vertParityBitArray[j]))
  //     {
  //       numValuesPassed++;
  //     }
  //   }
  //   printf("Num Values passed: %d\n\n", numValuesPassed);
  // }

  for (int k = 0; k < NUM_FILES; k++)
  { // closes all files in file array
    fclose(dataFiles[k]);
  }
  return 0;
}