a="""#inputstring"""
vitr = []

def p1():
    for i in range(1, len(a) - 1):
        for j in range(1, len(a[0]) - 1):
            el = int(a[i][j])
            s1 = max([int(x) for x in a[i][:j]])
            s2 = max([int(x) for x in a[i][j + 1:]])
            s3 = max([int(a[x][j]) for x in range(0, i)])
            s4 = max([int(a[x][j]) for x in range(i + 1, len(a))])
            if el > min(s1, s2, s3, s4):
                vitr.append(el)

    print(len(vitr) + 2 * len(a) + 2 * len(a[0]) - 4)

p1()
# this is part 2
def w(li):
    if not li: return 0
    if -1 in li: return li.index(-1) +1
    else: return len(li)

print(max([max(li) for li in [[(w(list(map(lambda x: -1 if x >= int(a[i][j]) else x, reversed([int(x) for x in a[i][:j]]))))
    * w(list(map(lambda x: -1 if x >= int(a[i][j]) else x, [int(x) for x in a[i][j + 1:]])))
    * w(list(map(lambda x: -1 if x >= int(a[i][j]) else x, [int(a[x][j]) for x in range(i-1, -1, -1)])))
    * w(list(map(lambda x: -1 if x >= int(a[i][j]) else x, [int(a[x][j]) for x in range(i + 1, len(a))]))))
    for j in range(len(a[0]) - 1)]
    for i in range(len(a))]]))
