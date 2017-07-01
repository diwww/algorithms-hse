#!/bin/bash
for f in gv/*; 
do
	dot -Tgif $f -o $f.gif;
done;
