#ifndef CARITEM_H
#define CARITEM_H

#include <QObject>
#include <QPixmap>
#include <QTimer>

class CarItem : public QObject
{
    Q_OBJECT
public:
    explicit CarItem(QObject *parent = nullptr);
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

#endif // CARITEM_H
