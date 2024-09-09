//
// Created by gerw on 8/20/24.
//
#include "MyGame.h"
#include "Scenes/BattleScene.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/StartMenuScene.h"

MyGame::MyGame(QWidget* parent) : QMainWindow(parent)
{
    // initialize the start menu scene
    startMenuScene = new StartMenuScene(this);
    view = new QGraphicsView(this);
    // view->setScene(startMenuScene);
    view->setScene(startMenuScene);

    // Set the view's window size to 1280x720
    view->setFixedSize(static_cast<int>(view->scene()->width()), static_cast<int>(view->scene()->height()));
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    setCentralWidget(view);
    // Adjust the QMainWindow size to tightly wrap the QGraphicsView
    setFixedSize(view->size());

    // Connect the startGame signal from the startMenuScene to the startGame slot of MyGame
    connect(dynamic_cast<const QtPrivate::FunctionPointer<void(StartMenuScene::*)()>::Object*>(startMenuScene),
            &StartMenuScene::startGame, this, &MyGame::startGame);
}

void MyGame::startGame(const QString& gameMode)
{
    battleScene = new BattleScene(this, gameMode);
    view->setScene(battleScene);
    battleScene->startLoop();
    connect(dynamic_cast<const QtPrivate::FunctionPointer<void(BattleScene::*)()>::Object*>(battleScene),
            &BattleScene::gameOver, this, &MyGame::gameOver);
}

void MyGame::gameOver(const QString& text)
{
    battleScene->stopLoop();
    gameOverScene = new GameOverScene(this, text);
    view->setScene(gameOverScene);
    connect(dynamic_cast<const QtPrivate::FunctionPointer<void(GameOverScene::*)()>::Object*>(gameOverScene), &GameOverScene::restartGame, this, &MyGame::reStartGame);
    connect(dynamic_cast<const QtPrivate::FunctionPointer<void(GameOverScene::*)()>::Object*>(gameOverScene), &GameOverScene::exitGame, this, &MyGame::exitGame);
    connect(dynamic_cast<const QtPrivate::FunctionPointer<void(GameOverScene::*)()>::Object*>(gameOverScene), &GameOverScene::backToMainMenu, this, &MyGame::backToMainMenu);
}

void MyGame::reStartGame()
{
    auto oldScene = battleScene;
    QString gameMode = dynamic_cast<BattleScene*>(battleScene)->get_game_mode();
    battleScene = new BattleScene(this, gameMode);
    view->setScene(battleScene);
    battleScene->startLoop();
    delete gameOverScene;
    delete oldScene;
    gameOverScene = nullptr;
    connect(dynamic_cast<const QtPrivate::FunctionPointer<void(BattleScene::*)()>::Object*>(battleScene),
            &BattleScene::gameOver, this, &MyGame::gameOver);
}

void MyGame::exitGame()
{
    QMainWindow::close();
}

void MyGame::backToMainMenu()
{
    view->setScene(startMenuScene);
    delete gameOverScene;
    gameOverScene = nullptr;

}
