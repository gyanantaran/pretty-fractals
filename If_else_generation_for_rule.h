#include<iostream>
using namespace std;

int Rules(int frame)
{
int L = frame >> 2;
int C = (frame >> 1)%2;
int R = frame%2;
if(!L && !C && !R) return 1;
return 0;
}