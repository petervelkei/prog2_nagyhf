#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<random>


using namespace std;

#define SEBESSEG 140
#define PRICEPERKM 10

// tervezői döntések
// vonat id-k növekvő sorrendben lesznek -> 1,2,3,4....
// minden vonatnak 4 kocsija lesz és minden kocsinak 100 helye
#define KOCSISZAM 4
#define HELYSZAM 100


class Allomas {
    string name;

public:
    Allomas() {}
    Allomas(string name) : name(name) {}

    string getNev() const { return name; }
};



class Csomopont : public Allomas {
    double distance;
    int hour;
    int min;
    int sec;
    double ar;

public:
    Csomopont() {}
    Csomopont(string name, double distance, int hour, int min, int sec, double ar)
        : Allomas(name), distance(distance), hour(hour), min(min), sec(sec), ar(ar) {}

    double getDistance() const { return distance; }
    int getHour() const { return hour; }
    int getMin() const { return min; }
    int getSec() const { return sec; }
    double getAr() const { return ar; }
};



class Vasutvonal {
    Csomopont* allomasok;
    size_t size;

public:
    Vasutvonal() : allomasok(nullptr), size(0) {}

    string operator[](size_t idx) const {
        if (idx >= size) {
            cerr << "Hiba: Tulindexeles!" << endl;
            return "";
        }
        return allomasok[idx].getNev();
    }

    Csomopont* getAllomasok()const{ return allomasok;}
    int getmeret() const { return size; }



    void addAllomas(const Csomopont& allomas) {
        Csomopont* temp = new Csomopont[size + 1];
        for (size_t i = 0; i < size; ++i) {
            temp[i] = allomasok[i];
        }
        temp[size++] = allomas;
        delete[] allomasok;
        allomasok = temp;
    }

};




// Kedvezményes osztálok
class Kedvezmeny{
    double percentage;

public:
    Kedvezmeny(double percentage = 0) : percentage(percentage) {}
    virtual string tipus() {}
	virtual double jegyar(double ar){
		return ar * getPercentage();
	}

    void setPercentage(int szazalek){
        percentage = szazalek;
    }

    double getPercentage()const{return (100 - percentage) / 100;}

};

class Teljesaru : public Kedvezmeny {
public:
    string tipus() override { return "Teljesaru"; }

	double jegyar(double ar){
		return ar * getPercentage();
	}

};

class Diak : public Kedvezmeny {
public:
    string tipus() override { return "Diak"; }

	double jegyar(double ar){
		return ar * getPercentage();
	}
};

class Nyugdijas : public Kedvezmeny {
public:
    string tipus() override { return "Nyugdijas"; }
	double jegyar(double ar){
		return ar * getPercentage();
	}
};




// Egy vonat adatai
class Vonat {
    Vasutvonal utvonal;

public:
    Vonat() {}
    Vonat(Vasutvonal utvonal) : utvonal(utvonal) {}

