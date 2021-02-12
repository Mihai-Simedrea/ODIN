#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>

using namespace std;


class Matrice
{
public:
    struct matrice
    {
       int linii = 0, coloane = 0;
       vector<vector<double>> valori;
    }proprietati;
};

namespace odin
{
    Matrice init(int numar_linii, int numar_coloane, string tip_matrice, double valoare)
    {
        if(numar_linii < 0 || numar_coloane < 0)
        {
            cout << " > Numarul de linii si coloane trebuie sa fie pozitiv." << endl;
            throw int(1);
        }

        else
        {
            Matrice matrice;
            bool val = false;
            bool random = false;

            if(tip_matrice == "valoare")
                val = true;
            if(tip_matrice == "random")
                random = true;


            matrice.proprietati.linii = numar_linii;
            matrice.proprietati.coloane = numar_coloane;

            for (int h = 0; h < numar_linii; h++)
            {
                vector<double> temp;
                for (int w = 0; w < numar_coloane; w++)
                {
                    if(val)
                        temp.push_back(valoare);
                    else if(random)
                    {
                        double x;
                        int numar_random = rand() % 2;

                        if(numar_random == 0)
                            x = 1;
                        else
                            x = -1;

                        temp.push_back((double(rand())/double((RAND_MAX)) * valoare * x));
                    }

                }

                matrice.proprietati.valori.push_back(temp);

            }

            return matrice;
        }

    }

    void afisare(Matrice matrice)
    {

        for(int i = 0;i < matrice.proprietati.linii;i++)
        {
            for(int j = 0;j< matrice.proprietati.coloane;j++)
            {
                cout << matrice.proprietati.valori[i][j] << " ";
            }
            cout << endl;
        }

    }

    void vectorizare(Matrice &matrice)
    {
        Matrice vector_nou;

        vector_nou = init(1, matrice.proprietati.linii * matrice.proprietati.coloane, "valoare", 0);

        int index = 0;

        for(int i = 0; i < matrice.proprietati.linii; i++)
        {
            for(int j = 0; j < matrice.proprietati.coloane; j++)
            {
                index = i * matrice.proprietati.coloane + j;
                vector_nou.proprietati.valori[0][index] = matrice.proprietati.valori[i][j];
            }
        }

        matrice = vector_nou;
    }

    void adauga(Matrice &matrice, double valoare)
    {
        Matrice vector_nou;
        vector_nou = init(1, matrice.proprietati.linii * matrice.proprietati.coloane + 1, "valoare", 0);


        int index = 0;

        for(int i = 0; i < matrice.proprietati.linii; i++)
        {
            for(int j = 0; j < matrice.proprietati.coloane; j++)
            {
                index = i * matrice.proprietati.coloane + j;
                vector_nou.proprietati.valori[0][index] = matrice.proprietati.valori[i][j];
            }
        }

        vector_nou.proprietati.valori[0][matrice.proprietati.coloane * matrice.proprietati.linii ] = valoare;

        matrice = vector_nou;


    }

    void suma(Matrice &rezultat, Matrice matrice1, Matrice matrice2)
    {

        if(!(matrice1.proprietati.coloane == matrice2.proprietati.coloane && matrice1.proprietati.linii == matrice2.proprietati.linii))
        {
            cout << " > Nu se poate realiza suma intre cele doua matrice deoarece nu au aceeasi dimensiune." << endl;
            throw int(2);
        }
        else
        {
            rezultat = init( matrice1.proprietati.linii, matrice1.proprietati.coloane, "valoare", 0);
            for(int i = 0; i < matrice1.proprietati.linii; i++)
                for(int j = 0;j < matrice1.proprietati.coloane; j++)
                    rezultat.proprietati.valori[i][j] = matrice1.proprietati.valori[i][j] + matrice2.proprietati.valori[i][j];
        }
    }

    void diferenta(Matrice &rezultat, Matrice matrice1, Matrice matrice2)
    {
        if(!(matrice1.proprietati.coloane == matrice2.proprietati.coloane && matrice1.proprietati.linii == matrice2.proprietati.linii))
        {
            cout << " > Nu se poate realiza diferenta intre cele doua matrice deoarece nu au aceeasi dimensiune." << endl;
            throw int(3);
        }

        else
        {
            rezultat = init(matrice1.proprietati.linii, matrice1.proprietati.coloane, "valoare", 0);
            for(int i = 0; i < matrice1.proprietati.linii; i++)
                for(int j = 0;j < matrice1.proprietati.coloane; j++)
                    rezultat.proprietati.valori[i][j] = matrice1.proprietati.valori[i][j] - matrice2.proprietati.valori[i][j];
        }
    }

