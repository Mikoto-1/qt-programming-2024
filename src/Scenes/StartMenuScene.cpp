//
// Created by hp on 24-9-6.
//

#include "StartMenuScene.h"

StartMenuScene::StartMenuScene(QObject* parent) : Scene(parent)
{
    setSceneRect(0, 0, 1280, 720);
    background = new QGraphicsPixmapItem(QPixmap(":/Items/Maps/Battlefield/country-platform.png"));
    addItem(background);
    startButton = new QPushButton();
    startButton->setIcon(QIcon(":/Icons/StartGameButton.ico"));
    startButton->setIconSize(QSize(200, 50));
    startButtonProxy = addWidget(startButton);
    startButtonProxy->setPos(540, 360);
    startButtonProxy->setMaximumSize(200, 50);
    startButtonProxy->setMinimumSize(200, 50);
    connect(startButton, &QPushButton::clicked, this, &StartMenuScene::startGame);
}
