#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "self_glwidget.h"
#include <QHBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    self_glWidget *glWindow;
    QHBoxLayout *mainLayout;
};
#endif // WIDGET_H
