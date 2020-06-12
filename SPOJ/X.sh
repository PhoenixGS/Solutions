g++ data.cpp -o data -O2
g++ QTREE5.cpp -o QTREE5 -O2
g++ QTREE5-LCT.cpp -o QTREE5-LCT -O2
while true; do
	./data > QTREE5.in
	time ./QTREE5 < QTREE5.in > QTREE5.out
	time ./QTREE5-LCT < QTREE5.in > QTREE5-LCT.out
	if diff QTREE5.out QTREE5-LCT.out; then
		echo AC
	else
		echo WA
		break
	fi
done
