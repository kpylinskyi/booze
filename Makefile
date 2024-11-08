build:
	./build_booze.sh

rebuild:
	./build_booze.sh -B

booze:
	./build/booze $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))