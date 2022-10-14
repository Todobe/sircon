#!/bin/bash

#video game
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Deg -k 0 -MC 1000 -o video.txt

./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Imm  -MC 1000 -theta 10000 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Deg  -MC 1000 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg EdgeDel  -MC 1000 -edge 7998 -o video.txt -kdetail 1


./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Imm  -MC 10000 -theta 10000 -delta 0.8 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Deg  -MC 1000 -delta 0.8 -o video.txt -kdetail 1
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg EdgeDel  -MC 1000 -delta 0.8 -edge 7998 -o video.txt -kdetail 1


#p2p
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Deg -k 0 -MC 1000 -o p2p_result.txt

./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Imm  -MC 1000 -theta 10000 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Deg  -MC 1000 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg EdgeDel  -MC 1000 -edge 7412 -o p2p_result.txt -kdetail 1


./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Imm  -MC 1000 -theta 10000 -delta 0.8 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Deg  -MC 1000 -delta 0.8 -o p2p_result.txt -kdetail 1
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg EdgeDel  -MC 1000 -delta 0.8 -edge 7412 -o p2p_result.txt -kdetail 1


#wiki

./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Deg -k 0 -MC 1000 -o wiki_result.txt

./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Imm  -MC 1000 -theta 10000 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Deg  -MC 1000 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg EdgeDel  -MC 1000 -edge 20737 -o wiki_result.txt -kdetail 1


./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Imm  -MC 1000 -theta 10000 -delta 0.8 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Deg  -MC 1000 -delta 0.8 -o wiki_result.txt -kdetail 1
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg EdgeDel  -MC 1000 -delta 0.8 -edge 20737 -o wiki_result.txt -kdetail 1



#####T=4
#video game

./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o video.txt -T 4
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o video.txt -T 4
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -o video.txt -T 4
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -o video.txt -T 4

./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o video.txt -T 4
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o video.txt -T 4
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o video.txt -T 4
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o video.txt -T 4

#p2p

./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o p2p_result.txt -T 4
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o p2p_result.txt -T 4
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -o p2p_result.txt -T 4
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -o p2p_result.txt -T 4


./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -T 4
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -T 4
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o p2p_result.txt -T 4
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o p2p_result.txt -T 4


#wiki


./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o wiki_result.txt -T 4
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o wiki_result.txt -T 4
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -o wiki_result.txt -T 4
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -o wiki_result.txt -T 4


./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -T 4
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -T 4
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o wiki_result.txt -T 4
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o wiki_result.txt -T 4

#####T=6
#video game

./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o video.txt -T 6
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o video.txt -T 6
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -o video.txt -T 6
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -o video.txt -T 6


./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o video.txt -T 6
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o video.txt -T 6
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o video.txt -T 6
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o video.txt -T 6


#p2p

./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o p2p_result.txt -T 6
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o p2p_result.txt -T 6
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -o p2p_result.txt -T 6
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -o p2p_result.txt -T 6


./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -T 6
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -T 6
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o p2p_result.txt -T 6
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o p2p_result.txt -T 6

#wiki

./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Deg -k 0 -MC 1000 -o wiki_result.txt -T 6

./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o wiki_result.txt -T 6
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o wiki_result.txt -T 6
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -o wiki_result.txt -T 6
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -o wiki_result.txt -T 6


./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -T 6
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -T 6
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o wiki_result.txt -T 6
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o wiki_result.txt -T 6



#####T=8
#video game

./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o video.txt -T 8
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o video.txt -T 8
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -o video.txt -T 8
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -o video.txt -T 8


./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o video.txt -T 8
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o video.txt -T 8
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o video.txt -T 8
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o video.txt -T 8


#p2p

./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o p2p_result.txt -T 8
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o p2p_result.txt -T 8
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -o p2p_result.txt -T 8
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -o p2p_result.txt -T 8


./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -T 8
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -T 8
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o p2p_result.txt -T 8
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o p2p_result.txt -T 8


#wiki

./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o wiki_result.txt -T 8
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o wiki_result.txt -T 8
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -o wiki_result.txt -T 8
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -o wiki_result.txt -T 8


./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -T 8
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -T 8
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o wiki_result.txt -T 8
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o wiki_result.txt -T 8


#####T=10
#video game

./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o video.txt -T 10
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o video.txt -T 10
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -o video.txt -T 10
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -o video.txt -T 10


./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o video.txt -T 10
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o video.txt -T 10
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o video.txt -T 10
./sircon ./data/Video_game_network.txt  -rs ./data/rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o video.txt -T 10


#p2p
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o p2p_result.txt -T 10
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o p2p_result.txt -T 10
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -o p2p_result.txt -T 10
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -o p2p_result.txt -T 10


./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -T 10
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o p2p_result.txt -T 10
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o p2p_result.txt -T 10
./sircon ./data/p2p.txt  -rs ./data/p2p_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o p2p_result.txt -T 10


#wiki

./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -theta 1 -o wiki_result.txt -T 10
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -theta 1 -o wiki_result.txt -T 10
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -o wiki_result.txt -T 10
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -o wiki_result.txt -T 10


./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Eig  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -T 10
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Ris-Deg  -MC 1000 -delta 0.8 -theta 1 -o wiki_result.txt -T 10
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Eig  -MC 1000 -delta 0.8 -o wiki_result.txt -T 10
./sircon ./data/wiki.txt  -rs ./data/wiki_rumor.txt -alg Lon-Deg  -MC 1000 -delta 0.8 -o wiki_result.txt -T 10
