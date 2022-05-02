#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <time.h>

#include "weather.h"
#include "ground.h"

using namespace std;

//Üres fájlokra
bool isEmpty(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}


//függvény, amely feldolgozza a bemeneti fájlt
//bemeneti adatai egy Groundra mutató pointereket tartalmazó tömb és fájlnév
//a függvényben szerepel statikus változó értékadása is
void create(const string &str, vector<Ground*> &grounds)
{

    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}
    if(isEmpty(f)) { cout << "The file is empty!\n"; exit(1);}
    int n; f >> n;
    grounds.resize(n);
    for(int i=0; i<n; i++) {
        string name; char ch; int e;
        string tmp;
        f >> name >> tmp >> ch >> e;
        name += " " + tmp;
        switch(ch) {
            case 't': grounds[i] = new Lake(name, e); break;
            case 'p': grounds[i] = new Desert(name, e); break;
            case 'z': grounds[i] = new Green(name, e); break;
        }
    }
    f >> Weather::humidity;
    f.close();
}

void printGrounds(vector<Ground*> &grounds) {
    if (grounds[0] != nullptr) {
        cout << "Number of grounds: " << grounds.size() << '\n';
        for(unsigned int i=0; i<grounds.size(); i++) {
            if (grounds[i]->exist()) cout << grounds[i]->getName() << " type: " << grounds[i]->getType() << " water: " << grounds[i]->getWater() << '\n';
        }
        cout << "The humidity: " << Weather::humidity <<"\n\n\n\n";
    } else {
        cout << "Empty!\n";
    }
}

//A valószínûségi eset eldöntésére való függvény, százalékot kell megadni neki floatban
bool yesOrNo(float probabilityOfYes) {
   srand (time(NULL));
   return (float)(rand() % 100 + 1) < probabilityOfYes;
}

//Törli az összes heapen lévõ Weather objektumot
void destroyWeather() {
    Sunny::destroy();
    Rainy::destroy();
    Cloudy::destroy();
}

//Törli a földeket a heap-rõl
void destroy(vector<Ground*> &grounds) {
    for (unsigned int i=0;i<grounds.size();i++) {
      delete grounds[i];
      grounds[i] = nullptr;
    }
}


//Minden föld egyszerre hat az idõjárásra, esõ után csak akkor lesz 30% páratartalom, ha elõtte 70% volt
void simulation(vector<Ground*> &grounds) {
    bool allTheSame = true;
    for (unsigned int i=0;i<grounds.size()-1;i++) {
        if (grounds[i]->exist()) allTheSame = allTheSame && grounds[i]->getType() == grounds[i+1]->getType();
    }
    while (!allTheSame) {
        if (Weather::humidity > 70) {
            Weather *w = Rainy::instance();
            cout << "The weather will be rainy!\n";
            for (unsigned int i=0;i<grounds.size();i++) {
                Ground* tmp;
                tmp = grounds[i]->change(w);
                grounds[i] = tmp;
                cout << grounds[i]->getName() << " type: " << grounds[i]->getType() << ", water amount: " << grounds[i]->getWater() << endl;
            }
            Weather::humidity = 30;
            cout << Weather::humidity << '\n';
            cout << "End of round!\n\n";
            allTheSame = true;
            for (unsigned int i=0;i<grounds.size()-1;i++) { //Ezt lehetne elegánsabban is, beleágyazni a kölcsönhatásokat szimuláló cikolusba
                if (grounds[i]->exist()) allTheSame = allTheSame && grounds[i]->getType() == grounds[i+1]->getType();
            }
    } else if (Weather::humidity < 40) {
        Weather *w = Sunny::instance();
        cout << "The weather will be sunny!\n";
        for (unsigned int i=0;i<grounds.size();i++) {
                Ground* tmp;
                tmp = grounds[i]->change(w);
                grounds[i] = tmp;
                cout << grounds[i]->getName() << " type: " << grounds[i]->getType() << ", water amount: " << grounds[i]->getWater() << endl;
            }
        cout << Weather::humidity << '\n';
        cout << "End of round!\n\n";
        allTheSame = true;
        for (unsigned int i=0;i<grounds.size()-1;i++) { //Ezt lehetne elegánsabban is, beleágyazni a kölcsönhatásokat szimuláló cikolusba
            if (grounds[i]->exist()) allTheSame = allTheSame && grounds[i]->getType() == grounds[i+1]->getType();
        }
    } else /*if (40 <= Weather::humidity && Weather::humidity <= 70)*/ { //ez a három ág lefedi az összes lehetséges értéket
        float probability = (Weather::humidity-30) * 3.3;
        bool rainy = yesOrNo(probability);
        if (rainy) {
            Weather *w = Rainy::instance();
            cout << "The weather will be rainy!\n";
            for (unsigned int i=0;i<grounds.size();i++) {
                Ground* tmp;
                tmp = grounds[i]->change(w);
                grounds[i] = tmp;
                cout << grounds[i]->getName() << " type: " << grounds[i]->getType() << ", water amount: " << grounds[i]->getWater() << endl;
            }
            cout << Weather::humidity << '\n';
            cout << "End of round!\n\n";
            allTheSame = true;
            for (unsigned int i=0;i<grounds.size()-1;i++) { //Ezt lehetne elegánsabban is, beleágyazni a kölcsönhatásokat szimuláló cikolusba
                if (grounds[i]->exist()) allTheSame = allTheSame && grounds[i]->getType() == grounds[i+1]->getType();
            }
        } else {
            Weather *w = Cloudy::instance();
            cout << "The weather will be Cloudy!\n";
            for (unsigned int i=0;i<grounds.size();i++) {
                Ground* tmp;
                tmp = grounds[i]->change(w);
                grounds[i] = tmp;
                cout << grounds[i]->getName() << " type: " << grounds[i]->getType() << ", water amount: " << grounds[i]->getWater() << endl;
            }
            cout << Weather::humidity << '\n';
            cout << "End of round!\n\n";
            allTheSame = true;
            for (unsigned int i=0;i<grounds.size()-1;i++) { //Ezt lehetne elegánsabban is, beleágyazni a kölcsönhatásokat szimuláló cikolusba
                if (grounds[i]->exist()) allTheSame = allTheSame && grounds[i]->getType() == grounds[i+1]->getType();
            }
        }
    }
    }
}

