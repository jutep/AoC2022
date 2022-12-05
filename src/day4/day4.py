
f = open("input_day4.txt", "r")
lines = f.readlines()

arr = []

for line in lines:
    if (line != "\n"):
        t = line.split(',')
        arr.append([int(t[0].split('-')[0]),
                    int(t[0].split('-')[1]),
                    int(t[1].split('-')[0]),
                    int(t[1].split('-')[1])])
        
sum = 0
oao = 0

for s1, e1, s2, e2 in arr:
    if ((s1 <= s2) and (e1 >= e2)):
        sum += 1
        oao += 1
    elif ((s1 >= s2) and (e1 <= e2)): 
        sum += 1
        oao += 1
    elif ((s1 <= e2) and (s1 >= s2)):
        oao += 1
    elif ((s2 <= e1) and (s2 >= s1)):
        oao += 1

print("part 1: ", sum)
print("part2: ", oao)
f.close()
