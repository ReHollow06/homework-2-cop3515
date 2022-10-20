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
bool hasVerticalParity(int *vertArray, int vertArraySize, int parityByte);
bool hasHorizontalParity(int *horiArray, int horiArraySize, int parityByte);

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

bool hasVerticalParity(int *vertArray, int vertArraySize, int parityByte)
{
  int parityBitArray[8];
  int vertBitArray[8][8];
  int numPassedVertChecks = 0;
  decToBinArray(parityByte, parityBitArray, 8);

  for (int i = 0; i < 8; i++)
  {
    int temp[8];
    decToBinArray(vertArray[i], temp, 8);
    for (int j = 0; j < 8; j++)
    {
      vertBitArray[j][i] = temp[j]; // Transposes bit matrix
    }
  }

  for (int i = 0; i < 8; i++)
  {
    if (hasEvenParity(vertBitArray[i], 8, parityBitArray[i]))
    {
      numPassedVertChecks++;
    }
  }

  if (numPassedVertChecks == vertArraySize)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool hasHorizontalParity(int *horiArray, int horiArraySize, int parityByte)
{
  int parityBitArray[8];
  int horiBitArray[8][8];
  int numPassedHoriChecks = 0;
  decToBinArray(parityByte, parityBitArray, 8);

  for (int i = 0; i < 8; i++)
  {
    int temp[8];
    decToBinArray(horiArray[i], temp, 8);
    for (int j = 0; j < 8; j++)
    {
      horiBitArray[i][j] = temp[j];
    }
  }

  for (int i = 0; i < 8; i++)
  {
    if (hasEvenParity(horiBitArray[i], 8, parityBitArray[i]))
    {
      numPassedHoriChecks++;
    }
  }

  if (numPassedHoriChecks == horiArraySize)
  {
    return true;
  }
  else
  {
    return false;
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

      printf("\n");
    }
    printf("\n");
    printf("Press ENTER to continue to next line: ");
    char input;
    scanf("%c", &input);
    printf("\n\n");
    lineNumberParity++;
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
        //printf("parityData[i]: %d, Binary: ", dataBytes[i]);
        //arrayOut(dataValBin, 8);
        //printf("\n\n");
      }

      printf("Sum of data items: %d, Binary: ", sumDataBytes);
      arrayOut(sumDataBytesBin, 8);
      printf("\n");
      printf("Checksum value: %d, Binary: ", checksumVal);
      arrayOut(checksumValBin, 8);
      printf("\n");
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
        printf("Checksum: No errors in transmission\n\n");
      }
      else
      {
        printf("Checksum: Errors in transmission\n\n");
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
        //printf("parityData[i]: %d, Binary: ", dataBytes[i]);
        //arrayOut(dataValBin, 10);
        //printf("\n\n\n");
      }

      printf("Sum of data items: %d, Binary: ", sumDataBytes);
      arrayOut(sumDataBytesBin, 10);
      printf("\n");
      printf("Checksum value: %d, Binary: ", checksumVal);
      arrayOut(checksumValBin, 10);
      printf("\n");
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
        printf("Checksum: No errors in transmission\n\n");
      }
      else
      {
        printf("Checksum: Errors in transmission\n\n");
      }
    }
    
    printf("Press ENTER to continue to next line: ");
    char input;
    scanf("%c", &input);
    lineNumberChecksum++;
  }

  // PART 3 2D PARITY

  int blockNumber2dParity = 1;

  printf("\n** Part 3 - Two-dimensional Parity check\n\n\n");

  while (!feof(dataFiles[2]))
  {
    printf("==> Processing Transmission Block %d\n\n", blockNumber2dParity);

    int dataMatrix[8][8];
    int dataMatrixRow = 8;
    int dataMatrixColumn = 8;
    int parityByteMatrix[8][2];
    bool passedVerticalParity = false;
    bool passedHorizontalParity = false;
    int numVertParityChecksPassed = 0;
    int numHoriParityChecksPassed = 0;

    for (int i = 0; i < 8; i++)
    {
      fscanf(dataFiles[2], "%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d", &dataMatrix[i][0], &dataMatrix[i][1], &dataMatrix[i][2], &dataMatrix[i][3], &dataMatrix[i][4], &dataMatrix[i][5], &dataMatrix[i][6], &dataMatrix[i][7], &parityByteMatrix[i][0], &parityByteMatrix[i][1]);
    }

    printf("Data streams:\n");

    for (int i = 0; i < dataMatrixColumn; i++)
    {
      arrayOutFormatted(dataMatrix[i], dataMatrixRow, "%d ");
      printf(" [V:%4d] [H:%4d]\n", parityByteMatrix[i][0], parityByteMatrix[i][1]);
    }

    printf("\n--> Processing Columns\n\n");

    for (int i = 0; i < dataMatrixColumn; i++) // VERTICAL PROCESSING
    {
      int currentColumn[8];
      int parityBitArray[8];
      decToBinArray(parityByteMatrix[i][0], parityBitArray, 8);
      //printf("\n** Vertical processing transmission line %d\n\n", i);
      for (int j = 0; j < dataMatrixRow; j++)
      {
        int dataByteBin[8];
        currentColumn[j] = dataMatrix[j][i];
        //printf("Value %d: %4d, Binary: ", j + 1, dataMatrix[j][i]);
        decToBinArray(dataMatrix[j][i], dataByteBin, 8);
        //arrayOut(dataByteBin, 8);
        //printf(", Parity Bit: %d", parityBitArray[j]);
        //printf("\n");
      }
      //printf("\n");
      //printf("Vertical Parity Byte: %d\n", parityByteMatrix[i][0]);

      if (hasVerticalParity(currentColumn, 8, parityByteMatrix[i][0]))
      {
        //arrayOut(currentColumn, 8);
        //printf("\n");
        printf("Transmission Line %d passed vertical parity\n", i);
        numVertParityChecksPassed++;
      }
      else
      {
        printf("Transmission Line %d failed vertical parity\n", i);
      }

    }
    printf("\n");

    //printf("Passed: %d\n\n", numVertParityChecksPassed);

    if (numVertParityChecksPassed == dataMatrixColumn)
    {
      passedVerticalParity = true;
      printf("Transmission block %d PASSED complete vertical parity test\n", blockNumber2dParity);
    }
    else
    {
      printf("Transmission block %d FAILED complete vertical parity test\n", blockNumber2dParity);
    }

    printf("\n");
    printf("\n--> Processing Rows\n\n");

    for (int i = 0; i < dataMatrixColumn; i++) // HORIZONTAL PROCESSING
    {
      int currentRow[8];
      int parityBitArray[8];
      decToBinArray(parityByteMatrix[i][1], parityBitArray, 8);
      //printf("\n** Horizontal processing transmission line %d\n\n", i);
      for (int j = 0; j < dataMatrixRow; j++)
      {
        int dataByteBin[8];
        currentRow[j] = dataMatrix[i][j];
        //printf("Value %d: %4d, Binary: ", j + 1, dataMatrix[i][j]);
        decToBinArray(dataMatrix[i][j], dataByteBin, 8);
        //arrayOut(dataByteBin, 8);
        //printf(", Parity Bit: %d", parityBitArray[j]);

        //printf("\n");
      }
      //printf("\n");
      //printf("Horizontal Parity Byte: %d\n", parityByteMatrix[i][1]);

      if (hasHorizontalParity(currentRow, 8, parityByteMatrix[i][1]))
      {
        printf("Transmission Line %d passed horizontal parity\n", i);
        numHoriParityChecksPassed++;
      }
      else
      {
        printf("Transmission Line %d failed horizontal parity\n", i);
      }
    }

    //printf("passed: %d\n\n", numHoriParityChecksPassed);
    printf("\n\n");
    if (numHoriParityChecksPassed == dataMatrixRow)
    {
      passedHorizontalParity = true;
      printf("Transmission block %d PASSED complete horizontal parity test\n", blockNumber2dParity);
    }
    else
    {
      printf("Transmission block %d FAILED complete horizontal parity test\n", blockNumber2dParity);
    }

    if (passedHorizontalParity && passedVerticalParity)
    {
      printf("---> Transmission block %d PASSED - it is error free\n", blockNumber2dParity);
    }
    else
    {
      printf("---> Transmission block %d FAILED - it has errors\n", blockNumber2dParity);
    }
    

    printf("\n\nPress ENTER to continue to next block: ");
    char input;
    scanf("%c", &input);
    blockNumber2dParity++;
    printf("\n\n");
  }

  for (int k = 0; k < NUM_FILES; k++)
  { // closes all files in file array
    fclose(dataFiles[k]);
  }
  return 0;
}