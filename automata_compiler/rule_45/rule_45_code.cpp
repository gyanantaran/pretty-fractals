/*
 * -*- coding: utf-8 -*-
 * AUTHOR: Vishal Paudel  (@vishalpaudel)
 * DATE: 25 January 2023
 * NOTES: A certain notion of input in one language and excutable in another
 *         and output in yet another.
 */

#include <stdint.h>
#include <stdio.h>

uint64_t return_state( uint64_t state ) 
{
		return 
		( ( ~( state >> 1 ) ) & ( ~( state ) ) & ( ~( state << 1 ) ) ) | 
		( ( ~( state >> 1 ) ) & ( state ) & ( ~( state << 1 ) ) ) | 
		( ( ~( state >> 1 ) ) & ( state ) & ( state << 1 ) ) | 
		( ( state >> 1 ) & ( ~( state ) ) & ( state << 1 ) ) | 
		0;
	}

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
}
