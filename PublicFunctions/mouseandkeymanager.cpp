#include "mouseandkeymanager.h"
MouseAndKeyManager::MouseAndKeyManager(QObject *parent) : QObject(parent)
{

}

void MouseAndKeyManager::keyPressed(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_A){
        emit sgkeyPressed_A(true);
    }else if(ev->key() == Qt::Key_D){
        emit sgkeyPressed_D(true);
    }else if(ev->key() == Qt::Key_E){
        emit sgkeyPressed_E(true);
    }else if(ev->key() == Qt::Key_Q){
        emit sgkeyPressed_Q(true);
    }else if(ev->key() == Qt::Key_S){
        emit sgkeyPressed_S(true);
    }else if(ev->key() == Qt::Key_W){
        emit sgkeyPressed_W(true);
    }
}

MouseAndKeyManager *MouseAndKeyManager::getInstance()
{
    static MouseAndKeyManager* instance = nullptr;
    if(!instance){
        instance = new MouseAndKeyManager();
    }
    return instance;
}

bool MouseAndKeyManager::getIsKeyPressed(Qt::Key key, int state)
{
    if(key == Qt::Key_A){
        return isKeyPressed(0X41);
    }else if(key == Qt::Key_D){
        return isKeyPressed(0X44);
    }else if(key == Qt::Key_E){
        return isKeyPressed(0X45);
    }else if(key == Qt::Key_Q){
        return isKeyPressed(0X51);
    }else if(key == Qt::Key_S){
        return isKeyPressed(0X53);
    }else if(key == Qt::Key_W){
        return isKeyPressed(0X57);
    }else if(key == Qt::Key_Control){
        return isKeyPressed(VK_CONTROL);
    }else if(key == Qt::Key_Space){
        return isKeyPressed(VK_SPACE);
    }
    return false;
}

bool MouseAndKeyManager::isKeyPressed(int keyValue)
{
    return (GetKeyState(keyValue))&(1<<(sizeof(SHORT)*8-1));
}
