//
//  dfa.c
//  Project1-CS173
//
//  Created by Victor A on 9/20/18.
//  Copyright © 2018 Victor A. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"


typedef struct DFA *DFA;

struct DFA {
    int states;
    int current_state;
    bool *accepting_state;
    int **transition_table;
    //x is row, y is column
};

DFA new_DFA(int nstates) {
    DFA this = (DFA)malloc(sizeof(struct DFA));
    this -> states = nstates;
    int **table;
    bool *acceptance;
    
    acceptance = (bool*) malloc(nstates*sizeof(bool));
    
    table = (int**) malloc(nstates*sizeof(int *));
    
    for(int i = 0; i < nstates; i++){
        table[i] = malloc(128 * sizeof(int));
    }
    
    this -> transition_table = table;
    this -> accepting_state = acceptance;
    this -> current_state = 0;
    
    //MEMORY ALLOCATION FOR TRANSITION TABLE
    return this;
}


int DFA_get_size(DFA current) {
    return current ->  states;
}

void DFA_free(DFA current){
    
    for(int i = 0; i < current -> states; i++){
        free(current ->transition_table[i]);
    }
    
    free(current -> transition_table);
    free(current -> accepting_state);
    free(current);
}

void DFA_set_transition (DFA dfa, int src, char sym, int dst){
    
    int input = (int) sym;
    
    dfa -> transition_table[src][input] = dst;
    
}

int DFA_get_transition(DFA dfa, int src, char sym){
    
    if (src == -1) {
        return -1;
    }
    
    return dfa -> transition_table[src][(int)sym];
}

void DFA_set_transition_str(DFA dfa, int src, char *str, int dst){
    for(int i = 0; str[i] != '\0'; i++){
        DFA_set_transition (dfa, src, str[i],dst);
    }
}

void DFA_set_transition_all(DFA dfa, int src, int dst){
    for(int i = 0; i < 128; i++){
        DFA_set_transition (dfa, src, (char) i,dst);
    }
}

void DFA_set_accepting(DFA dfa, int state, bool value){
    dfa -> accepting_state[state] = value;
}

bool DFA_get_accepting(DFA dfa, int state){
    return dfa -> accepting_state[state];
}

bool DFA_execute(DFA dfa, char *input){
    int current_state = 0;
    int next_state;
    for(int i = 0; input[i] != '\0'; i++){
        dfa -> current_state = current_state;
        //printf("\n current state = %d \n", dfa -> current_state);
        next_state = DFA_get_transition(dfa, current_state, input[i]);
        current_state = next_state;
        //printf("\n next state = %d \n", next_state);
    }
    
    return dfa -> accepting_state[current_state];
}

void DFA_print(DFA dfa){
    
    for(int i = 0; i < dfa -> states; i++){
        for(int j = 0; j < 128; j++){
            printf(" %d", dfa -> transition_table[i][j]);
        }
        printf("\\n");
    }
    
}


void DFA_get_accepting_states(DFA);

void DFA_get_accepting_states(DFA dfa){
    for(int i = 0; i < dfa -> states; i++){
        bool boolean = dfa -> accepting_state[i];
        printf("%d", boolean);
    }
}


