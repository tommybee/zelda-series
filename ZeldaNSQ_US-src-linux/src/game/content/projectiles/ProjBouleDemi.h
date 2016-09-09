/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJBOULEDEMI_H__
#define __PROJBOULEDEMI_H__

#include "../types/Projectile.h"

class ProjBouleDemi : public Projectile {
    public :
        ProjBouleDemi(int x, int y, double dx, double dy);
        ~ProjBouleDemi();

        void projLoop();
        void draw(int offsetX, int offsetY);

        BoundingBox* getBoundingBox();

        int getX();
        int getY();
        int getDown();

        void renvoie(Direction dir);

    private :

        int speed;
        double dx;
        double dy;
        int force;
        int parcouru;
        double histX[16];
        double histY[16];
        double longX;
        double longY;
        bool retour;
};

#endif  // ProjBouleDemi.h
