//
//  main.c
//  Project1-CS173
//
//  Created by Victor A on 9/20/18.
//  Copyright © 2018 Victor A. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"
#include "nfa.h"
#include "cDFA.h"
#include "IntHashSet.h"


DFA return_abc(void);
DFA return_xyz(void);

DFA return_xyz(){
    DFA test = new_DFA(4);
    
    
    DFA_set_transition_all(test,0,-1);
    DFA_set_transition_all(test,1,-1);
    DFA_set_transition_all(test,2,-1);
    DFA_set_transition_all(test,3,-1);
    
    DFA_set_transition(test, 0, 'z', 1);
    DFA_set_transition(test, 1, 'x', 2);
    DFA_set_transition(test, 2, 'y', 3);
    
     DFA_set_accepting(test, 3, true);
    
    return test;
}

DFA return_abc(){
      DFA test = new_DFA(4);
    
    DFA_set_transition_all(test, 0, -1);
    DFA_set_transition_all(test, 1, -1);
    DFA_set_transition_all(test, 2, -1);
    DFA_set_transition_all(test, 3, 3);
    
    DFA_set_transition(test, 0, 'a', 1);
    DFA_set_transition(test, 1, 'b', 2);
    DFA_set_transition(test, 2, 'c', 3);
    
    DFA_set_accepting(test, 3, true);
    
    return test;
}

DFA return_odd_0s(void);

DFA return_odd_0s(){
    
     DFA test = new_DFA(2);
    
    DFA_set_transition_all(test, 0, -1);
    DFA_set_transition_all(test, 1, -1);
    
    DFA_set_transition(test, 0, '1', 0);
    DFA_set_transition(test, 1, '1', 1);
    DFA_set_transition(test, 0, '0', 1);
    DFA_set_transition(test, 1, '0', 0);
    
    DFA_set_accepting(test, 1, true);
    
    return test;
}

DFA return_odd_0s_1s(void);

DFA return_odd_0s_1s(){
    DFA test = new_DFA(4);
    
    DFA_set_transition_all(test, 0, -1);
    DFA_set_transition_all(test, 1, -1);
    
     DFA_set_transition(test, 0, '1', 1);
     DFA_set_transition(test, 0, '0', 2);
     DFA_set_transition(test, 1, '1', 0);
     DFA_set_transition(test, 1, '0', 3);
     DFA_set_transition(test, 2, '1', 3);
     DFA_set_transition(test, 2, '0', 0);
     DFA_set_transition(test, 3, '1', 2);
     DFA_set_transition(test, 3, '0', 1);
    
    DFA_set_accepting(test, 3, true);
   
    
    return test;
}

DFA return_float(void);

DFA return_float(){
    
     DFA test = new_DFA(3);
    
    DFA_set_transition_all(test, 0, -1);
    DFA_set_transition_all(test, 1, -1);
    DFA_set_transition_all(test, 2, -1);
    
    
    DFA_set_transition_str(test, 0, "0123456789", 0);
    DFA_set_transition(test, 0, '.', 1);
    DFA_set_transition_str(test, 1, "0123456789", 2);
    DFA_set_transition_str(test, 2, "0123456789", 2);
    
    
    
    DFA_set_accepting(test, 2, true);
    
    return test;
    
}

NFA return_car_end(void);

NFA return_car_end(){
    NFA trial = new_NFA(4);
    NFA_add_transition_all(trial, 0, 0);
    NFA_add_transition(trial, 0, 'c', 1);
    NFA_add_transition(trial, 1, 'a', 2);
    NFA_add_transition(trial, 2, 'r', 3);
    
    NFA_set_accepting(trial, 3, 1);
    return trial;
}

NFA return_car_contain(void);

NFA return_car_contain(){
    NFA trial = new_NFA(4);
    NFA_add_transition_all(trial, 0, 0);
    
    
    NFA_add_transition(trial, 0, 'c', 1);
    NFA_add_transition(trial, 1, 'a', 2);
    NFA_add_transition(trial, 2, 'r', 3);
    
    NFA_add_transition_all(trial, 3, 3);
    
    NFA_set_accepting(trial, 3, 1);
    return trial;
}

NFA return_number(void);

NFA return_number(){
    NFA trial = new_NFA(3);
    

    NFA_add_transition_str(trial, 0, "0123456789", 0);
    NFA_add_transition_str(trial, 0, "0123456789", 1);
    NFA_add_transition_str(trial, 1, "0123456789", 1);
    NFA_add_transition_str(trial, 1, ".", 2);
    NFA_add_transition_str(trial, 2, "0123456789", 2);
    
    NFA_set_accepting(trial, 1, 1);
    NFA_set_accepting(trial, 2, 1);

    
    return trial;
}


NFA return_anagram(void);

