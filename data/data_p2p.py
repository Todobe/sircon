import random
import numpy as np
from scipy import linalg


f = open("Wiki-Vote.txt")
nodeCount=0

edges = []

edgeCount = 0

line=f.readline()
while line:
    ls=line.split('\t')
    u,v=int(ls[0]),int(ls[1])
    edges.append((u,v))
    edges.append((v,u))
    nodeCount=max(nodeCount,max(u,v))
    edgeCount+=1
    edgeCount+=1
    line=f.readline()

nodeCount+=1
mat=[[0]*nodeCount]*nodeCount
for edge in edges:
    mat[edge[0]][edge[1]]=1
    mat[edge[1]][edge[0]]=1

deg = [0]*nodeCount
with open("wiki.txt","w") as file:
    file.write(f"{nodeCount} {edgeCount}\n")
    for edge in edges:
        deg[edge[0]] += 1
        deg[edge[1]] += 1
        file.write(f"{edge[0]} {edge[1]}\n")

    A = np.array(mat)
    (eva,evt) = linalg.eigh(A)
    file.write(f"{eva[-1]}\n")
    for val in evt[-1]:
        file.write(f"{val} ")
    file.write("\n")
    file.close()

selected = []
for i in range(0,nodeCount):
    selected.append((i,deg[i]))

selected.sort(key=lambda a:-a[1])

with open("wiki_rumor.txt","w") as file:
    for i in range(0,20):
        x = selected[random.randint(0,500)][0]
        print(deg[x])
        file.write(f"{x} ")
    file.close()

