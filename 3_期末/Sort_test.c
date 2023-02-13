#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
  int compareCount;
  int swapCount;
} sortresult_t;

void print_result(sortresult_t result);
void run_bubble_ascend_sort(int length, int array[]);
void run_bubble_descend_sort(int length, int array[]);
void run_radix_ascend_sort(int length, int array[]);
void radix_ascend_sort(int length, int array[], int radix, int loopNum);
void run_radix_descend_sort(int length, int array[]);
void radix_descend_sort(int length, int array[], int radix, int loopNum);
void run_selection_ascend_sort(int length, int array[]);
void run_selection_descend_sort(int length, int array[]);
void run_quick_ascend_sort(int length, int array[], int startIndex, int endIndex);
sortresult_t quick_ascend_sort(int length, int array[], int startIndex, int endIndex);
void run_quick_descend_sort(int length, int array[], int startIndex, int endIndex);
sortresult_t quick_descend_sort(int length, int array[], int startIndex, int endIndex);
void ascend_randomize(int length, int array[], int startIndex, int endIndex);
void descend_randomize(int length, int array[], int startIndex, int endIndex);
void ascend_initialize(int length, int array[]);
void descend_initialize(int length, int array[]);
void swap(int array[], int indexA, int indexB);
void show_array(int length, int array[]);
int get_digit(int num, int digit);
void init_array(int array[], int length);

int main(void)
{
  char DUMMY;
  int NUMBER, percent = 70, startIndex = 0;
  // printf("length of array? (0<) : ");
  // scanf("%d%c", &NUMBER, &DUMMY); // #1
  NUMBER = 50;
  if (NUMBER < 1)
  {
    printf("length is must be positive.\n");
    return -1;
  }

  char METHOD;
  // printf("Sort Method? ( Bubble: b, Selection: s, Quick: q, Radix: r ) : ");
  // scanf("%c%c", &METHOD, &DUMMY); // #2

  char ORDER;
  // printf("Order? (Ascending: a, Descending: d ) : ");
  // scanf("%c%c", &ORDER, &DUMMY); // #3

  // printf("ORDER: %c, METHOD: %c\n", ORDER, METHOD);

  int MODE;
  // printf("What is type of Array?\n");
  // printf("1: Ordered Ascending\n");
  // printf("2: Ordered Descending\n");
  // printf("3: Randomized\n");
  // printf("4: Partially Ordered Ascending\n");
  // printf("5: Partially Ordered Descending\n");
  // printf("> ");
  // scanf("%d", &MODE); // #4

  srand((unsigned long)time(NULL));

  char methodi[] = {'b', 's', 'q', 'r'};
  char orderi[] = {'a', 'd'};

  char *fullMet[] = {"Bubble Sort", "Selection Sort", "Quick Sort", "Radix Sort"};
  char *fullOrd[] = {"Ascend", "Descend"};
  char *fullMod[] = {"", "Ordered Ascending", "Ordered Descending", "Fully Randomized", "Partially Ordered Ascending", "Partially Ordered Descending"};

for (int mei = 0; mei < 4; mei++)
for (int oi = 0; oi < 2; oi++)
for (int moi = 1; moi < 6; moi++)
  for (int i = 0; i < 10; i++ ){
  int array[NUMBER];
  MODE = moi;
  METHOD = methodi[mei];
  ORDER = orderi[oi];

printf("\n#%d\nmethod: %s with %s\n50 elements init with: %s\n", i + 1, fullMet[mei], fullOrd[oi], fullMod[moi]);

  switch (MODE)
  {
  case 1:
    ascend_initialize(NUMBER, array);
    break;
  case 2:
    descend_initialize(NUMBER, array);
    break;
  case 3:
    ascend_randomize(NUMBER, array, 0, NUMBER - 1);
    break;
  case 4:
    // printf("random ratio?(0-100): ");
    // scanf("%d", &percent);

    percent = 70;

    printf("random ratio %d\n", percent);

    startIndex = (100 - percent) * NUMBER / 100;
    ascend_randomize(NUMBER, array, startIndex, NUMBER - 1);
    break;

  case 5:
    // printf("random ratio?(0-100): ");
    // scanf("%d", &percent);
    percent = 70;
    printf("random ratio %d\n", percent);

    startIndex = (100 - percent) * NUMBER / 100;
    descend_randomize(NUMBER, array, startIndex, NUMBER - 1);
    break;

  default:
    printf("we can't recognized.\n");
    return -1;
    break;
  }

  // printf("array: ");
  // show_array(NUMBER, array);

  switch (ORDER)
  {
  case 'a':
    switch (METHOD)
    {
    case 'q':
      run_quick_ascend_sort(NUMBER, array, 0, NUMBER - 1);
      break;
    case 's':
      run_selection_ascend_sort(NUMBER, array);
      break;
    case 'b':
      run_bubble_ascend_sort(NUMBER, array);
      break;
    case 'r':
      run_radix_ascend_sort(NUMBER, array);
    default:
      break;
    };
    break;
  case 'd':
    switch (METHOD)
    {
    case 'q':
      run_quick_descend_sort(NUMBER, array, 0, NUMBER - 1);
      break;
    case 's':
      run_selection_descend_sort(NUMBER, array);
      break;
    case 'b':
      run_bubble_descend_sort(NUMBER, array);
      break;
    case 'r':
      run_radix_descend_sort(NUMBER, array);
      break;
    default:
      break;
    }
  default:
    break;
  }

  // show_array(NUMBER, array);
  }
}

