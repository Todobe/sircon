#!/bin/bash


./sircon ./data/Video_game_network.txt -alg Ris-Eig
./sircon ./data/Video_game_network.txt -alg Ris-Deg
./sircon ./data/Video_game_network.txt -alg Lon-Eig
./sircon ./data/Video_game_network.txt -alg Lon-Deg
./sircon ./data/Video_game_network.txt -alg Imm
./sircon ./data/Video_game_network.txt -alg EdgeDel
./sircon ./data/Video_game_network.txt -alg Deg

./sircon ./data/Video_game_network.txt -alg Ris-Eig -k 0
./sircon ./data/Video_game_network.txt -alg Ris-Eig -r 0
./sircon ./data/Video_game_network.txt -alg Ris-Deg -r 0
./sircon ./data/Video_game_network.txt -alg Lon-Eig -r 0
./sircon ./data/Video_game_network.txt -alg Lon-Deg -r 0
./sircon ./data/Video_game_network.txt -alg Imm -r 0
./sircon ./data/Video_game_network.txt -alg Deg -r 0

