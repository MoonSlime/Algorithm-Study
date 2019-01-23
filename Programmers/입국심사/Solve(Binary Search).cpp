#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool check(int n, vector<int> times, unsigned long long target) {
    for (auto itr=times.begin(); itr != times.end(); ++itr) {
        n -= target/(*itr);
        if (n<=0)return true;
    }
    return false;
}

unsigned long long solution(int n, vector<int> times) {
    unsigned long long answer = 0;
    
    sort(times.begin(), times.end(), less<int>());
    
    unsigned long long start=0;
    unsigned long long end=times.back() * n;//Max time
    unsigned long long target;
    
    while (start < end) {
        target = (start + end)/2;
        
        if (check(n, times, target)) {//target초를 넘지않고 심사를 끝마칠 수 있을 경우.
            end = target;
        }
        else start = target+1;
    }
    
    answer = start;
    
    return answer;
}
