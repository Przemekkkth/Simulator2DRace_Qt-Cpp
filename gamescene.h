#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QVector>

#include "game.h"
#include "line.h"
#include "quad.h"

class QTimer;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private slots:
    void update();
private:
    void loadPixmap();
    Game m_game;
    QPixmap m_pixmaps[7];
    QPixmap m_bgPixmap;
    QVector<Line> m_lines;
    Quad m_quad;
    QTimer *m_timer;

    bool m_rightMove, m_leftMove, m_upMove, m_downMove, m_speedUp, m_speedDown, m_accelerate;

    int m_N;
    float m_playerX;
    int m_pos;
    int m_H;
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
