#include <cstdio>

int arr[12][12][12][12];

void init() {
}

int C(int n, int c) {
    int result=0;

    int i;
    for (i=0; i<c; ++i) {
        result = result * (n-i) / (i+1);
    }
    return result;
}

int dp(int n, int a, int b, int c) {
    if (n==0) {
        return 1;
    }
    else if (arr[n][a][b][c]>0) {
        return arr[n][a][b][c];
    }
    
    arr[n][a][b][c]=0;

    if (n>=3) {
        arr[n][a][b][c] += dp(n-3, a, b, c+1);
    }
    if (n>=2) {
        arr[n][a][b][c] += dp(n-2, a, b+1, c);
    }
    if (n>=1) {
        arr[n][a][b][c] += dp(n-1, a+1, b, c);
    }

    return arr[n][a][b][c];
}

int main(void) {
    int T;
    scanf("%d", &T);

    int t;
    for (t=0; t<T; ++t) {
        init();
        int N;
        scanf("%d", &N);
        printf("%d\n", dp(N, 0, 0, 0));
    }
}
