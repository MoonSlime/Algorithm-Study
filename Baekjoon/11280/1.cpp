/**
 * 2-SAT 연습문제.
 * 우선 해설보지않고 풀어보자.=> 실패....
 *
 * 교집합 = 논리곱. (두개모두 참인경우에만 참)
 * 합집합 = 논리합. (둘중하나만 참인경우 참):
 */

#include <stdio.h>
#include <math.h>

using namespace std;

int N,M;

int main(void) {
    int answer=0;

    scanf("%d %d", &N, &M);

    int x, y;
    int i;
    for (i=0; i<M; ++i) {
        scanf("%d %d", &x, &y);

        if (fabs(x)!= fabs(y)) {
            answer=1;
        }
        else if (x*y>0)
    }

    printf("%d\n", answer);

    return 0;
}
