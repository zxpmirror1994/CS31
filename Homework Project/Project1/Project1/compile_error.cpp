// Code for Project 1
// Report poll results

#include <iostream>
using namespace std;

int main()
{
    int numberSurveyed preferHomeTeam preferAwayTeam;   //1st compile error
    
    cout << "How many fans in attendance were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them prefer the home team? ";
    cin >> preferHomeTeam;
    cout >> "How many of them prefer the away team? ";   //2nd compile error
    cin >> preferAwayTeam;
    
    double pctHome = 100.0 * preferHomeTeam / numberSurveyed;
    double pctAway = 100.0 * preferAwayTeam / numberSurveyed;
    
    cout.setf(ios::fixed);
    cout.precision(1);
    
    cout << endl;
    cout << pctHome << "% prefer the home team." << endl;
    cout << pctAway << "% prefer the away team." << endl;
    
    if (pctHome > pctAway)
        cout << "The home team is more popular with this crowd." << endl;
    else
        cout << "The away team is more popular with this crowd." << endl;
}

