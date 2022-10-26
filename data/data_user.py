import json
import random
import gzip
import sys
import os

userthreshold = int(sys.argv[1]) #first param to control user size
threshold = int(sys.argv[2]) #second param to control item size
edges_num = int(sys.argv[3]) #third param, edge number
dataset = sys.argv[4] #dataset path
outputFile = sys.argv[5] #outputfile name
rumorFile = sys.argv[6] #rumorfile name

random.seed(20010312)

def parse(path):
    g = gzip.open(path, 'rb')
    for l in g:
        yield json.loads(l.decode())


def get_time_stamp(tmStr):
    gomma = tmStr.index(',')
    return int(tmStr[gomma+2:]+tmStr[0:2]+tmStr[3:gomma])


userID = {}
idUser = []
userCount = 0
reviewCount = 0

cascades = {}
usercnt = {}
for d in parse(dataset):
    reviewCount = reviewCount + 1
    if d['reviewerID'] in usercnt:
        usercnt[d['reviewerID']] = usercnt[d['reviewerID']] + 1
    else:
        usercnt[d['reviewerID']] = 1

for d in parse(dataset):
    if usercnt[d['reviewerID']] < userthreshold:
        continue
    if d['asin'] in cascades:
        cascades[d['asin']].append((d['reviewerID'], get_time_stamp(d['reviewTime'])))
    else:
        cascades[d['asin']] = []
        cascades[d['asin']].append((d['reviewerID'], get_time_stamp(d['reviewTime'])))

if not os.path.exists(os.path.dirname(outputFile)):
    os.makedirs(os.path.dirname(outputFile))

fi = open(outputFile, "w")

itemCount  =0
item_list = []

for key, cascade_list in cascades.items():
    if len(cascade_list) >= threshold:
        item_list.append(key)
        itemCount = itemCount+1
        for val in cascade_list:
            if val[0] not in userID:
                idUser.append(val[0])
                userID[val[0]] = userCount
                userCount = userCount + 1


cascade_count = 0
cascade_pair_count = {}
for cascade_list in cascades.values():
    if len(cascade_list) >= threshold:
        cascade_list.sort(key=lambda x:x[1])
        i = 0
        while i < len(cascade_list):
            j = i + 1
            while j < len(cascade_list):
                user_pair = (userID[cascade_list[i][0]], userID[cascade_list[j][0]])
                if user_pair not in cascade_pair_count:
                    cascade_pair_count[user_pair] = 1
                    cascade_count = cascade_count + 1
                else:
                    cascade_pair_count[user_pair] = cascade_pair_count[user_pair] + 1
                j = j + 1
            i = i + 1

if cascade_count < edges_num:
    edges_num = cascade_count

pairs = {}
max_val = 0
for key, val in cascade_pair_count.items():
    if val > max_val:
        max_val = val
    if val in pairs:
        pairs[val].append(key)
    else:
        pairs[val] = [key]

for key in pairs:
    random.shuffle(pairs[key])

all_pairs = []

while max_val > 0:
    if max_val in pairs:
        if len(pairs[max_val]) < edges_num:
            edges_num = edges_num - len(pairs[max_val])
            all_pairs = all_pairs + pairs[max_val]
        else:
            all_pairs = all_pairs + pairs[max_val][0:edges_num]
            break
    max_val = max_val - 1

fi.write("%d %d\n" % (userCount, len(all_pairs)))

deg=[0]*userCount
userEdgeCount = 0
for pair in all_pairs:
    fi.write("%d %d\n" % (pair[0], pair[1]))
    deg[pair[0]]+=1
    userEdgeCount = userEdgeCount + 1


fi.write("0\n")
for i in range(0,userCount):
    fi.write("0 0 ")

fi.close()


print("review Count:",reviewCount)
print("user num:", userCount, " user edge num:", userEdgeCount)

selected = []
for i in range(0,userCount):
    selected.append((i,deg[i]))

selected.sort(key=lambda a:-a[1])

with open(rumorFile, "w") as file:
    for i in range(0,20):
        x = selected[random.randint(0,100)][0]
        print(deg[x])
        file.write(f"{x} ")
    file.close()

