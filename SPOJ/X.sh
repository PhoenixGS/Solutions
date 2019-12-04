g++ data.cpp -o data -O2
g++ QTREE5.cpp -o QTREE5 -O2
g++ tmp.cpp -o tmp -O2
while true; do
	./data > QTREE5.in
	time ./QTREE5 < QTREE5.in > QTREE5.out
	time ./tmp < QTREE5.in > tmp.out
	if diff QTREE5.out tmp.out; then
		echo AC
	else
		echo WA
		break
	fi
done
