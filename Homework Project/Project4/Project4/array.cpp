#include <iostream>
#include <string>
#include <cassert>
using namespace std;


int count(const string a[], int n, string target)
{
    int num = 0;
    if (n < 0)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i] == target)
            {
                num++;
            }
            else
            {
                continue;
            }
        }
    }
    return num;
}


int findFirst(const string a[], int n, string target)
{
    if (n < 0)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i] == target)
            {
                return i;
            }
            else
            {
                continue;
            }
        }
    }
    return -1;
}


int moveToEnd(string a[], int n, int pos)
{
    string temp = a[pos];
    if (n < 0)
    {
        return -1;
    }
    else
    {
        for (int i = pos; i < n - 1; i++)
        {
            a[i] = a[i + 1];
        }
        a[n - 1] = temp;
    }
    return pos;
}

int firstInequality(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }
    else
    {
        if (n1 > n2)
        {
            int num = 0;
            for (int i = 0; i < n2; i++)
            {
                if (a1[i] == a2[i])
                {
                    num++;
                    continue;
                }
                else
                {
                    return i;
                }
            }
            return num;
        }
        else
        {
            int num = 0;
            for (int j = 0; j < n1; j++)
            {
                if (a1[j] == a2[j])
                {
                    num++;
                    continue;
                }
                else
                {
                    return j;
                }
            }
            return num;
        }
    }
}


int removeCopies(string a[], int n)
{
    int num = 1;
    if (n < 0)
    {
        return -1;
    }
    else
    {
        int i = 0;
        int k = 0;
        while (i < n - k - 1)
        {
            if (a[i] == a[i + 1])
            {
                moveToEnd(a, n, i + 1);
                k++;
            }
            else
            {
                num++;
                i++;
            }
        }
        return num;
    }
}


bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
    {
        return false;
    }
    else if (n2 > n1)
    {
        return false;
    }
    else
    {
        int i = 0;
        int j = 0;
        while (i < n2)
        {
            while (j < n1)
            {
                if (a1[j] == a2[i])
                {
                    j++;
                    i++;
                    break;
                }
                else
                {
                    j++;
                    if (j == n1)
                    {
                        return false;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        return true;
    }
}


int takeSides(string a[], int n, string barrier)
{
    if (n < 0)
    {
        return -1;
    }
    else
    {
        int i = 0;
        int k = 0;
        while (i < n - k)
        {
            if (a[i] == barrier)
            {
                moveToEnd(a, n, i);
                k++;
            }
            else
            {
                i++;
            }
        }
        
        int num = count(a, n ,barrier);
        int j = 0;
        int m = 0;
        while (j < n - num - m)
        {
            if (a[j] > barrier)
            {
                moveToEnd(a, n, j);
                m++;
            }
            else
            {
                j++;
            }
        }
        return (n - num - m);
    }
}



int main()
{
    string h[7] = { "Phil", "Keegan", "Morgan", "Charl", "", "Stevie", "Morgan" };
    assert(count(h, 7, "Morgan") == 2);
    assert(count(h, 7, "") == 1);
    assert(count(h, 7, "Jhonattan") == 0);
    assert(count(h, 0, "Morgan") == 0);
    assert(findFirst(h, 7, "Morgan") == 2);
    assert(findFirst(h, 2, "Morgan") == -1);
    
    string g[4] = { "Phil", "Keegan", "Charl", "Stevie" };
    assert(firstInequality(h, 4, g, 4) == 2);
    assert(moveToEnd(g, 4, 1) == 1 && g[1] == "Charl" && g[3] == "Keegan");
    
    
    string e[5] = { "Charl", "Charl", "Charl", "Morgan", "Morgan" };
    assert(removeCopies(e, 5) == 2 && e[1] == "Morgan");
    
    string big[10] = { "Phil", "Charl", "Keegan", "Vijay", "Jhonattan", "Keegan" };
    string little1[10] = { "Charl", "Vijay", "Jhonattan" };
    string little3[10] = { "Charl", "Keegan", "Keegan" };
    assert(subsequence(big, 6, little1, 3));
    assert(subsequence(big, 6, little3, 3));
    
    assert(takeSides(h, 7, "Morgan") == 3);
    
    string a[10] = { "James", "Durant", "Durant", "Durant", "Paul", "Howard", "Howard", "Curry", "Paul", "Kobe"};
    assert(count(a, -1, "Kobe") == -1);
    assert(count(a, 2, "Durant") == 1);
    assert(count(a, 10, "Paul") == 2);
    assert(count(a, 10, "Chris") == 0);
    assert(count(a, 10, "Durant") == 3);
    assert(count(a, 10, "DURANT") == 0);
    assert(findFirst(a, -7, "James") == -1);
    assert(findFirst(a, 5, "Paul") == 4);
    assert(findFirst(a, 10, "Howard") == 5);
    assert(findFirst(a, 10, "PAUL") == -1);
    assert(moveToEnd(a, -1, 5) == -1);
    //assert(moveToEnd(a, 10, 4) == 4 && a[4] == "Howard" && a[5] == "Howard");
    //assert(moveToEnd(a, 10, 3) == 3 && a[0] == "James" && a[3] == "Paul");
    //assert(moveToEnd(a, 10, 0) == 0 && a[0] == "Durant" && a[9] == "James");
    //assert(removeCopies(a, 10) == 7 && a[2] == "Paul" && a[4] == "Curry");
    assert(removeCopies(a, -5) == -1);
    //assert(takeSides(a, 10, "Durant") == 1 && a[7] > "Durant");
    assert(takeSides(a, -6, "Paul") == -1);
    //assert(takeSides(a, 10, "James") == 6);
    //assert(takeSides(a, 10, "Paul") == 8);
    
    string b[3] = { "James", "Durant", "Durant"};
    assert(firstInequality(a, -1, b, 3) == -1);
    assert(firstInequality(a, 10, b, -1) == -1);
    assert(firstInequality(a, 2, b, 2) == 2);
    assert(firstInequality(a, 3, b, 2) == 2);
    assert(firstInequality(a, 10, b, 3) == 3);
    assert(firstInequality(b, 2, a, 1) == 1);
    assert(firstInequality(b, 3, a, 10) == 3);
    assert(subsequence(a, 7, b, 3));
    assert(!subsequence(a, -1, b, 3));
    assert(!subsequence(b, 3, a, 5));
    assert(!subsequence(a, 10, b, -7));
    
    string c[5] = { "James", "Durant", "Paul", "Howard", "Kobe"};
    assert(firstInequality(a, 10, c, 5) == 2);
    assert(firstInequality(a, 5, c, 5) == 2);
    assert(firstInequality(a, 10, c, 3) == 2);
    assert(subsequence(a, 10, c, 5));
    assert(!subsequence(c, 5, b, 3));
    
    
    
}