void print_result(sortresult_t result)
{
  printf("compare count: %d\n", result.compareCount);
  printf("swap count: %d\n", result.swapCount);
}

void run_bubble_ascend_sort(int length, int array[])
{
  int compareCount = 0, swapCount = 0, swapIndex;

  for (int baseIndex = 0; baseIndex < length; baseIndex++)
  {
    for (int compareIndex = 0; compareIndex < length - baseIndex - 1; compareIndex++)
    {
      compareCount++;
      if (array[compareIndex] > array[compareIndex + 1])
      {
        swapCount++;
        swap(array, compareIndex, compareIndex + 1);
      }
    }
  }

  sortresult_t resultData = {
      .compareCount = compareCount,
      .swapCount = swapCount};

  print_result(resultData);
}

void run_radix_ascend_sort(int length, int array[])
{
  radix_ascend_sort(length, array, 10, 0);
}

/**
 * @param radix 基数
 * @param loopNum ループしている回数 最初は0
 */
void radix_ascend_sort(int length, int array[], int radix, int loopNum)
{
  int indexes[length]; // 基数配列
  int tmpArr[length];  // 作業配列
  bool isSorted = true;

  init_array(indexes, length);
  init_array(tmpArr, length);

  for (int idx = 0; idx < length; idx++)
  {
    int tmp = get_digit(array[idx], loopNum); // 基数とってくる
    indexes[idx] = tmp;
    if (array[idx] > (int)pow(radix, loopNum))
      isSorted = false;
  }

  if (isSorted)
    return;

  int tmpArrIdx = 0; // 作業配列のどこに差し込むかのidx

  // 基数ベースの昇順ソート
  for (int rad = 0; rad < radix; rad++)
  {
    for (int arrIdx = 0; arrIdx < length; arrIdx++)
    {
      if (indexes[arrIdx] == rad)
      {
        tmpArr[tmpArrIdx] = array[arrIdx];
        tmpArrIdx += 1;
      }
    }
  }

  for (int idx = 0; idx < length; idx++)
  {
    array[idx] = tmpArr[idx];
  }

  radix_ascend_sort(length, array, radix, loopNum + 1);
}

void run_radix_descend_sort(int length, int array[])
{
  radix_descend_sort(length, array, 10, 0);
}

