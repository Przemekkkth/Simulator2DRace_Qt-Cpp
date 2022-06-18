#include "view.h"
#include "gamescene.h"
#include <QApplication>
#include <QKeyEvent>

View::View()
    : QGraphicsView(), m_gameScene(new GameScene())
{
    setScene(m_gameScene);
    resize(m_gameScene->sceneRect().width() + 2, m_gameScene->sceneRect().height() + 2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:
    {
        QApplication::instance()->quit();
    }
        break;
    }
    QGraphicsView::keyPressEvent(event);
}
