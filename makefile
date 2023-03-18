all: primes delegator prime1 prime2

primes: primes.cpp
	g++ primes.cpp -o primes

delegator: delegator.cpp
	g++ delegator.cpp -o delegator

prime1: prime1.cpp
	g++ prime1.cpp -o prime1

prime2: prime2.cpp
	g++ prime2.cpp -o prime2

clean:
	rm -f primes delegator prime1 prime2 *.o