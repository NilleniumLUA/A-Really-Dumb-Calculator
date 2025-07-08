// author: nilleniumENT
// proj: calculator improved
// time took: 2h 1 min
// target os: win32/win64/win86

// target version of os: win10,win8,win11

// raw coded thing i made, learning C, second day!

// main libraries
#include <stdio.h>
#include <limits.h>

#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include <strings.h>
#include <errno.h>
#include <ctype.h>

// definitions
#define nil 0;
#define VERSION "0.0.1v";
#define lastupdated "7/8/2025";
#define projectName "Calculator Thing";

// struct typedefs
typedef struct
{
  char *LAST_UPDATED;
  char *SEGMENT_NAME;
  char *SEGMENT_VERSION;
  bool SUCCESS;
} segmentConstructionPathTypes;

typedef struct
{
  const char *RED;
  const char *YELLOW;
  const char *MAGENTA;
  const char *GREEN;
  const char *BLUE;
  const char *CYAN;
  const char *RESET;
} colorPath;

// constants
const colorPath colorPathNew = {
    .RED = "\x1b[1;31m",
    .GREEN = "\x1b[1;32m",
    .YELLOW = "\x1b[1;33m",
    .BLUE = "\x1b[1;34m",
    .MAGENTA = "\x1b[1;35m",
    .CYAN = "\x1b[1;36m",
    .RESET = "\x1b[0m"
};

const char *const userDictionary[] = {
    [1] = "Negate",
    [2] = "Add",
    [3] = "Divide",
    [4] = "Multiply",
    [5] = "Quit"
};

// funcs
// TODO: get actual info from .env file from our launch.json or either tasks.json 
// no todo do it from defs idiot!!!!!!!!!!!!!!!!!!!!!!!
segmentConstructionPathTypes loadsegmentConstructionPaths()
{
  segmentConstructionPathTypes segmentStructNew;

  segmentStructNew.SUCCESS = false;

  // temporary using defs due to my json being shit 
  segmentStructNew.LAST_UPDATED =  lastupdated // getenv("LASTUPDATED") ? getenv("LASTUPDATED") : "datafail";
  segmentStructNew.SEGMENT_NAME = projectName // getenv("NAME") ? getenv("NAME") : "datafail"
  segmentStructNew.SEGMENT_VERSION = VERSION  // getenv("VERSION") ? getenv("VERSION") : "datafail"

  segmentStructNew.SUCCESS = true;

  return segmentStructNew;
};

// build it so it looks beautiful on startup
// must include tasks.json or launch.json before getting this shit.
void loadconstructedPathPoint()
{
  segmentConstructionPathTypes constructionPath = loadsegmentConstructionPaths();

  if (!(constructionPath.SUCCESS == true))
  {
    printf("Failed to abbrevate and construct the console dir.");
  };

  printf("\n %s ===[ %s ]=== %s \n", colorPathNew.CYAN, constructionPath.SEGMENT_NAME, colorPathNew.RESET);
  printf("stable build version: %s \n", constructionPath.SEGMENT_VERSION);
  printf("last updated: %s %s %s \n", colorPathNew.YELLOW, constructionPath.LAST_UPDATED, colorPathNew.RESET);
};

// this function was implemented to actually colorcode patterns on user terminals that are on windows 10
// by user terminals i mean cmd and powershell
// TLDR; works on windows 11 and older platforms (not windows 7 or lower fuck them), just for translating ANSI colors to patterns that are visible
void useWindowsColorCodeAPI()
{
  HANDLE hOUT = GetStdHandle(STD_OUTPUT_HANDLE);

  DWORD DWMODE = 0;
  if (!GetConsoleMode(hOUT, &DWMODE))
  {
    printf("useWindowsColorCodeAPI() failed to batch GetConsoleMode to colorcode ANSI colored text");
    return;
  };

  DWMODE |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

  if (!SetConsoleMode(hOUT, DWMODE))
  {
    printf("useWindowsColorCodeAPI() failed to batch SetConsoleMode to colorcode ANSI colored text");
    return;
  };
};

