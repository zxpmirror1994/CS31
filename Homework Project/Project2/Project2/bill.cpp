#include <iostream>
#include <string>
using namespace std;

int main()
{
    int year, powerUsed;
    char yesOrNo;
    string city;
    double amount1 = 0;
    double amount2 = 0;
    double amount = 0;
    
    cout << "Years as customer: ";
    cin >> year;
    cout << "Energy efficient home? (y/n): ";
    cin >> yesOrNo;
    cout << "Residential city: ";
    cin.ignore(10000, '\n');
    getline(cin, city);
    cout << "Number of gigawatts used: ";
    cin >> powerUsed;
    if (year <= 3 && year >= 0)
    {
        if (yesOrNo == 'y' || yesOrNo == 'n')
        {
            if (powerUsed <= 2 && powerUsed >= 0)
            {
                amount = 1.05 * powerUsed;
            }
            else if (powerUsed > 2)
            {
                amount = 1.21 + 0.88 * powerUsed;
            }
            else
            {
                cout << "---" << endl;
                cout << "The number of gigawatts used must not be negative" << endl;
                return 1;
            }
        }
        else
        {
            cout << "---" << endl;
            cout << "You must enter y or n" << endl;
            return 1;
        }
    }
    else if (year > 3 && year < 10)
    {
        if (yesOrNo == 'y')
        {
            if (powerUsed <= 2 && powerUsed >= 0)
            {
                amount = 1.05 * powerUsed;
            }
            else if (powerUsed > 2)
            {
                amount = 2.10 + 0.88 * (powerUsed - 2);
            }
            else
            {
                cout << "---" << endl;
                cout << "The number of gigawatts used must not be negative" << endl;
                return 1;
            }
        }
        else if (yesOrNo == 'n')
        {
            amount = 1.21 + 0.88 * powerUsed;
        }
        else
        {
            cout << "---" << endl;
            cout << "You must enter y or n" << endl;
            return 1;
        }
    }
    else if (year >= 10)
    {
        if (yesOrNo == 'y')
        {
            if (powerUsed <= 2 && powerUsed >= 0)
            {
                amount1 = 1.05 * powerUsed;
                amount2 = 0.80 + 0.30 * powerUsed;
                if (amount1 >= amount2)
                {
                    amount = amount2;
                }
                else
                {
                    amount = amount1;
                }
            }
            else if (powerUsed > 2)
            {
                amount = 0.80 + 0.30 * powerUsed;
            }
            else
            {
                cout << "---" << endl;
                cout << "The number of gigawatts used must not be negative" << endl;
                return 1;
            }
        }
        else if (yesOrNo == 'n')
        {
            if (powerUsed >= 0)
            {
                amount = 0.80 + 0.30 * powerUsed;
            }
            else
            {
                cout << "---" << endl;
                cout << "The number of gigawatts used must not be negative" << endl;
                return 1;
            }
        }
        else
        {
            cout << "---" << endl;
            cout << "You must enter y or n" << endl;
            return 1;
        }
    }
    else
    {
        cout << "---" << endl;
        cout << "The years as customer must not be negative" << endl;
        return 1;
    }
    
    if (city == "")
    {
        cout << "---" << endl;
        cout << "You must enter a residence" << endl;
        return 1;
    }
    else
    {
        cout << "---" << endl;
        cout << "The bill for this customer in " << city << " is $" << amount << endl;
        return 0;
    }
}

