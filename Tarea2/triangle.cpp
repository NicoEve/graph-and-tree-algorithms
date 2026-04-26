/*
B-Problem B
Nicolas Zapata
8984273
 */

#include <iostream>
#include <cmath>

using namespace std;

double EPS = 1e-7;

double calculateRatio(double AD, double AB)
{
    double ratio = (AD * AD) / (AB * AB - AD * AD);
    return ratio;
}

double findAD(double AB, double ratio)
{
    double low = 0, high = AB, mid = 0;
    while(high - low > EPS)
    {
        mid = (low + high) / 2.0;
        if(calculateRatio(mid, AB) < ratio)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    return mid;
}

int main()
{
    int T;
    cin >> T;
    for(int caseNum = 1; caseNum <= T; caseNum++)
    {
        double AB, AC, BC, ratio;
        cin >> AB >> AC >> BC >> ratio;
        double AD = findAD(AB, ratio);
        printf("Case %d: %.6f\n", caseNum, AD);
    }
    return 0;
}