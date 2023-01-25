#!/bin/bash

# Join the two codes to cross compile and return the executable
rule_num=$1

RULE_NAME=rule_"${rule_num}"
DIR_NAME=rule_"${rule_num}"
mkdir ./"$DIR_NAME"

function generate_dynamic_code ()
{
    # THE HEADERS
    echo '/*
 * -*- coding: utf-8 -*-
 * AUTHOR: Vishal Paudel  (@vishalpaudel)
 * DATE: 25 January 2023
 * NOTES: A certain notion of input in one language and excutable in another
 *         and output in yet another.
 */

#include <stdint.h>
#include <stdio.h>
'

    # THE DYNAMIC PART
    g++ -o ./"$DIR_NAME"/"$RULE_NAME"_dynamic ./rule_compiler.cpp
    cat <(echo $rule_num | ./"$DIR_NAME"/"$RULE_NAME"_dynamic)

    # THE PROGRAM
    echo '
int main()
{
    uint64_t state = 1u << 31;  /* The initial column */

    for( int i = 0; i < 32; ++i )
    {
        for( int j = 64; j--; )
        {
            printf( state >> j & 1 ? "O" : "." );
        }
        printf( "\n" );

        state = return_state( state );
    }

    return 0;
}'
}

generate_dynamic_code rule_num > ./"$DIR_NAME"/"$RULE_NAME"_code.cpp

g++ -o ./"$DIR_NAME"/"$RULE_NAME"_executable ./"$DIR_NAME"/"$RULE_NAME"_code.cpp
./"$DIR_NAME"/"$RULE_NAME"_executable

