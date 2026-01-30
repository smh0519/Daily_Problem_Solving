import sys
input = sys.stdin.readline
weight = [0] * 26 # 알파벳 가중치 구하는 배열
words = [] #단어들 저장 배열
n = int(input())
for i in range(n):
    words.append(input().strip())

for word in words:# 알파벳 가중치 구하기
    length = len(word)
    for i in range(len(word)):
        weight[ord(word[i]) - 65] += 10**(length - (i+1))


weight.sort(reverse=True)
result = 0
num = 9
for w in weight:
    if w == 0: break 
    result += w * num
    num -= 1
print(result)