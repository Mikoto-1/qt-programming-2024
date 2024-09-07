//
// Created by gerw on 8/20/24.
//

#include <QDateTime>
#include "Scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent), timer(new QTimer(this))
{
    connect(timer, &QTimer::timeout, this, &Scene::update);
}

void Scene::update()
{
    const auto currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if (lastTime == -1)
    {
        // first frame
        deltaTime = 0;
    }
    else
    {
        deltaTime = currentTime - lastTime;
    }
    lastTime = currentTime;

    processInput();
    processMovement();
    processPicking();
}

void Scene::startLoop() const
{
    timer->start(1000 / 90); // 90FPS
}

void Scene::stopLoop() const
{
    timer->stop();
}

void Scene::processInput()
{
}

void Scene::processMovement()
{
}

void Scene::processPicking()
{
}