void radix_descend_sort(int length, int array[], int radix, int loopNum)
{
  int indexes[length]; // 基数配列
  int tmpArr[length];  // 作業配列
  bool isSorted = true;

  init_array(indexes, length);
  init_array(tmpArr, length);

  for (int idx = 0; idx < length; idx++)
  {
    int tmp = get_digit(array[idx], loopNum); // 基数とってくる
    indexes[idx] = tmp;
    if (array[idx] > (int)pow(radix, loopNum))
      isSorted = false;
  }

  if (isSorted)
    return;

  int tmpArrIdx = 0; // 作業配列のどこに差し込むかのidx

  // 基数ベースの降順ソート
  for (int rad = radix; rad >= 0; rad--)
  {
    for (int arrIdx = 0; arrIdx < length; arrIdx++)
    {
      if (indexes[arrIdx] == rad)
      {
        tmpArr[tmpArrIdx] = array[arrIdx];
        tmpArrIdx += 1;
      }
    }
  }

  for (int idx = 0; idx < length; idx++)
  {
    array[idx] = tmpArr[idx];
  }

  radix_descend_sort(length, array, radix, loopNum + 1);
}

void run_bubble_descend_sort(int length, int array[])
{
  int compareCount = 0, swapCount = 0, swapIndex;

  for (int baseIndex = 0; baseIndex < length; baseIndex++)
  {
    for (int compareIndex = 0; compareIndex < length - baseIndex - 1; compareIndex++)
    {
      compareCount++;
      if (array[compareIndex] < array[compareIndex + 1])
      {
        swapCount++;
        swap(array, compareIndex, compareIndex + 1);
      }
    }
  }

  sortresult_t resultData = {
      .compareCount = compareCount,
      .swapCount = swapCount};

  print_result(resultData);
}

void run_selection_ascend_sort(int length, int array[])
{
  int compareCount = 0, swapCount = 0, swapIndex;

  for (int baseIndex = 0; baseIndex < length; baseIndex++)
  {
    swapIndex = baseIndex;
    for (int compareIndex = baseIndex + 1; compareIndex < length; compareIndex++)
    {
      compareCount++;
      if (array[swapIndex] > array[compareIndex])
      {
        swapIndex = compareIndex;
      }
    }
    swapCount++;
    swap(array, baseIndex, swapIndex);
  }
  sortresult_t resultData = {
      .compareCount = compareCount,
      .swapCount = swapCount};

  print_result(resultData);
}

void run_selection_descend_sort(int length, int array[])
{
  int compareCount = 0, swapCount = 0, swapIndex;

  for (int baseIndex = 0; baseIndex < length; baseIndex++)
  {
    swapIndex = baseIndex;
    for (int compareIndex = baseIndex + 1; compareIndex < length; compareIndex++)
    {
      compareCount++;
      if (array[swapIndex] < array[compareIndex])
      {
        swapIndex = compareIndex;
      }
    }
    swapCount++;
    swap(array, baseIndex, swapIndex);
  }
  sortresult_t resultData = {
      .compareCount = compareCount,
      .swapCount = swapCount};

  print_result(resultData);
}

void run_quick_ascend_sort(int length, int array[], int startIndex, int endIndex)
{
  sortresult_t sortResult = quick_ascend_sort(length, array, startIndex, endIndex);

  print_result(sortResult);
}

sortresult_t quick_ascend_sort(int length, int array[], int startIndex, int endIndex)
{
  int compareCount = 0, swapCount = 0, swapIndex;
  int leftIndex = startIndex;
  int rightIndex = endIndex;
  bool rightFlag = false; // false: move left, true: move right

    if (startIndex >= endIndex ) {
    sortresult_t resultData = {
      .compareCount = 0,
      .swapCount = 0
      };
      return resultData;
  }

  while (leftIndex != rightIndex)
  {
    compareCount++;
    if (array[leftIndex] > array[rightIndex])
    {
      swapCount++;
      swap(array, leftIndex, rightIndex);
      rightFlag = !rightFlag;
    }
    leftIndex += !rightFlag;
    rightIndex -= rightFlag;
  }

  sortresult_t resultLeft ={
      .compareCount = 0,
      .swapCount = 0
      };
if (leftIndex != 0)
  resultLeft = quick_ascend_sort(length, array, startIndex, leftIndex - 1);

  sortresult_t resultRight = {
      .compareCount = 0,
      .swapCount = 0
      };
      if (rightIndex < length - 1)
  resultRight = quick_ascend_sort(length, array, rightIndex + 1, endIndex);

  compareCount += resultLeft.compareCount + resultRight.compareCount;
  swapCount += resultLeft.swapCount + resultRight.swapCount;

  sortresult_t resultData = {
      .compareCount = compareCount,
      .swapCount = swapCount};

  return resultData;
}

