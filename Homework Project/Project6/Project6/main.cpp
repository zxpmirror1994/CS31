#include <iostream>

using namespace std;



void removeF(char* str)
{
    char* charPtr = str;
    while (*charPtr != 0)
    {
        if (*charPtr == 'f' || *charPtr == 'F')
        {
            if (*(charPtr + 1) == 0)
            {
                *charPtr = 0;
                continue;
            }
            
            while (*(charPtr + 1) != 0)
            {
                *charPtr = *(charPtr + 1);
                charPtr++;
            }
            
            *charPtr = 0;
            charPtr = str;
            continue;
        }
        charPtr++;
    }
}
int main()
{
    char msg[50] = "The factor that fails us is Frank.";
    removeF(msg);
    cout << msg;  // prints   The actor that ails us is rank.
}