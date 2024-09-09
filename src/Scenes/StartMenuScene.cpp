//
// Created by hp on 24-9-6.
//

#include "StartMenuScene.h"

StartMenuScene::StartMenuScene(QObject* parent) : Scene(parent)
{
    setSceneRect(0, 0, 1280, 720);
    background = new QGraphicsPixmapItem(QPixmap(":/Items/Maps/Battlefield/country-platform.png"));
    addItem(background);

    // initialize start button
    startButton = new QPushButton();
    startButton->setIcon(QIcon(":/Icons/StartGameButton.ico"));
    startButton->setIconSize(QSize(200, 50));
    startButtonProxy = addWidget(startButton);
    startButtonProxy->setPos(540, 360);
    startButtonProxy->setMaximumSize(200, 50);
    startButtonProxy->setMinimumSize(200, 50);

    // initialize mode choose label
    modeChooseLabel = new QLabel();
    modeChooseLabel->setPixmap(QPixmap(":/Icons/ModeChooseHint.ico"));
    modeChooseLabel->setVisible(false);
    QGraphicsProxyWidget* modeChooseLabelProxy = addWidget(modeChooseLabel);
    modeChooseLabelProxy->setPos(515, 420);
    modeChooseLabelProxy->setMaximumSize(250, 50);
    modeChooseLabelProxy->setMinimumSize(250, 50);

    // initialize player mode button
    playerModeButton = new QPushButton();
    playerModeButton->setIcon(QIcon(":/Icons/PlayerMode.ico"));
    playerModeButton->setIconSize(QSize(100, 50));
    playerModeButton->setVisible(false);
    playerModeButtonProxy = addWidget(playerModeButton);
    playerModeButtonProxy->setPos(540, 480);
    playerModeButtonProxy->setMaximumSize(100, 50);
    playerModeButtonProxy->setMinimumSize(100, 50);

    // initialize ai mode button
    aiModeButton = new QPushButton();
    aiModeButton->setIcon(QIcon(":/Icons/AIMode.ico"));
    aiModeButton->setIconSize(QSize(100, 50));
    aiModeButton->setVisible(false);
    aiModeButtonProxy = addWidget(aiModeButton);
    aiModeButtonProxy->setPos(640, 480);
    aiModeButtonProxy->setMaximumSize(100, 50);
    aiModeButtonProxy->setMinimumSize(100, 50);

    connect(startButton, &QPushButton::clicked, this, &StartMenuScene::chooseMode);
    connect(playerModeButton, &QPushButton::clicked, this, &StartMenuScene::startPlayerMode);
    connect(aiModeButton, &QPushButton::clicked, this, &StartMenuScene::startAIMode);
}

void StartMenuScene::chooseMode()
{
    startButton->setVisible(false);
    modeChooseLabel->setVisible(true);
    playerModeButton->setVisible(true);
    aiModeButton->setVisible(true);
}

void StartMenuScene::startPlayerMode()
{
    emit startGame("PLAYER");
}

void StartMenuScene::startAIMode()
{
    emit startGame("AI");
}
