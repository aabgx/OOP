//
// Created by Laura on 5/26/2022.
//

#ifndef UNTITLED_COSREADONLYGUI_H
#define UNTITLED_COSREADONLYGUI_H
#include "Observer.h"
#include "Service.h"
#include "CosProd.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 256

class CosReadOnlyGUI : public QWidget, public Observer {
private:
    List& cos;

public:
    CosReadOnlyGUI(List& cos);

    void update() override;

    void paintEvent(QPaintEvent* event) override;

    ~CosReadOnlyGUI() {
        this->cos.removeObserver(this);
    }
};
#endif //UNTITLED_COSREADONLYGUI_H
