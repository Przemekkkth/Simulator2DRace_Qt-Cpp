#ifndef CARANIM_H
#define CARANIM_H

#include <QObject>
#include <QPixmap>
#include <QTimer>

class CarAnim : public QObject
{
    Q_OBJECT
public:
    explicit CarAnim(QObject *parent = nullptr);
    bool m_moveRight;
    bool m_moveLeft;
    int m_currentFrame;
    QPixmap m_carPixmap;
    QPixmap returnPixmap();
signals:

private:
    void updateFrame();
    QTimer *m_timer;
};

#endif // CARANIM_H
