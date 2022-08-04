#ifndef MOUSEANDKEYMANAGER_H
#define MOUSEANDKEYMANAGER_H

#include <QObject>
#include <QDebug>
#include <QKeyEvent>
#include "windows.h"
#include "WinUser.h"
class MouseAndKeyManager : public QObject
{
    Q_OBJECT
public:
    explicit MouseAndKeyManager(QObject *parent = nullptr);
    void keyPressed(QKeyEvent *ev);

    static MouseAndKeyManager* getInstance();
    bool getIsKeyPressed(Qt::Key key, int state = 4); // 1=left, 2=right. 3=left&&right, 4 = left||right}
protected:
    bool isKeyPressed(int keyValue);
signals:
    void sgkeyPressed_A(bool isPressed);
    void sgkeyPressed_B(bool isPressed);
    void sgkeyPressed_C(bool isPressed);
    void sgkeyPressed_D(bool isPressed);
    void sgkeyPressed_E(bool isPressed);
    void sgkeyPressed_F(bool isPressed);
    void sgkeyPressed_G(bool isPressed);
    void sgkeyPressed_H(bool isPressed);
    void sgkeyPressed_I(bool isPressed);
    void sgkeyPressed_J(bool isPressed);
    void sgkeyPressed_K(bool isPressed);
    void sgkeyPressed_L(bool isPressed);
    void sgkeyPressed_M(bool isPressed);
    void sgkeyPressed_N(bool isPressed);
    void sgkeyPressed_O(bool isPressed);
    void sgkeyPressed_P(bool isPressed);
    void sgkeyPressed_Q(bool isPressed);
    void sgkeyPressed_R(bool isPressed);
    void sgkeyPressed_S(bool isPressed);
    void sgkeyPressed_T(bool isPressed);
    void sgkeyPressed_U(bool isPressed);
    void sgkeyPressed_V(bool isPressed);
    void sgkeyPressed_W(bool isPressed);
    void sgkeyPressed_X(bool isPressed);
    void sgkeyPressed_Y(bool isPressed);
    void sgkeyPressed_Z(bool isPressed);
};

#endif // MOUSEANDKEYMANAGER_H
