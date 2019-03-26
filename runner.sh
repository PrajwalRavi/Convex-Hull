#!/bin/sh

g++ -g jarvis.cpp -std=c++14
time ./a.out > out.txt < inp_1000_gen.txt 
python3 hull_plotter.py
