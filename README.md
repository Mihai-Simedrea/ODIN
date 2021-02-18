# INTROUDCERE
---
ODIN reprezintă începutul primei biblioteci de inteligență artificială din România, a cărui scop este dezvoltarea unor programe de AI cât mai eficiente și utile în viața de zi cu zi.

# CUM SE INSTALEAZĂ ODIN?
---
Pentru a inițializa ODIN va trebui să descărcați fișierele necesare funcționării acesteia, ci anume : fișierul Lib care conține : matrice.hpp și odin.hpp. 
Apoi, în fișierul .cpp, includerea bibliotecii poate fi realizată folosind comanda #include "Lib/odin.hpp"

# UN SCURT EXEMPLU AL UNUI PROGRAM ODIN
---
Problema XOR
```c++

/// INCLUDEREA BIBLIOTECILOR
#include <iostream> 
#include "Lib/odin.hpp"

using namespace std;
using namespace odin; // ODIN folosește un namespace specific în ceea ce privește utilizarea funcțiilor necesare

int main()
{

   vector<Matrice> input; // inițializarea unui vector de input-uri pentru a stoca informațiile necesare training-ului.
   vector<Matrice> output; // inițializarea unui vector de output-uri pentru a stoca informațiile necesare training-ului.

   Matrice a; // declararea unei matrice auxiliare pentru a putea utiliza funcțiile din clasa ”Matrice”.


   /// INPUTURI
   
   /* Aici are loc inițializarea matricelor cu valorile respective programului XOR. 
   Mai întâi inițializăm matricea auxiliară cu valorile necesare, urmând ca mai apoi să adăugăm
   matricea respectivă în vectorul de input-uri folosind comanda ”push_back()” din biblioteca ”<vector>”. */
   
   input.push_back(a.init(2, 1, "valoare", 1));
   input.push_back(a.init(2, 1, "valoare", 0));
   input.push_back(a.init(1, 1, "valoare", 0));
   input[2].adauga(1);  /* deoarece input[2] are o singură valoare, va trebui să adăugăm și un 1, 
   pentru a avea matricea (0, 1)*/
   
   input[2] = input[2].forma(2, 1); /* după această adăugare forma matricei se va schimba într-o matrice de tip coloană.
   Acest lucru poate fi remediat folosind comanda ”forma()”, care va schimba dimensiunea matricei. */

   input.push_back(a.init(1, 1, "valoare", 1));
   input[3].adauga(0);
   input[3] = input[2].forma(2, 1);


   /// OUTPUTURI
   
   /* Aici are loc inițializarea output-urilor, care nu sunt altceva decât 4 valori situate într-o matrice. */
   output.push_back(a.init(1, 1, "valoare", 0));
   output.push_back(a.init(1, 1, "valoare", 0));
   output.push_back(a.init(1, 1, "valoare", 1));
   output.push_back(a.init(1, 1, "valoare", 1));


   /// RETEA NEURONALA
   ReteaNeuronala model;  // declararea rețelei neuronale în ”model”.
   model.input = input;  // atribuirea input-urilor create anterior.
   model.output = output;  // atribuirea output-urilor create anterior.
   model.rata_de_invatare = 0.2;  // rata de învățare poate fi omisă, aceasta este default ”0.8”.
   model.structura = "[2, 2, 1]";  /* folosind această comandă putem stabili arhitectura programului. 
   În cazul nostru, avem 2 neuroni pentru input-uri, 2 neuroni pentru 
   primul hidden layer și un singur neuron pentru output. */
   model.antreneaza(20000);  // antrenarea funcției pentru 20000 de iterații.
   model.verificare(); // această funcție afișează output-ul pentru toate valorile din input.
}

```
# FUNCȚIILE SPECIFICE LUCRULUI CU MATRICE (matrice.hpp)
---

În acest fișier se găsește o clasă cu următoarele metode : 

<details>
<summary> 1. Funcția de inițializare </summary>
<p>


```c++
/* Aceasta este functia de initializare a unei matrice. Primeste ca parametri un numar de linii, respectiv de coloane,
un string care reprezinta tipul matricei, putand lua doar doua valori : "valoare" sau "random". Primul string va genera
o matrice care contine doar valoarea din variabila valoare, iar "random" va genera numere random in intervalul
(-valoare, valoare)*/
Matrice init(int numar_linii, int numar_coloane, string tip_matrice, double valoare)
{


  /* Aici are loc initializarea seed-ului folosind biblioteca <random>, in defavoarea implementarii functiei rand(),
  din cauza previzibilitatii acesteia */

  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> dist(-valoare, valoare);

  if(numar_linii < 0 || numar_coloane < 0)  /* daca numarul de linii sau coloane este mai mic decat 0, 
  initializarea nu are sens si nu va avea loc. */
  {
      cout << " > Numarul de linii si coloane trebuie sa fie pozitiv." << endl;
      throw int(1);
  }

  else
  {
      Matrice matrice;  // initializarea unei matrice care va reprezenta matricea initializata in fisierul .cpp
      bool val = false;
      bool random = false;

      /* Aceste structuri decizionale verifica tipul matricei, transmis ca parametru prin functia principalt */
      if(tip_matrice == "valoare")
          val = true;
      if(tip_matrice == "random")
          random = true;


      matrice.linii = numar_linii;  // initializarea numarului de linii cu valoarea din parametrul specific
      matrice.coloane = numar_coloane;  // initializarea numarului de coloane cu valoarea din parametrul specific

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

          matrice.valori.push_back(temp);  // adaugam linia curenta in matrice

      }

      this->linii = matrice.linii;  // preluam numarul de linii al matricei si il atribuim clasei
      this->coloane = matrice.coloane;  // preluam numarul de coloane al matricei si il atribuim clasei
      this->valori = matrice.valori;  // preluam valorile din matrice si le atribuim clasei
      return matrice;  // returnam matricea
  }

}
```

</p>
</details>

<details>
<summary> 2. Funcția de adăugare </summary>
<p>
   
```c++

void adauga(double valoare)  /* unicul parametru al functiei este de tip double,
reprezentand valoarea ce va fi adaugata in matrice */
{
  Matrice vector_nou;  /* initializarea unei matrice care va stoca informatiile anterioare, 
  dar, in plus, va avea si noua valoare adaugata */

  vector_nou = vector_nou.init(1, this->linii * this->coloane + 1, "valoare", 0); 
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
  this->valori = vector_nou.valori;  // setam valorile in functie de valorile matricei construite in functie


}

```
</p>
</details>
  


