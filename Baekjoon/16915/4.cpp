#include <stdio.h>
#include <iostream>
#include <vector>

#define MAX 100001

using namespace std;

int N,M;
int room[MAX], visit[MAX], vc=1, btn_used[MAX];
vector<int> btn[MAX], rooms_btn[MAX];//rooms_btn[x].size() is always 2

int match(int idx) {
    if (room[idx]==1)return 1;
    if (visit[idx]==vc)return 0;
    visit[idx]=vc;

    vector<int> cur = rooms_btn[idx];
    for (int i=0; i<cur.size(); ++i) {
        if (btn_used[cur[i]]==0) {
            btn_used[cur[i]]=1;

            int cur_btn=cur[i];
            for (int i=0; i<btn[cur_btn].size(); ++i) {
                room[btn[cur_btn][i]]+=1;
                room[btn[cur_btn][i]]%=2;
            }

            int ret=0;
            for (int i=0; i<btn[cur_btn].size(); ++i) {
                if (btn[cur_btn][i]==idx)continue;
                if((ret = match(btn[cur_btn][i]))==0)break;
            }

            if (ret==0) {
                for (int i=0; i<btn[cur_btn].size(); ++i) {
                    room[btn[cur_btn][i]]+=1;
                    room[btn[cur_btn][i]]%=2;
                }
                btn_used[cur[i]]=0;
            }
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

    for (int i=1; i<=N; ++i) {
        vc++;
        if (match(i)==0){
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");
    return 0;
}
