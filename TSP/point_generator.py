from random import randint
N = int(input("点数:"))
MAX_X = 10
point = [(randint(0,MAX_X), randint(0,MAX_X)) for _ in range(N)]
output_file = "in.txt"
with open(output_file, "w") as f:
    f.write("{}\n".format(N))
    for x,y in point:
        f.write("{} {}\n".format(x,y))