NFA return_anagram(){
    NFA trial = new_NFA(19);
    
    NFA_add_transition_all(trial, 0, 0);
    
    
    NFA_add_transition(trial, 0, 'a', 1);
    NFA_add_transition_all(trial, 1, 1);
    trial -> transition_table[1][(int)'a'][1] = 0;
    NFA_add_transition(trial, 1, 'a', 2);
    
    NFA_add_transition(trial, 0, 'g', 3);
    NFA_add_transition_all(trial, 3, 3);
    trial -> transition_table[3][(int)'g'][3] = 0;
    NFA_add_transition(trial, 3, 'g', 4);
    
    NFA_add_transition(trial, 0, 'h', 5);
    NFA_add_transition_all(trial, 5, 5);
    trial -> transition_table[5][(int)'h'][5] = 0;
    NFA_add_transition(trial, 5, 'h', 6);
    
    NFA_add_transition(trial, 0, 'i', 7);
    NFA_add_transition_all(trial, 7, 7);
    trial -> transition_table[7][(int)'i'][7] = 0;
    NFA_add_transition(trial, 7, 'i', 8);
    
    NFA_add_transition(trial, 0, 'n', 9);
    NFA_add_transition_all(trial, 9, 9);
    trial -> transition_table[9][(int)'n'][9] = 0;
    NFA_add_transition(trial, 9, 'n', 10);
    NFA_add_transition_all(trial, 10, 10);
    trial -> transition_table[10][(int)'n'][10] = 0;
    NFA_add_transition(trial, 10, 'n', 11);
    
    NFA_add_transition(trial, 0, 'o', 12);
    NFA_add_transition_all(trial, 12, 12);
    trial -> transition_table[12][(int)'o'][12] = 0;
    NFA_add_transition(trial, 12, 'o', 13);
    
    NFA_add_transition(trial, 0, 's', 14);
    NFA_add_transition_all(trial, 14, 14);
    trial -> transition_table[14][(int)'s'][14] = 0;
    NFA_add_transition(trial, 14, 's', 15);
    
    NFA_add_transition(trial, 0, 't', 16);
    NFA_add_transition_all(trial, 16, 16);
    trial -> transition_table[16][(int)'t'][16] = 0;
    NFA_add_transition(trial, 16, 't', 17);
    
    NFA_add_transition(trial, 0, 'w', 18);
    NFA_add_transition_all(trial, 18, 18);
    trial -> transition_table[18][(int)'w'][18] = 0;
    NFA_add_transition(trial, 18, 'w', 19);
    
    
    
    NFA_set_accepting(trial, 2, 1);
    NFA_set_accepting(trial, 4, 1);
    NFA_set_accepting(trial, 8, 1);
    NFA_set_accepting(trial, 6, 1);
    NFA_set_accepting(trial, 11, 1);
    NFA_set_accepting(trial, 15, 1);
    NFA_set_accepting(trial, 13, 1);
    NFA_set_accepting(trial, 17, 1);
    NFA_set_accepting(trial, 19, 1);
    
    return trial;
}

void DFA_tester(DFA dfa, char* tester);

void DFA_tester(DFA dfa, char* tester){
    
    printf("Now Testing: DFA that %s \n", tester);
    printf("enter + to continue to next DFA \n");
    
    
    char* input = (char*) malloc(127*sizeof(char));
    
    printf("enter a string\n");
    scanf("%s", input);
    
    while (input[0] != '+') {
        if (DFA_execute(dfa, input) == true){
            printf("\n %s is a valid input --> DFA accepts", input);
        } else {
            printf("\n %s is an invalid input --> DFA does not accept", input);
        }
        printf("\n enter a string \n");
        scanf("%s", input);
    }
    
    
    free(dfa);
    
}

void NFA_tester(NFA nfa, char* tester);
void NFA_tester(NFA nfa, char* tester){
    
    printf("Now Testing: NFA that %s \n", tester);
    printf("enter + to continue to next NFA \n");

    
    char* input = (char*) malloc(127*sizeof(char));
    
    printf("enter a string \n");
    scanf("%s", input);
    
    while (input[0] != '+') {
        reset_current_states(nfa);
        if (NFA_execute(nfa, input) == true){
            printf("\n %s is a valid input --> NFA accepts", input);
        } else {
            printf("\n %s is an invalid input --> NFA does not accept", input);
        }
        printf("\n enter a string \n");
        scanf("%s", input);
    }
    
    free(nfa);
}

void cDFA_tester(NFA nfa, char* tester);
void cDFA_tester(NFA nfa, char* tester) {
    
    printf("Now Testing: NFA converted into DFA that %s \n", tester);
    printf("enter + to continue to next DFA \n");
    

    cDFA converted = NFA_to_DFA(nfa);
    
    printf("NFA has been converted into DFA and has %d reachable states \n", cDFA_get_size(converted));
    
    char* input = (char*) malloc(127*sizeof(char));
    
    printf("enter a string \n");
    scanf("%s", input);
    
    while (input[0] != '+') {
        if (cDFA_execute(converted, input) == true){
            printf("\n %s is a valid input --> DFA accepts", input);
        } else {
            printf("\n %s is an invalid input --> DFA does not accept", input);
        }
        printf("\n enter a string \n");
        scanf("%s", input);
    }
    
    free(converted);
    free(nfa);
    
}


int main(int argc, const char * argv[]) {
    
     char* tester = (char*) malloc(127*sizeof(char));
   
    tester = "accepts exactly the string zxy";
    DFA_tester(return_xyz(), tester);
    tester = "accepts any string which starts with abc";
    DFA_tester(return_abc(), tester);
    tester = "accepts binary input with an odd number of 0’s";
    DFA_tester(return_odd_0s(), tester);
    tester = "accepts binary input with an odd number of both 0’s and 1’s";
    DFA_tester(return_odd_0s_1s(), tester);
    tester = "accepts floating point number";
    DFA_tester(return_float(), tester);
    tester = "accepts strings ending in car";
    NFA_tester(return_car_end(), tester);
    tester = "accepts strings containing car";
    NFA_tester(return_car_contain(), tester);
    tester = "rejects partial anagrams of washington";
    NFA_tester(return_anagram(), tester);
    tester = "accepts any numeric input including floats";
    NFA_tester(return_number(), tester);
    tester = "accepts strings ending in car";
    cDFA_tester(return_car_end(), tester);
    tester = "accepts strings containing car";
    cDFA_tester(return_car_contain(), tester);
    //tester = "rejects partial anagrams of washington";
    //cDFA_tester(return_anagram(), tester);
    return 0;
    
}


//MAKE ARRAY OF ARRAYS OF ARRAYS FOR






