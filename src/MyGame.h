//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_MYGAME_H
#define QT_PROGRAMMING_2024_MYGAME_H

#include <QGraphicsView>
#include <QMainWindow>

#include "Scenes/BattleScene.h"
#include "Scenes/Scene.h"

class MyGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyGame(QWidget* parent = nullptr);

    void startGame(const QString& gameMode);

    void gameOver(const QString&);

    void reStartGame();

    void exitGame();

    void backToMainMenu();

private:
    Scene* startMenuScene = nullptr;
    Scene* battleScene = nullptr;
    Scene* gameOverScene = nullptr;
    QGraphicsView* view;
};


#endif //QT_PROGRAMMING_2024_MYGAME_H