    void beolvasas(const char* filename, int melyik) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Hiba: A fajl nem nyithato meg!" << endl;
            return;
        }

        string line;
        int utvonal_szama = 0;
        bool elsoutvonal_beolvasva = false;

        while (getline(file, line) && !elsoutvonal_beolvasva) {
            stringstream ss(line);
            string token;

            getline(ss, token, ';'); // vonatszam
            int vonatszam = stoi(token);

            getline(ss, token, ';'); // allomas
            string allomas_nev = token;

            getline(ss, token, ';'); // tavolsag
            double tavolsag = stod(token);

            getline(ss, token, ';'); // ora
            int ora = stoi(token);

            getline(ss, token, ';'); // perc
            int perc = stoi(token);

            getline(ss, token, ';'); // mp
            int mp = stoi(token);

            int ar = tavolsag * PRICEPERKM;

            if (vonatszam == melyik) {
                Csomopont allomas(allomas_nev, tavolsag, ora, perc, mp, ar);
                utvonal.addAllomas(allomas);
                ++utvonal_szama;
            }

            if(vonatszam > melyik){
                elsoutvonal_beolvasva = true;
            }
        }

        file.close();
    }

    string operator[](size_t idx)const{
        if(idx >= utvonal.getmeret()) throw "error";
        return utvonal[idx];
    }

    string induloallomas() {
        if (utvonal.getmeret() == 0) {
            cerr << "Hiba: Ures vasutvonal!" << endl;
            return "";
        }
        return utvonal[0];
    }

    string vegall() const {
        if (utvonal.getmeret() == 0) {
            cerr << "Hiba: Ures vasutvonal!" << endl;
            return "";
        }
        return utvonal[utvonal.getmeret() - 1];
    }

    void kiir(size_t honnantol = 0){
        for(size_t i = honnantol; i < utvonal.getmeret(); i++){
            cout << i+1 << ". " <<utvonal[i] << endl;
        }
        cout << endl;
    }

    void idokiir(size_t honnatol, size_t meddig, int ibekapcs){
        int i = 1;
        if(ibekapcs){
            cout << i++ << ". " << setw(2) << setfill('0')  << utvonal.getAllomasok()[honnatol - 1].getHour() << ":" 
                << setw(2) << setfill('0') << utvonal.getAllomasok()[honnatol - 1].getMin()<< ":" 
                << setw(2) << setfill('0') << utvonal.getAllomasok()[honnatol - 1].getSec()
                << " - "
                << setw(2) << setfill('0')  << utvonal.getAllomasok()[meddig - 1].getHour() << ":" 
                << setw(2) << setfill('0') << utvonal.getAllomasok()[meddig - 1].getMin()<< ":" 
                << setw(2) << setfill('0') << utvonal.getAllomasok()[meddig - 1].getSec() << endl;
        }
        else{
            cout << setw(2) << setfill('0')  << utvonal.getAllomasok()[honnatol - 1].getHour() << ":" 
                << setw(2) << setfill('0') << utvonal.getAllomasok()[honnatol - 1].getMin()<< ":" 
                << setw(2) << setfill('0') << utvonal.getAllomasok()[honnatol - 1].getSec()
                << " - "
                << setw(2) << setfill('0')  << utvonal.getAllomasok()[meddig - 1].getHour() << ":" 
                << setw(2) << setfill('0') << utvonal.getAllomasok()[meddig - 1].getMin()<< ":" 
                << setw(2) << setfill('0') << utvonal.getAllomasok()[meddig - 1].getSec() << endl;
        }
    }

    void jegykiiro(size_t honnan, size_t meddig){
        cout << utvonal[honnan - 1] << " - " << utvonal[meddig - 1] << endl;
        idokiir(honnan, meddig, 0);
    }

    double jegyarmeghat(size_t honnan, size_t meddig){
        return utvonal.getAllomasok()[meddig-1].getAr() - utvonal.getAllomasok()[honnan-1].getAr();
    }

    int kocsimeghat(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, KOCSISZAM);
        return dis(gen);
    }

    // kellene egy olyan függvény amelyik a kiválasztott random kocsi alapján foglalja az (adott foglaltság + 1). helyet
    // ha az egyenlo a helykapacitassal akkor ugorjon a kovetkezo kocsira és ott foglaljon helyet
    // fajlba is irja at a foglaltsagot az adott vonat adott kocsi adott helyszamat novelje meg
    int helyfoglalas(const char* filename, int vonatid, int kocsiszam) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Hiba: A fajl nem nyithato meg!" << endl;
            return 1;
        }

        string line;
        int db = 0;
        stringstream updated_file;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ';');
            int vonatszam = stoi(token);
            int kocsi1, hely1, kocsi2, hely2, kocsi3, hely3, kocsi4, hely4;
            getline(ss, token, ';');
            kocsi1 = stoi(token);
            getline(ss, token, ';');
            hely1 = stoi(token);
            getline(ss, token, ';');
            kocsi2 = stoi(token);
            getline(ss, token, ';');
            hely2 = stoi(token);
            getline(ss, token, ';');
            kocsi3 = stoi(token);
            getline(ss, token, ';');
            hely3 = stoi(token);
            getline(ss, token, ';');
            kocsi4 = stoi(token);
            getline(ss, token, ';');
            hely4 = stoi(token);

            if (vonatszam == vonatid) {
                if (kocsiszam == 1) {
                    if (hely1 < HELYSZAM) {
                        hely1++;
                        db = hely1;
                    } else {
                        kocsiszam++;
                        hely2++;
                        db = hely2;
                    }
                } else if (kocsiszam == 2) {
                    if (hely2 < HELYSZAM) {
                        hely2++;
                        db = hely2;
                    } else {
                        kocsiszam++;
                        hely3 ++;
                        db = hely3;
                    }
                } else if (kocsiszam == 3) {
                    if (hely3 < HELYSZAM) {
                        hely3++;
                        db = hely3;
                    } else {
                        kocsiszam++;
                        hely4 ++;
                        db = hely4;
                    }
                } else if (kocsiszam == 4) {
                    if (hely4 < HELYSZAM) {
                        hely4++;
                        db = hely4;
                    } else {
                        kocsiszam = 1;
                        hely1 ++;
                        db = hely1;
                    }
                }

                updated_file << vonatszam << ";" << kocsi1 << ";" << hely1 << ";" << kocsi2 << ";" << hely2 << ";" << kocsi3 << ";" << hely3 << ";" << kocsi4 << ";" << hely4 << endl;
            } else {
                updated_file << line << endl;
            }
        }
        file.close();
        ofstream temp(filename);
        temp << updated_file.str();
        temp.close();
        return db;
    }



    void kezdovegall(){
        cout << induloallomas() << " - " << vegall() << endl;
    }

};



