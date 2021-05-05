#include <iostream>
#include "matrice.hpp"
#include <fstream>
#include <iomanip>
#include <windows.h>
#include "client.hpp"
#include <algorithm>
#include <thread>

using namespace odin;


bool thread2_start = true;
vector<Matrice> aux;

DWORD WINAPI thread2(LPVOID pm)
{

    string s;
    std::cin >> s;
    while (s != "stop")  // daca s-a citit stop se opreste thread-ul secund.
    {
        if(s == "cls")
            system("cls");
        std::cin >> s;
    }

    thread2_start = false;
    return 0;

}

class ReteaNeuronala
{

private:

    struct punct
    {
        int x, y;
    };
    int index = 0;
    vector<Matrice> weights;
    vector<Matrice> biases;
    string structura;
    vector<Matrice> input;
    vector<Matrice> output;
    double rata_de_invatare = 0.8;

public:

    ReteaNeuronala(vector<Matrice> input_retea, vector<Matrice> output_retea = aux, string structura_retea = "[]", double rata_de_invatare_retea = 0.8)
    {
        input = input_retea;
        output = output_retea;
        structura = structura_retea;
        rata_de_invatare = rata_de_invatare_retea;

    }


    // Aceasta functie este extrem de importanta in aceasta biblioteca deoarece antreneaza sinapsele neuronilor in vederea unor rezultate cat mai bune.
    void antreneaza(int iteratii, bool GUI = false)  // primeste un singur parametru, ci anume, numarul de iteratii
    {
        string structura_nou = structura;
        if(GUI)
        {
            structura_nou.erase( remove( structura_nou.begin(), structura_nou.end(), ' ' ), structura_nou.end()); // sterge spatiile din string
            system("start Lib/GUI.exe"); // deschide GUI-ul si porneste serverul

            system("cls");
            int i = 10;
            while(i > 0)
            {
                if(i > 1 && i < 20)
                    std::cout << "Procesul de antrenare va incepe in " << i << " secunde.";
                else if(i == 1)
                    std::cout << "Procesul de antrenare va incepe intr-o secunda.";

                i--;
                Sleep(1000);
                system("cls");
            }
            std::cout << '\n';


        }

        int n = structura.length(); // retine in variabila n lungimea structurii
        char s[n + 1]; // declararea unui tablou de char in care o sa fie structura
        strcpy(s, structura.c_str());  // copiaza structura in vectorul de char (pentru a putea utiliza functiile specifice vectorului de char, ci nu string-ului.

        char *p = strtok(s, ", [ ]");  // retine primul numar din strctura, pointeaza la acel caracter. Spre exemplu : daca avem [2, 2, 1], va retine in pointerul p : 2

        int structura_int[1000]; // aici este un vector de int, care va retine fiecare numar de neuroni din fiecare hidden layer
        while(p != NULL)
        {
            structura_int[index] = atoi(p);  // converteste pointerul in int si il retine in vectorul specficic
            p = strtok(NULL, ", [ ]");  // pointeaza la urmatorul string
            index++;  // incrementeaza pozitia vectorului
        }


        for(int i = 0; i <= index - 2; i++)
        {
            weights.push_back(Matrice(structura_int[i+1], structura_int[i], "random", 2));  // initalizeaza vectorul de sinapse cu valori random in (-2, 2). Iar dimensiunea este stabilita in functie de numarul de pe poztia i + 1 din strctura si numarul de pe pozitia i
            // aceasta initializare este facuta in felul acesta pentru a putea realiza operatiile specifice matricelor, precum : adunare, scadere, produs, etc...
        }

        for(int i = 0; i <= index - 1; i++)
        {
            biases.push_back(Matrice(structura_int[i + 1], 1, "random", 2));  // initializeaza bias-urile in functie de pozitia de pe i + 1 cu valori in (-2, 2)
        }



        vector<Matrice> hidden_layers;  // declararea unui vector de hidden layers

        for(int z = 0; z < iteratii; z++)  // parcurgem numarul de iteratii transmise ca parametru
        {

            input[z].randomizare(input, output, input.size());  // randomizam input-urile pentru a evita o problema frecvent intalnita in ML, ci anume overfit-ul
            vector<Matrice> errori_hidden_layers; // initializare matrice de erori pentru hidden layers
            for(int i = 0 ; i < input.size(); i++)  // parcurgem lungimea input-urilor
            {
                vector<Matrice> hidden_layers;  // initalizare hidden layers

                hidden_layers.push_back(weights[0] * input[i]);  // adaugarea primului hidden layer in vector


                hidden_layers[0] = hidden_layers[0] + biases[0];  // adaugarea bias-ului in primul hidden layer

                hidden_layers[0].sigmoid_matrice(hidden_layers[0]);  // aplicarea functiei sigmoidale pentru primul hidden layer


                for(int j = 1; j <= index - 2; j++)  // parcurgerea urmatoarelor layere.
                {
                    hidden_layers.push_back(weights[j] * hidden_layers[j - 1]);  // adauga in vector rezultatul (calculeaza produsul in functie de sinapsele curente si hidden layer-ul anterior)
                    hidden_layers[j] = biases[j] + hidden_layers[j]; // adauga bias-ul hidden layer-ului
                    hidden_layers[j].sigmoid_matrice(hidden_layers[j]);  // aplica functia sigmoidala hidden layer-ului de pe pozitia j

                }

                vector<Matrice> erori_hidden_layers;  // declararea vectorului de erori
                for(int j = 0; j <= index - 2; j++)  // parcurgem vectorul pentru a-l putea initializa cu valori nule
                {
                    erori_hidden_layers.push_back(Matrice(1, 1, "valoare", 0));
                }

                erori_hidden_layers[index - 2] = output[i] - hidden_layers[index - 2];  // in felul acesta putem calcula eroarea output-ului.
                // Daca facem diferenta intre output-ul pe care il cunoastem si output-ul care a fost prezis de catre program putem calcula eroarea acestuia


                for(int j = index - 2 - 1; j >= 0; j -- )  // parcurgere hidden layers
                {

                    weights[j+1] = weights[j+1].transpusa();  // facem transpusa matricei pentru a putea realiza operatiile viitoare

                    erori_hidden_layers[j] = weights[j + 1] * erori_hidden_layers[j + 1];  // distribuim erorile pe pozitia j in functie de cele de pe pozitia j+1

                    weights[j+1] = weights[j+1].transpusa(); // aducem matricea la forma initiala, aplicand inca o data traspusa



                }


                vector<Matrice> hidden_layers_derivate;
                vector<Matrice> gradienturi;
                vector<Matrice> delta_weights;

                for(int j = 0; j <= index - 2; j++)  // parcurgem vectorii declarati anterior si le atribuim valori nule
                {
                    hidden_layers_derivate.push_back(Matrice(1, 1, "valoare", 0));
                    gradienturi.push_back(Matrice(1, 1, "valoare", 0));
                    delta_weights.push_back(Matrice(1, 1, "valoare", 0));
                }


                for(int j = index - 2 ; j >= 0; j -- )  // parcurgem vectorii
                {
                    hidden_layers_derivate[j] = hidden_layers[j];  // retinem hidden layerul de pe pozitia j in noul vector
                    hidden_layers_derivate[j].d_sigmoid_matrice(hidden_layers_derivate[j]);  // aplicam derivata functiei sigmoidale hidden layer-ului

                    gradienturi[j] = erori_hidden_layers[j] % hidden_layers_derivate[j];  // calculam gradientul in functie de eroare si derivata (inmultim matricele element cu element)
                    gradienturi[j] = rata_de_invatare * gradienturi[j];  // aplicam rata de invatare

                    biases[j] = biases[j] + gradienturi[j]; // adaugam gradient-urile bias-ului

                }


                for(int j = index - 2; j >= 1; j--)
                {
                    hidden_layers[j - 1] = hidden_layers[j-1].transpusa(); // transpusa matricei
                    delta_weights[j] = gradienturi[j] * hidden_layers[j - 1];  // calculam delta weights-urile pentru a putea adauga diferenta necesara in vederea imbunatatirii retelei neuronale, acesta valori sunt relativ mici.
                    hidden_layers[j - 1] = hidden_layers[j - 1].transpusa();  // revenirea la forma initiala a matricei
                }

                input[i] = input[i].transpusa();  // transpusa input-ului

                delta_weights[0] = gradienturi[0] * input[i];  // calculam delta weights-urile necesare pentru input-uri
                input[i] = input[i].transpusa();  // revenim la forma initiala a input-urilor


                // folosind acest for actualizam sinapsele in functie de delta_weights (pe care le-am calculat la pasii anteriori)
                for(int j = 0; j<=index-2;j++)
                {
                    weights[j] = delta_weights[j] + weights[j];
                }

                // daca GUI-ul este true va trimite datele server-ului pentru a le putea prelucra
                if(GUI)
                    conectare_server(z, weights, structura_nou, index, hidden_layers);


            }

            cout << "\n";
            cout << z << " / " << iteratii;
            cout << "\n";
        }

        cout << "\n\n";

        // daca a ajuns la final si GUI-ul este true va inchide serverul.
        if(GUI)
        {
            SOCKET out = conectare_server(0, weights, structura_nou, 0, hidden_layers);
            system("taskkill /F /T /IM GUI.exe");
        }

    }

