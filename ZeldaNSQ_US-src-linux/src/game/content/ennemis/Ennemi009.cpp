#include "Ennemi009.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi009::Ennemi009(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi9.png", true);
    chrono.reset();

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 24;

    box.setX(x);
    box.setY(y+8);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = expert ? 8 : 5;
    maxLife = expert ? 8 : 5;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_MAGIE_PEU, 20);
    items.addType(TI_RUBIS_VERT, 20);
    items.addType(TI_RUBIS_BLEU, 10);

    forceEnn = expert ? 4 : 2;
}

Ennemi009::~Ennemi009() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi009::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi009::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        if (link->getStatus()->isVisible()) {
            pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

            move(dir.first, dir.second);

            if (link->getBoundingBox()->intersect(getBoundingBox())) {
                testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
            }
        } else {
            idle = true;
            testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
        }
    } else {
        idle = true;
    }

    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi009::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height + (gel ? height * 2 : 0), width, height, dstX, dstY);
}

int Ennemi009::getX() {
    return x;
}

int Ennemi009::getY() {
    return y;
}

BoundingBox* Ennemi009::getBoundingBox() {
    box.setX(x);
    box.setY(y + 8);
    return &box;
}
