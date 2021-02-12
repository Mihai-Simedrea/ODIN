#include <iostream>
#include "matrice.hpp"
#include <fstream>

using namespace std;
using namespace odin;

class ReteaNeuronala
{

    struct punct
    {
        int x, y;
    };

public:
    string structura;
    vector<Matrice> input;
    vector<Matrice> output;
    double rata_de_invatare = 0.8;
    vector<Matrice> weights;
    vector<Matrice> biases;
    int index = 0;


    void antreneaza(int iteratii, bool afisare_progres)
    {
        int n = structura.length();
        char s[n + 1];
        strcpy(s, structura.c_str());

        char *p = strtok(s, ", [ ]");

        int structura_int[1000];
        while(p != NULL)
        {
            structura_int[index] = stoi(p);
            p = strtok(NULL, ", [ ]");
            index++;
        }


        for(int i = 0; i <= index - 2; i++)
            weights.push_back(init(structura_int[i+1], structura_int[i], "random", 2));

        for(int i = 0; i <= index - 1; i++)
            biases.push_back(init(structura_int[i + 1], 1, "random", 2));


        vector<Matrice> hidden_layers;
        for(int z = 0; z < iteratii; z++)
        {

            randomizare(input, output, input.size());
            vector<Matrice> errori_hidden_layers;
            for(int i = 0 ; i < input.size(); i++)
            {
                vector<Matrice> hidden_layers;
                Matrice rezultat;
                produs(rezultat, weights[0], input[i]);
                hidden_layers.push_back(rezultat);

                suma(hidden_layers[0], hidden_layers[0], biases[0]);

                sigmoid_matrice(hidden_layers[0]);


                for(int j = 1; j <= index - 2; j++)
                {
                    produs(rezultat, weights[j], hidden_layers[j - 1]);
                    hidden_layers.push_back(rezultat);
                    suma(hidden_layers[j], biases[j], hidden_layers[j]);
                    sigmoid_matrice(hidden_layers[j]);

                }

                vector<Matrice> erori_hidden_layers;
                for(int j = 0; j <= index - 2; j++)
                    erori_hidden_layers.push_back(init(1, 1, "valoare", 0));

                diferenta(erori_hidden_layers[index - 2], output[i], hidden_layers[index - 2]);


                for(int j = index - 2 - 1; j >= 0; j -- )
                {

                    weights[j+1] = transpusa(weights[j + 1]);

                    produs(erori_hidden_layers[j], weights[j + 1], erori_hidden_layers[j + 1]);

                    weights[j+1] = transpusa(weights[j + 1]);



                }


                vector<Matrice> hidden_layers_derivate;
                vector<Matrice> gradienturi;
                vector<Matrice> delta_weights;

                for(int j = 0; j <= index - 2; j++)
                {
                    hidden_layers_derivate.push_back(init(1, 1, "valoare", 0));
                    gradienturi.push_back(init(1, 1, "valoare", 0));
                    delta_weights.push_back(init(1, 1, "valoare", 0));
                }


                for(int j = index - 2 ; j >= 0; j -- )
                {
                    hidden_layers_derivate[j] = hidden_layers[j];
                    d_sigmoid_matrice(hidden_layers_derivate[j]);

                    produs2(gradienturi[j], erori_hidden_layers[j], hidden_layers_derivate[j]);
                    scalar(gradienturi[j], rata_de_invatare, gradienturi[j]);

                    suma(biases[j], biases[j], gradienturi[j]);

                }


                for(int j = index - 2; j >= 1; j--)
                {
                    hidden_layers[j - 1] = transpusa(hidden_layers[j - 1]);
                    produs(delta_weights[j], gradienturi[j], hidden_layers[j - 1]);
                    hidden_layers[j - 1] = transpusa(hidden_layers[j - 1]);
                }

                input[i] = transpusa(input[i]);

                produs(delta_weights[0], gradienturi[0], input[i]);
                input[i] = transpusa(input[i]);


                for(int j = 0; j<=index-2;j++)
                    suma(weights[j], delta_weights[j], weights[j]);

            }
            cout << endl;
            cout << z << " / " << iteratii;
            cout << endl;
        }

        cout << endl << endl;

    }

