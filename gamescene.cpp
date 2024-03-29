#include "gamescene.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this)), m_rightMove(false), m_leftMove(false),
      m_upMove(false), m_downMove(false), m_speedUp(false), m_speedDown(false), m_accelerate(false),
      m_playerX(0), m_pos(0), m_H(400)
{
    loadPixmap();
    setSceneRect(0, 0, m_game.RESOLUTION.width(), m_game.RESOLUTION.height());


    for(int i = 0; i < 1600; i++)
    {
        Line line;
        line.z = i * Game::segL;

        if (i > 300 && i < 700)
        {
            line.curve = 0.5;
        }
        if (i > 1100)
        {
            line.curve = -0.7;
        }

        if (i < 300 && i%20 == 0)
        {
            line.spriteX = -2;
            line.fileToPixmap = Game::PATH_TO_IMAGES[4];
            line.pixmap = m_pixmaps[4];
        }
        if (i%17 == 0  )
        {
            line.spriteX = 1.0;
            line.fileToPixmap = Game::PATH_TO_IMAGES[5];
            line.pixmap = m_pixmaps[5];
        }
        if ( i > 300 && i%20 == 0)
        {
            line.spriteX= -1.7;
            line.fileToPixmap = Game::PATH_TO_IMAGES[3];
            line.pixmap= m_pixmaps[3];
        }
        if (i > 800 && i%20 == 0)
        {
            line.spriteX= -2;
            line.fileToPixmap = Game::PATH_TO_IMAGES[0];
            line.pixmap= m_pixmaps[0];
        }
        if ( i==400 )
        {
            line.spriteX = -2;
            line.fileToPixmap = Game::PATH_TO_IMAGES[6];
            line.pixmap= m_pixmaps[6];
        }

        m_lines.push_back(line);
    }
//    exit(0);
    m_N = m_lines.size();
    connect(m_timer, &QTimer::timeout, this, &GameScene::update);
    m_timer->start(m_game.ITERATION_VALUE);

    m_carAnim = new CarAnim(this);
}

