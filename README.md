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
   <summary> 1. Functia de initializare </summary>
    <p>
       
  <p>Parametri : <br>
   <b>numar_linii</b> : numarul de linii a matricei <br>
   <b>numar_coloane</b> : numarul de coloane a matricei <br>
   <b>tip_matrice</b> : tipul matricei, poate lua doar doua valori : "valoare" sau "random", pentru valoare va initializa matricea cu o anumita valoare, pentru random o va initializa cu valori random <br>
   <b>valoare</b> : acest parametru stabileste valoarea matricei, in cazul tipului de matrice "valoare" sau intervalul (-valoare, valoare) in cazul numerelor random
</p> 

---
       
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
  
<details>
<summary> 3. Funcția de vectorizare </summary>
<p>

```c++
Matrice vectorizare()  // aceasta functie nu primeste niciun parametru, pur si simplu schimba forma matricei intr-o matrice de tip coloana.
{
  Matrice vector_nou;  // initializarea unei matrice care va stoca informatiile anterioare


  vector_nou.init(1, this->linii * this->coloane, "valoare", 0);  /* initializarea matricei cu valori nule, luand in considerare numarul de linii si coloane ale matricei din fisierul cpp*/

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
```

</p>
</details>

<details>
<summary> 4. Functia de randomizare </summary>
<p>
      
```c++
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
```

</p>
</details>

<details>
<summary> 5. Funcția de schimbare de formă </summary>
<p>
   
```c++
/* Functia "forma" schimba dimensiunea unei matrice.
 Functia are doar doi parametri, prima dimensiune si a doua, acestea reprezinta
 dimensiunile in care dorim sa convertim matricea. */
Matrice forma(int dimensiune1, int dimensiune2)
{
  if(dimensiune1 * dimensiune2 == this->coloane * this->linii)  // daca produsul dimensiunilor introduse e egal cu cel al matricei se va realiza conversia.
  {

      Matrice vector_nou, vn;  // initializarea unui nou vector, in care sunt copiate informatiile matricei
      vector_nou = this->vectorizare();  // transformarea matricei intr-o matrice de tip coloana

      vn.init(dimensiune1, dimensiune2, "valoare", 0);  // initializarea vectorului cu dimensiunile corespunzatoare

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
```

</p>
</details>

<details>
<summary> 6. Funcția de transpunere a unei matrice </summary>
<p>

```c++
/* Aceasta functie calculeaza transpusa matricei, exemplu : pentru o matrice de (3, 1), o va converti in (1, 3) */
Matrice transpusa(Matrice matrice)  
{
  int coloane = matrice.coloane;  // retine numarul de coloane ale matricei in "coloane"
  int linii = matrice.linii;  // retine numarul de linii ale matricei in "linii"

  matrice = forma(coloane, linii);  // schimba forma matricei, liniile devin coloane, iar coloanele devin linii

  return matrice;  // returneaza matricea

}
```

</p>
</details>

<details>
<summary> 7. Funcția sigmoidală </summary>
<p>

```c++
/* Functia sigmoidala */
double sigmoid(double x)
{
  return 1 / (1 + exp(-x));  // returneaza o valoare dupa aplicarea functiei sigmoidale
}
```

</p>
</details>  
 
 
<details>
<summary> 8. Funcția sigmoidală aplicată matricei </summary>
<p>

```c++
/* Aceasta metoda aplica functia sigmoidala pentru o matrice */
void sigmoid_matrice(Matrice &matrice)
{
  int coloane = matrice.coloane;  // retine numarul de coloane
  int linii = matrice.linii;  // retine numarul de linii

  matrice = matrice.vectorizare();  // vectorizeaza matricea

  for(int i = 0; i < coloane * linii; i++)  // parcurge toate elementele matricei
      matrice.valori[0][i] = sigmoid(matrice.valori[0][i]);  // aplica functia sigmoidala pentru fiecare valoare

  matrice = forma(linii, coloane);  // schimba forma matricei la cea initiala
}
```

</p>
</details>  

<details>
<summary> 9. Funcția sigmoidală (derivata) </summary>
<p>

```c++
/* Derivata functiei sigmoidale */
double d_sigmoid(double x)
{
  return x * (1 - x);  /* o sa returneze valoarea dupa derivarea unei valori folosind functia sigmoidala (Valoarea trebuie sa aiba in componenta functia sigmoidala inainte de a fi aplicata derivata!!) */
}

```

</p>
</details>  


<details>
<summary> 10. Funcția sigmoidală (derivata) aplicată matricei </summary>
<p>

```c++
// Derivata functiei sigmoidale aplicata matricei 
void d_sigmoid_matrice(Matrice &matrice)
{
  int coloane = matrice.coloane;  // retine numarul de coloane
  int linii = matrice.linii;  // retine numarul de linii

  matrice = matrice.vectorizare();  // vectorizeaza matricea

  for(int i = 0; i < coloane * linii; i++)  // parcurge toate elementele matricei
      matrice.valori[0][i] = d_sigmoid(matrice.valori[0][i]);  // aplica derivata sigmoidalei pentru fiecare valoare din matrice

  matrice = forma(linii, coloane);  // schimba forma matricei la cea initiala
}
```

</p>
</details>  
