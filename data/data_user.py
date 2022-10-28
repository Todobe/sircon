import json
import random
import gzip
import sys
import os
import argparse
import heapq
from collections import defaultdict

def parse(path):
    g = gzip.open(path, 'rb')
    for l in g:
        yield json.loads(l.decode())

def get_time_stamp(tmStr):
    gomma = tmStr.index(',')
    return int(tmStr[gomma+2:]+tmStr[0:2]+tmStr[3:gomma])

class P():
    def __init__(self,node1,node2,count):
        self.node1 = node1
        self.node2 = node2
        self.count = count
    def __lt__(self, other):
        if self.count<other.count:
            return True
        else:
            return False


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='dataGenerator')

    parser.add_argument('--data_path', default="Video_Games.json.gz", type=str, help='data path')
    parser.add_argument('--output_file', default="./network.txt", type=str, help='output file')
    parser.add_argument('--rumor_file', default="./rumor.txt", type=str, help='output file')
    parser.add_argument('--user_threshold', default=4, type=int, help='user threshold')
    parser.add_argument('--cascade_threshold', default=5, type=int, help='cascade threshold')
    parser.add_argument('--edge_num', default=500, type=int, help='edge_num')
    parser.add_argument('--max_deg', default=500, type=int, help='deg bound')
    args = parser.parse_args()

    random.seed(20010312)

    userID = {}
    idUser = []
    userCount = 0
    reviewCount = 0

    cascades = {}
    usercnt = {}
    for d in parse(args.data_path):
        reviewCount = reviewCount + 1
        if d['reviewerID'] in usercnt:
            usercnt[d['reviewerID']] = usercnt[d['reviewerID']] + 1
        else:
            usercnt[d['reviewerID']] = 1

    for d in parse(args.data_path):
        if usercnt[d['reviewerID']] < args.user_threshold:
            continue
        if d['asin'] in cascades:
            cascades[d['asin']].append((d['reviewerID'], get_time_stamp(d['reviewTime'])))
        else:
            cascades[d['asin']] = []
            cascades[d['asin']].append((d['reviewerID'], get_time_stamp(d['reviewTime'])))

    for key in cascades:
        cascades[key].sort(key=lambda x:x[1])

    user_buy = []
    for key, cascade_list in cascades.items():
        if len(cascade_list) >= args.cascade_threshold:
            for val in cascade_list:
                if val[0] not in userID:
                    idUser.append(val[0])
                    userID[val[0]] = userCount
                    userCount = userCount + 1
                    user_buy.append([])
                user_buy[userID[val[0]]].append(key)

    all_pairs = []
    for u in range(0,userCount):
        node_cnt=defaultdict(int)
        user_buy[u]=list(set(user_buy[u]))
        for item in user_buy[u]:
            flag=0
            for val in cascades[item]:
                if flag:
                    node_cnt[userID[val[0]]] += 1
                if userID[val[0]] == u:
                    flag =1

        tmpV=[]
        for key, val  in node_cnt.items():
            tmpV.append((key,val))
        tmpV.sort(key=lambda x:-x[1])
        for i in range(0,len(tmpV)):
            if i>= args.max_deg:
                break
            if tmpV[i][1]!=0:
                tmp = P(u,tmpV[i][0],tmpV[i][1])
                heapq.heappush(all_pairs,tmp)
                if len(all_pairs)>args.edge_num:
                    heapq.heappop(all_pairs)


    if not os.path.exists(os.path.dirname(args.output_file)):
        os.makedirs(os.path.dirname(args.output_file))
    deg=[0]*userCount
    with open(args.output_file, "w") as file:
        edgeCount=len(all_pairs)
        file.write(f"{userCount} {edgeCount}\n")
        for pair in all_pairs:
            file.write(f"{pair.node1} {pair.node2}\n")
            deg[pair.node1] += 1

        file.write("0\n")
        for i in range(0,userCount):
            file.write("0 0 ")

        file.close()


    print("review Count:",reviewCount)
    print("user num:", userCount, " user edge num:", len(all_pairs))

    selected = []
    for i in range(0,userCount):
        selected.append((i,deg[i]))

    selected.sort(key=lambda a:-a[1])

    if not os.path.exists(os.path.dirname(args.rumor_file)):
        os.makedirs(os.path.dirname(args.rumor_file))
    with open(args.rumor_file, "w") as file:
        for i in range(0,20):
            x = selected[random.randint(0,100)][0]
            print(deg[x])
            file.write(f"{x} ")
        file.close()

