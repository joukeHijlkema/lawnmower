#!/bin/bash
## C++
mkdir -p Grasmaaier/Clients/C++
mkdir -p Grasmaaier/Clients/Python
rsync -r --update --exclude=*.o hylkema@$1:/home/hylkema/Dropbox/Programs/Grasmaaier/C++/Sources /home/pi/Grasmaaier/Clients/C++
rsync -r hylkema@$1:/home/hylkema/Dropbox/Programs/Grasmaaier/C++/Tests /home/pi/Grasmaaier
rsync hylkema@$1:/home/hylkema/Dropbox/Programs/Grasmaaier/C++/Makefile /home/pi/Grasmaaier/Clients/C++/Makefile
rsync hylkema@$1:/home/hylkema/Dropbox/Programs/Grasmaaier/C++/*.sh /home/pi/Grasmaaier/Clients/C++
rsync hylkema@$1:/home/hylkema/Dropbox/Programs/Grasmaaier/C++/sync.sh /home/pi
## Python
rsync -r --update --exclude=*.o hylkema@$1:/home/hylkema/Dropbox/Programs/Grasmaaier/Python/* /home/pi/Grasmaaier/Clients/Python
