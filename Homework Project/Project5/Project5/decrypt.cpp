#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

//mark the end of the cstring, ignoring blanks after the last letter character
void truncate(char a[])
{
    for (int i = (int)strlen(a) - 1; i >= 0; i--)
    {
        if (!isalpha(a[i]))
        {
            continue;
        }
        else
        {
            a[i + 1] = '\0';
            return;
        }
    }
}

//check one of key points of the cipher: the same-letter problem
bool isConvertible(char a[], char b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int index = i; index < n; index++)
        {
            if (a[index] == a[i] && b[index] == b[i])
            {
                continue;
            }
            else if (a[index] != a[i] && b[index] != b[i])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

bool decrypt(istream& cipherstream, const char crib[])
{
    int num1 = 0;
    for (int i1 = 0; i1 < strlen(crib); i1++)
    {
        if (isalpha(crib[i1]))
        {
            num1++;
        }
        else
        {
            continue;
        }
    }
    
    if (num1 == 0)
    {
        return false;
    }
    
    //create a newCrib to store the normalized crib
    //assign a '\0' to appropriate position
    char newCrib[strlen(crib) + 1];
    int i2 = 0;
    int i3 = 1;
    for (int i = 0; i < strlen(crib); i++)
    {
        if (isalpha(crib[i]))
        {
            newCrib[i2] = tolower(crib[i]);
            i2++;
            i3 = 0;
        }
        else
        {
            if (i3 == 0)
            {
                newCrib[i2] = ' ';
                i2++;
                i3++;
            }
            else
            {
                i3++;
            }
        }
    }
    
    truncate(newCrib);
    
    
    //do the same thing for each line read from the file before finding the cipher
    const int numOfLine = 51, MAX = 81;
    char line[numOfLine][MAX];
    char normalLine[numOfLine][MAX];
    int j1 = 0;
    while (j1 < numOfLine)
    {
        int num = 0;
        //store all lines in the file to a 2-dimensional c-string
        //at the same time, normalize all of them
        while (cipherstream.getline(line[j1], 81))
        {
            
            int j2 = 0;
            int j3 = 1;
            for (int j = 0; j < strlen(line[j1]); j++)
            {
                if (isalpha(line[j1][j]))
                {
                    normalLine[j1][j2] = tolower(line[j1][j]);
                    j2++;
                    j3 = 0;
                }
                else
                {
                    if (j3 == 0)
                    {
                        normalLine[j1][j2] = ' ';
                        j2++;
                        j3++;
                    }
                    else
                    {
                        j3++;
                    }
                }
            
            }
            normalLine[j1][j2] = '\0';
            truncate(normalLine[j1]);
            
            j1++;
            num++;
            //count the number of lines to limit the decryption
            continue;
        }
        
        
        
    
        for (int d = 0; d < num; d++)
        {
            //special case1: ciphertext contains no valid letters
            int num2 = 0;
            for (int e = 0; e < strlen(normalLine[d]); e++)
            {
                if (isalpha(normalLine[d][e]))
                {
                    num2++;
                }
                else
                {
                    continue;
                }
            }
        
            if (num2 == 0)
            {
                continue;
            }
        
            //special case2: crib is longer than ciphertext
            if (strlen(normalLine[d]) < strlen(newCrib))
            {
                continue;
            }
        
            for (int k = 0; k < strlen(normalLine[d]) - strlen(newCrib) + 1; k++)
            {
                int k1 = k;
                
                if (isalpha(normalLine[d][k1 - 1]))
                {
                    continue;
                }
                int n = 0;
                //check the length problem:
                for (; n < strlen(newCrib); n++)
                {
                    if (newCrib[n] != ' ' && normalLine[d][k1] != ' ')
                    {
                        k1++;
                        continue;
                    }
                    else if (newCrib[n] == ' ' && normalLine[d][k1] == ' ')
                    {
                        k1++;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
            
                if (n == strlen(newCrib))
                {
                    //create a c-string called cipher[] to store the cipher derived from crib[]
                    //This cipher does not involve same-letter problem and will replace itself if inapprpriate
                    if (!isalpha(normalLine[d][k + strlen(newCrib)]))
                    {
                        int k2 = k;
                        char cipher[strlen(newCrib) + 1];
                        for (int m = 0; m < strlen(newCrib); m++)
                        {
                            cipher[m] = normalLine[d][k2];
                            k2++;
                        }
                        cipher[strlen(newCrib)] = '\0';

                        

                        //check the same-letter problem:
                        if (isConvertible(newCrib, cipher, (int)strlen(newCrib)))
                        {
                            //start here to convert ciphertext into plaintext according to crib
                            for (int f = 0; f < num; f++)
                            {
                                char decrypted[strlen(line[f]) + 1];
                                int index3 = 0;
                                for (int index1 = 0; index1 < strlen(line[f]); index1++)
                                {
                                    int r = 0;
                                    if (!isalpha(line[f][index1]))
                                    {
                                        decrypted[index3] = line[f][index1];
                                        index3++;
                                    }
                                    else
                                    {
                                        for (int index2 = 0; index2 <strlen(cipher); index2++)
                                        {
                                            if (tolower(line[f][index1]) == cipher[index2])
                                            {
                                                decrypted[index3] = newCrib[index2];
                                                index3++;
                                                break;
                                            }
                                            else
                                            {
                                                r++;
                                                if (r == strlen(cipher))
                                                {
                                                    decrypted[index3] = toupper(line[f][index1]);
                                                    index3++;
                                                    break;
                                                    
                                                }
                                                else
                                                {
                                                    continue;
                                                }
                                            }
                            
                                        }
                                    }
                                }
                                decrypted[strlen(line[f])] = '\0';
                                cout << decrypted << endl;
                            }
                            return true;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    continue;
                }
            }
            continue;
        
        }
        return false;
        
    }
    return false;
}


void runtest(const char filename[], const char crib[])
{
    cout << "====== " << crib << endl;
    ifstream cfile(filename);
    if (!cfile)
    {
        cout << "Cannot open " << filename << endl;
        return;
    }
    bool result = decrypt(cfile, crib);
    cout << "Return value: " << result << endl;
}

int main()
{
    cout.setf(ios::boolalpha); // output bools as "true"/"false"
    
    
    runtest("/Users/apple/Documents/CS 31/Homework Project/Project5/Project5/test data.txt", "shadowy");
}