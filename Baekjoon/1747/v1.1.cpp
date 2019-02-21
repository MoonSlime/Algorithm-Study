#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int N; //1 <= N <= 1,000,000
vector<int> prime;

//check palindrome.
bool check(int x) {
    string str = to_string(x);

    int len = str.length();
    for (int i=0; i<len/2; ++i) {
        if (str[i] != str[len-i-1])return false;
    }

    return true;
}

int main(void) {
    scanf("%d", &N);

    int cur = 1;
    while (++cur < 150) {
        bool is_prime = true;
        for (int elem : prime) {
            if (cur % elem==0) {
                is_prime=false;
                break;
            }
        }

        if (is_prime)prime.push_back(cur);
        else continue;

        if (cur >= N && check(cur)) {
            printf("%d\n", cur);
            break;
        }
    }

    return 0;
}
