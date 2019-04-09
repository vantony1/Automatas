//
//  cDFA.h
//  Project1-CS173
//
//  Created by Victor A on 9/22/18.
//  Copyright © 2018 Victor A. All rights reserved.
//

#ifndef cDFA_h
#define cDFA_h

#include <stdio.h>
#include <stdbool.h>
#include "IntHashSet.h"
#include "Set.h"

/**
 * The data structure used to represent a deterministic finite automaton which has states in terms of set.
 * @see FOCS Section 10.2
 * Note that YOU must specify this data structure, although you can hide
 * (encapsulate) its implementation behind the declared API functions and
 * only provide a partial declaration in the header file.
 */
typedef struct cDFA{
    int states;
    int a_index;
    IntHashSet current_state;
    int *accepting_state;
    IntHashSet **transition_table;
    //x is row, y is column
} *cDFA;

/**
 * Allocate and return a new DFA containing the given number of states.
 */
extern cDFA new_cDFA(int nstates);

/**
 * Free the given DFA.
 */
extern void cDFA_free(cDFA dfa);

/**
 * Return the number of states in the given DFA.
 */
extern int cDFA_get_size(cDFA dfa);

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
extern IntHashSet cDFA_get_transition(cDFA dfa, IntHashSet src, char sym);

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
extern void cDFA_set_transition(cDFA dfa, IntHashSet src, char sym, IntHashSet dst);

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
extern void cDFA_set_transition_str(cDFA dfa, IntHashSet src, char *str, IntHashSet dst);

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
extern void cDFA_set_transition_all(cDFA dfa, IntHashSet src, IntHashSet dst);

/**
 * Set whether the given DFA's state is accepting or not.
 */
extern void cDFA_set_accepting(cDFA dfa, int state);

/**
 * Return true if the given DFA's state is an accepting state.
 */
extern bool cDFA_get_accepting(cDFA dfa, IntHashSet state);

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool cDFA_execute(cDFA dfa, char *input);

/**
 * Print the given DFA to System.out.
 */
extern void cDFA_print(cDFA dfa);

/**
 * Print the given DFA's accepting states to System.out.
 */
extern void cDFA_get_accepting_states(cDFA dfa);

extern int find_state_index(IntHashSet src, cDFA dfa);


#endif
