#include <cstdio>

#define MAX 10001

using namespace std;

int top=0, st[MAX];

int main(void) {

    int x;
    while (true) {
        if (scanf("%d", &x)==EOF)break;

//        if (x==-1)break;
            
        if (top==0)st[++top]=x;
        else {
            while (top>=2 && st[top] < x && st[top-1] < x) {
                //printf("top=%d -> [%d]\n", top, st[top--]);
                printf("%d\n", st[top--]);
            }
            st[++top] = x;
        }
//        printf("========\n");
    }

    while (top>0) {
        printf("%d\n", st[top--]);
    }

    return 0;
}
