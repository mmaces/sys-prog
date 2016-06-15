#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestParser: ParserTarget ParserTestTarget
	g++ -g ../Parser/objs/Parser.o objs/ParserTest.o ../Scanner/objs/Scanner.o ../Buffer/objs/Buffer.o ../Automat/objs/Automat.o ../Symboltable/objs/Symboltable.o ../Scanner/objs/Token.o -o debug/ParserTest
	

# compilieren des Files Automat.cpp zu Automat.o, 
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
# flag:
# -c --> nur compilieren
# -g --> debug Informationen erzeugen
# -Wall --> alle meldungen erzeugen (Warning all)

ParserTarget :  src/Parser.cpp includes/Parser.h
	g++ -g  -c -Wall src/Parser.cpp -o objs/Parser.o


# TestAutomat.o ist abhängig von src/TestAutomat.cpp und src/Automat.h
ParserTestTarget :  src/ParserTest.cpp includes/Parser.h
	g++ -g  -c -Wall src/ParserTest.cpp  -o objs/ParserTest.o  



# loeschen aller files im verzeichnis obj und debug, dann neu erzeugen

cleanParser:
	rm -f objs/*.o
	rm -f debug/*
	$(MAKE) makeTestParser
	
	
# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer Gesamtprojekt loeschen und dann neu erzeugen
ParserOBJTarget:
	$(MAKE) ParserTarget

