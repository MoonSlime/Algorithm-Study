#include <stdio.h>
 
int N;
long long M;    //총예산
int yesan[10010];
int max;
 
void inputData()
{
        scanf("%d", &N);
        for (register int i = 0; i < N; i++)
            {
                    scanf("%d", &yesan[i]);
                    if (max < yesan[i]) max = yesan[i];
                }
        scanf("%lld", &M);
}
 
int check(int target)
{
        long long sum = 0;
        for (register int i = 0; i < N; i++)
            {
                    if (yesan[i] > target) sum += target;
                    else sum += yesan[i];
                }
        
        if (sum <= M) return 1;
        return 0;
}
 
int binarySearch()
{
        int start, end, target;
        start = 0;
        end = max;
        int sol = 0;
        
        while (start <= end)
            {
                    target = (start + end) / 2;
             
                    if (check(target))
                        {
                                sol = target;
                                start = target + 1;
                            }
                    else
                        {
                                end = target - 1; 
                            }
                }
        return sol;
}
 
int main()
{
        inputData();
        printf("%d\n", binarySearch());
     
        return 0;
}
