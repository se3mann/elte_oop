#include "weather.h"
#include "ground.h"

int Weather::humidity = 0;

//implementation of class Sunny
Sunny* Sunny::_instance = nullptr;
Sunny* Sunny::instance() {
    if (_instance == nullptr) _instance = new Sunny();
    return _instance;
}

void Sunny::destroy() {
    if (_instance!=nullptr) delete _instance;
}

void Sunny::change(Lake* p) {
    p->changeWater(-10);
    if (p->exist()) humidity += 15;
}

void Sunny::change(Desert* p) {
    p->changeWater(-3);
    if (p->exist()) humidity += 5;
}

void Sunny::change(Green* p) {
    p->changeWater(-6);
    if (p->exist()) humidity += 10;
}

//implementation of class Cloudy
Cloudy* Cloudy::_instance = nullptr;
Cloudy* Cloudy::instance() {
    if (_instance == nullptr) _instance = new Cloudy();
    return _instance;
}

void Cloudy::destroy() {
    if (_instance!=nullptr) delete _instance;
}

void Cloudy::change(Lake* p) {
    p->changeWater(-3);
    if (p->exist()) humidity += 15;
}

void Cloudy::change(Desert* p) {
    p->changeWater(-1);
    if (p->exist()) humidity += 5;
}

void Cloudy::change(Green* p) {
    p->changeWater(-2);
    if (p->exist()) humidity += 10;
}

//implementation of class Rainy
Rainy* Rainy::_instance = nullptr;
Rainy* Rainy::instance() {
    if (_instance == nullptr) _instance = new Rainy();
    return _instance;
}

void Rainy::destroy() {
    if (_instance!=nullptr) delete _instance;
}

void Rainy::change(Lake* p) {
    p->changeWater(20);
    if (p->exist()) humidity += 15;
}

void Rainy::change(Desert* p) {
    p->changeWater(20);
    if (p->exist()) humidity += 5;
}

void Rainy::change(Green* p) {
    p->changeWater(15);
    if (p->exist()) humidity += 10;
}