    // Aceasta functie este asemanatoare cu cea de training, doar ca nu antreneaza nimic, ci doar genereaza valorile in functie de sinapsele antrenate pentru input-urile introduse
    void verificare(int zecimale = 6, bool GUI = false)
    {
        string structura_nou = structura;
        if(GUI)
        {
            structura_nou.erase( remove( structura_nou.begin(), structura_nou.end(), ' ' ), structura_nou.end()); // sterge spatiile din string
            system("start Lib/GUI.exe"); // deschide GUI-ul si porneste serverul
            system("cls");
            int i = 10;
            while(i > 0)
            {
                if(i > 1 && i < 20)
                    std::cout << "Procesul de verificare va incepe in " << i << " secunde.";
                else if(i == 1)
                    std::cout << "Procesul de verificare va incepe intr-o secunda.";

                i--;
                Sleep(1000);
                system("cls");
            }
            std::cout << '\n';
        }

        vector<Matrice> hidden_layers;
        int n = structura.length();
        char s[n + 1];
        strcpy(s, structura.c_str());

        char *p = strtok(s, ", [ ]");


        int index = 0;
        int structura_int[1000];
        while(p != NULL)
        {
            structura_int[index] = atoi(p);
            p = strtok(NULL, ", [ ]");
            index++;
        }


        for(int i = 0; i <= index - 2; i++)
        {
            hidden_layers.push_back(Matrice(1, 1, "valoare", 0));
        }

        if(GUI)
        {
            bool ok = true;
            HANDLE handle = CreateThread(NULL, 0, thread2, NULL, 0, NULL);  // incepe cel de-al doilea thread pentru a putea scrie comenzi in loop.
            while(thread2_start)  // cat timp thread-ul este pornit...
            {

                for(int i = 0 ; i < input.size(); i++)
                {
                    hidden_layers[0] = weights[0] * input[i];
                    hidden_layers[0] = hidden_layers[0] + biases[0];
                    hidden_layers[0].sigmoid_matrice(hidden_layers[0]);


                    for(int j = 1; j <= index - 2; j++)
                    {
                        hidden_layers[j] = weights[j] * hidden_layers[j - 1];
                        hidden_layers[j] = hidden_layers[j] + biases[j];
                        hidden_layers[j].sigmoid_matrice(hidden_layers[j]);

                    }

                    // daca GUI-ul este true atunci se conecteaza la server si trimite datele
                    if(GUI)
                        conectare_server(i, weights, structura_nou, index, hidden_layers);

                    if(ok)
                    {
                        cout << std::fixed << std::setprecision(zecimale) << (hidden_layers[index-2]) << "\n";

                        if(i == input.size() - 1)
                            std::cout << "\n > Pentru a inchide vizualizarea scrie 'stop' \n\n";
                    }

                }
                ok = false;

            }
        }
        else
        {
            for(int i = 0 ; i < input.size(); i++)
            {
                hidden_layers[0] = weights[0] * input[i];
                hidden_layers[0] = hidden_layers[0] + biases[0];
                hidden_layers[0].sigmoid_matrice(hidden_layers[0]);


                for(int j = 1; j <= index - 2; j++)
                {
                    hidden_layers[j] = weights[j] * hidden_layers[j - 1];
                    hidden_layers[j] = hidden_layers[j] + biases[j];
                    hidden_layers[j].sigmoid_matrice(hidden_layers[j]);

                }

                if(GUI)
                    conectare_server(i, weights, structura_nou, index, hidden_layers);

                cout << std::fixed << std::setprecision(zecimale) << (hidden_layers[index-2]) << "\n";

            }
        }

        // daca a ajuns la final si GUI-ul este true va inchide serverul.
        if(GUI)
        {
            SOCKET out = conectare_server(0, weights, structura_nou, 0, hidden_layers);
            system("taskkill /F /T /IM GUI.exe");
        }

    }