// Az összes vonat adatja
class Jegy {
    Vonat* tomb;
    size_t tombmeret;
    Kedvezmeny kedv;

public:
    Jegy() : tomb(nullptr), tombmeret(0), kedv(0) {}


    // Vonat hozzáadása a tömbhöz
    void add(const Vonat& vonat) {
        Vonat* temp = new Vonat[tombmeret + 1];
        for (size_t i = 0; i < tombmeret; ++i) {
            temp[i] = tomb[i];
        }
        temp[tombmeret++] = vonat;
        delete[] tomb;
        tomb = temp;
    }

    // Vonatok db számának meghatározása
    int vonatszam(const char* filename){
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Hiba: A fajl nem nyithato meg!" << endl;
            return 1;
        }

        string line;
        int db = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ';');
            int vonatszam = stoi(token);
            db = vonatszam;
        }
        return db;
    }


    // Vonatok beolvasása a tömbbe
    void beolvasas(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Hiba: A fajl nem nyithato meg!" << endl;
            return;
        }

        string line;
        int vonatok_szama = vonatszam("inputs/vasutvonalak.csv");
        int beolvasott_vonatok_szama = 1;
        int db = 0;
        while (getline(file, line) && beolvasott_vonatok_szama <= vonatok_szama) {
            stringstream ss(line);
            string token;

            getline(ss, token, ';');
            int vonatszam = stoi(token);
            Vonat vonat;
            
            if(vonatszam == beolvasott_vonatok_szama){
                ++db;
                if(db == 1){
                    vonat.beolvasas(filename, vonatszam);
                    add(vonat);
                    ++beolvasott_vonatok_szama;
                }
            }
            db = 0;
        }

        file.close();
    }


    // Tömb elemeinek kiírása
    void indulo(size_t choice){
        if(choice > tombmeret) throw "error";

        system("cls || clear");
        cout << "Válassz induló állomást" << endl
            << "-----------------------" << endl;
        
        tomb[choice - 1].kiir();
    }


    void veg(size_t mettol, size_t choice){
        if(choice > tombmeret) throw "error";

        system("cls || clear");
        cout << "Válassz célállomást" << endl
            << "-------------------" << endl;
        
        tomb[choice - 1].kiir(mettol);
    }


    // Időpontok kiírása
    void idopontok(size_t mettol, size_t meddig, size_t choice){
        if(choice > tombmeret) throw "error";

        system("cls || clear");
        cout << "Válassz időpontot" << endl
            << "-----------------" << endl;

        tomb[choice - 1].idokiir(mettol, meddig, 1);
    }

    void jegytipus(size_t choice, size_t mettol, size_t meddig, size_t mikor){
        system("cls || clear");
        cout << "Válassz jegytipust" << endl
            << "------------------" << endl;
        
        cout << "1. Teljesaru jegy" << endl
            << "2. Diakjegy" << endl
            << "3. Nyugdijas jegy" << endl;

        int a;
        cout << endl << "Valassz egy menupontot: ";
        cin >> a;

        system("cls || clear");
        cout << "Jegyadatok" << endl
            << "----------" << endl;
        
        // honnan - hova, mikor
        tomb[choice - 1].jegykiiro(mettol, meddig);

        // melyik kocsi - melyik hely
        int kocs = tomb[choice - 1].kocsimeghat();
        int hely;
        hely = tomb[choice-1].helyfoglalas("inputs/vonatok.csv",choice,kocs);
        cout << kocs << ". kocsi - " << hely << ". hely"<< endl;

        // jegytipus - ar
        // dynamic castokat kiszedtem mert pointeresen nem tudtam megcsinálni
        double jegyara = tomb[choice-1].jegyarmeghat(mettol, meddig);
        if(a == 1){
            kedv.setPercentage(0);
            //Teljesaru* t = dynamic_cast<Teljesaru*>(kedv);
            cout << "Teljesaru" << " - " << kedv.jegyar(jegyara)  << " Ft" << endl;
        }
        else if(a == 2){
            kedv.setPercentage(50);
            //Diak* d = dynamic_cast<Diak*>(kedv);
            cout << "Diak" << " - " << kedv.jegyar(jegyara)  << " Ft" << endl;
        }
        else if(a == 3){
            kedv.setPercentage(90);
            //Nyugdijas* n = dynamic_cast<Nyugdijas*>(kedv);
            cout << "Nyugdijas" << " - " << kedv.jegyar(jegyara) << " Ft" << endl;
        }
    }


    // Kezdő és végállomások kiírása
    void kezdoesvegallomasok(){
        system("cls || clear");
        cout << "Válassz útvonalat" << endl
            << "-----------------" << endl;

        for(size_t i = 0; i < tombmeret ; i++){
            cout << i+1 << ". ";
            tomb[i].kezdovegall();
        }
        cout << endl;
    }


    ~Jegy() {
        delete[] tomb;
    }
};



