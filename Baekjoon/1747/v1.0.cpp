#include <cstdio>
#include <vector>

using namespace std;

int N; //1 <= N <= 1,000,000
vector<int> prime;

//check palindrome.
bool check(int x, int rvs) {
    int tmp;
    for (tmp=10,rvs/=10; tmp<rvs;tmp*=10,rvs/=10) {
        if (x/rvs != x%tmp)return false;
        x = (x%rvs) - x%tmp;
    }

    return true;
}

int main(void) {
    scanf("%d", &N);

    int cur = 1;
    int rvs = 1;//reverse
    while (++cur) {
        bool is_prime = true;
        for (int elem : prime) {
            if (cur % elem==0) {
                is_prime=false;
                break;
            }
        }

        if (is_prime)prime.push_back(cur);
        else continue;

        if (cur > rvs)rvs*=10;

        if (cur >= N && check(cur, rvs)) {
            printf("%d\n", cur);
            break;
        }
    }

    return 0;
}
