#ifndef LINE_H
#define LINE_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QString>
#include "game.h"

struct Line
{
    float x,y,z; //3d center of line
    float X,Y,W; //screen coord
    float curve,spriteX,clip,scale;
    QString fileToPixmap;
    QPixmap pixmap;

    Line()
        : x(0), y(0), z(0), curve(0), spriteX(0)
    {}

    void project(int camX,int camY,int camZ)
    {
        scale = Game::camD/(z-camZ);
        X = (1 + scale*(x - camX)) * Game::RESOLUTION.width()/2;
        Y = (1 - scale*(y - camY)) * Game::RESOLUTION.height()/2;
        W = scale * Game::roadW  * Game::RESOLUTION.width()/2;
    }

    void drawSprite(QGraphicsScene *_scene)
    {
        QPixmap s = pixmap;

        int w = s.rect().width();
        int h = s.rect().height();

        float destX = X + scale * spriteX * Game::RESOLUTION.width()/2;
        float destY = Y + 4;
        float destW  = w * W / 266;
        float destH  = h * W / 266;

        destX += destW * spriteX; //offsetX
        destY += destH * (-1);    //offsetY

        float clipH = destY+destH-clip;
        if (clipH < 0)
        {
            clipH=0;
        }

        if (clipH>=destH)
        {
            return;
        }
        QPixmap pixmap = s.copy(0,0,w ,h-h*clipH/destH);

        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
        pixmapItem->setPos(destX, destY);
        pixmapItem->setScale(destW/w);

        _scene->addItem(pixmapItem);
    }
};

#endif // LINE_H
