#pragma once

#include <QtWidgets>

class BufferContainer : public QWidget
{
    Q_OBJECT

    QVBoxLayout *layhi;
    QWidget *buf;

public:
    explicit BufferContainer(QWidget *init_widget = 0, QWidget *parent = 0);

    void closeEvent(QCloseEvent *);
    
signals:
    void imclosing(BufferContainer*);
    
public slots:
    
};
