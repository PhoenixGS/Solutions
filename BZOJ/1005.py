n = input()
ans = 1
mi = [1]
for i in range(1, n - 1):
    mi = mi + [mi[i - 1] * i]
#print mi
ans = mi[n - 2]
cnt = 0
s = n - 2
for i in range(0, n):
    x = input()
    if x != -1:
        ans = ans / mi[x - 1]
        s = s - (x - 1)
    else:
        cnt = cnt + 1
#print s, cnt
ans = ans / mi[s]
for i in range(0, s):
    ans = ans * cnt
print ans
