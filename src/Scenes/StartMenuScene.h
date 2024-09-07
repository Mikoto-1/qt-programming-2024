//
// Created by hp on 24-9-6.
//

#ifndef STARTMENUSCENE_H
#define STARTMENUSCENE_H
#include "Scene.h"
#include <QGraphicsItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class StartMenuScene : public Scene
{
    Q_OBJECT

public:
    explicit StartMenuScene(QObject* parent);

signals:
    void startGame();

private:
    QGraphicsPixmapItem* background;

    QPushButton* startButton;

    QGraphicsProxyWidget* startButtonProxy;
};


#endif //STARTMENUSCENE_H