void loadUsermenuOptions()
{
  loadconstructedPathPoint();
  printf("exhausting due to %s possible error checks... %s\n", colorPathNew.CYAN, colorPathNew.RESET);
  Sleep(750);

  printf("Options: \n");
  printf("[1]. Negate \n");
  printf("[2]. Add \n");
  printf("[3]. Divide \n");
  printf("[4]. Multiply \n");
  printf("[5]. Quit \n");
};

// to just check not breaking segfault limits and int limits which i think is int32 and -int32
// i barely use this 😱😰
bool segFaultCheckLimitNumber(int num, int num2)
{
  if (num > INT_MAX / num2 || num < INT_MIN / num2)
  {
    printf("value bypassed INT_MAX or INT_MIN. num, num2: %d, %d", num, num2);
    return nil;
  };

  return true;
}

int segFaultCheckThroughFgetsBuffer(int intPoint)
{
  // fgets() since scanf() is horrible asf
  // we're also garbage checking & compressing, removing seg. faults at any point of result
  char BYTE_BUFFER[64];

  if (fgets(BYTE_BUFFER, sizeof(BYTE_BUFFER), stdin) == NULL || BYTE_BUFFER[0] == '\n')
  {
    printf("Failed to concetate action, avoided prestarted segmentation fault. You tried to confuse the char limit. \n");
    return nil;
  };
  BYTE_BUFFER[strcspn(BYTE_BUFFER, "\n")] = '\0';

  if (BYTE_BUFFER == '\0')
  {
    printf("slot is empty");
    return nil;
  }

  int i = 0;
  errno = 0;

  char *endPointer;

  if (BYTE_BUFFER[0] == '-')
  {
    i = 1;
    if (BYTE_BUFFER == '\0')
    {
      printf("incorrect valid serial number detected in input. \n");
      return nil
    }
  }

  for (; BYTE_BUFFER[i] != '\0'; i++)
  {
    if (!isdigit(BYTE_BUFFER[i]))
    {
      printf("incorrect valid serial number detected in input. \n");
      return nil
    };
  }

  long internalValue = strtol(BYTE_BUFFER, &endPointer, 10);

  return (int)internalValue;
};

int multiply(int num, int num2)
{
  if (!(segFaultCheckLimitNumber(num, num2) == true))
  {
    return nil;
  }

  return num * num2;
};

int divide(int num, int num2)
{
  if (num == 0 || num2 == 0)
  {
    printf("Cannot divide 0 to any number! \n");
    return nil;
  };

  return num / num2;
};

int negate(int num, int num2)
{
  return num - num2;
};

int add(int num, int num2)
{
  return num + num2;
};

// main funcs
int main()
{

  int MainChoice;
  int NumberValue1, NumberValue2, RESULT;

  useWindowsColorCodeAPI();
  loadUsermenuOptions();

  // we just so happen to repeat this bcus if the user is still active we dont want to make the script sleep at just an exhaustion time or instant execution
  while (1)
  {
    int segValue = segFaultCheckThroughFgetsBuffer(MainChoice);

    if (!segValue)
    {
      printf("failed to process, segfaultcheck failed through buffer \n");
      break;
    };

    if (segValue == 5)
    {
      exit(0);
      break;
    }

    if (!userDictionary[segValue])
    {
      printf("Not found in the options tab.\n");
      break;
    }

    printf("Enter the first number: ");
    int segValue2 = segFaultCheckThroughFgetsBuffer(NumberValue1);

    if (!segValue2)
    {
      printf("failed to process, segfaultcheck failed through buffer \n");
      break;
    }

    printf("Enter the second number: ");
    int segValue3 = segFaultCheckThroughFgetsBuffer(NumberValue2);

    if (!segValue3)
    {
      printf("failed to process, segfaultcheck failed through buffer \n");
    };

    RESULT = 0;

    // hahaha lua doesn't have this 😋😂😂
    // switches are rlly gud
    switch (segValue)
    {
    case 1:
      RESULT = negate(segValue2, segValue3);
      break;
    case 2:
      RESULT = add(segValue2, segValue3);
      break;
    case 3:
      RESULT = divide(segValue2, segValue3);
      break;
    case 4:
      RESULT = multiply(segValue2, segValue3);
      break;
    case 5:
      exit(0);
      break;
    default:
      printf("value is unacceptable");
      break;
    };

    printf("ANSWER: %d", RESULT);
  };

  return 0;
}