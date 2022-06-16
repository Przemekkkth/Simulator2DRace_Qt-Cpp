#ifndef GAME_H
#define GAME_H
#include <QSize>

class Game
{
public:
    Game();
    static const QSize RESOLUTION;
    static int roadW;
    static int segL;//segment length
    static float camD;
    static const QString PATH_TO_IMAGES[7];
    static const QString PATH_TO_BG;
    static const float ITERATION_VALUE;
};

#endif // GAME_H
