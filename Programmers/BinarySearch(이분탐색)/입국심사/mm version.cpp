#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

unsigned long long solution(int n, vector<int> times) {
    unsigned long long answer = 0;

    sort(times.begin(), times.end(), less<int>());
    multimap<unsigned long long, int> mm;

    for (int i=0; i<times.size(); ++i) {
        mm.insert(pair<unsigned long long, int>(times[i], i));
    }

    while (n>1) {
        multimap<unsigned long long, int>::iterator itr;
        itr = mm.begin();
        mm.insert(pair<unsigned long long, int>(itr->first+ times[itr->second], itr->second));
        mm.erase(itr);
        n--;
    }

    answer = (mm.begin()) -> first;

    return answer;
}
