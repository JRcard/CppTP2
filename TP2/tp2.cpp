#include <iostream>
#include <chrono>
#include <ctime>

#include "tp2.h"

int main(int argc, char** argv){

#ifdef TOP_CHRONO
	chrono::time_point<std::chrono::system_clock> debut, fin;
	debut = chrono::system_clock::now();
#endif

	Process(argc,argv);

#ifdef TOP_CHRONO
	fin = chrono::system_clock::now();

	int temps_ecoule_seconde = \
				chrono::duration_cast<chrono::seconds> (fin-debut).count();
	int temps_ecoule_microsecondes = \
		chrono::duration_cast<chrono::microseconds> (fin-debut).count();

	time_t temps_fin = \
			chrono::system_clock::to_time_t(chrono::system_clock::now());

	cerr << "calul termine a " << ctime(&temps_fin) << \
			"temps ecoule (s): " << temps_ecoule_seconde << "s ; " \
			<< temps_ecoule_microsecondes << " micros\n";
#endif

	
	return 0;
}