    // Aceasta este functia care salveaza datele referitoare la training
    void salvare(char fisier[])
    {

        char fis[1000];  // un vector de char care stocheaza informatii referitoare la fisierul in care vor fi datele
        strcpy(fis, fisier);  // copiaza numele fisierului in vectorul fis
        char extensie[] = {".odin"};  // creeaza extensia bazei de date
        strcat(fis, extensie); // adauga extensia fisierului

        ofstream o(fis);  // declara fisierul de iesire

        o << index << "\n";  // scrie in fisierul de iesire indexul

        for(int i = 0; i <= index - 2; i++)
        {
            o << weights[i].linii << " " << weights[i].coloane << "\n";  // scrie numarul de linii si coloane a tuturor sinapselor
        }
        for(int i = 0; i <= index - 2; i++)
        {
            o << biases[i].linii << " " << biases[i].coloane << "\n";  // scrie numarul de linii si coloane a tuturor bias-urilor
        }

        o << "\n";


        for(int z = 0; z <= index - 2; z++)  // parcurge toate sinapsele
        {
            for(int i = 0;i < weights[z].linii;i++)  // parcurge liniile pentru sinapsa la pozitia z
            {
                for(int j = 0;j< weights[z].coloane;j++) // parcurge coloanele pentru sinapsa la pozitia z
                {
                    o << weights[z].valori[i][j] << " ";  // scrie valorile sinapselor in fisier
                }
                o << "\n";
            }
            o << "\n";
        }

        o << "\n";

        for(int z = 0; z <= index - 2; z++)  // parcurge toate bias-urile
        {
            for(int i = 0;i < biases[z].linii;i++) // parcurge liniile pentru bias-ul la pozitia z
            {
                for(int j = 0;j< biases[z].coloane;j++)  // parcurge coloanele pentru bias-ul la pozitia z
                {
                    o << biases[z].valori[i][j] << " ";  // scrie valorile bias-urilor
                }
                o << "\n";
            }
            o << "\n";
        }

        o << "\n";
        o << structura;  // scrie arhitectura retelei neuronale

        o.close();  // inchide fisierul
    }



