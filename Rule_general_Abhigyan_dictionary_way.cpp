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
    int *dictionary;

    General_Rule(int array_length, int frame_size, int rule_numb, int curr_state)
    {
        this->array_length = array_length;
        this->frame_size = frame_size;
        this->rule_numb = rule_numb;
        this->curr_state = curr_state;
        this->dictionary = new int(1 << frame_size);

    }
    // Makes the dictionary according to the rule.
    void fill_dictionary()
    {
        int rule = rule_numb;
        for(int i = 0;i<(1<<frame_size);i+=1)
        {
            dictionary[i] = rule%2;
            rule = rule >> 1;
            cout << i << ":" << dictionary[i] << endl;
        }

    }


    // """
    // Gets the the frame according to the index of the number which has to be changed
    // """
    int get_frame(int index)
    {
        // removing +1 to just try if it works  
        int shift = (array_length - (index + frame_size/2 +1));
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

    // Function updates curr_state to new_state by calling upon get_frame\
    looking up the value from the dictionary
    void update_new_state()
    {
        int frame;
        int new_state = 0;
        for(int i = 0;i<array_length;i+=1)
        {
            frame = get_frame(i);
            // cout << frame << endl;
            new_state += (dictionary[frame] << i);
        }
        curr_state = new_state;
    }

    // Function updates rule_numb to new_rule_numb according to logic we decide
    void update_new_rule()
    {
        // rule_numb -= 1;
        return;
    }

    // Function updates whatever new things we decide
    void update()
    {
        update_new_state();
        update_new_rule();
    }

    // funtion prints the new state.\
    '|' if 1 at index, ' ' if 0 at index 
    void print(int curr_state, int count)
    {
        if(count == 0) return;
        int remainder = curr_state%2;
        print(curr_state >> 1, count - 1);
        // if(remainder == 0)
        // {
        //     cout << ' ';
        // }
        // if(remainder == 1)
        // {
        //     cout << '|';
        // }
        cout << remainder;
        
    }

    // Function raises a flag if some neccessary condition is surpassed
    bool checks()
    {
        if(rule_numb <= 0) 
        {
            return false;
        }
        return true;
    }

    // Function continously runs all the programs till it does\
    not exceed the passed duration
    void execute(int duration)
    {
        // filling dictionary according to the initial rule
        this->fill_dictionary();
        print(curr_state,array_length);
        for(int i = 0; i<duration; i+=1)
        {
            if(checks())
            {
                
                update();
                cout << endl;
                print(curr_state,array_length);
            }
            else
            {
                break;
            }
        }

    }
};

int main()
{
    int rule_numb = 35;
    int array_length = 8;
    int frame_size = 3;
    int curr_state = 0b00111000;
    int duration = 20;
    // int index = 5;
    General_Rule Gr(array_length,frame_size,rule_numb,curr_state);
    Gr.execute(duration);    
    
    return 0;

}