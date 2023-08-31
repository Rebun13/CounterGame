#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <bitset>
#include <chrono>

#define CHAR_BIT 8

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * The function is expected to return a STRING.
 * The function accepts LONG_INTEGER n as parameter.
 */

string counterGameAlt(long n) {
    int currentPlayer = 0;
    bitset<sizeof(int) * CHAR_BIT> bits(n);
    int index = 0;
    int size = bits.size();
    while(1) {
        if(bits.count() == 1) {
            if(bits[0] == 1) return currentPlayer ? "Louise" : "Richard";
            bits >>= 1;
            index += 1;
        } else {
            for(int i = index; i < size; ++i) {
                if(bits[size - 1 - i] == 1) {
                    bits.reset(size - i - 1);
                    index = i;
                    break;
                }
            }
        }
        currentPlayer = !currentPlayer;
    }
}

string counterGame(long n) {
    bitset<sizeof(int) * CHAR_BIT> bits(n);
    int zeroCounter = 0;
    // Count zeros to the right
    for(int i = 0; i < bits.size(); i++) {
        if(bits[i] == 0) zeroCounter += 1;
        else break;
    }
    return ((bits.count() - 1) + zeroCounter) % 2 == 0 ? "Richard" : "Luise";
}

int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        long n = stol(ltrim(rtrim(n_temp)));

        string result = counterGame(n);

        cout << result << endl;
    }

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](unsigned char c) { return !ispunct(c); })
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !ispunct(c); }).base(),
        s.end()
    );

    return s;
}
