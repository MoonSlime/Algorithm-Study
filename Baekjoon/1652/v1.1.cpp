/** 
 * 변경되는 사항
 * 1. 한줄에 누울자리가 한개 뿐만아니라, 장애물로 막혀있을 경우 여러개의 누울 자리 가능.
 * 2. 입력의 경우 공백을 제대로 처리하지 못하였음. 
 */
#include <cstdio>

#define MAX 101

using namespace std;

int N, h_cnt, v_cnt, room[MAX][MAX];

int main(void) {
    scanf("%d", &N);

    for (int h=0; h<N; ++h) {
        for (int v=0; v<N; ++v) {
            char c;
            scanf("%c", &c);
            if (c=='.') {
                room[h][v] = 0;
            }
            else if (c=='X'){
                room[h][v] = 1;
            }
            else v--;
        }
    }
/**
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            printf("%d ", room[i][j]);
        }
        printf("\n");
    }
**/
    h_cnt=0;
    for (int h=0; h<N; ++h) {
        int cnt=0;
        for (int v=0; v<N; ++v) {
            if (room[h][v]==1)cnt=0;
            else if (++cnt==2)h_cnt++;
        }
    }

    v_cnt=0;
    for (int v=0; v<N; ++v) {
        int cnt=0;
        for (int h=0; h<N; ++h) {
            if (room[h][v]==1)cnt=0;
            else if (++cnt==2)v_cnt++;
        }
    }

    printf("%d %d", h_cnt, v_cnt);
}
