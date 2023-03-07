//
// Created by Laura on 5/25/2022.
//

#ifndef UNTITLED_COSCRUDGUI_H
#define UNTITLED_COSCRUDGUI_H
#include "CosProd.h"

#include "Observer.h"
#include "Service.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qslider.h>
#include <qlayout>
#include <vector>

using std::vector;

class CosCRUDGUI : public QWidget, public Observer {
private:
    List& cos;
    ProdService& srv;
    QWidget* wndcos;
    QHBoxLayout* layout;
    QTableWidget* table;
    QSlider* slider;
    QPushButton* btnadd;
    QPushButton* btnempty;


    void initComponents();
    void connectSignals();

    void populateTable(QTableWidget* table, const vector<Produs>& all);

public:
    explicit CosCRUDGUI(List& cos,ProdService& srv):cos{cos},srv{srv}{
        wndcos = new QWidget;
        layout=new QHBoxLayout;
        btnadd = new QPushButton("GENERARE PRODUSE RANDOM");
        btnempty = new QPushButton("GOLESTE COSUL");
        slider=new QSlider;
        table=new QTableWidget(0,4);

    };
    //CosCRUDGUI(List& cos,ProdService& srv);
    void run();

    void update() override;

    ~CosCRUDGUI() {
        this->cos.removeObserver(this);
    }
};
#endif //UNTITLED_COSCRUDGUI_H
