#ifndef WEATHER_H
#define WEATHER_H

class Lake;
class Desert;
class Green;

class Weather
{
public:
    virtual void change(Lake *p) = 0;
    virtual void change(Desert *p) = 0;
    virtual void change(Green *p) = 0;
    virtual ~Weather() {}
    static int humidity;
};

class Sunny: public Weather
{
public:
    static Sunny* instance();
    void change(Lake *p);
    void change(Desert *p);
    void change(Green *p);
    static void destroy();
protected:
    Sunny(){}
private:
    static Sunny* _instance;
};

class Cloudy: public Weather
{
public:
    static Cloudy* instance();
    void change(Lake *p);
    void change(Desert *p);
    void change(Green *p);
    static void destroy();
protected:
    Cloudy(){}
private:
    static Cloudy* _instance;
};

class Rainy: public Weather
{
public:
    static Rainy* instance();
    void change(Lake *p);
    void change(Desert *p);
    void change(Green *p);
    static void destroy();
protected:
    Rainy(){}
private:
    static Rainy* _instance;
};


#endif // WEATHER_H