    void scalar(Matrice &rezultat, double valoare_scalar, Matrice matrice)
    {
        rezultat = init(matrice.proprietati.linii, matrice.proprietati.coloane, "valoare", 0);
        for(int i = 0; i < matrice.proprietati.linii; i++)
            for(int j = 0;j < matrice.proprietati.coloane; j++)
                rezultat.proprietati.valori[i][j] = valoare_scalar * matrice.proprietati.valori[i][j];

    }


    void produs(Matrice &rezultat, Matrice matrice1, Matrice matrice2)
    {

        bool ok = false;

        if(matrice1.proprietati.coloane == matrice2.proprietati.linii)
            ok = true;


        if (ok)
        {
            rezultat = init(matrice1.proprietati.linii, matrice2.proprietati.coloane, "valoare", 0);
            for(int i = 0; i < matrice1.proprietati.linii; i++)
            {
                for(int j = 0;j < matrice2.proprietati.coloane; j++)
                {
                    int k = 0;
                    for(int z = 0; z < matrice1.proprietati.coloane; z++)
                    {
                        rezultat.proprietati.valori[i][j] += matrice1.proprietati.valori[i][k] * matrice2.proprietati.valori[k][j];
                        k ++ ;
                    }
                }
            }
        }
        else
        {
            cout << " > Nu se poate realiza produsul intre cele doua matrice deoarece " << matrice1.proprietati.coloane << " != " << matrice2.proprietati.linii << ". \n";
            throw int(4);
        }


    }

    void produs2(Matrice &rezultat, Matrice matrice1, Matrice matrice2)
    {
        bool ok = false;

        if(matrice1.proprietati.coloane == matrice2.proprietati.coloane && matrice1.proprietati.linii == matrice2.proprietati.linii)
            ok = true;


        if (ok)
        {
            rezultat = init(matrice1.proprietati.linii, matrice2.proprietati.coloane, "valoare", 0);
            for(int i = 0; i < matrice1.proprietati.linii; i++)
            {
                for(int j = 0;j < matrice2.proprietati.coloane; j++)
                {
                    rezultat.proprietati.valori[i][j] = matrice1.proprietati.valori[i][j] * matrice2.proprietati.valori[i][j];
                }
            }
        }
        else
        {
            cout << " > Nu se poate realiza produsul intre cele doua matrice deoarece nu au aceeasi dimensiune." << endl;
            throw int(5);
        }
    }

    void forma(Matrice &matrice, int dimensiune1, int dimensiune2)
    {
        if(dimensiune1 * dimensiune2 == matrice.proprietati.coloane * matrice.proprietati.linii)
        {

            Matrice vector_nou;
            vectorizare(matrice);

            vector_nou = init(dimensiune1, dimensiune2, "valoare", 0);

            int index = 0;
            for(int i = 0;i < dimensiune1; i++)
            {
                for(int j = 0; j < dimensiune2; j++)
                {
                    vector_nou.proprietati.valori[i][j] = matrice.proprietati.valori[0][index];
                    index++;
                }
            }

            matrice = vector_nou;

        }
        else
        {
            cout << " > Dimensiunea matricei nu poate fi schimbata deoarece valorile introduse nu corespund cu numarul de linii si coloane ale matricei introduse." << endl;
            throw int(6);
        }

    }

    void randomizare(vector<Matrice> input, vector<Matrice> output, int numar_inputuri)
    {

        for(int i = 0; i < numar_inputuri; i++)
        {
            int random = rand() % numar_inputuri;
            swap(input[i], input[random]);
            swap(output[i], output[random]);

        }


    }


    double sigmoid(double x)
    {
        return 1 / (1 + exp(-x));
    }

    double d_sigmoid(double x)
    {
        return x * (1 - x);
    }

    void sigmoid_matrice(Matrice &matrice)
    {
        int coloane = matrice.proprietati.coloane;
        int linii = matrice.proprietati.linii;

        vectorizare(matrice);

        for(int i = 0; i < coloane * linii; i++)
            matrice.proprietati.valori[0][i] = sigmoid(matrice.proprietati.valori[0][i]);

        forma(matrice, linii, coloane);
    }

    void d_sigmoid_matrice(Matrice &matrice)
    {
        int coloane = matrice.proprietati.coloane;
        int linii = matrice.proprietati.linii;

        vectorizare(matrice);

        for(int i = 0; i < coloane * linii; i++)
            matrice.proprietati.valori[0][i] = d_sigmoid(matrice.proprietati.valori[0][i]);

        forma(matrice, linii, coloane);
    }

    Matrice transpusa(Matrice matrice)
    {
        int coloane = matrice.proprietati.coloane;
        int linii = matrice.proprietati.linii;

        forma(matrice, coloane, linii);

        return matrice;

    }


}
