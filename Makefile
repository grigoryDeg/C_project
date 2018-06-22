matrix_det.o: matrix_det.c
	gcc -c -o matrix_det.o matrix_det.c
reverse_gauss.o: reverse_gauss.c
	gcc -c -o reverse_gauss.o reverse_gauss.c
hello: matrix_det.o reverse_gauss.o
	gcc -o hello matrix_det.o reverse_gauss.o