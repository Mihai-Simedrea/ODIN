#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <random>

using namespace std;


class Matrice
{
public:

    int linii = 0, coloane = 0;
    vector<vector<double>> valori;

    // Constructorul clasei
    Matrice (int numar_linii, int numar_coloane, string tip_matrice, double valoare)
    {


        /* Aici are loc initializarea seed-ului folosind biblioteca <random>, in defavoarea implementarii functiei rand(),
        din cauza previzibilitatii acesteia */

        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(-valoare, valoare);

        if(numar_linii < 0 || numar_coloane < 0)  // daca numarul de linii sau coloane este mai mic decat 0, initializarea nu are sens si nu va avea loc.
        {
            cout << " > Numarul de linii si coloane trebuie sa fie pozitiv." << endl;
            throw int(1);
        }

        else
        {
            //Matrice matrice; // initializarea unei matrice care va reprezenta matricea initializata in fisierul .cpp
            bool val = false;
            bool random = false;


            /* Aceste structuri decizionale verifica tipul matricei, transmis ca parametru prin functia principalt */
            if(tip_matrice == "valoare")
                val = true;
            if(tip_matrice == "random")
                random = true;


            for (int h = 0; h < numar_linii; h++)  // parcurgem numarul de linii al matricei
            {
                vector<double> temp;  // initializam un vector temporar care va retine valorile de pe linia "h"
                for (int w = 0; w < numar_coloane; w++)  // parcurgem numarul de coloane
                {
                    if(val)  // daca tipul matricei este "valoare" adaugam in vectorul temporar valoarea respectiva
                        temp.push_back(valoare);
                    else if(random)  // altfel adaugam un numar random in intervalul cunoscut
                    {

                        temp.push_back((dist(mt)));
                    }

                }

                this->valori.push_back(temp);  // adaugam linia curenta in matrice

            }

            this->linii = numar_linii;  // preluam numarul de linii al matricei si il atribuim clasei
            this->coloane = numar_coloane;  // preluam numarul de coloane al matricei si il atribuim clasei

        }


    }


    void adauga(double valoare)  /* unicul parametru al functiei este de tip double,
    reprezentand valoarea ce va fi adaugata in matrice */
    {
        Matrice vector_nou(1, this->linii * this->coloane + 1, "valoare", 0);  /* initializarea unei matrice care va stoca informatiile anterioare,
        dar, in plus, va avea si noua valoare adaugata */

        /* initializam matricea cu liniile matricei din fisierul .cpp, de asemenea, numarul de coloane se va
        incrementa cu 1, reprezentand locul pentru valoarea ce va fi adaugata */


        int index = 0;  // initializam un index care va fi pozitia in functie de linii si coloane

        for(int i = 0; i < this->linii; i++)  // parcurgem numarul de linii a matricei
        {
            for(int j = 0; j < this->coloane; j++)  // parcurgem numarul de coloane a matricei
            {
                index = i * this->coloane + j;  // construim index-ul pe baza liniei si coloanei curente
                vector_nou.valori[0][index] = this->valori[i][j];  // atribuim pozitiei curente valorile din matricea de pe pozitiile i si j
            }
        }

        vector_nou.valori[0][this->coloane * this->linii ] = valoare;  // aici adaugam valoarea dorita pe ultima pozitie a matricei

        this->linii = vector_nou.linii;  // setam numarul de linii in functie de numarul de linii ale matricei construite in functie
        this->coloane = vector_nou.coloane;  // setam numarul de coloane in functie de numarul de coloane ale matricei construite in functie
        this->valori = vector_nou.valori;  // preluam valorile din vector si le setam matricei


    }

