
#include <stdio.h>
#include <stdlib.h>

int print_if( int rule_num )
{
    for ( int frame = 0; frame < 8; frame++ )
    {
        if( ( rule_num & 1 ) && ( frame == 0 ) )
        {
            printf( "\t\t" );
            printf("( ( ~( state >> 1 ) ) & ( ~( state ) ) & ( ~( state << 1 ) ) ) | ");
            printf( "\n" );
        }
        else if( ( rule_num & 1 ) && ( frame == 1 ) )
        {
            printf( "\t\t" );
            printf("( ( ~( state >> 1 ) ) & ( ~( state ) ) & ( state << 1 ) ) | ");
            printf( "\n" );
        }
        else if( ( rule_num & 1 ) && ( frame == 2 ) )
        {
            printf( "\t\t" );
            printf("( ( ~( state >> 1 ) ) & ( state ) & ( ~( state << 1 ) ) ) | ");
            printf( "\n" );
        }
        else if( ( rule_num & 1 ) && ( frame == 3 ) )
        {
            printf( "\t\t" );
            printf("( ( ~( state >> 1 ) ) & ( state ) & ( state << 1 ) ) | ");
            printf( "\n" );
        }
        else if( ( rule_num & 1 ) && ( frame == 4 ) )
        {
            printf( "\t\t" );
            printf("( ( state >> 1 ) & ( ~( state ) ) & ( ~( state << 1 ) ) ) | ");
            printf( "\n" );
        }
        else if( ( rule_num & 1 ) && ( frame== 5 ) )
        {
            printf( "\t\t" );
            printf("( ( state >> 1 ) & ( ~( state ) ) & ( state << 1 ) ) | ");
            printf( "\n" );
        }
        else if( ( rule_num & 1 ) && ( frame == 6 ) )
        {
            printf( "\t\t" );
            printf("( ( state >> 1 ) & ( state ) & ( ~( state << 1 ) ) ) | ");
            printf( "\n" );
        }
        else if( ( rule_num & 1 ) && ( frame == 7 ) )
        {
            printf( "\t\t" );
            printf("( ( state >> 1 ) & ( state ) & ( state << 1 ) ) | ");
            printf( "\n" );
        }
        rule_num >>= 1;

    }

    return 0;
}

int main()
{

    int rule_num;
    scanf( "%i", &rule_num );

    printf( "uint64_t return_state( uint64_t state ) \n" );
    printf( "{\n" );
    printf( "\t\treturn \n" );
    print_if( rule_num );
    printf( "\t\t0;\n" );
    printf( "\t}\n" );

    return 0;
}
