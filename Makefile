r:
	cmake . -B build
	make -C build -j4
	mv build/game .
	./game