    Matrice vectorizare()  // aceasta functie nu primeste niciun parametru, pur si simplu schimba forma matricei intr-o matrice de tip coloana.
    {
        Matrice vector_nou(1, this->linii * this->coloane, "valoare", 0);  // initializarea unei matrice care va stoca informatiile anterioare

        int index = 0;  // initializam un index care va fi pozitia in functie de linii si coloane

        for(int i = 0; i < this->linii; i++)  // parcurgem numarul de linii ale matricei
        {
            for(int j = 0; j < this->coloane; j++)  // parcurgem numarul de coloane ale matricei
            {
                index = i * this->coloane + j;  // construim index-ul pe baza liniei si coloanei curente
                vector_nou.valori[0][index] = this->valori[i][j];  // atribuim noii matrice elementele de pe pozitiile i si j
            }
        }

        return vector_nou;  // returnam noua matrice de tip coloana
    }

    /* Functia "forma" schimba dimensiunea unei matrice.
       Functia are doar doi parametri, prima dimensiune si a doua, acestea reprezinta
       dimensiunile in care dorim sa convertim matricea. */
    Matrice forma(int dimensiune1, int dimensiune2)
    {
        if(dimensiune1 * dimensiune2 == this->coloane * this->linii)  // daca produsul dimensiunilor introduse e egal cu cel al matricei se va realiza conversia.
        {

            Matrice vector_nou(0,0,"valoare",0), vn(dimensiune1, dimensiune2, "valoare", 0);  // initializarea unui nou vector, in care sunt copiate informatiile matricei
            vector_nou = this->vectorizare();  // transformarea matricei intr-o matrice de tip coloana

            int index = 0;  // initializam un index care va fi pozitia in functie de linii si coloane
            for(int i = 0;i < dimensiune1; i++)  // parcurgerea liniilor in functie de dimensiunea introdusa
            {
                for(int j = 0; j < dimensiune2; j++)  // parcurgerea liniilor in functie de dimensiunea introdusa
                {
                    vn.valori[i][j] = vector_nou.valori[0][index];  // atribuirea noului vector cu valorile din matricea coloana principala
                    index++;
                }
            }

            return vn;  // returnam matricea

        }
        else  // daca dimensiunile nu sunt corespunzatoare operatia nu poate fi realizata
        {
            cout << " > Dimensiunea matricei nu poate fi schimbata deoarece valorile introduse nu corespund cu numarul de linii si coloane ale matricei introduse." << endl;
            throw int(6);
        }

    }

    /* Functia de randomizare are 3 parametri. Primul este reprezentat de vectorul de input-uri,
    al doilea de vectorul de output-uri, iar al treilea de numarul de elemente care sunt supuse randomizarii */
    void randomizare(vector<Matrice> input, vector<Matrice> output, int numar_inputuri)
    {

        /* Aici are loc initializarea seed-ului folosind biblioteca <random>, in defavoarea implementarii functiei rand(),
        din cauza previzibilitatii acesteia */
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(0, numar_inputuri);


        for(int i = 0; i < numar_inputuri; i++)  // parcurgem numarul de elemente care vor fi randomizate
        {
            int random = dist(mt);  // retinem in variabila random o valoare random in intervalul [0, numar_inputuri]
            swap(input[i], input[random]);  // schimbam valorile de pe pozitia curenta, cu cele de pe pozitia generata random
            swap(output[i], output[random]);  // schimbam valorile de pe pozitia curenta, cu cele de pe pozitia generata random

        }
    }

    /* Functia sigmoidala */
    double sigmoid(double x)
    {
        return 1 / (1 + exp(-x));  // returneaza o valoare dupa aplicarea functiei sigmoidale
    }

    /* Derivata functiei sigmoidale */
    double d_sigmoid(double x)
    {
        return x * (1 - x);  // o sa returneze valoarea dupa derivarea unei valori folosind functia sigmoidala (Valoarea trebuie sa aiba in componenta functia sigmoidala inainte de a fi aplicata derivata!!)
    }


    /* Aceasta metoda aplica functia sigmoidala pentru o matrice */
    void sigmoid_matrice(Matrice &matrice)
    {
        int coloane = matrice.coloane;  // retine numarul de coloane
        int linii = matrice.linii;  // retine numarul de linii

        matrice = matrice.vectorizare();  // vectorizeaza matricea

        for(int i = 0; i < coloane * linii; i++)  // parcurge toate elementele matricei
            matrice.valori[0][i] = sigmoid(matrice.valori[0][i]);  // aplica functia sigmoidala pentru fiecare valoare

        matrice = matrice.forma(linii, coloane);  // schimba forma matricei la cea initiala
    }

