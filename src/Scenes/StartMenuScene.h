//
// Created by hp on 24-9-6.
//

#ifndef STARTMENUSCENE_H
#define STARTMENUSCENE_H
#include "Scene.h"
#include <QGraphicsItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QLabel>

class StartMenuScene : public Scene
{
    Q_OBJECT

public:
    explicit StartMenuScene(QObject* parent);

signals:
    void startGame(QString);

private:
    QGraphicsPixmapItem* background;

    QPushButton* startButton;

    QGraphicsProxyWidget* startButtonProxy;

    QLabel* modeChooseLabel;

    QPushButton* playerModeButton;

    QPushButton* aiModeButton;

    QGraphicsProxyWidget* modeChooseWidgetProxy;

    QGraphicsProxyWidget* playerModeButtonProxy;

    QGraphicsProxyWidget* aiModeButtonProxy;

private slots:
    void chooseMode();

    void startPlayerMode();

    void startAIMode();
};


#endif //STARTMENUSCENE_H
