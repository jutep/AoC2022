a= """#innputstring"""
a = a.split("\n")
a = [x.split(" ") for x in a]

X = 1
loop = 0
sig_sum = 0
crt = [["."]*40,["."]*40,["."]*40,["."]*40,["."]*40,["."]*40]

for i in a:
        for j in range(2):
            loop += 1
            if loop in [20, 60, 100, 140, 180, 220]: sig_sum += loop * X
            if (loop - (loop // 40) * 40)-1 in [X - 1, X, X + 1]: crt[loop // 40][(loop - (loop // 40) * 40)-1] = "#"
            if i[0] == "noop":break
            elif j == 1: X += int(i[1])



print(sig_sum)
for i in crt:
    print(i)
