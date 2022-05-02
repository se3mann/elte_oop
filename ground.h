#ifndef GROUND_H
#define GROUND_H

#include <string>
#include "weather.h"

class Ground
{
public:
    std::string getName() const { return _name; }
    int getWater() const { return _water; }
    virtual std::string getType() const = 0;
    bool exist() const { return _water > -1; }
    void changeWater(int e) { _water += e; }
    virtual Ground* change(Weather* x) = 0;
    virtual ~Ground() {}
protected:
    std::string _name;
    int _water;
    Ground(const std::string &str, int e = 0) : _name(str), _water(e) {}
};

class Lake: public Ground {
public:
    Lake(const std::string &str, int e = 0) : Ground(str, e) {}
    Ground* change(Weather* x) override;
    std::string getType() const override { return "lake"; }
};


class Desert: public Ground {
public:
    Desert(const std::string &str, int e = 0) : Ground(str, e) {}
    Ground* change(Weather* x) override;
    std::string getType() const override { return "desert"; }
};

class Green: public Ground {
public:
    Green(const std::string &str, int e = 0) : Ground(str, e) {}
    Ground* change(Weather* x) override;
    std::string getType() const override { return "green"; }
};

#endif // GROUND_H
