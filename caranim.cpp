#include "caranim.h"

CarAnim::CarAnim(QObject *parent)
    : QObject{parent}, m_moveRight(false), m_moveLeft(false)
{
    m_carPixmap.load(":/images/car.png");
    m_currentFrame = 4;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CarAnim::updateFrame);
    m_timer->start(50);
}

QPixmap CarAnim::returnPixmap()
{
    return m_carPixmap.copy(720*m_currentFrame,0,720,368);
}

void CarAnim::updateFrame()
{
    if(m_moveRight && m_currentFrame <= 8)
    {
        m_currentFrame++;
        if(m_currentFrame > 8)
        {
            m_currentFrame = 8;
        }
    }
    else if(m_moveLeft && m_currentFrame >= 0)
    {
        m_currentFrame--;
        if(m_currentFrame < 0)
        {
            m_currentFrame = 0;
        }
    }
    else
    {
        if(m_currentFrame > 4)
        {
            m_currentFrame--;
        }
        else if(m_currentFrame < 4)
        {
            m_currentFrame++;
        }
    }
}

