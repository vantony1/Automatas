//
//  cDFA.c
//  Project1-CS173
//
//  Created by Victor A on 9/22/18.
//  Copyright © 2018 Victor A. All rights reserved.
//

#include "cDFA.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"
#include "nfa.h"


typedef struct cDFA *cDFA;

/*struct cDFA {
    int states;
    int a_index;
    IntHashSet current_state;
    IntHashSet *accepting_state;
    IntHashSet **transition_table;
    //x is row, y is column
};*/

cDFA new_cDFA(int nstates) {
    cDFA this = (cDFA)malloc(sizeof(struct cDFA));
    this -> states = 2<<nstates;
    IntHashSet **table;
    int *acceptance;
    this -> a_index = 0;
    
    acceptance = (int*) malloc(this->states*sizeof(int));
    
    table = (IntHashSet**) malloc(this->states*sizeof(IntHashSet *));
    
    for(int i = 0; i < 2<<nstates; i++){
        table[i] = calloc(129, sizeof(IntHashSet));
    }
    
    for(int i = 0; i < nstates; i++){
        IntHashSet current = new_IntHashSet(1);
        IntHashSet_insert(current, i);
        table[i][0] = current;
    }
    
    for(int i = nstates; i < 2<<nstates; i++){
        IntHashSet current = NULL;
        table[i][0] = current;
    }
    
    IntHashSet current = new_IntHashSet(1);
    IntHashSet_insert(current, 0);
    

    
    this -> transition_table = table;
    this -> accepting_state = acceptance;
    this -> current_state = current;
    
    //MEMORY ALLOCATION FOR TRANSITION TABLE
    return this;
}


int cDFA_get_size(cDFA current) {
    
    int size = 0;
    for (int i = 0; i < current -> states; i++) {
        if(current -> transition_table [i][0] != NULL){
            size ++;
        }
    }
    
    return size;
}

void cDFA_free(cDFA current){
    
    for(int i = 0; i < current -> states; i++){
        for (int j = 0; j < 129; j++) {
            IntHashSet_free(current ->transition_table[i][j]);
        }
    }
    
    free(current -> transition_table);
    free(current -> accepting_state);
    IntHashSet_free(current -> current_state);
    free(current);
}

int find_state_index(IntHashSet src, cDFA dfa){
    for(int i = 0; i < dfa -> states; i++){
      //  printf("comparing: \n");
        //IntHashSet_print(src);
        //IntHashSet_print(dfa -> transition_table[i][0]);
        if(dfa -> transition_table[i][0] != NULL && IntHashSet_equals(src, dfa -> transition_table[i][0])){
            return i;
        }
    }
    
    return -1;
}

void cDFA_set_transition (cDFA dfa, IntHashSet src, char sym, IntHashSet dst){
    
    int input = (int) sym + 1;
    
    int src_index = find_state_index(src, dfa);
    
    dfa -> transition_table[src_index][input] = dst;
    
}

IntHashSet cDFA_get_transition(cDFA dfa, IntHashSet src, char sym){
   // printf("\n accessing state = %d \n", find_state_index(src, dfa));
    return dfa -> transition_table[find_state_index(src, dfa)][(int)sym];
}

void cDFA_set_transition_str(cDFA dfa, IntHashSet src, char *str, IntHashSet dst){
    for(int i = 0; str[i] != '\0'; i++){
        cDFA_set_transition (dfa, src, str[i],dst);
    }
}

void cDFA_set_transition_all(cDFA dfa, IntHashSet src, IntHashSet dst){
    for(int i = 0; i < 128; i++){
        cDFA_set_transition (dfa, src, (char) i,dst);
    }
}

void cDFA_set_accepting(cDFA dfa, int state){
    dfa -> accepting_state[dfa -> a_index] = state;
    dfa -> a_index = dfa -> a_index + 1;
}

bool cDFA_get_accepting(cDFA dfa, IntHashSet state){
    
    IntHashSetIterator state_iterator = IntHashSet_iterator(state);
    
    while(IntHashSetIterator_hasNext(state_iterator)){
        int check_state = IntHashSetIterator_next(state_iterator);
        
        for (int m = 0; m < dfa -> a_index; m++) {
            if(dfa -> accepting_state[m] == check_state){
                return true;
            }
        }
        
    }
        return false;
}

bool cDFA_execute(cDFA dfa, char *input){
    IntHashSet current_state = new_IntHashSet(dfa -> states);
    IntHashSet_insert(current_state, 0);
    IntHashSet next_state = new_IntHashSet(dfa -> states);
    for(int i = 0; input[i] != '\0'; i++){
        //printf("\n testing for char %c \n", input[i]);
       // printf("\n current state is: ");
       // IntHashSet_print(current_state);
       // printf("\n ");
        dfa -> current_state = current_state;
       // IntHashSet_print(current_state);
        next_state = cDFA_get_transition(dfa, current_state, input[i]);
       // printf("\n next state is: ");
        //IntHashSet_print(next_state);
        current_state = next_state;
        
        
    }
    /*
    for(int s = 0; s < sizeof(dfa -> accepting_state)/sizeof(int); s++){
        printf("accepting state is: %d", dfa -> accepting_state[s]);
    }
   */
    if(cDFA_get_accepting(dfa, current_state)){
        return true;
    } else {
        return false;
    }
}

void cDFA_print(cDFA dfa){
    
    for(int i = 0; i < dfa -> states; i++){
        if(dfa -> transition_table[i][0] == NULL){
            break;
        }
        for (int j = 0; j < 128; j++) {
            printf("j = %d \n", j);
            if(j == 0){
                printf("printing transitions for state { %s } \n", IntHashSet_toString(dfa -> transition_table[i][j]));
            } else {
                printf("for input %d transition is { %s } \n", j, IntHashSet_toString(dfa -> transition_table[i][j]));
            }
        }
    }
    
}


void cDFA_get_accepting_states(cDFA);

void cDFA_get_accepting_states(cDFA dfa){
    for(int i = 0; i < dfa -> states; i++){
        bool boolean = dfa -> accepting_state[i];
        printf("%d", boolean);
    }
}



