#!/bin/bash
## C++
mkdir -p Grasmaaier/Clients/C++
mkdir -p Grasmaaier/Clients/Python
mkdir -p Grasmaaier/HTML
ROOT_DIR=/home/hylkema/Programs/lawnmower
rsync -r --update --exclude=*.o hylkema@$1:$ROOT_DIR/C++/Sources /home/pi/Grasmaaier/Clients/C++
rsync -r hylkema@$1:$ROOT_DIR/C++/Tests /home/pi/Grasmaaier
rsync hylkema@$1:$ROOT_DIR/C++/Makefile /home/pi/Grasmaaier/Clients/C++/Makefile
rsync hylkema@$1:$ROOT_DIR/C++/*.sh /home/pi/Grasmaaier/Clients/C++
rsync hylkema@$1:$ROOT_DIR/C++/sync.sh /home/pi
## Python
rsync -r --update --exclude=*.o hylkema@$1:$ROOT_DIR/Python/* /home/pi/Grasmaaier/Clients/Python
## Html
rsync -r --update --exclude=*.o hylkema@$1:$ROOT_DIR/HTML/* /home/pi/Grasmaaier/HTML