// A tányleges menü megvalósítása itt történik
class JegyMenedzser {
    Jegy teszt;
public:
    JegyMenedzser() {
        teszt.beolvasas("inputs/vasutvonalak.csv");
    }

    void menu() {
        int choice;
        do {
            system("cls || clear");
            cout << "1. Vonat hozzaadas" << endl
                << "2. Vonat törles" << endl
                << "3. Jegy vasarlas" << endl
                << "4. Kilepes" << endl
                << endl << "Valassz egy menupontot: ";
            cin >> choice;
            switch (choice) {
            case 1:
                system("cls || clear");
                cout << "Vonat hozzadasa" << endl
                    << "----------------" << endl;

                cout << endl << "Nyomj enter a menube valo visszatereshez ";
                getchar();
                getchar();
                break;

            case 2:
                system("cls || clear");
                cout << "Vonatútvonal kiválasztása" << endl
                    << "-------------------------" << endl;

                cout << endl << "Válassz egy menüpontot: ";
                getchar();
                getchar();
                break;

            case 3:
                // kezdő és végállomások listázása
                teszt.kezdoesvegallomasok();

                // választott utvonal állomásainak listázása
                int c;
                cout << endl << "Válassz egy menüpontot: ";
                cin >> c;
                teszt.indulo(c);

                // választott utvonal állomásainak listázása
                // az előbb választott állomástól
                int d;
                cout << endl << "Válassz egy menüpontot: ";
                cin >> d;
                teszt.veg(d, c);

                // időpontok listázása
                int f;
                cout << endl << "Válassz egy menüpontot: ";
                cin >> f;
                teszt.idopontok(d,f,c);

                // jegytípus véglegesítése
                int g;
                cout << endl << "Válassz egy menüpontot: ";
                cin >> g;
                teszt.jegytipus(c, d, f , g);


                cout << endl << "Nyomj entert a menube valo visszatereshez: ";
                getchar();
                getchar();
                break;

            case 4:
                break;

            default:
                system("cls || clear");
                cout << "Error, nyomj entert a menube valo visszatereshez: ";
                getchar();
                getchar();
                break;

            }
        } while (choice != 4);
    }
};



int main() {
    JegyMenedzser t;
    t.menu();
}