    void verificare()
    {
        vector<Matrice> hidden_layers;
        int n = structura.length();
        char s[n + 1];
        strcpy(s, structura.c_str());

        char *p = strtok(s, ", [ ]");


        int index = 0;
        int structura_int[1000];
        while(p != NULL)
        {
            structura_int[index] = stoi(p);
            p = strtok(NULL, ", [ ]");
            index++;
        }

        for(int i = 0; i <= index - 2; i++)
            hidden_layers.push_back(init(1, 1, "valoare", 0));

        for(int i = 0 ; i < input.size(); i++)
        {
            produs(hidden_layers[0], weights[0], input[i]);
            suma(hidden_layers[0], hidden_layers[0], biases[0]);
            sigmoid_matrice(hidden_layers[0]);


            for(int j = 1; j <= index - 2; j++)
            {
                produs(hidden_layers[j], weights[j], hidden_layers[j - 1]);
                suma(hidden_layers[j], hidden_layers[j], biases[j]);
                sigmoid_matrice(hidden_layers[j]);

            }

            afisare(hidden_layers[index-2]);
            cout << endl;

        }
    }

    void salvare(char fisier[])
    {

        char fis[1000];
        strcpy(fis, fisier);
        char extensie[] = {".odin"};
        strcat(fis, extensie);

        ofstream o(fis);

        o << index;
        o << endl;

        for(int i = 0; i <= index - 2; i++)
        {
            o << weights[i].proprietati.linii << " " << weights[i].proprietati.coloane << endl;
        }
        for(int i = 0; i <= index - 2; i++)
        {
            o << biases[i].proprietati.linii << " " << biases[i].proprietati.coloane << endl;
        }

        o << endl;


        for(int z = 0; z <= index - 2; z++)
        {
            for(int i = 0;i < weights[z].proprietati.linii;i++)
            {
                for(int j = 0;j< weights[z].proprietati.coloane;j++)
                {
                    o << weights[z].proprietati.valori[i][j] << " ";
                }
                o << endl;
            }
            o << endl;
        }

        o << endl;

        for(int z = 0; z <= index - 2; z++)
        {
            for(int i = 0;i < biases[z].proprietati.linii;i++)
            {
                for(int j = 0;j< biases[z].proprietati.coloane;j++)
                {
                    o << biases[z].proprietati.valori[i][j] << " ";
                }
                o << endl;
            }
            o << endl;
        }

        o << endl;
        o << structura;

        o.close();
    }

    void incarcare(char fisier[])
    {
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
        while(f >> x)
        {
            if(lungime == 0)
                index = x;
            else  if(lungime > 0 && lungime <= (index - 1)* 2 * 2)
            {

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

            lungime ++;
        }

        for(int i = 0; i < pct.size(); i++)
            suma += pct[i].x * pct[i].y;


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
            if(lungime > pct.size() * 2)
            {
                if(pos < pct.size())
                {
                    Matrice matrice;

                    matrice.proprietati.linii = pct[pos].x;
                    matrice.proprietati.coloane = pct[pos].y;

                    for(int i = 0; i < pct[pos].x; i++)
                    {
                        vector<double> temp;
                        for(int j = 0; j < pct[pos].y; j++)
                        {
                            f >> x;
                            temp.push_back(x);
                        }
                        matrice.proprietati.valori.push_back(temp);
                    }

                    if(pos < pct.size() / 2)
                    {
                        forma(matrice, pct[pos].x, pct[pos].y);
                        weights.push_back(matrice);
                    }
                    else
                    {
                        forma(matrice, pct[pos].x, pct[pos].y);
                        biases.push_back(matrice);
                    }

                    pos ++ ;
                }
                else
                {
                    f >> c;

                    str += c;

                    if(c == ']')
                        ok = false;
                }
            }
            else
            {
                f >> x;
                lungime ++ ;
            }
        }

        structura = str;

    }
};
