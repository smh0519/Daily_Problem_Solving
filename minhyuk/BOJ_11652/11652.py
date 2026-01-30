number = int(input())
cards = []

## 입력 받는 부분 ##
for i in range(number):
    cards.append(int(input()))
cards.sort()


## 코드 로직 ##
# max_val: 가장 빈도수가 높은 카드 값
# max_cnt: 그 카드의 빈도수
# current_cnt: 현재 확인 중인 카드의 연속된 개수
max_val = cards[0]
max_cnt = 1
current_cnt = 1
for i in range(1, number):
    if cards[i] == cards[i-1]:
        current_cnt += 1
    else:
        current_cnt = 1

    if current_cnt > max_cnt:
        max_cnt = current_cnt
        max_val = cards[i]
        
print(max_val)