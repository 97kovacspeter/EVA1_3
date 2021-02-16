#include <QString>
#include <QtTest>
#include <QThread>
#include <gamemanager.h>

class HunterTestTest : public QObject{

    Q_OBJECT

public:
    HunterTestTest();

private:
    GameManager* _gameManager;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNewGame();
    void testStepGame();
    void testPause();
    void testWinY();

};

HunterTestTest::HunterTestTest(){


}

void HunterTestTest::initTestCase(){

    _gameManager = new GameManager;
}

void HunterTestTest::cleanupTestCase(){

    delete _gameManager;
}

void HunterTestTest::testNewGame(){

    _gameManager->newGame(3);

   QCOMPARE(_gameManager->getField(0,0),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(0,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(0,2),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(1,0),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(1,1),GameManager::RED);
   QCOMPARE(_gameManager->getField(1,2),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(2,0),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(2,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(2,2),GameManager::YELLOW);

}

void HunterTestTest::testStepGame(){
    _gameManager->newGame(3);

   QCOMPARE(_gameManager->getField(0,0),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(0,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(0,2),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(1,0),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(1,1),GameManager::RED);
   QCOMPARE(_gameManager->getField(1,2),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(2,0),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(2,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(2,2),GameManager::YELLOW);

   _gameManager->stepGame(1,0);

   QCOMPARE(_gameManager->getField(0,0),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(0,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(0,2),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(1,0),GameManager::RED);
   QCOMPARE(_gameManager->getField(1,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(1,2),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(2,0),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(2,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(2,2),GameManager::YELLOW);

   _gameManager->enableYellow(0,0);
   _gameManager->stepGame(0,1);

   QCOMPARE(_gameManager->getField(0,0),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(0,1),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(0,2),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(1,0),GameManager::RED);
   QCOMPARE(_gameManager->getField(1,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(1,2),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(2,0),GameManager::YELLOW);
   QCOMPARE(_gameManager->getField(2,1),GameManager::GRAY);
   QCOMPARE(_gameManager->getField(2,2),GameManager::YELLOW);



}

void HunterTestTest::testPause(){
    _gameManager->newGame(3);
    _gameManager->pauseTester();
    _gameManager->stepGame(1,0);
    QCOMPARE(_gameManager->getField(0,0),GameManager::YELLOW);
    QCOMPARE(_gameManager->getField(0,1),GameManager::GRAY);
    QCOMPARE(_gameManager->getField(0,2),GameManager::YELLOW);
    QCOMPARE(_gameManager->getField(1,0),GameManager::GRAY);
    QCOMPARE(_gameManager->getField(1,1),GameManager::RED);
    QCOMPARE(_gameManager->getField(1,2),GameManager::GRAY);
    QCOMPARE(_gameManager->getField(2,0),GameManager::YELLOW);
    QCOMPARE(_gameManager->getField(2,1),GameManager::GRAY);
    QCOMPARE(_gameManager->getField(2,2),GameManager::YELLOW);
    _gameManager->pauseTester();
    _gameManager->stepGame(1,0);
    QCOMPARE(_gameManager->getField(0,0),GameManager::YELLOW);
    QCOMPARE(_gameManager->getField(0,1),GameManager::GRAY);
    QCOMPARE(_gameManager->getField(0,2),GameManager::YELLOW);
    QCOMPARE(_gameManager->getField(1,0),GameManager::RED);
    QCOMPARE(_gameManager->getField(1,1),GameManager::GRAY);
    QCOMPARE(_gameManager->getField(1,2),GameManager::GRAY);
    QCOMPARE(_gameManager->getField(2,0),GameManager::YELLOW);
    QCOMPARE(_gameManager->getField(2,1),GameManager::GRAY);
    QCOMPARE(_gameManager->getField(2,2),GameManager::YELLOW);
}

void HunterTestTest::testWinY(){
     _gameManager->newGame(3);
     _gameManager->stepGame(0,1);
     _gameManager->enableYellow(2,0);
     _gameManager->stepGame(1,0);
     _gameManager->stepGame(1,1);
     _gameManager->enableYellow(2,2);
     _gameManager->stepGame(1,2);
     _gameManager->stepGame(0,1);
     _gameManager->enableYellow(1,2);
     _gameManager->stepGame(1,1);
     QCOMPARE(_gameManager->canstepTester(),false);
}






QTEST_APPLESS_MAIN(HunterTestTest)

#include "tst_huntertesttest.moc"
