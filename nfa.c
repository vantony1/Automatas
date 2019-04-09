//
//  nfa.c
//  Project1-CS173
//
//  Created by Victor A on 9/20/18.
//  Copyright © 2018 Victor A. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "nfa.h"
#include "dfa.h"
#include "cDFA.h"


typedef struct NFA *NFA;

/*struct NFA {
    int states;
    int *current_state;
    int *accepting_state;
    int ***transition_table;
};*/

NFA new_NFA(int nstates) {
     NFA this = (NFA)malloc(sizeof(struct NFA));
    
    
    int ***table;
    int *current_state;
    int *acceptance;
    
    table = (int***) malloc(nstates*sizeof(int **));
    
    for(int i = 0; i < nstates; i++){
       
        table[i] = (int **) malloc (128 * sizeof(int*));

        for(int j = 0; j < 128; j++){
            table[i][j] = (int*) malloc(nstates*sizeof(int));
        }
    }
    
    for(int i = 0; i < nstates; i++){
        for(int j = 0; j < 128; j++){
            for(int k = 0; k < nstates; k++){
                table[i][j][k] = 0;
            }
        }
    }
    
     acceptance = (int*) malloc(nstates*sizeof(int));
     current_state = (int*) malloc(nstates*sizeof(int));
    
    
    for(int i = 0; i < nstates; i++){
        current_state[i] = 0;
        acceptance[i] = 0;
    }
    
    current_state[0] = 1;
    
    
    
    
    
    this -> states = nstates;
    this -> accepting_state = acceptance;
    this -> current_state = current_state;
    this -> transition_table = table;
    
    return this;
}

int NFA_get_size(NFA nfa){
    return nfa -> states;
}

void NFA_free(NFA nfa) {
    
    
    for(int i = 0; i < nfa -> states; i++){
        for(int j = 0; j < 128; i++){
            free(nfa -> transition_table[i][j]);
            
        }
        free(nfa -> transition_table[i]);
    }
    
    free(nfa -> transition_table);
    free(nfa -> accepting_state);
    free(nfa -> current_state);
    free(nfa);
    
}

void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    int input = (int) sym;
    
    nfa -> transition_table[src][input][dst] = 1;
    
    
    
}

int* NFA_get_transitions(NFA nfa, int state, char sym){
    
    int* transitions = (int*) calloc(nfa->states, sizeof(int));
    int index = 0;
    int input = (int) sym;
    
    for(int k = 0; k < nfa -> states; k++){
                 if( nfa -> transition_table[state][input][k] != 0){
                     transitions[k] = 1;
                     index ++;
                 }
         }

    //printf("returning transitions after processing %c \n", sym);
    //array_printer(transitions, nfa -> states);
    
    return transitions;
}

void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
    for(int i = 0; str[i] != '\0'; i++){
        NFA_add_transition (nfa, src, str[i],dst);
    }
}

void NFA_add_transition_all(NFA nfa, int src, int dst){
    for(int i = 0; i < 128; i++){
    
        NFA_add_transition (nfa, src, (char) i,dst);
    }
}

void NFA_set_accepting(NFA nfa, int state, int value){
    nfa -> accepting_state[state] = value;
}

int NFA_get_accepting(NFA nfa, int state){
    return nfa -> accepting_state[state];
}

void array_adder(int* holder, int* transitions, int states){
    for(int i = 0; i < states; i++){
        if(transitions[i] == 1 && holder[i] != 1){
            holder[i] = transitions[i];
        }
    }
}

int one_same_element(int* accepting, int* final_states, int states){
    for(int i = 0; i < states; i++){
        if(accepting[i] == 1 && final_states[i] == 1){
              return 1;
          }
    }
    return 0;
}

void array_printer(int* print, int states) {
    
    for(int i = 0; i < states; i++){
       printf("%d ", print[i]);
    }
    printf("\n");
}

bool NFA_execute(NFA nfa, char *input) {
    int states = nfa -> states;
    int* states_holder = (int*) calloc(states, sizeof(int));
    int* transition_holder = (int*) calloc(states, sizeof(int));
    int* transition = (int*) calloc(states, sizeof(int));
    
    //printf("before processing input current states are: \n");
    //array_printer(nfa->current_state, states);
    //printf("\n");
    
   
    for(int i = 0; input[i] != '\0'; i++){
        transition_holder = (int*) calloc(states, sizeof(int));
        for (int s = 0; s < states; s++) {
            if(nfa -> current_state[s] != 0){
                
                transition = NFA_get_transitions(nfa, s, input[i]);
                //printf("after processing char %c for state %d transitions are: \n", input[i], s);
                //array_printer(transition, states);
                array_adder(transition_holder, transition, states);
            }
        }
        states_holder = transition_holder;
        nfa -> current_state = states_holder;
    }
    
     nfa -> current_state = states_holder;
  
    /*
      printf("\n");
    printf("after processing input accpeting states are: \n");
    array_printer(nfa->accepting_state, states);
    printf("after processing input current states are: \n");
    array_printer(nfa->current_state, states);
     */
    
    //printf("the test of accepatbility returns: %d", one_same_element(nfa -> accepting_state, nfa -> current_state, states));
    
    if(one_same_element(nfa -> accepting_state, nfa -> current_state, states) == 1){
        return true;
    } else {
        return false;
    }
}

