#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <bitset>
#include <chrono>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * The function is expected to return a STRING.
 * The function accepts LONG_INTEGER n as parameter.
 */

string counterGameAlt(long long n)
{
    int currentPlayer = 0;
    bitset<sizeof(long long) * 8> bits(n);
    int index = 0;
    int size = bits.size();
    while (1)
    {
        if (bits.count() == 1)
        {
            if (bits[0] == 1)
                return currentPlayer ? "Louise" : "Richard";
            bits >>= 1;
            index += 1;
        }
        else
        {
            for (int i = index; i < size; ++i)
            {
                if (bits[size - 1 - i] == 1)
                {
                    bits.reset(size - i - 1);
                    index = i;
                    break;
                }
            }
        }
        currentPlayer = !currentPlayer;
    }
}

string counterGame(long long n)
{
    if (n == 0)
        return "Richard";
    bitset<sizeof(long long) * 8> bits(n);
    string bitstr = bits.to_string();
    int rightZeroCounter = 0;
    int index = bitstr.length() - 1;
    while(bitstr.at(index) == '0') {
        rightZeroCounter++;
        index--;
    }
    int numberOfPlays = bits.count() - 1 + rightZeroCounter;
    return numberOfPlays % 2 == 0 ? "Richard" : "Louise";
}

int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        string n_temp;
        getline(cin, n_temp);

        long long n = stoll(ltrim(rtrim(n_temp)));

        string result = counterGame(n);

        cout << result << endl;
    }

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](unsigned char c)
                { return !ispunct(c); }));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char c)
                { return !ispunct(c); })
            .base(),
        s.end());

    return s;
}
