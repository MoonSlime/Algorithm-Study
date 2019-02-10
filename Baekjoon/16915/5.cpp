/**
 *  3.cpp -> 5.cpp => 시간초과!!
 */


#include <stdio.h>
#include <iostream>
#include <vector>

#define MAX 100001

using namespace std;

int N,M;
int room[MAX], btn_used[MAX];
vector<int> rooms_btn[MAX];//rooms_btn[x].size() is always 2.

int dfs(int idx) {
    if (idx == N+1)return 1;

    vector<int> cur = rooms_btn[idx];

    bool x,y;
    if (room[idx]==1) {
        //XX
        x=y=false;
        if (btn_used[cur[0]]<1 && btn_used[cur[1]]<1) {
            if (btn_used[cur[0]]==0) {
                btn_used[cur[0]]=-1;
                x=true;
            }
            if (btn_used[cur[1]]==0) {
                btn_used[cur[1]]=-1;
                y=true;
            }
            
            if(dfs(idx+1))return 1;
        
            if (x)btn_used[cur[0]]=0;
            if (y)btn_used[cur[1]]=0;
        }

        //OO
        x=y=false;
        if (btn_used[cur[0]]==-1 || btn_used[cur[1]]==-1)return 0;

        if (btn_used[cur[0]]==0) {
            btn_used[cur[0]]=1;
            x=true;
        }
        if (btn_used[cur[1]]==0) {
            btn_used[cur[1]]=1;
            y=true;
        }

        if (dfs(idx+1))return 1;

        if (x)btn_used[cur[0]]=0;
        if (y)btn_used[cur[1]]=0;
    }
    else if (room[idx]==0) {
        //OX
        x=y=false;
        if (btn_used[cur[0]]>-1 && btn_used[cur[1]]<1) {
            if (btn_used[cur[0]]==0) {
                btn_used[cur[0]]=1;
                x=true;
            }
            if (btn_used[cur[1]]==0) {
                btn_used[cur[1]]=-1;
                y=true;
            }
            
            if (dfs(idx+1))return 1;
            
            if (x)btn_used[cur[0]]=0;
            if (y)btn_used[cur[1]]=0;
        }

        //XO
        x=y=false;
        if (btn_used[cur[0]]<1 && btn_used[cur[1]]>-1) {
            if (btn_used[cur[0]]==0) {
                btn_used[cur[0]]=-1;
                x=true;
            }
            if (btn_used[cur[1]]==0) {
                btn_used[cur[1]]=1;
                y=true;
            }
            if (dfs(idx+1))return 1;
            
            if (x)btn_used[cur[0]]=0;
            if (y)btn_used[cur[1]]=0;
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
            //btn[i].push_back(b);
            rooms_btn[b].push_back(i);
        }
    }

    printf("%d\n", dfs(1));

    return 0;
}
