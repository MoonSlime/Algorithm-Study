#include <cstdio>

int visit[1000001];

int dp(int n, int cnt) {
    if (visit[n]!=0 && visit[n] <= cnt)return -1;
    else visit[n]=cnt;

    if (n<=1)return 1;

    if (n%3==0)dp(n/3, cnt+1);
    if (n%2==0)dp(n/2, cnt+1);
    dp(n-1, cnt+1);

    return 1;
}

int main(void) {
    int N;
    scanf("%d", &N);

    dp(N, 0);

    printf("%d\n", visit[1]);

}
