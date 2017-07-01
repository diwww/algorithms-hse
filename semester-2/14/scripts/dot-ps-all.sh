for f in gv/*; 
do
	dot -Tps $f -o $f.ps;
done;