    // Derivata functiei sigmoidale aplicata matricei
    void d_sigmoid_matrice(Matrice &matrice)
    {
        int coloane = matrice.coloane;  // retine numarul de coloane
        int linii = matrice.linii;  // retine numarul de linii

        matrice = matrice.vectorizare();  // vectorizeaza matricea

        for(int i = 0; i < coloane * linii; i++)  // parcurge toate elementele matricei
            matrice.valori[0][i] = d_sigmoid(matrice.valori[0][i]);  // aplica derivata sigmoidalei pentru fiecare valoare din matrice

        matrice = matrice.forma(linii, coloane);  // schimba forma matricei la cea initiala
    }

    /* Aceasta functie calculeaza transpusa matricei, exemplu : pentru o matrice de (3, 1), o va converti in (1, 3) */
    Matrice transpusa(Matrice matrice)
    {
        int coloane = matrice.coloane;  // retine numarul de coloane ale matricei in "coloane"
        int linii = matrice.linii;  // retine numarul de linii ale matricei in "linii"

        matrice = matrice.forma(coloane, linii);  // schimba forma matricei, liniile devin coloane, iar coloanele devin linii

        return matrice;  // returneaza matricea

    }




};


namespace odin
{
    // Acesta este operatorul de afisare, adica putem folosi cout << matrice;
    ostream& operator<<(ostream &out, Matrice matrice)
    {

        for(int i = 0;i < matrice.linii;i++) // parcurge numarul de linii
        {
            for(int j = 0;j< matrice.coloane;j++) // parcurge numarul de coloane
            {
                out << matrice.valori[i][j] << " "; // afiseaza fiecare element
            }
            out << endl;
        }
        return out;  // returneaza "afisarea"

    }

    // Acesta este operatorul de adunare, face suma intre doua matrice (matrice1 + matrice2)
    Matrice operator+(Matrice matrice1, Matrice matrice2)
    {
        Matrice rezultat(matrice1.linii, matrice1.coloane, "valoare", 0);  // declararea unei matrice care va stoca noile informatii din adunarea celor doua matrice

        if(!(matrice1.coloane == matrice2.coloane && matrice1.linii == matrice2.linii))  // daca liniile/coloanele primei matrice nu sunt egale cu liniile/coloanele celei de a doua matrice nu se realizeaza operatiunea
        {
            cout << " > Nu se poate realiza suma intre cele doua matrice deoarece nu au aceeasi dimensiune." << endl;
            throw int(2);
        }
        else  // altfel, are loc adunarea
        {
            for(int i = 0; i < matrice1.linii; i++)  // parcurgerea liniilor
                for(int j = 0;j < matrice1.coloane; j++) // parcurgerea coloanelor
                    rezultat.valori[i][j] = matrice1.valori[i][j] + matrice2.valori[i][j];  // retine suma elementelor de pe pozitia i si j in noua matrice

            return rezultat;  // returneaza rezultatul
        }
    }

    // Acesta este operatorul de scadere, face diferenta intre doua matrice (matrice1 + matrice2)
    Matrice operator-(Matrice matrice1, Matrice matrice2)
    {
        Matrice rezultat(matrice1.linii, matrice1.coloane, "valoare", 0); // declararea unei matrice care va stoca noile informatii din scaderea celor doua matrice
        if(!(matrice1.coloane == matrice2.coloane && matrice1.linii == matrice2.linii)) // daca liniile/coloanele primei matrice nu sunt egale cu liniile/coloanele celei de a doua matrice nu se realizeaza operatiunea
        {
            cout << " > Nu se poate realiza diferenta intre cele doua matrice deoarece nu au aceeasi dimensiune." << endl;
            throw int(3);
        }

        else // altfel, are loc scaderea
        {
            for(int i = 0; i < matrice1.linii; i++)  // parcurgerea liniilor
                for(int j = 0;j < matrice1.coloane; j++)  // parcurgerea coloanelor
                    rezultat.valori[i][j] = matrice1.valori[i][j] - matrice2.valori[i][j];  // retine suma elementelor de pe pozitia i si j in noua matrice
            return rezultat;  // returneaza rezultatul
        }
    }

