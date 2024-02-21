#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Define ProductionRule structure
typedef struct {
    char head;
    char** body;
    int num_productions;
} ProductionRule;

// Define CFG structure
typedef struct {
    ProductionRule* rules;
    char* terminals;
    char startSymbol;
    int num_rules;
    int num_terminals;
} CFG;

// Function to initialize a CFG object
void initializeCFG(CFG* grammar) {
    grammar->rules = (ProductionRule*)malloc(2 * sizeof(ProductionRule));
    grammar->num_rules = 2;

    grammar->rules[0].head = 'S';
    grammar->rules[0].body = (char**)malloc(8 * sizeof(char*));
    grammar->rules[0].num_productions = 8;
    grammar->rules[0].body[0] = strdup("aSa");
    grammar->rules[0].body[1] = strdup("bSb");
    grammar->rules[0].body[2] = strdup("cSc");
    grammar->rules[0].body[3] = strdup("dSd");
    grammar->rules[0].body[4] = strdup("a");
    grammar->rules[0].body[5] = strdup("b");
    grammar->rules[0].body[6] = strdup("c");
    grammar->rules[0].body[7] = strdup("d");

    grammar->rules[1].head = 'V';
    grammar->rules[1].body = (char**)malloc(8 * sizeof(char*));
    grammar->rules[1].num_productions = 8;
    grammar->rules[1].body[0] = strdup("aSa");
    grammar->rules[1].body[1] = strdup("bSb");
    grammar->rules[1].body[2] = strdup("cSc");
    grammar->rules[1].body[3] = strdup("dSd");
    grammar->rules[1].body[4] = strdup("a");
    grammar->rules[1].body[5] = strdup("b");
    grammar->rules[1].body[6] = strdup("c");
    grammar->rules[1].body[7] = strdup("d");

    grammar->terminals = (char*)malloc(4 * sizeof(char));
    grammar->terminals[0] = 'a';
    grammar->terminals[1] = 'b';
    grammar->terminals[2] = 'c';
    grammar->terminals[3] = 'd';

    grammar->num_terminals = 4;
    grammar->startSymbol = 'S';
}

ProductionRule* findRule(CFG* grammar, char symbol) {
  for (int i = 0; i < grammar->num_rules; i++) {
    if (grammar->rules[i].head == symbol) {
      return &(grammar->rules[i]);
    }
  }
  return NULL;
}

char* getRandomElement(char** ruleBody, int array_size) {
  int randomIndex = rand() % array_size;

  return ruleBody[randomIndex];
}


bool checkForSymbol(CFG* grammar, char symbol) {
  for (int i = 0; i < grammar->num_terminals; i++) {
    if (grammar->terminals[i] == symbol) {
      return true;
    }
  }
  return false;
}


char* generatePalindrome(CFG* grammar, char symbol, int mallocSize) {
    if (checkForSymbol(grammar, symbol)) {
        char* returnSymbol = (char*)malloc(2 * sizeof(char)); // Allocate memory for symbol and null terminator
        returnSymbol[0] = symbol;
        returnSymbol[1] = '\0'; // Null terminator
        return returnSymbol;
    }

    ProductionRule* rule = findRule(grammar, symbol);
    char* randomProduction = getRandomElement(rule->body, rule->num_productions);
    //printf("%s\tran\n", randomProduction);
    char* generatedString = (char*)malloc(sizeof(char) * mallocSize); // Allocate memory for generated string
    generatedString[0] = '\0'; // Initialize with null terminator

    for (int i = 0; i < strlen(randomProduction); i++) {
        char* subGeneratedString = generatePalindrome(grammar, randomProduction[i], mallocSize);
        //printf("Random Production Element: %c\n", randomProduction[i]);
        strcat(generatedString, subGeneratedString);
        //printf("Generated String: %s\n", generatedString);
        free(subGeneratedString); // Free memory allocated for subGeneratedString
    }

    return generatedString;
}

char* substring(const char* string, int start, int end) {
  int length = end - start + 1;
  char *sub = (char*)malloc(length + 1);
  if (sub == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  strncpy(sub, string + start, length);
  sub[length] = '\0';
  return sub;
}

bool checkString(CFG* grammar, char* string) {
  if (strlen(string) == 1) {
    return checkForSymbol(grammar, string[0]);
  }
  if (strlen(string) == 0) {
    return true;
  }
  char first = string[0];
  char last = string[strlen(string) - 1];
  if (first != last) {
    return false;
  }

  for (int i = 0; i < grammar->num_rules; i++) {
    for (int j = 0; j < grammar->rules[i].num_productions; j++) {
      char* singleProd = grammar->rules[i].body[j];
      if (singleProd[0] == first && singleProd[strlen(singleProd) - 1] == last) {
        return checkString(grammar, substring(string, 1, strlen(string) - 2));
      }
    }
  }
  return false;

}



void testParser(CFG* grammar, int numTests) {
  printf("Testing Parser with Random Palindrome: \n");
  for (int i = 1; i < numTests + 1; i++) {
    char* testPalindrome = generatePalindrome(grammar, grammar->startSymbol, 1000);
    printf("Test %i: Palindrome - %s\n", i, testPalindrome);
    if (checkString(grammar, testPalindrome)) {
      printf("  Parser Result: Valid \n");
    } else {
      printf("  Parser Result: Invalid \n");
    }
  }
}




int main() {
    time_t t;
    srand((unsigned) time(&t));
    // Create a CFG object
    CFG grammar;
    initializeCFG(&grammar);
    char* userInput = (char*)malloc(1000);
    userInput[0] = '\0';

    ProductionRule* rule = findRule(&grammar, 'S');

    char* pa = generatePalindrome(&grammar, 'S', 1000);

    printf("Random Palindrome: %s\n", pa);

    testParser(&grammar, 5);

    printf("Enter a string to test if is a palindrome: ");
    scanf("%s", userInput);

    if (checkString(&grammar, userInput)) {
      printf("The string is generated by the CFG.\n");
    } else {
      printf("The string is not generated by the CFG.\n");
    }
    
    return 0;
}
