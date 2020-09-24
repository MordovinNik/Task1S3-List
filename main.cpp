//21 variant

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 50

enum fails//список возможных возвращаемых значений ф-ции
{
  OK, NOT_ENOUGH_MEMORY, EMPTY_STRING_ON_INPUT, MATCH_OF_KEY_NUMBERS
};

typedef struct MyList
{
  struct MyList* ptrToNext;
  char word[MAX_WORD_SIZE];
  int keyDigit;
}LST;

LST* CreateElement(int keyDigit, const char* word)
{
  LST* element;

  element = malloc(sizeof(LST));

  if (element == NULL)
    return NULL;

  strcpy_s(element->word, MAX_WORD_SIZE, word);
  element->keyDigit = keyDigit;
  return element;
}

enum fails AddElementToList(LST** list, int keyDigit, const char* word)
{
  if (word == NULL)
    return EMPTY_STRING_ON_INPUT;

  //если список абсолютно пуст (создаем первый элемент и заполняем его)
  if ((*list) == NULL)
  {
    (*list) = CreateElement(keyDigit, word);

    if ((*list) == NULL)
      return NOT_ENOUGH_MEMORY;

    (*list)->ptrToNext = (*list);//конечный элемент указывает на себя
    return 0;
  }

  LST* currentElement = (*list),
    * previousElement = (*list),
    * newElement;
  //поиск места для нового элемента
  while (currentElement->ptrToNext != currentElement && currentElement->keyDigit < keyDigit)
  {
    previousElement = currentElement;
    currentElement = currentElement->ptrToNext;
  }

  if (currentElement->keyDigit == keyDigit)
    return MATCH_OF_KEY_NUMBERS;

  newElement = CreateElement(keyDigit, word);

  if (newElement == NULL)
    return NOT_ENOUGH_MEMORY;

  //ключ нового элемента меньше чем у текущего, вставляем новый элемент перед текущим
  if (currentElement->keyDigit > newElement->keyDigit)
  {
    newElement->ptrToNext = currentElement;

    if (currentElement == (*list))//текущий элемент - начальный
      (*list) = newElement;
    else
      previousElement->ptrToNext = newElement;
  }
  //вставляем новый элемент в конец, если его ключ самый большой
  else
  {
    newElement->ptrToNext = newElement;
    currentElement->ptrToNext = newElement;
  }

  return 0;
}

int FindElementInList(const LST* list, int keyDigit)
{
  const LST* temp = list;

  while (temp->ptrToNext != temp && temp->keyDigit < keyDigit)
  {
    temp = temp->ptrToNext;
  }

  return temp->keyDigit == keyDigit;
}

void DeleteList(LST* list)
{
  LST* temp,
    * next = list;
  do
  {
    temp = next;
    next = temp->ptrToNext;
    free(temp);
  } while (temp != next);
}

void PrintList(const LST* list)
{
  LST* temp,
    * next = list;

  do
  {
    temp = next;
    next = temp->ptrToNext;
    printf("%s   %d\n", temp->word, temp->keyDigit);

  } while (temp->ptrToNext != temp);
}

int main()
{
  LST* list = NULL;
  FILE* inputFile = NULL;
  char inputFileName[261] = "D:\\folders\\Desktop\\123.txt",//путь к файлу с входными данными
    word[MAX_WORD_SIZE + 1];
  int keyDigit = 0, err;

  //Открываем файл
  fopen_s(&inputFile, inputFileName, "r");
  if (!inputFile)
  {
    printf("The file cannot be opened!");
    return -1;
  }

  //чтение из файла в список
  while (1)
  {
    if (fscanf_s(inputFile, "%s", word, MAX_WORD_SIZE) == EOF ||
      fscanf_s(inputFile, "%d", &keyDigit) == EOF)
      break;

    err = AddElementToList(&list, keyDigit, word);

    //вывод ошибки на экран (если есть) и завершение программы
    if (err)
    {
      switch (err)
      {
      case NOT_ENOUGH_MEMORY:
        printf("Not enough memory!");
        break;
      case EMPTY_STRING_ON_INPUT:
        printf("Wrong input format!");
      case MATCH_OF_KEY_NUMBERS:
        printf("This key number already exists!");
      }
      return -1;
    }
  }
  int key = 3;
  printf("there %s element with keycode %d in the list\n", FindElementInList(list, key) ? "is an" : "is not", key);
  PrintList(list);
  DeleteList(list);
  system("pause");
}
