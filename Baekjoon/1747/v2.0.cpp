/**
 *
 * v1.0 (이전의 소수들 탐색) -> v2.0 (에라토스테네스의 체) 방식으로 변경.
 *
 * 발생하였던 문제
 * 1. 0, 1의 경우 소수 판별을 해주지 못하였음.
 * 2. 최대 1,000,000 라고 생각 하였으나, 답은 그 이상이 나올 수 있음.
 */
#include <cstdio>
#include <cmath>
#include <string>

#define MAX 1500001

using namespace std;

int N, prime[MAX]={0,}; //1 <= N <= 1,000,000

//check palindrome.
bool check(int x) {
    string str = to_string(x);

    int len = str.length();
    for (int i=0; i<len/2; ++i) {
        if (str[i]!=str[len-i-1])return false;
    }

    /**
    int tmp=x,y=0;

    while (tmp > 0) {
        y *= 10;
        y += tmp%10;
        tmp/=10;
    }

    if (x!=y)return false;
    **/

    return true;
}

int main(void) {
    scanf("%d", &N);

    prime[0]=prime[1]=1;
    for (int i=2; i<=sqrt(MAX); ++i) {
        if (prime[i]==1)continue;
        for (int j=i*i; j<MAX; j+=i) {
            prime[j]=1;
        }
    }

    int rvs=1;
    for (int i=N; i<MAX; ++i) {
        if (prime[i]==1)continue;

        if (check(i)) {
            printf("%d\n", i);
            break;
        }
    }
    
    return 0;
}
