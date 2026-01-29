
import sys
sys.setrecursionlimit(10**6) 
input = sys.stdin.readline

def dfs(y:int,x:int):
    if 0 > y or 0 > x or width <= x or arr[y][x] == '1':
        return False
    
    if y == height-1:
        return True

    arr[y][x] = '1'
   
    if dfs(y+1,x) or dfs(y-1,x) or dfs(y,x+1) or dfs(y,x-1): # 좌우상하중에서 하나만 도달해도 성공
        return True
    
    return False

height,width = map(int, input().split())
arr = []
result = False 
for i in range(height):
    arr.append(list(input()))

for idx in range(width):
    if arr[0][idx] == '0':
        if dfs(0,idx):
            result = True
            break

if result:
    print("YES")
else:
    print("NO")