//Az idõjárás lineárisan járja be mindig a földeket
void simulation_2(vector<Ground*> &grounds) {
    bool allTheSame = true;
    for (unsigned int i=0;i<grounds.size()-1;i++) {
        if (grounds[i]->exist()) allTheSame = allTheSame && grounds[i]->getType() == grounds[i+1]->getType();
    }
    while(!allTheSame) {
        Weather* r = Rainy::instance();
        Weather* s = Sunny::instance();
        Weather* c = Cloudy::instance();

        for (unsigned int i=0;i<grounds.size();i++) {
            Ground *tmp;
            if (Weather::humidity > 70) {
                tmp = grounds[i]->change(r);
                Weather::humidity  = 30;
            } else if (Weather::humidity < 40) {
                tmp = grounds[i]->change(s);
            } else {
                float prob = (Weather::humidity-30) * 3.3;
                bool rainy = yesOrNo(prob);
                if (rainy) {
                    tmp = grounds[i]->change(r);
                    } else {
                        tmp = grounds[i]->change(c);
                    }
            }
            grounds[i] = tmp;
            cout << grounds[i]->getName() << " type: " << grounds[i]->getType() << ", water amount: " << grounds[i]->getWater() << " humidity: " << Weather::humidity << endl;
        }

        allTheSame = true;
        for (unsigned int i=0;i<grounds.size()-1;i++) {
            if (grounds[i]->exist()) allTheSame = allTheSame && grounds[i]->getType() == grounds[i+1]->getType();
        }
        cout << "End of round!\n\n";
    }
}


#define NORMAL
#ifdef NORMAL

int main()
{
    vector<Ground*> grounds;
    create("input_4.txt", grounds);
    printGrounds(grounds);
    simulation(grounds);
    create("input_4.txt", grounds);
    simulation_2(grounds);
    destroy(grounds);

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1 elem", "input_1.txt")
{
    vector<Ground*> grounds;
    vector<Ground*> tmp;
    create("input_1.txt", grounds);
    create("input_1.txt", tmp);
    simulation(grounds); //Ha 1 darab föld van, nem szabad szimulációnak lefutnia
    CHECK(grounds.size() == 1);
    CHECK(grounds[0]->getName() == tmp[0]->getName());
    CHECK(grounds[0]->getType() == tmp[0]->getType());
    CHECK(grounds[0]->getWater() == tmp[0]->getWater());
    CHECK(Weather::humidity == 80);
    destroy(grounds);
    destroy(tmp);
}


TEST_CASE("2 elem esos", "input_2.txt")
{
    vector<Ground*> grounds;
    vector<Ground*> tmp;
    create("input_2.txt", grounds);
    create("input_2.txt", tmp);
    CHECK(Weather::humidity == 98);
    simulation(grounds);
    CHECK(grounds.size() == 2);
    CHECK(grounds[0]->getType() == grounds[1]->getType());
    CHECK(grounds[0]->getWater()-20 == tmp[0]->getWater());
    CHECK(grounds[1]->getWater()-15 == tmp[1]->getWater());
    CHECK(Weather::humidity == 30);
    destroy(grounds);
    destroy(tmp);
}


TEST_CASE("2_b", "input_3.txt")
{
    vector<Ground*> grounds;
    vector<Ground*> tmp;
    create("input_3.txt", grounds);
    create("input_3.txt", tmp);
    CHECK(Weather::humidity == 20);
    simulation(grounds);
    CHECK(grounds[0]->getType() == grounds[1]->getType());
    CHECK(grounds[0]->getWater()+10 == tmp[0]->getWater());
    CHECK(grounds[1]->getWater()+6 == tmp[1]->getWater());
    CHECK(Weather::humidity == 45);
    destroy(grounds);
    destroy(tmp);
}

TEST_CASE("4 elem", "input_4.txt")
{
    vector<Ground*> grounds;
    create("input_4.txt", grounds);
    CHECK(Weather::humidity == 98);
    simulation(grounds);
    CHECK(grounds[0]->getType() == grounds[1]->getType());
    CHECK(grounds[1]->getType() == grounds[2]->getType());
    CHECK(grounds[2]->getType() == grounds[3]->getType());
    destroy(grounds);
}

TEST_CASE("osztalyok", "")
{
    Weather::humidity = 0;
    CHECK(Weather::humidity == 0);
    Ground* p = new Lake("MR Lake", 80);
    CHECK(p->getName() == "MR Lake");
    CHECK(p->getWater() == 80);
    CHECK(p->getType() == "lake");
    Weather* sunny = Sunny::instance();
    Ground* x = p->change(sunny);
    CHECK(Weather::humidity == 15);
    CHECK(x->getType() == p->getType());
    CHECK(p->getWater() == 70);
    CHECK(p->exist() == true);
    x = p->change(sunny);
    x = p->change(sunny); //p által mutatott terület felszabadul
    CHECK(x->getType() == "green");
    Ground* y = new Desert("Mr Desert", 2);
    y = y->change(sunny);
    CHECK(y->exist() == false);
    delete x;
    delete y;
}


#endif // NORMAL_MODE
