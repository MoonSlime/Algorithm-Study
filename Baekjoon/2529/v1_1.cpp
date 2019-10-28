#include <cstdio>
#include <vector>


using namespace std;

bool used[11];
char arr[11];
int K;

vector<int> q, answer_max, answer_min;

bool solve_min(int cnt) {
    if (cnt==K+1) {
        return true;
    }

    bool ret=false;
    for (int i=0; i<=9; ++i) {
        if (used[i])continue;

        answer_min.push_back(i);
        used[i]=true;
        if (cnt==0) {
            if (solve_min(cnt+1))return true;
        }
        else {
            if (arr[cnt-1]=='<' && answer_min[cnt-1] < i) {
                if(solve_min(cnt+1))return true;
            }
            else if (arr[cnt-1]=='>' && answer_min[cnt-1] > i) {
                if(solve_min(cnt+1))return true;
            }
        }
        used[i]=false;
        answer_min.pop_back();
    }

    return false;
}

bool solve_max(int cnt) {
    if (cnt==K+1) {
        return true;
    }

    bool ret=false;
    for (int i=9; i>=0; --i) {
        if (used[i])continue;
        
        answer_max.push_back(i);
        used[i]=true;
        if (cnt==0) {
            if (solve_max(cnt+1))return true;
        }
        else {
            if (arr[cnt-1]=='<' && answer_max[cnt-1] < i) {
                if(solve_max(cnt+1))return true;
            }
            else if (arr[cnt-1]=='>' && answer_max[cnt-1] > i) {
                if(solve_max(cnt+1))return true;
            }
        }
        used[i]=false;
        answer_max.pop_back();
    }

    return false;
}

int main(void) {
    scanf("%d", &K);


    for (int k=0; k<K; ++k) {
        getchar();
        scanf("%c", &arr[k]);
    }


    solve_max(0);
    
    for (int i=0; i<10; ++i) {
        used[i]=false;
    }
    solve_min(0);

    for (int i=0; i<=K; ++i) {
        printf("%d", answer_max[i]);
    }
    printf("\n");
    for (int i=0; i<=K; ++i) {
        printf("%d", answer_min[i]);
    }

}
