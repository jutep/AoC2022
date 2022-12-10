a="""#inputstring"""
s = (0,0)
H = (0,0)
T = (0,0)

tail_steps = [(0,0)]

a = a.split("\n")
for i in range(len(a)):
    a[i] = [a[i][0], int(a[i][2:])]
sol = [(0,0)]
for move in a:
    if move[0] == "L" or move[0] == "R":
        val = -1
        if move[0] == "R": val = 1
        for j in range(int(move[1])):
            H = (H[0]+val, H[1])
            if abs(T[0]-H[0]) == 2:
                if T[1] == H[1]:
                    T = (T[0]+val, T[1])
                elif T[1] < H[1]:
                    T = (T[0]+val, T[1]+1)
                else:
                    T = (T[0]+val, T[1]-1)
            sol.append(T)
    elif move[0] == "U" or move[0] == "D":
        val = -1
        if move[0] == "D": val = 1
        for j in range(int(move[1])):
            H = (H[0], H[1]+val)
            if abs(T[1]-H[1]) == 2:
                if T[0] == H[0]:
                    T = (T[0], T[1]+val)
                elif T[0] < H[0]:
                    T = (T[0]+1, T[1]+val)
                else:
                    T = (T[0]-1, T[1]+val)
            sol.append(T)

print(len(set(sol)))

def d9_2_fuckyou(H,T):
    if T[0] - H[0] == 2 and T[1]-H[1] == 2: # bot left
        return (T[0]-1, T[1]-1)
    if T[0] - H[0] == 2 and T[1] - H[1] == -2: # topleft
        return (T[0] - 1, T[1] +1)
    if T[0] - H[0] == -2 and T[1] - H[1] == 2: # bot right
        return (T[0] + 1, T[1] - 1)
    if T[0] - H[0] == -2 and T[1] - H[1] == -2: # top right
        return (T[0] + 1, T[1] + 1)
    if T[0]-H[0] == 2: # left
        if T[1] == H[1]:
            return (T[0]-1, T[1])
        elif T[1] < H[1]:
            return (T[0]-1, T[1]+1)
        else:
            return (T[0]-1, T[1]-1)
    if T[1]-H[1] == 2: # down
        if T[0] == H[0]:
            return (T[0], T[1]-1)
        elif T[0] < H[0]:
            return (T[0]+1, T[1]-1)
        else:
            return (T[0]-1, T[1]-1)
    if T[0]-H[0] == -2: # right
        if T[1] == H[1]:
            return (T[0]+1, T[1])
        elif T[1] < H[1]:
            return (T[0]+1, T[1]+1)
        else:
            return (T[0]+1, T[1]-1)
    if T[1]-H[1] == -2: # up
        if T[0] == H[0]:
            return (T[0], T[1]+1)
        elif T[0] < H[0]:
            return (T[0]+1, T[1]+1)
        else:
            return (T[0]-1, T[1]+1)
    return T

def d9_2_head(head,d):
    val = -1
    if d == "L" or d == "R":
        if d == "R":
            val = 1
        head = (head[0]+val,head[1])
    else:
        if d == "U":
            val = 1
        head = (head[0],head[1]+val)
    return head

visknots = []
H = (0,0)
rope = [(0,0)]*9

for i in a:
    for j in range(i[1]):
        H = d9_2_head(H, i[0])
        rope[0] = d9_2_fuckyou(H, rope[0])
        for k in range(len(rope)-1):
            rope[k+1] = d9_2_fuckyou(rope[k], rope[k+1])
            if k == 7:
                visknots.append(rope[k+1])

print(len(set(visknots)))
