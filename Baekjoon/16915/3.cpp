/**
 *
 *dfs()로 풀어보려 함.
 *-> 풀어보다가 queue를 이용하면 더 좋은 속도로 끝낼수 있을것 같아서
 * queue를 이용하는 4.cpp를 먼저 코딩하게 됨.(는 해보려했는데 생각이 안남.)
 *
 * 확실히 dfs는아니고 추가적인 조건이 필요.
 */


#include <stdio.h>
#include <iostream>
#include <vector>

#define MAX 100001

using namespace std;

int N,M;
int room[MAX], btn_used[MAX];
vector<int> btn[MAX], rooms_btn[MAX];//rooms_btn[x].size() is always 2.

void use(int btn_num) {
    vector<int> cur = btn[btn_num];
    for (int i=0; i<cur.size(); ++i) {
        room[cur[i]]++;
        room[cur[i]]%=2;
    }
}

int dfs(int idx) {
    if (idx == N+1)return 1;

    vector<int> cur = rooms_btn[idx];

    if (room[idx]==1) {
        //XX
        if(dfs(idx+1))return 1;

        //OO
        if (btn_used[cur[0]] + btn_used[cur[1]] == 0) {
            btn_used[cur[0]]=1;
            btn_used[cur[1]]=1;
            use(cur[0]);
            use(cur[1]);
            if(dfs(idx+1))return 1;
            btn_used[cur[0]]=0;
            btn_used[cur[1]]=0;
            use(cur[0]);
            use(cur[1]);
        }

    }
    else if (room[idx]==0) {
        //OX
        if (btn_used[cur[0]]==0) {
            btn_used[cur[0]]=1;
            use(cur[0]);
            if(dfs(idx+1))return 1;
            btn_used[cur[0]]=0;
            use(cur[0]);
        }

        //XO
        if (btn_used[cur[1]]==0) {
            btn_used[cur[1]]=1;
            use(cur[1]);
            if(dfs(idx+1))return 1;
            btn_used[cur[1]]=0;
            use(cur[1]);
        }

    }

    return 0;
}

int main() {
    //Input : N,M
    scanf("%d %d", &N, &M);

    //Input : room state
    for (int i=1; i<=N; ++i) {
        scanf("%d", &room[i]);
    }

    //Input : switch(btn) connected room.
    for (int i=1; i<=M; ++i) {
        int a;
        scanf("%d", &a);
    
        int b;
        while(a--) {
            scanf("%d", &b);
            btn[i].push_back(b);
            rooms_btn[b].push_back(i);
        }
    }

    printf("%d\n", dfs(1));

    return 0;
}