void run_quick_descend_sort(int length, int array[], int startIndex, int endIndex)
{
  sortresult_t sortResult = quick_descend_sort(length, array, startIndex, endIndex);

  print_result(sortResult);
}

sortresult_t quick_descend_sort(int length, int array[], int startIndex, int endIndex)
{
  int compareCount = 0, swapCount = 0, swapIndex;
  int leftIndex = startIndex;
  int rightIndex = endIndex;
  bool rightFlag = false; // false: move left, true: move right

    if (startIndex >= endIndex ) {
    sortresult_t resultData = {
      .compareCount = 0,
      .swapCount = 0
      };
      return resultData;
  }

  while (leftIndex != rightIndex)
  {
    compareCount++;
    if (array[leftIndex] < array[rightIndex])
    {
      swapCount++;
      swap(array, leftIndex, rightIndex);
      rightFlag = !rightFlag;
    }
    leftIndex += !rightFlag;
    rightIndex -= rightFlag;
  }

  sortresult_t resultLeft ={
      .compareCount = 0,
      .swapCount = 0
      };
if (leftIndex != 0)
  resultLeft = quick_descend_sort(length, array, startIndex, leftIndex - 1);

  sortresult_t resultRight = {
      .compareCount = 0,
      .swapCount = 0
      };
      if (rightIndex < length - 1)
  resultRight = quick_descend_sort(length, array, rightIndex + 1, endIndex);

  compareCount += resultLeft.compareCount + resultRight.compareCount;
  swapCount += resultLeft.swapCount + resultRight.swapCount;

  sortresult_t resultData = {
      .compareCount = compareCount,
      .swapCount = swapCount};

  return resultData;
}

/**
 * ランダム初期化(昇順)
 */
void ascend_randomize(int length, int array[], int startIndex, int endIndex)
{
  ascend_initialize(length, array);

  // int randomIndex;
  int random;
  int base = endIndex - startIndex;

  for (int i = startIndex; i < endIndex; i++)
  {
    // randomIndex = rand() % base + startIndex;
    // swap(array, i, randomIndex);
    random = rand() % base + startIndex;
    array[i] = random;
  }
}

/**
 * ランダム初期化(降順)
 */
void descend_randomize(int length, int array[], int startIndex, int endIndex)
{
  descend_initialize(length, array);

  // int randomIndex;
  int random;
  int base = endIndex - startIndex;

  for (int i = startIndex; i < endIndex; i++)
  {
    // randomIndex = rand() % base + startIndex;
    // swap(array, i, randomIndex);
    random = rand() % base + startIndex;
    array[i] = random;
  }
}

void ascend_initialize(int length, int array[])
{
  for (int i = 0; i < length; i++)
  {
    array[i] = i + 1;
  }
}

void descend_initialize(int length, int array[])
{
  for (int i = 0; i < length; i++)
  {
    array[i] = length - i;
  }
}

void swap(int array[], int indexA, int indexB)
{
  int temp;
  temp = array[indexA];
  array[indexA] = array[indexB];
  array[indexB] = temp;
}

void show_array(int length, int array[])
{
  printf("[");
  for (int i = 0; i < length; i++)
  {
    printf("%d, ", array[i]);
  }
  printf("]\n");
}

int get_digit(int num, int digit)
{
  int modded = num % (int)pow(10, digit + 1);
  return modded / (int)pow(10, digit);
}

void init_array(int array[], int length)
{
  for (int i = 0; i < length; i++)
  {
    array[i] = 0;
  }
}