void GameScene::update()
{

    int speed=0;

    if(m_upMove)
    {
        m_H += 100;
    }
    if(m_downMove)
    {
        m_H -= 100;
    }
    if(m_rightMove)
    {
        m_playerX += 0.1;
        m_carAnim->m_moveRight = true;
    }
    else
    {
        m_carAnim->m_moveRight = false;
    }
    if(m_leftMove)
    {
        m_playerX -= 0.1;
        m_carAnim->m_moveLeft = true;
    }
    else
    {
        m_carAnim->m_moveLeft = false;
    }
    if(m_speedUp)
    {
        speed = 500;
    }
    if(m_speedDown)
    {
        speed = -200;
    }
    if(m_accelerate)
    {
        speed *= 3;
    }

    clear();
    setBackgroundBrush(QBrush(QColor(105,205,4)));
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_bgPixmap);
    //bgItem->setPos(-2000,0);
    addItem(bgItem);


    m_pos += speed;
    while (m_pos >= m_N*Game::segL) m_pos -= m_N * Game::segL;
    while (m_pos < 0) m_pos += m_N*Game::segL;

    int startPos = m_pos / Game::segL;
    m_startPos = startPos;
    int camH = m_lines[startPos].y + m_H;
    if (speed>0)
    {
        bgItem->moveBy(-m_lines[startPos].curve*2,0);
    }
    if (speed<0)
    {
        bgItem->moveBy( m_lines[startPos].curve*2,0);
    }
    int maxy = Game::RESOLUTION.height();
    float x=0,dx=0;

    ///////draw road////////
    for(int n = startPos; n < startPos+300; n++)
    {
        Line &l = m_lines[n%m_N];
        l.project(m_playerX * Game::roadW - x, camH, startPos * Game::segL - ( n >= m_N ? m_N * Game::segL:0));
        x += dx;
        dx += l.curve;

        l.clip = maxy;
        if (l.Y >= maxy) continue;
        maxy = l.Y;

        QColor grass  = (n/3)%2? QColor(16,200,16) : QColor(0,154,0);
        QColor rumble = (n/3)%2? QColor(255,255,255) : QColor(0,0,0);
        QColor road   = (n/3)%2? QColor(107,107,107) : QColor(105,105,105);
        QColor road_lanes = (n/3)%2? QColor(255, 255, 255) : QColor(105,105,105);

        Line p = m_lines[(n-1)%m_N]; //previous line

        m_quad.drawQuad(this, grass, 0, p.Y, Game::RESOLUTION.width(), 0, l.Y, Game::RESOLUTION.width());
        m_quad.drawQuad(this, rumble,p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2);
        m_quad.drawQuad(this, road,  p.X, p.Y, p.W, l.X, l.Y, l.W);
        m_quad.drawQuad(this, road_lanes, p.X, p.Y, p.W/25, l.X, l.Y, l.W/25);
    }

    ////////draw objects////////
    for(int n=startPos+300; n>startPos; n--)
    {
        if(!m_lines[n%m_N].fileToPixmap.isEmpty())
        {
            m_lines[n%m_N].drawSprite(this);
            //qDebug() << "File to pixmap " << m_lines[n%m_N].fileToPixmap;
        }
    }
    ////////draw car ///////////////
    QGraphicsPixmapItem *carItem = new QGraphicsPixmapItem(m_carAnim->returnPixmap());
    carItem->setTransformationMode(Qt::SmoothTransformation);
    carItem->setScale(0.75f);
    carItem->setPos(Game::RESOLUTION.width()/2-carItem->boundingRect().width() + 200, 300);
    addItem(carItem);

    QGraphicsRectItem* lRect = new QGraphicsRectItem();
    lRect->setRect(0,0,m_game.RESOLUTION.width(), m_game.RESOLUTION.height());
    lRect->setBrush(Qt::black);
    lRect->setPen(QColor(Qt::black));
    lRect->setPos(-m_game.RESOLUTION.width(), 0);
    addItem(lRect);

    QGraphicsRectItem* rRect = new QGraphicsRectItem();
    rRect->setRect(0,0,m_game.RESOLUTION.width(), m_game.RESOLUTION.height());
    rRect->setBrush(Qt::black);
    rRect->setPen(QColor(Qt::black));
    rRect->setPos(+m_game.RESOLUTION.width(), 0);
    addItem(rRect);

    QGraphicsRectItem* tRect = new QGraphicsRectItem();
    tRect->setRect(0,0,m_game.RESOLUTION.width(), m_game.RESOLUTION.height());
    tRect->setBrush(Qt::black);
    tRect->setPen(QColor(Qt::black));
    tRect->setPos(0, -m_game.RESOLUTION.height());
    addItem(tRect);

    QGraphicsRectItem* bRect = new QGraphicsRectItem();
    bRect->setRect(0,0,m_game.RESOLUTION.width(), m_game.RESOLUTION.height());
    bRect->setBrush(Qt::black);
    bRect->setPen(QColor(Qt::black));
    bRect->setPos(0, -m_game.RESOLUTION.height());
    addItem(bRect);
}

void GameScene::loadPixmap()
{
    for(int i = 0; i < 7; ++i)
    {
        if(m_pixmaps[i].load(m_game.PATH_TO_IMAGES[i]))
        {
            qDebug() << "Pixmap " << i << " is loaded successfully";
        }
        else
        {
            qDebug() << "Pixmap " << i << " is not loaded successfully";
        }
    }

    if( m_bgPixmap.load(m_game.PATH_TO_BG) )
    {
        qDebug() << "BgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BgPixmap is not loaded successfully";
    }
}

void GameScene::renderScene()
{
    QString fileName = QDir::currentPath() + QDir::separator() + "game_scene.png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    {
        m_upMove = true;

    }
        break;
    case Qt::Key_Down:
    {
        m_downMove = true;
        qDebug() << "h " << m_H;
    }
        break;
    case Qt::Key_Right:
    {
        m_rightMove = true;
    }
        break;
    case Qt::Key_Left:
    {
        m_leftMove = true;
    }
        break;
    case Qt::Key_W:
    {
        m_speedUp = true;

    }
        break;
    case Qt::Key_S:
    {
        m_speedDown = true;
    }
        break;
    case Qt::Key_Tab:
    {
        m_accelerate = true;
    }
        break;
    case Qt::Key_Z:
    {
        //renderScene();
    }
        break;
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    {
        m_upMove = false;
    }
        break;
    case Qt::Key_Down:
    {
        m_downMove = false;
    }
        break;
    case Qt::Key_Right:
    {
        m_rightMove = false;
    }
        break;
    case Qt::Key_Left:
    {
        m_leftMove = false;
    }
        break;
    case Qt::Key_W:
    {
        m_speedUp = false;
    }
        break;
    case Qt::Key_S:
    {
        m_speedDown = false;
    }
        break;
    case Qt::Key_Tab:
    {
        m_accelerate = false;
    }
        break;
    }
}
