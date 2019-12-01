g++ data.cpp -o data -O2
g++ QTREE4.cpp -o QTREE4 -O2
g++ tmp.cpp -o tmp -O2
while true; do
	./data > QTREE4.in
	time ./QTREE4 < QTREE4.in > QTREE4.out
	time ./tmp < QTREE4.in > tmp.out
	if diff QTREE4.out tmp.out; then
		echo AC
	else
		echo WA
		break
	fi
done
