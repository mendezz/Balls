#define BALL_RADIUS 3
#define BALL_TILE_LENGTH 10
#define FRAMES_PER_SECOND 24

#include <QtGui>

#include "analogclock.h"

AnalogClock::AnalogClock(QWidget *parent) : QWidget(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000.0f / 24.0f);
}

void AnalogClock::addPointToWindow(QPoint clickPosition) {
}

void AnalogClock::mouseReleaseEvent(QMouseEvent *mouseEvent){
    QPoint position = mouseEvent->pos();
    QVector<QPoint> *path = new QVector<QPoint>;
    path->push_front(position);
    QPoint *velocity = new QPoint;
    velocity->setX(rand() % 10 - 5);
    velocity->setY(rand() % 10 - 5);
    velocitys.push_front(velocity);
    paths.push_front(path);
}

void AnalogClock::paintEvent(QPaintEvent *) {
    if (!paths.size()) {
        return ;
    }
    for (int i = 0; i < paths.size(); i++) {
        QVector<QPoint> *path = paths.at(i);
        QPainter painter(this);
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        QPoint position = path->at(0);
        QPoint *velocity = velocitys.at(i);
        position += *velocity;
        if (position.x() + BALL_RADIUS >= this->width() || position.x() - BALL_RADIUS <= 0) {
            if (position.x() - BALL_RADIUS <= 0) {
                position.setX(BALL_RADIUS);
            } else {
                position.setX(this->width() - BALL_RADIUS);
            }
            velocity->setX(-velocity->x());
        }
        if (position.y() + BALL_RADIUS >= this->height() || position.y() - BALL_RADIUS <= 0) {
            if (position.y() - BALL_RADIUS <= 0){
                position.setY(BALL_RADIUS);
            } else {
                position.setY(this->height() - BALL_RADIUS);
            }
            velocity->setY(-velocity->y());
        }

        if (path->size() < BALL_TILE_LENGTH) {
            path->push_front(position);
        } else {
            path->push_front(position);
            path->pop_back();
        }
        for (int i = 0; i < path->size(); i++) {
            painter.setOpacity(1.0f / (i + 1.0f));
            painter.drawEllipse(path->at(i),BALL_RADIUS,BALL_RADIUS);
        }
    }
}
