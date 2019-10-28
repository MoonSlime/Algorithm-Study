/**
 *  v1_2 -> v2_0
 *
 *  Modify Logic.
 *
 *  Solve the Time Out problem.
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

#define INF 1000000001

using namespace std;

int gcd(int a, int b) {
    if (a<b) {
        swap(a,b);
    }

    while (b!=0) {
        int tmp = a%b;
        a=b;
        b=tmp;
    }

    return a;
}

int main(void) {
    int N,M,MIN=INF;
    
    scanf("%d", &N);

    vector<int> arr;

    int tmp;
    for (int n=0; n<N; ++n) {
        scanf("%d", &tmp);
        arr.push_back(tmp);
        MIN = min(MIN, tmp);
    }

    sort(arr.begin(), arr.end());

    tmp = arr[1]-arr[0];
    for (int n=2; n<N; ++n) {
        tmp = gcd(tmp, arr[n]-arr[n-1]);
    }

    set<int> answer;
    answer.insert(tmp);
    for (int i=2; i*i<=tmp; ++i) {
        if (tmp%i==0) {
            answer.insert(i);
            answer.insert(tmp/i);
        }
    }

    for (set<int>::iterator iter = answer.begin(); iter!=answer.end();++iter) {
        printf("%d ", *iter);
    }
    printf("\n");

    return 0;
}
