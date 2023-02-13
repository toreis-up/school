#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

const int WORD_COUNT = 6;

void radix_ascend_sort(char** array, int wordCount, int radix, int position);
void init_array(int array[], int length);
int suffix(char str[], int pos);
int computeMax(char **dict, int count);

int main(void) {
  char **dict = (char **)malloc(sizeof(char *) * WORD_COUNT /* as wordCount */);
  dict[0] = "the";
  dict[1] = "five";
  dict[2] = "boxing";
  dict[3] = "wizards";
  dict[4] = "jump";
  dict[5] = "quickly";

  int maxLen = computeMax(dict, WORD_COUNT);

  for (int i = 0; i < maxLen; i++) {
    radix_ascend_sort(dict, WORD_COUNT, 'z' - 'a' + 1, i + 1);
    for (int j = 0; j < WORD_COUNT; j++) {
    printf("%s ", dict[j]);
  }
  printf("\n");
  }
}

int computeMax(char **dict, int count) {
  int res = 0;
  for (int i = 0; i < count; i++) {
    if (res < strlen(dict[i])) {
      res = strlen(dict[i]);
    }
  }

  return res;
}

/**
 * @param array 配列
 * @param wordCount 配列に含む単語の数
 * @param radix 基数
 * @param position どのindexを見て操作するか
*/
void radix_ascend_sort(char** array, int wordCount, int radix, int position) {
  int counts[radix + 1]; // 'a' : 1 / NULL : 0
  init_array(counts, radix + 1);

  char **new = (char **)malloc(sizeof(char *) * wordCount);

  for (int i = 0; i < wordCount; i++) {
    int idx = suffix(array[i], position);
    counts[idx]++;
  }

  for (int i = 1; i < radix + 1; i++) {
    counts[i] += counts[i-1];
  }

  for (int i = wordCount - 1; i >= 0; i--) {
    int idx = suffix(array[i], position); // 後ろからとってくる
    new[counts[idx] - 1] = array[i];
    counts[idx]--;
  }

  for (int i = 0; i < wordCount; i++) {
    array[i] = new[i];
  }
}

int suffix(char str[], int pos) {
  if (strlen(str) < pos) return suffix(str, pos -1);
  int idx = str[strlen(str) - pos];
  return idx % 'a' + idx / 'a';
}

void init_array(int array[], int length)
{
  for (int i = 0; i < length; i++)
  {
    array[i] = 0;
  }
}
