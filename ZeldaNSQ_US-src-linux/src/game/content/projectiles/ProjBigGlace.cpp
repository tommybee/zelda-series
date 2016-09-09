#include "ProjBigGlace.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

ProjBigGlace::ProjBigGlace(int i, int j, double dx, double dy) : dx(dx), dy(dy), retour(false) {
    x = i - 8;
    y = j - 8;
    longX = i;
    longY = j;

    if (dx > 0) {
        if (dy > 0) {
            if (dx > dy) direction = E;
            else direction = S;
        } else {
            if (dx > -dy) direction = E;
            else direction = N;
        }
    } else {
        if (dy > 0) {
            if (-dx > dy) direction = W;
            else direction = S;
        } else {
            if (-dx > -dy) direction = W;
            else direction = N;
        }
    }

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    vanim = 120;
    anim = 0;
    animMax = 1;
    chrono.reset();

    force = MainController::getInstance()->getGameController()->getSave()->isExpert() ? 24 : 12;

    image = ResourceManager::getInstance()->loadImage("data/images/projectiles/magieBig.png", true);
}

ProjBigGlace::~ProjBigGlace() {
    ResourceManager::getInstance()->free(image);
}

void ProjBigGlace::projLoop() {
    if (!alive) {
        return;
    }

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    // compute bounding box for collisions
    box.setX(longX - 8 + dx); box.setY(longY - 8 + dy);

    longX += dx;
    longY += dy;

    x = longX - 8;
    y = longY - 8;

    if (retour) {
        if (scene->testDegat(getBoundingBox(), direction, force, TA_MAGIC, TE_GLACE)) {
            alive = false;
            return;
        }
    } else {
        if (scene->testDegatOnLink(getBoundingBox(), direction, force, TA_MAGIC, TE_GLACE)
             || scene->testDegat(getBoundingBox(), direction, force, TA_MAGIC, TE_GLACE, false)) {
            alive = false;
            return;
        }
    }

    if (!scene->checkCollisions(&box, (Collisionable*)this, false)) {
        alive = false;
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void ProjBigGlace::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = longX - 8 - offsetX;
    int dstY = longY - 8 - offsetY;

    WindowManager::getInstance()->draw(image, anim * 16, 16, 16, 16, dstX, dstY);
}

BoundingBox* ProjBigGlace::getBoundingBox() {
    box.setX(longX - 8);
    box.setY(longY - 8);
    return &box;
}

int ProjBigGlace::getX() {return x;}
int ProjBigGlace::getY() {return y;}
int ProjBigGlace::getDown() {return y + 240;}

void ProjBigGlace::renvoie(Direction dir) {
    if (!retour) {

        switch (dir) {
            case N :
                if (dy > 0) dy = -dy;
                break;
            case S :
                if (dy < 0) dy = -dy;
                break;
            case W :
                if (dx > 0) dx = -dx;
                break;
            case E :
                if (dx < 0) dx = -dx;
                break;
        }

        AudioManager::getInstance()->playSound(TS_HITENNEMY);
        retour = true;
    }
}
