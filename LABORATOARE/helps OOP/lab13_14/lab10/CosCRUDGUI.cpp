//
// Created by Laura on 5/25/2022.
//

#include "CosCRUDGUI.h"

void CosCRUDGUI::run(){
    this->cos.addObserver(this);

    this->initComponents();
    this->connectSignals();
    this->update();
    wndcos->show();
}

void CosCRUDGUI::initComponents() {
    wndcos->setLayout(layout);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(table);

    slider->setMinimum(0);
    slider->setMaximum(40);
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    layout->addWidget(slider);


    layout->addWidget(btnadd);
    layout->addWidget(btnempty);
}

void CosCRUDGUI::connectSignals() {
    QObject::connect(btnadd, &QPushButton::clicked, [this]() {

        int number = slider->value();
        srv.addrandomsrv(number);
        cos.notify();
    });
    QObject::connect(btnempty, &QPushButton::clicked, [this]() {
        cos.emptylist();
        cos.notify();
    });
}

void CosCRUDGUI::populateTable(QTableWidget* table, const vector<Produs>& all) {
    this->table->clearContents();
    this->table->setRowCount(static_cast<int>(all.size()));

    int lineNumber = 0;
    for (auto& proc : all) {
        this->table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(proc.getNume())));
        this->table->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(proc.getTip())));
        this->table->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(proc.getProd())));
        this->table->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(proc.getPret())));
        lineNumber++;
    }
}

void CosCRUDGUI::update() {
    this->populateTable(table, this->cos.getallfromlist());
}