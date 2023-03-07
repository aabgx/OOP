#pragma once
#include <qwidget.h>
#include "Observer.h"
#include <qlistwidget.h>
#include "service.h"
#include <qmessagebox.h>
#include <qlayout.h>
#include <qwidget.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qimage.h>


#define CursorHeight 28
#define NormalWidth 130

using namespace std;




class ContractGUIReadOnly : public QWidget, public Observer {
private:
    Service& srv;
    
    void paintEvent(QPaintEvent* ev) override {
        auto lst = srv.get_all_contract();
        QPainter p{ this };
        for (auto el : lst) {
            int x = rand() % 600;
            int y = rand() % 400;
            p.drawRect(x, y, 70, 70);
        }
    }

    void initializeaza() {
        resize(800, 600);
    }
public:

    ContractGUIReadOnly(Service& srv) : srv(srv) {
        initializeaza();
        show();
    }

    void update() override {
        repaint();
    }
};