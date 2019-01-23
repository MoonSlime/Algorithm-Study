#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

typedef pair<unsigned long long, int> ptype;

unsigned long long solution(int n, vector<int> times) {
    unsigned long long answer = 0;
    
    priority_queue< ptype, vector<ptype>, greater<ptype>> pq;
    
    for (int i=0; i<times.size(); ++i) {
        pq.push(ptype(times[i], i));
    }
    
    while (--n>0) {
        ptype cur = pq.top();
        pq.pop();
        ptype next = pq.top();
        
        int idx = cur.second;
        unsigned long long time = cur.first + times[idx];
        
        while (time + times[idx] < next.first && n>0) {
            time += times[idx];
            n--;
        }
        pq.push(ptype(time, idx));
    }
    
    answer += pq.top().first;
    
    return answer;
}
