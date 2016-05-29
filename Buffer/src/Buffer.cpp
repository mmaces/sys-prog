/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Buffer.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>




// Konstruktor
//
Buffer::Buffer(const char* file) {
	// Öffnen der File
	filedescriptor = open(file, O_DIRECT|O_SYNC);
	index = 0;
	buffer1 = NULL;
	// Speicher allokieren für die Bufferfragmente
	int err = posix_memalign((void**)&buffer1,512,513);
	int err2 = posix_memalign((void**)&buffer2,512,513);

	if (err || err2){
		cout << "Ups... du Depp:!!!! Sry" << endl;
	}
	// Buffer1 befüllen und Ende markieren
	puffer_content1 = read(filedescriptor,buffer1,512);
	puffer_content2 = 1;
	buffer1[puffer_content1] = '\0';
	rank = 0;
	grenzeuebertreten = false;
}

// Destruktor
// Freigeben des allokierten Speichers und schließen des filedescriptors
Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
	close(filedescriptor);
	delete[] buffer1;
	delete[] buffer2;
}

char Buffer::getChar(){
	// Wenn nichts gelesen dann abbrechen
	if(puffer_content1 <= 0 || puffer_content2 <= 0){
		return '\0';
	}
	// Lesen aus dem ersten Puffer
	if(buffer1[index] != '\0' && rank == 0){
		char c = buffer1[index];
		index++;

		return c;
	}else{
		// Lesen aus dem zweiten Puffer
		if(buffer2[index] != '\0' && rank == 1){
			char c = buffer2[index];
			index++;
			return c;
		}else{
			index = 0;
			// Grenzfälle:
			// Grenze nicht übertreten - Letztes Zeichen des Puffer erreicht. Neuer Puffer wird befüllt.
			if(grenzeuebertreten == false){
				if(rank == 0){
					// Befüllen Puffer mit Rank 1
					if ((puffer_content2 = read(filedescriptor,buffer2,512)) <= 0){
						//perror("buffer2 ");
						errno=0;
						buffer2[puffer_content2 = 0] = '\0';
					} else
						buffer2[puffer_content2] = '\0';
				}else{ //rank == 1
					// Befüllen Puffer mit Rank 0
					if ((puffer_content1 = read(filedescriptor,buffer1,512)) <= 0){
						//perror("buffer1 ");
						errno=0;
						buffer1[puffer_content1 = 0] = '\0';
					} else
						buffer1[puffer_content1] = '\0';
				}
				// Rang tauschen und erstes Zeichen des neuen Puffers ausgeben, da letztes zu schreibendes Zeichen '\0' war
				rank = !rank;
				return getChar();
			}else{
				// Grenze wurde überschritten - kann nur nach dem Aufruf von ungetChar() auftreten
				grenzeuebertreten = false;
				rank = !rank;
				return getChar();
			}
		}
	}
}

void Buffer::ungetChar(){
	// Wechsel in den vorherigen Buffer wenn man am Anfang des Buffer ist und zurück will
	if(index == 0 && !grenzeuebertreten){
		grenzeuebertreten = !grenzeuebertreten;
		index = (rank == 0 ? puffer_content2-1 : puffer_content1-1);
		rank = !rank;

		if(puffer_content1 == 0){
			puffer_content1++;
		}else if(puffer_content2 == 0){
			puffer_content2++;
		}

	}else if (index == 0 && grenzeuebertreten){
		throw "Kann nicht weiter zurück gehen";		//Fehlermeldung
	}else{
		// Normalfall - Eins zurückgehen
		index--;
	}
}

// Debug
bool Buffer::getRank(){
	return rank;
}