    void incarcare(char fisier[])
    {

        // afla numele fisierului (la fel ca la salvare)
        char fis[1000];
        strcpy(fis, fisier);
        char extensie[] = {".odin"};
        strcat(fis, extensie);

        ifstream f(fis);

        double x;

        int lungime = 0;

        vector <punct> pct;
        int k = 0;
        int suma = 0;
        while(f >> x)  // citeste fiecare valoare din fisier si o atribuie valorii x
        {
            if(lungime == 0) // daca lungimea e 0, inseamna ca e la prima pozitie si retine index-ul, care reprezinta numarul de coloane pentru dimensiunile urmatoarelor matrice
                index = x;
            else  if(lungime > 0 && lungime <= (index - 1)* 2 * 2)  // daca lungimea e mai mare decat 0 si mai mica decat toate valorile dimensiunilor adunate executa urmatoarele :
            {

                // Creeaza un punct pe care il adauga vectorului de puncte (practic sunt dimensiunile matricelor (p.x = liniile, iar p.y = coloanele)
                punct p;
                if(lungime % 2 != 0)
                {
                    p.x = x;
                }
                else
                {
                    p.y = x;
                    pct.push_back(p);
                }
            }

            lungime ++;  // updateaza dimensiunea
        }

        for(int i = 0; i < pct.size(); i++)
            suma += pct[i].x * pct[i].y;


        // Reseteaza fisierul, pointerul va fi iarasi la inceputul fisierului
        f.clear();
        f.seekg(0, ios::beg);


        lungime = 0;
        int pos = 0;
        vector<Matrice> matrice;
        bool ok = true;
        char c;
        string str;

        while(ok)
        {
            if(lungime > pct.size() * 2)  // daca am trecut de identificarea dimensiunilor matricelor executam urmatoarele comenzi
            {
                if(pos < pct.size())  // daca pozitia e mai mica decat aceste dimeniuni
                {
                    Matrice matrice(0, 0, "valoare", 0);  // initializam o matrice

                    matrice.linii = pct[pos].x;  // matricea va avea numarul de linii din valoarea pct[pos].x, adica linia de pe pozitia "pos"
                    matrice.coloane = pct[pos].y;  // matricea va avea numarul de coloane din valoarea pct[pos].y, adica coloana de pe pozitia "pos"

                    for(int i = 0; i < pct[pos].x; i++)  // parcurge liniile matricei
                    {
                        vector<double> temp;
                        for(int j = 0; j < pct[pos].y; j++)  // parcurge coloanele matricei
                        {
                            f >> x;  // citeste valorile din fisier
                            temp.push_back(x);  // le adauga in vectorul temporar
                        }
                        matrice.valori.push_back(temp); // adauga vectorul temporar in matrice
                    }

                    if(pos < pct.size() / 2)  // daca sunt citite sinapsele
                    {
                        matrice = matrice.sforma(pct[pos].x, pct[pos].y);  // schimba forma matricei in functie de dimensiunile din vectorul construit anterior
                        weights.push_back(matrice);  // adauga matricea in vectorul de sinapse
                    }
                    else  // altfel sunt citite bias-urile
                    {
                        matrice = matrice.sforma(pct[pos].x, pct[pos].y); // schimba forma matricei in functie de dimensiunile din vectorul construit anterior
                        biases.push_back(matrice);  // adauga matricea in vectorul de bias-uri
                    }

                    pos ++ ;
                }
                else
                {
                    f >> c;  // citeste un caracter

                    str += c;  // adauga caracterul in acest string

                    if(c == ']')  // daca valoarea citita este ']' inseamna ca s-a ajuns la finalul fisierului si se opreste citirea
                        ok = false;
                }
            }
            else
            {
                f >> x;  // citeste x-ul
                lungime ++ ; // updateaza lungimea
            }
        }

        structura = str;  // retine str-ul constuit in while in variabila globala "structura"

    }
};