    // Acesta este operatorul de inmultire cu scalar, inmulteste fiecare element din matrice cu un numar de tip double
    Matrice operator*(double valoare_scalar, Matrice matrice)
    {
        Matrice rezultat(matrice.linii, matrice.coloane, "valoare", 0);  // declararea unei matrice care va stoca noile informatii din inmultirea matricei cu scalarul
        for(int i = 0; i < matrice.linii; i++)  // parcurgerea liniilor
            for(int j = 0;j < matrice.coloane; j++)  // parcurgerea coloanelor
                rezultat.valori[i][j] = valoare_scalar * matrice.valori[i][j];  // retine produsul dintre scalar si elementul matricei transmise in noua matrice
        return rezultat;  // returneaza matricea

    }


    // Aceasta este operatorul de inmultirea a doua matrice (matrice1 * matrice2) - dot product
    Matrice operator*(Matrice matrice1, Matrice matrice2)
    {
        Matrice rezultat(matrice1.linii, matrice2.coloane, "valoare", 0); // declararea unei matrice care va stoca noile informatii din inmultirea celor doua matrice

        bool ok = false;

        if(matrice1.coloane == matrice2.linii)  // daca numarul de coloane a primei matrice e egal cu cel de linii a celei de a doua matrice se poate realiza inmultirea
            ok = true;


        if (ok)
        {
            for(int i = 0; i < matrice1.linii; i++)  // parcurgerea liniilor
            {
                for(int j = 0;j < matrice2.coloane; j++)  // parcurgerea coloanelor
                {
                    int k = 0;
                    for(int z = 0; z < matrice1.coloane; z++)  // parcurgerea elementelor pentru a putea realiza dot product-ul
                    {
                        rezultat.valori[i][j] += matrice1.valori[i][k] * matrice2.valori[k][j];  // realizeaza dot product-ul
                        k ++ ;
                    }
                }
            }
            return rezultat;  // returneaza produsul dintre cele doua matrice
        }
        else
        {
            cout << " > Nu se poate realiza produsul intre cele doua matrice deoarece " << matrice1.coloane << " != " << matrice2.linii << ". \n";
            throw int(4);
        }


    }

    // Acesta este operatorul de inmutire a doua matrice (matrice1 % matrice2), imultirea are loc element cu element, este TOTAL diferita fata de (matrice1 * matrice2)
    Matrice operator%(Matrice matrice1, Matrice matrice2)
    {
        Matrice rezultat(matrice1.linii, matrice2.coloane, "valoare", 0);  // declararea unei matrice care va stoca noile informatii din inmultirea celor doua matrice
        bool ok = false;

        if(matrice1.coloane == matrice2.coloane && matrice1.linii == matrice2.linii)  // daca numarul de coloane a primei matrice e egal cu cel de linii a celei de a doua matrice se poate realiza inmultirea
            ok = true;


        if (ok)
        {
            for(int i = 0; i < matrice1.linii; i++)  // parcurgerea liniilor
            {
                for(int j = 0;j < matrice2.coloane; j++) // parcurgerea coloanelor
                {
                    rezultat.valori[i][j] = matrice1.valori[i][j] * matrice2.valori[i][j];  // inmulteste element cu element valorile dintre cele doua matrice si le stocheaza in noua matrice
                }
            }
            return rezultat;  // returneaza produsul dintre cele doua matrice
        }
        else
        {
            cout << " > Nu se poate realiza produsul intre cele doua matrice deoarece nu au aceeasi dimensiune." << endl;
            throw int(5);
        }
    }

}


