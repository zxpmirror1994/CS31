#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//Pre-condition; motion is a string of digits, letters and slashes, and it is a call-by-value parameter
//Post-consition: Return true if motion is meaningful and return false if not meaningful


bool isMotionMeaningful(string motion)
{
    
    //Return false if motion contains letters other than 'W', 'A', 'S' ,'D', 'w', 'a', 's', 'd'
    for (int i = 0; i < motion.size(); i++)
    {
       if((isalpha(motion[i])) && (motion[i] != 'w' && motion[i] != 'a' && motion[i] != 's' && motion[i] != 'd' && motion[i] != 'W' && motion[i] != 'A' && motion[i] != 'S' && motion[i] != 'D'))
       {
            return false;
       }
    }
        
    //Return true for the zero-beats condition
    if (motion == "")
    {
        return true;
    }
    
    //For a motion with one beat, only "/" is meaningful
    if (motion.size() == 1)
    {
        if (motion[0] == '/')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //For a motion with two beats, only "//" or a direction followed by a slash is meaningful
    else if (motion.size() == 2)
    {
        if (motion[1] == '/' && ((motion[0] == '/') || (isalpha(motion[0]))))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //Consider motion with more than two beats
    else
    {
        for (int i = 0; i < motion.size() - 1; i++)
        {
            
            //Return false if three digits are in sequence or one digit directly followed by a slash
            if ((isdigit(motion[i])) && (((isdigit(motion[i + 1]) && isdigit(motion[i + 2])) || (motion[i + 1] == '/'))))
            {
                return false;
            }
            
            //Return false if a direction is followed by a digit or another direction
            else if ((isalpha(motion[i])) && ((isalpha(motion[i + 1])) || isdigit(motion[i + 1])))
            {
                return false;
            }
            
            //Return false if the last character is not a slash
            else if (motion[motion.size() - 1] != '/')
            {
                return false;
            }
        }
        
        //Return true for all other situations
        return true;
    }
}

//Pre-condition: motion is a string with digits, letters and slashes
//Post-condition: return the number of beats in the motion sequence
int numberOfBeats(string motion)
{
    int count = 0;
    for (int i = 0; i < motion.size(); i++)
    {
        //The number of beats are exactly the same as the number of slashes
        if (motion[i] == '/')
        {
            count++;
        }
    }
    return count;
}

//Pre-condition: twochars is a string of length 2
//Post-condition: return the decimal number of these 2 digits(or other characters)
//1)Both of the characters of twochars are digits
//2)twochars[1] is a digit and twochars[2] is not
//3)If both of the characters of twochars are slashes, return 1
int convertToDecimal(string twochars)
{
    int num = 0;
    if (isdigit(twochars[0]) && isdigit(twochars[1]))
    {
        num = 10 * (twochars[0] - '0') + (twochars[1] - '0');
    }
    else if (!isdigit(twochars[0]) && isdigit(twochars[1]))
    {
        num = twochars[1] - '0';
    }
    else if (twochars == "//")
    {
        num = 1;
    }
    return num;
}

//Pre-condition: motion is a string of digits, letters and slashes, and it is a call-by-value parameter
//instructions is the translation of motion, and it is a call-by-reference parameter
//badBeats is a call-by-reference parameter
//Post-condition: Return 0 or 1 or 2 or 3 or 4 according to difference conditions
//instructions becomes the translation if 0 is returned and remains unchaged if 1 or 2 or 3 or 4is returned
//badBeats becomes an appropriate number if 1 or 2 or 3 or 4 is returned and remains unchanged if 0 is returned
int translateMotion(string motion, string& instructions, int& badBeat)
{
    //Call isMotionMeaningful function and return 1 if the motion is not meaningful
    if (isMotionMeaningful(motion) == false)
    {
        return 1;
    }
    else
    {
        
        //Consider the return-3 situation:
        //Check each character in the reverse order until a letter appears
        //Compare the decimal number before it with the number of beats from that letter to the end of the string
        //Return 3 and set badBeats to numberOfBeats + 1;
        int i = (int)motion.size() - 1;
        int num1 = 0;
        
        for (i = (int)motion.size() - 1; i > 0; i--)
        {
            if (motion[i] == '/')
            {
                num1++;
            }
            else if (isalpha(motion[i]) && i == 1 && isdigit(motion[0]) && ((motion[0] - '0') > num1))
            {
                badBeat = numberOfBeats(motion) + 1;
                return 3;
            }
            else if (isalpha(motion[i]) && i > 1 && convertToDecimal(motion.substr(i - 2,2)) > num1)
            {
                badBeat = numberOfBeats(motion) + 1;
                return 3;
            }
        }
        
        
        //Consider the return-4 situation:
        //If the first two characters appear to be "0 + letter", "00", "01"
        //Return 4 and set badBeat to 1
        if (motion[0] == '0'  && (isalpha(motion[1]) || motion[1] == '0' || motion[1] == '1'))
        {
            badBeat = 1;
            return 4;
        }
        
        //If the first two characters appear to be "1 + letter"
        //Return 4 and set badBeat to 1
        else if (motion[0] == '1' && isalpha(motion[1]))
        {
            badBeat = 1;
            return 4;
        }

        //Check each character of the string starting from element with index 2
        //If motion[j] is a letter, then return 4 if the substring of length 2 before it is "00", "01", "/1". "/0"
        int j = 2;
        for (j = 2; j < motion.size(); j++)
        {
            if (isalpha(motion[j]) && (motion.substr(j - 2,2) == "01" || motion.substr(j - 2,2) == "/1" || motion.substr(j - 2,2) == "00" || motion.substr(j - 2,2) == "/0"))
            {
                badBeat = numberOfBeats(motion.substr(0,j)) + 1;
                return 4;
            }
        }
        
        //Consider the return-2 situation:
        //If motion[0] is a digit and motion[1] is a letter and the substring starting at motion[2] of length less than the decimal number which the digit represents
        //then check which element of the substring starts to be characters other than the slash
        if (isdigit(motion[0]) && isalpha(motion[1]) && (numberOfBeats(motion.substr(2,motion[0] - '0')) < (motion[0] - '0')))
        {
            for (int m = 2; m < 2 + (motion[0] - '0'); m++)
            {
                if (motion[m] != '/')
                {
                    badBeat = m - 1;
                    return 2;
                }
            }
        }
        
        //Then a more general situation:
        //Check each character starting from the element of the string with index 2
        //If motion[k] is a letter, then convert the digit representation before it into decimal numbers
        //If the decimal number is larger than the number of consecutive slashes after that letter
        //Return 2 and set badBeat to numberOfBeats(motion.substr(0,k + 1)) + numberOfBeats(motion.substr(k + 1, n - k)) + 1
        int k = 2;
        for (k = 2; k < motion.size(); k++)
        {
            if (isalpha(motion[k]) && ((numberOfBeats(motion.substr(k + 1,convertToDecimal(motion.substr(k - 2,2))))) < (convertToDecimal(motion.substr(k - 2,2)))))
            {
                for (int n = k + 1; n < k + 1 + convertToDecimal(motion.substr(k - 2,2)); n++)
                {
                    if (motion[n] != '/')
                    {
                        badBeat = numberOfBeats(motion.substr(0,k + 1)) + numberOfBeats(motion.substr(k + 1, n - k)) + 1;
                        return 2;
                    }
                }
            }
        }
        
        
        
        int input_index = 0;
        int num = 0;
        int temp = 0;
        
        while (input_index < motion.size())
        {
            //If the character is a digit, convert the digit to a decimal number
            //Increase input_index by one to check next character
            if (isdigit(motion[input_index]))
            {
                num = 10 * num + (motion[input_index] - '0');
                input_index++;
            }
            
            //If the character is a direction
            //1) the value of num is 0, this direction does not mean a hold
            //Add the lowercase of the direction to instructions and check next character
            //2) the value of num is not 0, this direction means a hold
            //Add the uppercase of the direction to instructions
            //The number of uppercase letters should equal the value of num
            //Reinitialize the value of num to 0 and check next character
            else if (isalpha(motion[input_index]))
            {
                if (num == 0)
                {
                    instructions += tolower(motion[input_index]);
                    input_index++;
                }
                else
                {
                    for (int i = 0; i < num; i++)
                    {
                        instructions += toupper(motion[input_index]);
                    }
                    temp = num;
                    num = 0;
                    input_index++;
                }
            }
            
            //If the character is a slash
            //1) the value of num is not zero, then a hold is still in effect
            //2) the value of num is zero and the character before is a direction
            //3) the value of num is zero and the character before is a slash
            else if (motion[input_index] == '/')
            {
                if (temp != 0)
                {
                    temp--;
                    input_index++;
                }
                else if (temp == 0 && isalpha(motion[input_index - 1]))
                {
                    input_index++;
                }
                else if (temp == 0 && motion[input_index] == '/')
                {
                    instructions += ".";
                    input_index++;
                }
                
            }
        }
        return 0;
        
        
    }
    
    return 0;
}

        
        
        
        
        
        
        
        
        
        
        
        
        






int main()
{
    string name;
    cout << "Enter a motion: ";
    getline(cin, name);
    string instructions;
    int badBeat;
    if (isMotionMeaningful(name))
    {
        cout << "a";
    }
    else
    {
        cout << "b";
    }
    cout << endl;
    cout << translateMotion(name, instructions, badBeat) << endl;
    cout << instructions << endl;
    cout << badBeat << endl;
}
