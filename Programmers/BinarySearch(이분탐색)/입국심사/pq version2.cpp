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
    
    while (n>0) {
        ptype cur = pq.top();
        pq.pop();
        ptype next = pq.top();
        
        int cnt = (next.first - cur.first)/times[cur.second] + 1;
        
        unsigned long long time = cur.first + times[cur.second]*cnt;
        n-= cnt;
        if (n < 1) {
            time += times[cur.second]*(n-1);
        }
        
        pq.push(ptype(time, cur.second));
    }
    
    answer += pq.top().first;
    
    return answer;
}
