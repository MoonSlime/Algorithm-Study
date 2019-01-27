#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<int> budgets, int M) {
    sort(budgets.begin(),budgets.end(), less<int>());
    budgets.insert(budgets.begin(), 0);
    
    int answer=budgets.back();
    int Min=M;
    
    for (int i=budgets.size()-1; i>0; --i) {
        M-=budgets[i];
        if(M<0)break;
    }
    if (M>=0)return answer;
    M = Min;
    
    // if ((budgets.size()-1) * budgets.back() <= M)return answer;
    
    for (int i=1; i<budgets.size() && M>0; ++i) {
        int tmp1 = M/(budgets.size()-i);
        int tmp2 = M%(budgets.size()-i);
        if (budgets[i-1] <= tmp1 && tmp1 <= budgets[i]) {
            if (Min > tmp2) {
                Min = tmp2;
                answer = tmp1;
                if (Min == 0)break;
            }
        }
        M-=budgets[i];
    }
    
    return answer;
}
