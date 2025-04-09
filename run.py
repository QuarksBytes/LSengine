#!/usr/bin/python

import subprocess,sys,os

if(len(sys.argv)<2):
    print("[ Error ] : Filename not given")
    exit()

name=str(sys.argv[1])

if(not os.path.isdir('Output/')):
    os.mkdir('Output')

if(not os.path.isdir('Output/Debug')):
    os.mkdir('Output/Debug')

if(not os.path.isdir('Output/Release')):
    os.mkdir('Output/Release')

outFolder="Output/"
arguments=""

for i in sys.argv:
    if(i == "-debug"):
        outFolder="Output/Debug/"
    elif(i == "-release"):
        outFolder="Output/Release/"
    elif(i  == "-sanitizer"):
        arguments=" -fsanitize=address,undefined,alignment"

cppCommand="g++ -g -o "+outFolder+"output "+name+"  $(pkg-config --cflags --libs lua) -I"+os.getcwd()+" "+arguments+" && ./"+outFolder+"output"
cCommand="gcc -g  -o "+outFolder+"output "+name+"  $(pkg-config --cflags --libs lua) -I"+os.getcwd()+" "+arguments+" && ./"+outFolder+"output"


if(name.endswith('.cpp')):
    os.system(cppCommand)
elif(name.endswith('.c')):
    os.system(cCommand)
else:
    print("[ Error ] : File is not C/C++")

