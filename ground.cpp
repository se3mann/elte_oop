#include "ground.h"

Ground* Lake::change(Weather* x) {
    x->change(this);
    if (_water < 51) {
        Green *p = new Green(_name,_water);
        delete this;
        return p;
    } else {
        return this;
    }
}

Ground* Desert::change(Weather* x) {
    x->change(this);
    if (_water > 15) {
        Green *p = new Green(_name,_water);
        delete this;
        return p;
    } else {
        return this;
    }
}

Ground* Green::change(Weather* x) {
    x->change(this);
    if (_water > 50) {
        Lake *p = new Lake(_name, _water);
        return p;
        delete this;
    } else if (_water < 16) {
        Desert *p = new Desert(_name, _water);
        delete this;
        return p;
    } else {
        return this;
    }
}
