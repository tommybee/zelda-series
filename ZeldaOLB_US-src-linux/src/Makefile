#--------------------------------------------------------------
# Makefile generated with cmak version 0.9.6 (4/2006).
# Date: 13/1/2009 22:46:13
#--------------------------------------------------------------

#PREFIX  = /usr/local
#CFLAGS  = -O2 -Wall
#LDFLAGS = -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL

PREFIX  = ../zelda
CFLAGS  = -O2 -Wall  
#LDFLAGS = -L/mingw32/lib -lSDL_gfx -lSDL_image -lSDL_mixer  -L/mingw32/lib -lvorbis -lvorbisfile -lmingw32 -lSDLmain -lSDL -mwindows 

SDL_LIBS = -static -L/mingw32/lib -lSDL_gfx -lSDL_image -lSDL_mixer  -L/mingw32/lib -lvorbisfile -lvorbis -lmingw32 -lSDLmain -lSDL  \
			-lbz2 -lharfbuzz -lglib-2.0 -lintl -liconv -ltiff -ljpeg -llzma -lpng16 -lstdc++ -lwebp -lwinpthread -lz -larchive -lwinmm -lgdi32 -ldxguid \
			-lasprintf -lcharset -lcrypto -lcurl -lexpat -lffi -lFLAC++ -lFLAC -lfontconfig -lformw -lfreeglut_static -lgdbm -lgettextlib -lgettextpo -lgif \
			-lgio-2.0 -lglew32 -lglew32mx -lgmodule-2.0 -lgmp -lgmpxx -lgnurx -lgnutls -lgnutlsxx -lgobject-2.0 -lgthread-2.0 -lhistory -lhogweed -lidn -lisl -ljansson  \
			-ljsoncpp -llua  -llzo2  -lmenuw -lmetalink -lminizip -lmpc -lmpfr -lncurses++w -lncursesw -lnettle -lnghttp2 -logg -lopenal -lpanelw -lphysfs -lpixman-1 \
			-lreadline -lregex -lrtmp -lssh2 -lssl -lsystre -ltasn1 -ltclstub86 -ltermcap -ltheora -ltheoradec -ltheoraenc \
			-ltkstub86 -ltre -lturbojpeg -lvorbisenc -lwebpdecoder -lwebpdemux -lwebpmux -lole32 -lws2_32 -mwindows 
LDFLAGS = $(SDL_LIBS) 


CC = g++
RM = rm -f
INSTALL_PROG = install -m 755 -s

EXE = ZeldaOLB

OBJS = Audio.o Bouclier.o Caisse.o Carte.o Encyclopedie.o Ennemi.o Generique.o Jeu.o Joueur.o Keyboard.o Listable.o main.o Menu.o Monde.o Objet.o Personnage.o Pnj.o Projectile.o Snipe.o Statut.o Texte.o ZoneRect.o

ALL : $(EXE)

Audio.o : Audio.cpp
	$(CC) -c Audio.cpp $(CFLAGS) -o Audio.o

Bouclier.o : Bouclier.cpp
	$(CC) -c Bouclier.cpp $(CFLAGS) -o Bouclier.o

Caisse.o : Caisse.cpp
	$(CC) -c Caisse.cpp $(CFLAGS) -o Caisse.o

Carte.o : Carte.cpp
	$(CC) -c Carte.cpp $(CFLAGS) -o Carte.o

Encyclopedie.o : Encyclopedie.cpp
	$(CC) -c Encyclopedie.cpp $(CFLAGS) -o Encyclopedie.o

Ennemi.o : Ennemi.cpp
	$(CC) -c Ennemi.cpp $(CFLAGS) -o Ennemi.o

Generique.o : Generique.cpp
	$(CC) -c Generique.cpp $(CFLAGS) -o Generique.o

Jeu.o : Jeu.cpp
	$(CC) -c Jeu.cpp $(CFLAGS) -o Jeu.o

Joueur.o : Joueur.cpp
	$(CC) -c Joueur.cpp $(CFLAGS) -o Joueur.o

Keyboard.o : Keyboard.cpp
	$(CC) -c Keyboard.cpp $(CFLAGS) -o Keyboard.o

Listable.o : Listable.cpp
	$(CC) -c Listable.cpp $(CFLAGS) -o Listable.o

main.o : main.cpp
	$(CC) -c main.cpp $(CFLAGS) -o main.o

Menu.o : Menu.cpp
	$(CC) -c Menu.cpp $(CFLAGS) -o Menu.o

Monde.o : Monde.cpp
	$(CC) -c Monde.cpp $(CFLAGS) -o Monde.o

Objet.o : Objet.cpp
	$(CC) -c Objet.cpp $(CFLAGS) -o Objet.o

Personnage.o : Personnage.cpp
	$(CC) -c Personnage.cpp $(CFLAGS) -o Personnage.o

Pnj.o : Pnj.cpp
	$(CC) -c Pnj.cpp $(CFLAGS) -o Pnj.o

Projectile.o : Projectile.cpp
	$(CC) -c Projectile.cpp $(CFLAGS) -o Projectile.o

Snipe.o : Snipe.cpp
	$(CC) -c Snipe.cpp $(CFLAGS) -o Snipe.o

Statut.o : Statut.cpp
	$(CC) -c Statut.cpp $(CFLAGS) -o Statut.o

Texte.o : Texte.cpp
	$(CC) -c Texte.cpp $(CFLAGS) -o Texte.o

ZoneRect.o : ZoneRect.cpp
	$(CC) -c ZoneRect.cpp $(CFLAGS) -o ZoneRect.o

$(EXE) : $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LDFLAGS)

install : $(EXE)
	$(INSTALL_PROG) $(EXE) $(PREFIX)/bin

uninstall :
	$(RM) $(PREFIX)/bin/$(EXE)

clean :
	$(RM) $(OBJS) $(EXE)
