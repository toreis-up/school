#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
  char name;
  struct node *nodes[26]; // child nodes
  bool hasNodeFlags[26];  // hasNode?
  int hasCount;           // number of nodes that have
} node_t;

node_t *rootNode = NULL;

void RunTrieService(void);
void AddWordToTrie(char *string);
node_t *CreateNewNode(char ch);
void InitializeTree();
bool hasNode(node_t *node, char ch);
void AddNode(node_t *parentNode, char ch);
int length(char *str);
void DisplayTree();
int DisplayNode(node_t *node, int depth);
void printSpace(int count);

/**
 * test module
*/

void Test(void) {
  AddWordToTrie("kisarazu");
  AddWordToTrie("kaizen");
  AddWordToTrie("kimitsu");
  AddWordToTrie("kimisarazu");
  AddWordToTrie("kosen");
  DisplayTree();
}

int main(void)
{
  InitializeTree();
  RunTrieService();
}

void InitializeTree()
{
  node_t *newNode = CreateNewNode('@');
  rootNode = newNode;
}

void RunTrieService(void)
{
  char string[100];
  char mode, wantContinue, dummy;
  do
  {
    printf("What do you want? (A: Add word, D: Display Tree) : ");
    scanf("%c%c", &mode, &dummy);
    switch (mode)
    {
      case 'A':
      case 'a':
        printf("Word: ");
        scanf("%s%c", string, &dummy);
        AddWordToTrie(string);
        break;

      case 'D':
      case 'd':
        DisplayTree();
        break;

      case 'T':
        Test();
        break;

      default:
        break;
    }

    printf("continue? (y/N): ");
    scanf("%c%c", &wantContinue, &dummy);
  } while (wantContinue == 'y');
}

void AddWordToTrie(char *string)
{
  int len = length(string);
  int addedIndex = 0;
  node_t *currentNode = rootNode;
  char addedString[len];
  for (int idx = 0; idx < len; idx++)
  {
    addedString[idx] = 0;
  }

  for (int ci = 0; ci < len; ci++)
  {
    if (!hasNode(currentNode, string[ci]))
    {
      AddNode(currentNode, string[ci]);
      currentNode->hasCount += 1;
      printf("Added ch: %c\n", string[ci]);
      addedString[addedIndex] = string[ci];
      addedIndex += 1;
    }
    currentNode = currentNode->nodes[string[ci] - 'a'];
  }

  printf("Added: %s\n", addedString);
}

/**
 * @details nameをchで初期化した空っぽのノードを作って返す
 * @param ch ノードの名前
 */
node_t *CreateNewNode(char ch)
{
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  bool _hasNodeFlags[26] = {false};
  *newNode->hasNodeFlags = *(_hasNodeFlags);
  *newNode->nodes = (node_t *)malloc(sizeof(node_t) * 26);
  newNode->hasCount = 0;
  newNode->name = ch;

  return newNode;
}

/**
 * Nodeがあるかを返す
 * @param node 検索するNode
 * @param ch 探す文字
 * @return true ある
 * @return false ない
 */
bool hasNode(node_t *node, char ch)
{
  return node->hasNodeFlags[ch - 'a'];
}

/**
 * Nodeを追加する
 * @param parentNode 親ノード
 * @param ch 追加する子ノード用の情報
 */
void AddNode(node_t *parentNode, char ch)
{
  node_t *newNode = CreateNewNode(ch);
  parentNode->hasNodeFlags[ch - 'a'] = true;
  parentNode->nodes[ch - 'a'] = newNode;
}

int length(char *str)
{
  int c = 0;
  while (true)
  {
    if (str[c] == '\0')
    {
      break;
    }
    c++;
  }
  return c;
}

void DisplayTree()
{
  if (rootNode == NULL)
  {
    printf("Data is not found.\n");
    return;
  }
  else
  {
    DisplayNode(rootNode, /* depth = */ 0);
  }
}

int DisplayNode(node_t *node, int depth)
{
  // 設計方針: 行きがけ順で順々に表示する
  // depthは文字揃え
  int _depth = depth;
  int lineCount = 0;

  if (node != rootNode)
    printf("%c ", node->name);

  if (node->hasCount == 0) { // 末端
    printf("\n");
    return 0;
  }

  for (int idx = 0; idx < 26; idx++)
  {
    if (node->hasNodeFlags[idx]) {
      if (lineCount >= 1) {
        printSpace(depth);
        printf("└ ");
      }
      lineCount++;
      DisplayNode(node->nodes[idx], _depth + 1);
    }
  }
  return 0;
}

void printSpace(int count)
{
  for (int i = 0; i < count; i++) {
    printf("  ");
  }
}