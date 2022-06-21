#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include <QWidget>
class OSGWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OSGWidget(QWidget *parent = nullptr);
protected:
    void init();
signals:

};

#endif // OSGWIDGET_H
