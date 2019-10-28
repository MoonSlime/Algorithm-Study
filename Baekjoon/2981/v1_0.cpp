#include <cstdio>
#include <vector>
#include <algorithm>

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

    vector<int> arr,answer;

    int tmp;
    for (int n=0; n<N; ++n) {
        scanf("%d", &tmp);
        arr.push_back(tmp);
        MIN = min(MIN, tmp);
    }

    for (int bias=1; bias<MIN; ++bias) {
        tmp = arr[0]-bias;
        for (int n=1; n<N; ++n) {
            tmp = gcd(tmp, arr[n]-bias);
            if(tmp<=1)break;
        }
        
        if (tmp>1)answer.push_back(tmp);
    }

    sort(answer.begin(), answer.end());

    for (int i=0; i<answer.size(); ++i) {
        printf("%d ", answer[i]);
    }
    printf("\n");

    return 0;
}
