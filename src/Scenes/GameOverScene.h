//
// Created by hp on 24-9-6.
//

#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#include "Scene.h"
#include <QGraphicsItem>
#include <QLabel>
#include <QPushButton>

class GameOverScene : public Scene
{
    Q_OBJECT

public:
    explicit GameOverScene(QObject* parent, const QString& text);

    QGraphicsPixmapItem* background;

    QLabel* gameOverLabel;

    QPushButton* restartButton;

    QPushButton* exitButton;

    QPushButton* mainMenuButton;

    QGraphicsProxyWidget* gameOverLabelProxy;

    QGraphicsProxyWidget* restartButtonProxy;

    QGraphicsProxyWidget* exitButtonProxy;

    QGraphicsProxyWidget* mainMenuButtonProxy;

signals:
    void restartGame();

    void exitGame();

    void backToMainMenu();

};



#endif //GAMEOVERSCENE_H
