//
// Created by hp on 24-9-6.
//

#include "GameOverScene.h"

#include <QGraphicsProxyWidget>

GameOverScene::GameOverScene(QObject* parent, const QString& text) : Scene(parent)
{
    setSceneRect(0, 0, 1280, 720);
    background = new QGraphicsPixmapItem(QPixmap(":/Items/Maps/Battlefield/country-platform.png"));
    addItem(background);

    // Game Over Label
    gameOverLabel = new QLabel();
    if (text == "Left Win")
    {
        gameOverLabel->setPixmap(QPixmap(":/Icons/LeftWinHint.ico"));
    }
    else if (text == "Right Win")
    {
        gameOverLabel->setPixmap(QPixmap(":/Icons/RightWinHint.ico"));
    }
    gameOverLabel->setScaledContents(true);
    gameOverLabelProxy = addWidget(gameOverLabel);
    gameOverLabelProxy->setPos(440, 240);
    gameOverLabelProxy->setMaximumSize(400, 100);
    gameOverLabelProxy->setMinimumSize(400, 100);
    gameOverLabelProxy->setZValue(0);

    // Restart Button
    restartButton = new QPushButton();
    restartButton->setIcon(QIcon(":/Icons/RestartButton.ico"));
    restartButton->setIconSize(QSize(200, 50));
    restartButtonProxy = addWidget(restartButton);
    restartButtonProxy->setPos(240, 420);
    restartButtonProxy->setMaximumSize(200, 50);
    restartButtonProxy->setMinimumSize(200, 50);

    // Exit Button
    exitButton = new QPushButton();
    exitButton->setIcon(QIcon(":/Icons/ExitButton.ico"));
    exitButton->setIconSize(QSize(200, 50));
    exitButtonProxy = addWidget(exitButton);
    exitButtonProxy->setPos(540, 420);
    exitButtonProxy->setMaximumSize(200, 50);
    exitButtonProxy->setMinimumSize(200, 50);

    // Main Menu Button
    mainMenuButton = new QPushButton();
    mainMenuButton->setIcon(QIcon(":/Icons/MainMenuButton.ico"));
    mainMenuButton->setIconSize(QSize(200, 50));
    mainMenuButtonProxy = addWidget(mainMenuButton);
    mainMenuButtonProxy->setPos(840, 420);
    mainMenuButtonProxy->setMaximumSize(200, 50);
    mainMenuButtonProxy->setMinimumSize(200, 50);

    connect(restartButton, &QPushButton::clicked, this, &GameOverScene::restartGame);
    connect(exitButton, &QPushButton::clicked, this, &GameOverScene::exitGame);
    connect(mainMenuButton, &QPushButton::clicked, this, &GameOverScene::backToMainMenu);
}
