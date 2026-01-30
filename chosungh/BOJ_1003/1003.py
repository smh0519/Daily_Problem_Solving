# ------ 첫 번째 방식 ------
import sys
input = sys.stdin.readline

# 피보나치 함수
def fibonaci(num):
    dp = [[1, 0], [0, 1]]
    count_0 = 0
    count_1 = 0

    for i in range(2, num + 1):
        # 0이 몇번 나왔는지 더하기
        count_0 = dp[i-1][0] + dp[i-2][0]
        # 1이 몇번 나왔는지 더하기
        count_1 = dp[i-1][1] + dp[i-2][1]

        # 계산한 0과 1의 갯수를 append
        dp.append([count_0, count_1])

    # 출력문
    print(f'{dp[num][0]} {dp[num][1]}')

n = int(input())

for i in range(n):
    t = int(input())
    fibonaci(t)

# ------ 두 번째 방식 ------

import sys
input = sys.stdin.readline

# dp 배열을 fibonaci() 밖으로 꺼내어 함수를 호출할 때마다 초기화되던 것을 방지
dp = [[1, 0], [0, 1]]

def fibonaci(num):
    
    # num이 dp배열의 크기보다 작으면 이미 계산되었을 것
    if num >= len(dp): 
        for i in range(len(dp), num + 1):
            # 0이 몇번 나왔는지 더하기
            count_0 = dp[i-1][0] + dp[i-2][0]
            # 1이 몇번 나왔는지 더하기
            count_1 = dp[i-1][1] + dp[i-2][1]
            
            # 계산한 0과 1의 갯수를 append
            dp.append([count_0, count_1])

    # 출력문
    print(f'{dp[num][0]} {dp[num][1]}')

n = int(input())

for i in range(n):
    t = int(input())
    fibonaci(t)