#ifndef LYHLABEL_H
#define LYHLABEL_H

#include <QWidget>
#include <QColor>
#include "ui_lyhlabel.h"

class LYHLabel : public QWidget, public Ui_LYHLabel
{
    Q_OBJECT

public:
    explicit LYHLabel(QWidget *parent = nullptr);
    ~LYHLabel();

    void setText(QString text);
    void setPic(QString picPath);

    void updateQSS();
private:
    QColor m_borderColor;
    int m_borderWidth = 1;

    QString m_picPath;
};

#endif // LYHLABEL_H
