#pragma once

#define MAX_WORD_SIZE 50

typedef struct MyList
{
  struct MyList* ptrToNext;
  char word[MAX_WORD_SIZE];
  int keyDigit;
}LST;

enum fails//список возможных возвращаемых значений ф-ции
{
  OK, NOT_ENOUGH_MEMORY, NULLPTR_STRING_ON_INPUT, MATCH_OF_KEY_NUMBERS, FILE_CANNOT_BE_OPENED
};

void AddElementToListTest_nullptrWord_expect_errcode_2(enum fails(*f)(LST**, int, const char*));

void AddElementToListTest_Sort(enum fails(*f)(LST**, int, const char*));

void AddElementToListTest_SameKeyCodes_expect_errcode_3(enum fails(*f)(LST**, int, const char*));

void AddElementToListTest_addingNewElement(enum fails(*f)(LST**, int, const char*));

void FindElementInListTest_notExistingElement_expect_0(int(*f)(const LST*, int));

void FindElementInListTest_existingElement_expect_1(int(*f)(const LST*, int));
