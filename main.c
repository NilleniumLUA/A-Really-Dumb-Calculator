#include <stdio.h>
#include <limits.h> // using INT_MAX and INT_MIN to not abuse the calculator

int main() {
    int mathnum;
    int mathnum2;
    
    char arraypoint; // no fgets() pls
    
    printf("Enter the first number:");
    
    // anti segmentation fault #1
    if (scanf("%d", &mathnum) != 1) {
        printf("Invalid type should be a integer. Almost caused a segmentation fault.");
        
        return 0;
    }
    
    printf("Enter the second number:");
    
    // anti segmentation fault #2
    if (scanf("%d", &mathnum2) != 1) {
        printf("Invalid type should be a integer. Almost caused a segmentation fault.");
        
        return 0;
    }
    
    
    // build up guardian security over integrer overloads, avoid buffer loads
    if (mathnum >= INT_MAX || mathnum2 >= INT_MAX) {
        printf("You are over the limit on calculating the main value! Max Integrer based value (int32): %d", INT_MAX);
        
        return 0;
    }
    else if (mathnum <= INT_MIN || mathnum2 <= INT_MIN) {
        printf("You are under the limit on calculating the negative main value, Minimum Integrer based value (int32): -%d", INT_MIN);
        
        return 0;
    }
    
    
    
    printf("Enter the action you want to do with the both numbers, valid are *, -, +, / : ");
    
    // more bolster security
    // ... bull shit. C is so hard to come up with when you have no length detectors or typedef. segfault is expected here due to this thing only detecting ONE single character
    // no FGETS no party ahhhh...
    if (scanf(" %c", &arraypoint) != 1) {
        printf("Faulty point action detected. Required type: char [valid act points: *, -, +, /]");
        
        return 0;
    }
    
    
    
    // disabling authority over dividing nil to nil
    if ((mathnum == 0 || mathnum2 == 0) && (arraypoint == '/')) {
        printf("Tried to divide nil");
        return 0;
    };
    
    
    
    switch (arraypoint) {
        case '*':
          // also disabling authority to multiply to the max point of the number
          // test 1: multiplying -348519 * -3434 resulted into 1196814246, way above the max int32 var
          if (mathnum > INT_MAX / mathnum2 || mathnum > INT_MIN / mathnum2) {
              printf("Overloading the calculator project is not a good idea dude.");
              break;
          }
          printf("ANSWER: %d", mathnum * mathnum2);
          break;
        case '-':
          printf("ANSWER: %d", mathnum - mathnum2);
          break;
        case '/':
          printf("ANSWER: %d", mathnum / mathnum2);
          break;
        case '+':
          printf("ANSWER: %d", mathnum + mathnum2);
          break;
        default: 
          printf("unknown value given, value was given: %s", arraypoint);
          break;
    }



    return 0;
}
