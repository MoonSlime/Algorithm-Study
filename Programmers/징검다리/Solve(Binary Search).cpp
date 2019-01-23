#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool check(vector<int> v, int n, int target) {
    vector<int> tmp;
    tmp.reserve(v.size());
    tmp.assign(v.begin(),v.end());//깊은 복사
    // copy(v.begin(), v.end(), tmp.begin()); // 얕은복사
    
    for (int i=0; i<tmp.size(); ++i) {
        if (tmp[i] < target) {
            n--;
            if (n<0)return false;
            tmp[i+1]+=tmp[i];
        }
    }
    
    return true;
}

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    
    rocks.push_back(0);
    rocks.push_back(distance);
    sort(rocks.begin(), rocks.end(), less<int>());
    
    vector<int> v;
    v.reserve(rocks.size()-1);
    for (int i=1; i<rocks.size(); ++i) {
        v.push_back(rocks[i]-rocks[i-1]);
    }
    
    int start=0;
    int end=distance;
    int target;
    int cnt=0;
    while (start < end && cnt<100) {
        target = (start + end)/2;
        cnt++;
        
        if (check(v, n, target)) {
            if (start == target)start +=1;
            else start = target;
        }
        else {
            end = target-1;
        }
    }
    
    answer = start;
    
    return answer;
}
