#include "mainTests.h"
#include <crtdbg.h>
#include <string.h>
void AddElementToListTest_nullptrWord_expect_errcode_2(enum fails(*f)(LST**, int, const char*))
{
  LST* list = NULL;
  int err;

  err = f(&list, 1, NULL);
  _ASSERT(err == NULLPTR_STRING_ON_INPUT);
}

void AddElementToListTest_Sort(enum fails(*f)(LST**, int, const char*))
{
  LST* list = NULL;

  f(&list, 4, "4");
  f(&list, 2, "2");
  f(&list, 3, "3");

  _ASSERT(list->keyDigit < list->ptrToNext->keyDigit);
  _ASSERT(list->ptrToNext->keyDigit < list->ptrToNext->ptrToNext->keyDigit);
}

void AddElementToListTest_SameKeyCodes_expect_errcode_3(enum fails(*f)(LST**, int, const char*))
{
  LST* list = NULL;
  int err;

  f(&list, 1, "1");
  err = f(&list, 1, "2");

  _ASSERT(err == MATCH_OF_KEY_NUMBERS);
}

void AddElementToListTest_addingNewElement(enum fails(*f)(LST**, int, const char*))
{
  LST* list = NULL;
  f(&list, 10, "word");
  _ASSERT(list->keyDigit == 10);
  _ASSERT(!strcmp(list->word, "word"));
}

void FindElementInListTest_notExistingElement_expect_0(int(*f)(const LST*, int))
{
  LST list,list2;
  int output;
  list.keyDigit = 1;
  list.word[0] = 0;
  list.ptrToNext = &list2;
  list2.keyDigit = 2;
  list2.word[0] = 0;
  list2.ptrToNext = &list2;
  output = f(&list, 3);
  _ASSERT(output == 0);
}

void FindElementInListTest_existingElement_expect_1(int(*f)(const LST*, int))
{
  LST list, list2;
  int output;
  list.keyDigit = 1;
  list.word[0] = 0;
  list.ptrToNext = &list2;
  list2.keyDigit = 2;
  list2.word[0] = 0;
  list2.ptrToNext = &list2;
  output = f(&list, 2);
  _ASSERT(output == 1);
  output = f(&list, 1);
  _ASSERT(output == 1);
}