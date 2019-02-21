/** 
 * 변경되는 사항
 * 1. 한줄에 누울자리가 한개 뿐만아니라, 장애물로 막혀있을 경우 여러개의 누울 자리 가능.
 * 2. 입력의 경우 공백을 제대로 처리하지 못하였음. 
 */
#include <cstdio>

#define MAX 101

using namespace std;

int N, H, V, room[MAX][MAX];

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

    H=V=0;
    for (int i=0; i<N; ++i) {
        int h_cnt=0;
        int v_cnt=0;
        for (int j=0; j<N; ++j) {
            if (room[i][j]==1)h_cnt=0;
            else if (++h_cnt==2)H++;

            if (room[j][i]==1)v_cnt=0;
            else if (++v_cnt==2)V++;
        }
    }

    printf("%d %d", H, V);
}
