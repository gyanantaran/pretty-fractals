#include<stdio.h>
#include<iostream>
using namespace std;
class General_Rule
{
    public:

    int rule_numb;
    int array_length;
    int frame_size;
    int curr_state;
    General_Rule(int array_length, int frame_size, int rule_numb, int curr_state)
    {
        this->array_length = array_length;
        this->frame_size = frame_size;
        this->rule_numb = rule_numb;
        this->curr_state = curr_state;
    }

    int get_frame(int index)
    {
        int shift = (array_length - (index + frame_size/2 + 1));
        int shifted;
        if( shift < 0 )
        {
            // Right end
            shifted = (curr_state << -1 * shift);
        }
        if( shift >= 0 )
        {
            shifted = (curr_state >> shift);
        }
        return shifted & ((1 << frame_size) - 1);
    }

};

int main()
{
    int rule_numb = 30;
    int array_length = 8;
    int frame_size = 3;
    int curr_state = 0b00111010;
    General_Rule Gr(array_length,frame_size,rule_numb,curr_state);
    int index = 5;
    std::cout << Gr.get_frame(index) << endl;
    return 0;

}