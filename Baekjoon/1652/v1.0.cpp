#include <cstdio>

#define MAX 101

using namespace std;

int N, h_cnt, v_cnt, room[MAX][MAX];
int horizontal[MAX],vertical[MAX];

int main(void) {
    scanf("%d", &N);

    for (int h=0; h<N; ++h) {
        for (int v=0; v<N; ++v) {
            char c;
            scanf("%c", &c);
            if (c=='.') {
                room[h][v] = 0;
            }
            else {
                room[h][v] = 1;
            }
        }
    }

    h_cnt=0;
    for (int h=0; h<N; ++h) {
        int cnt=0;
        for (int v=0; v<N; ++v) {
            if (room[h][v]==1)cnt=0;
            else if (++cnt==2) {
                //horizontal[h]=1;
                h_cnt++;
                break;
            }
        }
    }

    v_cnt=0;
    for (int v=0; v<N; ++v) {
        int cnt=0;
        for (int h=0; h<N; ++h) {
            if (room[h][v]==1)cnt=0;
            else if (++cnt==2) {
                //vertical[v]=1;
                v_cnt++;
                break;
            }
        }
    }

    printf("%d %d\n", h_cnt, v_cnt);
}
