#include "game.h"

const QSize Game::RESOLUTION = QSize(1024, 768);
int Game::roadW = 2000;
int Game::segL = 200;//segment length
float Game::camD = 0.84f;
const float Game::ITERATION_VALUE = 1000.0f/60.0f;

const QString Game::PATH_TO_IMAGES[7] =
{
  QString(":/images/1.png"),
  QString(":/images/2.png"),
  QString(":/images/3.png"),
  QString(":/images/4.png"),
  QString(":/images/5.png"),
  QString(":/images/6.png"),
  QString(":/images/7.png")
};

const QString Game::PATH_TO_BG = ":/images/bg.png";

Game::Game()
{

}