void NFA_print(NFA nfa){
    int states = nfa -> states;
    for(int i = 0; i < states; i++){
        printf("Printing for state  %d \n", i);
         for(int j = 0; j < 128; j++){
                printf("and for input %d ", j);
              for(int k = 0; k < states; k++){
                  int output = nfa -> transition_table[i][j][k];
                  printf(" %d", output);
              }
             printf(" \n");
        }
    }
    
}


cDFA NFA_to_DFA(NFA nfa){
    
    int states = NFA_get_size(nfa);
    
    cDFA this = new_cDFA(states);
    
    
    for (int a = 0; a < nfa -> states; a++){
        if (nfa -> accepting_state[a] == 1) {
            // printf("\n SETTING STATE %d as ACCEPTING \n", a);
             cDFA_set_accepting(this, a);
        }
       
    }
    
    int* new_states = (int*) calloc(this->states, sizeof(int));
    int new_states_index = 0;
    
    //int stater = states
    
    
    
    for(int i = 0; i < states; i++){
        
        //printf("\n processing for STATE i = %d \n", i);
        
       
        for(int j = 1; j < 128; j++){
            
            //printf("\n j = %d \n", j);
            
            IntHashSet* final = (IntHashSet*) malloc(states*sizeof(IntHashSet));
            
            int index = 0;
            
            for(int k = 0; k < states; k++){
                
                IntHashSet holder = new_IntHashSet(states);
                if(nfa -> transition_table[i][j][k] == 1){
                   // printf("adding transition %d for k = %d", nfa -> transition_table[i][j][k], k);
                    IntHashSet_insert(holder, k);
                    final[index] = holder;
                    index++;
                }
            }
            
            IntHashSet holder = new_IntHashSet(index);
            
            for(int l = 0; l < index; l++){
                IntHashSet_union(holder, final[l]);
            }
            
            this -> transition_table[i][j] = holder;
            
            if (IntHashSet_toString(holder) != NULL) {
                
            
            
           // printf("\n Holder to string: %s \n ",IntHashSet_toString(holder));
            
             //printf("states = %d \n", this->states);
            
            int need_to_add = 0;

            for(int i = 0; i < this -> states; i++){
                
               /// printf("i = %d \n", i);
                if(IntHashSet_equals(holder, this -> transition_table[i][0])) {
                   // printf("STATE CLONE FOUND");
                    need_to_add = 0;
                    break;
                } else {
                    need_to_add = 1;
                     }
            }
            
            //printf("need to add = %d ", need_to_add);
            
              if(need_to_add == 1){
                for(int c = 0; c < this -> states; c++){
                    //printf("looping to find empty");
                    if (this -> transition_table[c][0] == NULL) {
                        //printf("ADDING STATE");
                        this -> transition_table[c][0] = holder;
                        new_states[new_states_index] = c;
                        new_states_index++;
                        need_to_add = 0;
                    }
                    if (need_to_add == 0) {
                        break;
                    }
                
            }
              }
            }
        }
    
  
    
    }
    
    
    
    for(int i = 0; i < this -> states; i++){
        if (array_contains(new_states, new_states_index, i)) {
            //printf("ENTERING UNIONING MODE for i = %d", i);
            
            IntHashSet state = new_IntHashSet(this -> states);
            
            state = this -> transition_table[i][0];
            
            for (int j = 1; j < 128; j++) {
                
                IntHashSet holder = new_IntHashSet(states);
                
                IntHashSetIterator current = IntHashSet_iterator(state);
                
                while(IntHashSetIterator_hasNext(current)){
                    //printf("ENTERING UNIONING MODE: PHASE ITERATION for j = %d \n", j);
                    int transition_for = IntHashSetIterator_next(current);
                    
                    IntHashSet_union(holder, this -> transition_table[transition_for][j]);
                 
                }
                
                this -> transition_table[i][j] = holder;
                
                if (IntHashSet_toString(holder) != NULL) {
                    
                    
                   // printf("\n Holder to string: %s \n ",IntHashSet_toString(holder));
                    
                  //  printf("states = %d \n", this->states);
                    
                    int need_to_add = 0;
                    
                    for(int i = 0; i < this -> states; i++){
                        
                       // printf("i = %d \n", i);
                        if(IntHashSet_equals(holder, this -> transition_table[i][0])) {
                            //printf("STATE CLONE FOUND");
                            need_to_add = 0;
                            break;
                        } else {
                            need_to_add = 1;
                        }
                    }
                    
                   // printf("need to add = %d ", need_to_add);
                    
                    if(need_to_add == 1){
                        for(int c = 0; c < this -> states; c++){
                         //   printf("looping to find empty");
                            if (this -> transition_table[c][0] == NULL) {
                            //    printf("ADDING STATE");
                                this -> transition_table[c][0] = holder;
                                new_states[new_states_index] = c;
                                new_states_index++;
                                need_to_add = 0;
                            }
                            if (need_to_add == 0) {
                                break;
                            }
                            
                        }
                    }
                }
            }
            
        }
           
            
            
    }
    
    return this;
    
}

/*
 for (int j = 0; j < 128; j++){
 for(int y = 0; y < nfa -> states; y++){
 IntHashSet_insert(holder, nfa -> transition_table[transition_for][j][y]);
 }
 }
 */


bool array_contains(int* array, int array_length, int element) {
    for (int i = 0; i < array_length; i++){
        if(array[i] == element){
            return true;
        }
    }
    
    return false;
}

void reset_current_states(NFA nfa){
    for(int i = 0; i < nfa -> states; i++){
        nfa -> current_state[i] = 0;
    }
    
    nfa -> current_state[0] = 1;
}







