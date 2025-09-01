#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>

using namespace std;


long long baseToDec(const string &s, int base) {
    long long val = 0;
    for (char c : s) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = tolower(c) - 'a' + 10; 
        val = val * base + digit;
    }
    return val;
}


long long lagrangeInterpolation(const vector<pair<long long, long long>> &points, int k) {
    long double result = 0.0;

    for (int i = 0; i < k; i++) {
        long double xi = points[i].first;
        long double yi = points[i].second;

        long double term = yi;
        for (int j = 0; j < k; j++) {
            if (i == j) continue;
            long double xj = points[j].first;
            term *= (0.0 - xj) / (xi - xj);
        }
        result += term;
    }
    return llround(result); 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   
    string input, line;
    while (getline(cin, line)) {
        input += line;
    }

   
    int n, k;
    {
        size_t posN = input.find("\"n\"");
        size_t posK = input.find("\"k\"");
        n = stoi(input.substr(input.find(":", posN) + 1));
        k = stoi(input.substr(input.find(":", posK) + 1));
    }

  
    vector<pair<long long, long long>> points;
    for (int i = 1; i <= n; i++) {
        string key = "\"" + to_string(i) + "\"";
        size_t pos = input.find(key);
        if (pos == string::npos) continue;

        size_t basePos = input.find("\"base\"", pos);
        size_t valPos = input.find("\"value\"", pos);
        if (basePos == string::npos || valPos == string::npos) continue;

        int base = stoi(input.substr(input.find("\"", basePos + 7) + 1));
        string valStr;
        {
            size_t q1 = input.find("\"", valPos + 8);
            size_t q2 = input.find("\"", q1 + 1);
            valStr = input.substr(q1 + 1, q2 - q1 - 1);
        }

        long long y = baseToDec(valStr, base);
        points.push_back({i, y});
    }

    
    if ((int)points.size() < k) {
        cerr << "Not enough points!\n";
        return 1;
    }

    long long secret = lagrangeInterpolation(points, k);
    cout << secret << "\n";

    return 0;
}
