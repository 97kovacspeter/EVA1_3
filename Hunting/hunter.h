#ifndef HUNTER_H
#define HUNTER_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QHBoxLayout>
#include <QGridLayout>
#include "gamemanager.h"
#include "savegamewidget.h"
#include "loadgamewidget.h"


class Hunter : public QWidget {

    Q_OBJECT

public:
    explicit Hunter(QWidget *parent = 0);
    ~Hunter();

private slots:
    void startNewGame();
    void gameManager_gameOver();
    void gameManager_gameWon(GameManager::Player player);
    void doTimerUpdate();
    void viewUpdate();
    void pauseMsg();
    void clickDecider();
    void senderSize(int size);


public slots:

    void loadGame();
    void saveGame();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    GameManager* _gameManager;
    SaveGameWidget* _saveGameWidget;
    LoadGameWidget* _loadGameWidget;
    QString _won;

    QGridLayout* _sightGrid;

    QLabel* _timerLabel;
    QLabel* _stepLabel;

    QPushButton* _threeButton;
    QPushButton* _fiveButton;
    QPushButton* _sevenButton;

    QPushButton* _pauseButton;





    std::vector<std::vector<QPushButton*> > buttonGrid;

};

#endif // HUNTER_H
