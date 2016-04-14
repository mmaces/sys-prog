
#include <iostream>
using namespace std;

#include "String.h"

/**
	"leeres" String erstellen (mit Terminatorsymbol erstellen)
*/
String::String() { 
    size = 0;
    str = new char[1];
    str[0] = '\0';
}

/**
	str initialisieren f�r size = 1.
*/
String::String(char c) {
    size = 1;
    str = new char[2];
    str[0] = c;
    str[1] = '\0';
}

/**
	str erstellen f�r den Fall dass es mehr als ein Zeichen ist.
*/
String::String(const char *s) {
  int res = 0;
  while(s[res] != '\0'){ //Zeichen z�hlen.
	  res++;
  }
  size = res; 
  str = new char[size+1];// Gr��e des Strings erstellen +1 wegen terminator symbol
  for(int i = 0;i<=res;i++){ // in String kopieren
	  str[i]=s[i];
  }

}

/**
	String in einen neuen String kopieren.
*/
String::String(const String& s) {
	size = s.size; // gr��e in neue Stringklasse kopieren.
	str = new char[size+1]; // neuen String erstellen mit gr��e +1 wegen Terminatorsymbole
	for(int i = 0;i<=size;i++){ // alten String in neuen r�berkopieren
		str[i]=s.str[i];
	}
}

String::~String() { delete[] str; }

/**
	Index aus einem String zur�ckgeben.
*/
char& String::operator[](int index) {
	if(index >=0 && index<size){
		return str[index];
	}
	else{
		return str[size];
	}
	
}

String& String::operator=(String& s) {
  /*int res = 0;
  while(s[res] != '\0'){ //Zeichen z�hlen von s
	  res++;
  }
  size = res;// gr��e ver�ndern*/
  size = s.size;
  delete[] str;
  str = new char[size+1];// String neu erstellen mit der gew�nschten gr��e
  for(int i = 0;i<size;i++){//zeichen von s nach str kopieren
	  str[i] = s[i];
  }
  str[size] = '\0'; // terminatorsymbol dazu f�gen
  return *this;
}

String& String::operator+=(String& s) {
  int nVonS = s.size;
  int nVonStr = size;
  /*while(s[nVonS] != '\0'){ //Zeichen z�hlen von s
	  nVonS++;
  }
  while(str[nVonStr] != '\0'){ //Zeichen z�hlen von str
	  nVonStr++;
  }*/
  char* temp = new char[(nVonStr+nVonS+1)]; // neues Array mit gew�nschter gr�sse erstellen. welches als zwischenspeicher dient
  size = (nVonS+nVonStr); // gr��e �ndern

  for(int i = 0;i<nVonStr;i++) // str in temp kopieren
  {
	  temp[i] = str[i];
  }

  for(int j = nVonStr;j<nVonS+nVonStr;j++){ // s danach in temp kopieren
	  temp[j] = s[j-nVonStr];
  }

  temp[nVonStr+nVonS] = '\0'; // terminatorsymbol dazu f�gen

  delete[] str;// altes str l�schen damit der Speicher nicht unn�tig verbraucht wird

  str = temp ; // temp �bergeben

  return *this;
}


