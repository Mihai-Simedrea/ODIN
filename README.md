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
       
  > Parametri : <br>
  <p>
      <b>numar_linii</b> : numărul de linii a matricei (tip : int)<br>
      <b>numar_coloane</b> : numărul de coloane a matricei (tip : int)<br>
      <b>tip_matrice</b> : tipul matricei, poate lua doar două valori : "valoare" sau "random", pentru valoare va inițializa matricea cu o anumită valoare, pentru random o va   inițializa cu valori random (tip : string) <br>
      <b>valoare</b> : acest parametru stabilește valoarea matricei, în cazul tipului de matrice "valoare" sau intervalul (-valoare, valoare), în cazul numerelor random (tip : double)
</p> 

  > Returnează : returnează matricea (opțional) 

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
   
   > Parametri : <br>
  <p>
   <b>valoare</b> : primește valoarea ce va fi adăugată în matrice (tip : double) <br>
</p> 

  > Returnează : - 
   
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
   
  > Parametri : - <br>
  > Returnează : returnează matricea de tip coloana

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
   
  > Parametri : <br>
  <p>
     <b>input</b> : vectorul de input-uri a căror poziții urmează să fie randomizate (tip : vector<Matrice>) <br>
     <b>output</b> : vectorul de output-uri a căror poziții urmează să fie randomizate (tip : vector<Matrice>) <br>
     <b>numar_inputuri</b> : numărul de elemente supuse randomizării (tip : int) <br>
   </p>

  > Returnează : - 
      
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
   
  > Parametri : <br>
  <p>
   <b>dimensiune1</b> : numărul de linii ale viitoarei matrice (tip : int) <br> 
   <b>dimensiune2</b> : numărul de coloane ale viitoarei matrice (tip : int) <br>
</p> 

  > Returnează : returnează matricea 
   
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
   
  > Parametri : <br>
  <p>
   <b>matrice</b> : primește matricea a cărei transpusă urmează să fie calculată (tip : Matrice) <br>
</p> 

  > Returnează : returnează matricea 

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

   > Parametri : <br>
  <p>
   <b>x</b> : primește o valoare căreia îi va aplica funcția sigmoidală (tip : double) <br>
</p> 

  > Returnează : returnează o valoare după aplicarea funcției sigmoidale 

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
   
   
   > Parametri : <br>
  <p>
   <b>matrice</b> : primește o matrice, apoi fiecărui element din matrice i se va aplica funcția sigmoidală (tip : Matrice) <br>
</p> 

  > Returnează : returnează matricea

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
   
   
   > Parametri : <br>
  <p>
   <b>x</b> : primește o valoare căreia îi va aplica funcția sigmoidală (derivata) (tip : double) <br>
</p> 

  > Returnează : returnează o valoare dupa aplicarea funcției sigmoidale 

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
   
   > Parametri : <br>
  <p>
   <b>matrice</b> : primește o matrice, apoi fiecărui element din matrice i se va aplica funcția sigmoidală (derivata) (tip : Matrice) <br>
</p> 

  > Returnează : returnează matricea

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

---
În acest fișier se mai găsește și un namespace cu următoarele funcții :

<details>
<summary> 1. Funcția de afișare a matricei </summary>
<p>

> Parametri : <br>
<p>
<b>out : </b> permite folosirea operatorului "<<", urmat de o matrice <br>
<b>matrice : </b> matrice ce urmează să fie afișată (tip : Matrice) <br>
</p>

> Returnează : "afișarea"

```c++

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

```

</p>
</details>  


<details>
<summary> 2. Funcția de sumă </summary>
<p>

> Parametri : <br>
<p>
<b>matrice1 : </b> prima matrice (tip : Matrice) <br>
<b>matrice2 : </b> a doua matrice (tip : Matrice) <br>
</p>

> Returnează : suma dintre cele două matrice

```c++

// Acesta este operatorul de adunare, face suma intre doua matrice (matrice1 + matrice2)
Matrice operator+(Matrice matrice1, Matrice matrice2)  
{
  Matrice rezultat;  // declararea unei matrice care va stoca noile informatii din adunarea celor doua matrice

  if(!(matrice1.coloane == matrice2.coloane && matrice1.linii == matrice2.linii))  // daca liniile/coloanele primei matrice nu sunt egale cu liniile/coloanele celei de a doua matrice nu se realizeaza operatiunea
  {
      cout << " > Nu se poate realiza suma intre cele doua matrice deoarece nu au aceeasi dimensiune." << endl;
      throw int(2);
  }
  else  // altfel, are loc adunarea
  {
      rezultat = rezultat.init( matrice1.linii, matrice1.coloane, "valoare", 0);  // initializarea matricei cu numarul de coloane, respectiv de linii din prima matrice
      for(int i = 0; i < matrice1.linii; i++)  // parcurgerea liniilor
          for(int j = 0;j < matrice1.coloane; j++) // parcurgerea coloanelor
              rezultat.valori[i][j] = matrice1.valori[i][j] + matrice2.valori[i][j];  // retine suma elementelor de pe pozitia i si j in noua matrice

      return rezultat;  // returneaza rezultatul
  }
}

```

</p>
</details>  

<details>
<summary> 3. Funcția de diferență </summary>
<p>

> Parametri : <br>
<p>
<b>matrice1 : </b> prima matrice (tip : Matrice) <br>
<b>matrice2 : </b> a doua matrice (tip : Matrice) <br>
</p>

> Returnează : diferența dintre cele două matrice

```c++

// Acesta este operatorul de scadere, face diferenta intre doua matrice (matrice1 - matrice2)
Matrice operator-(Matrice matrice1, Matrice matrice2)
{
  Matrice rezultat; // declararea unei matrice care va stoca noile informatii din scaderea celor doua matrice
  if(!(matrice1.coloane == matrice2.coloane && matrice1.linii == matrice2.linii)) // daca liniile/coloanele primei matrice nu sunt egale cu liniile/coloanele celei de a doua matrice nu se realizeaza operatiunea
  {
      cout << " > Nu se poate realiza diferenta intre cele doua matrice deoarece nu au aceeasi dimensiune." << endl;
      throw int(3);
  }

  else // altfel, are loc scaderea
  {
      rezultat = rezultat.init(matrice1.linii, matrice1.coloane, "valoare", 0);  // initializarea matricei cu numarul de coloane, respectiv de linii din prima matrice
      for(int i = 0; i < matrice1.linii; i++)  // parcurgerea liniilor
          for(int j = 0;j < matrice1.coloane; j++)  // parcurgerea coloanelor
              rezultat.valori[i][j] = matrice1.valori[i][j] - matrice2.valori[i][j];  // retine suma elementelor de pe pozitia i si j in noua matrice
      return rezultat;  // returneaza rezultatul
  }
}

```

</p>
</details>  


<details>
<summary> 4. Funcția de înmulțire cu scalar </summary>
<p>

> Parametri : <br>
<p>
<b>valoare_scalar : </b> valoarea cu care vom înmulți fiecare element din matrice (tip : double) <br>
<b>matrice : </b> matrice căruia i se va aplica scalarul (tip : Matrice) <br>
</p>

> Returnează : matricea înmulțită cu valoarea scalarului

```c++

// Acesta este operatorul de inmultire cu scalar, inmulteste fiecare element din matrice cu un numar de tip double
Matrice operator*(double valoare_scalar, Matrice matrice)
{
  Matrice rezultat;  // declararea unei matrice care va stoca noile informatii din inmultirea matricei cu scalarul
  rezultat = rezultat.init(matrice.linii, matrice.coloane, "valoare", 0);  // initializarea matricei cu numarul de coloane, respectiv de linii din prima matrice
  for(int i = 0; i < matrice.linii; i++)  // parcurgerea liniilor
      for(int j = 0;j < matrice.coloane; j++)  // parcurgerea coloanelor
          rezultat.valori[i][j] = valoare_scalar * matrice.valori[i][j];  // retine produsul dintre scalar si elementul matricei transmise in noua matrice
  return rezultat;  // returneaza matricea

}

```

</p>
</details>  

<details>
<summary> 5. Funcția de înmulțire între două matrice </summary>
<p>

> Parametri : <br>
<p>
<b>matrice1 : </b> prima matrice (tip : Matrice) <br>
<b>matrice2 : </b> a doua matrice (tip : Matrice) <br>
</p>

> Returnează : produsul dintre cele două matrice

```c++

// Aceasta este operatorul de inmultirea a doua matrice (matrice1 * matrice2) - dot product
Matrice operator*(Matrice matrice1, Matrice matrice2)
{
  Matrice rezultat; // declararea unei matrice care va stoca noile informatii din inmultirea celor doua matrice

  bool ok = false;

  if(matrice1.coloane == matrice2.linii)  // daca numarul de coloane a primei matrice e egal cu cel de linii a celei de a doua matrice se poate realiza inmultirea
      ok = true;


  if (ok)
  {
      rezultat = rezultat.init(matrice1.linii, matrice2.coloane, "valoare", 0); // initializarea matricei cu numarul de coloane, respectiv de linii din prima matrice
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


```

</p>
</details>  



<details>
<summary> 6. Funcția a doua de înmulțire între două matrice </summary>
<p>

> Parametri : <br>
<p>
<b>matrice1 : </b> prima matrice (tip : Matrice) <br>
<b>matrice2 : </b> a doua matrice (tip : Matrice) <br>
</p>

> Returnează : produsul dintre cele două matrice (înmulțirea are loc element cu element)

```c++

// Acesta este operatorul de inmutire a doua matrice (matrice1 % matrice2), imultirea are loc element cu element, este TOTAL diferita fata de (matrice1 * matrice2)
Matrice operator%(Matrice matrice1, Matrice matrice2)
{
  Matrice rezultat;  // declararea unei matrice care va stoca noile informatii din inmultirea celor doua matrice
  bool ok = false;

  if(matrice1.coloane == matrice2.coloane && matrice1.linii == matrice2.linii)  // daca numarul de coloane a primei matrice e egal cu cel de linii a celei de a doua matrice se poate realiza inmultirea
      ok = true;


  if (ok)
  {
      rezultat = rezultat.init(matrice1.linii, matrice2.coloane, "valoare", 0);  // initializarea matricei cu numarul de coloane, respectiv de linii din prima matrice
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


```

</p>
</details>  

# FUNCȚIILE SPECIFICE LUCRULUI CU REȚEAUA NEURONALĂ (odin.hpp)
---

În acest fișier se găsește o clasă cu următoarele metode : 

<details>
<summary> 1. Funcții din odin.cpp </summary>
<p>

> Ce reprezintă fiecare funcție din odin.hpp?

```c++

ReteaNeuronala model;  // declararea rețelei neuronale
model.input = input;  // atribuirea input-urilor ce urmează să fie antrenate
model.output = output;  // atribuirea output-urilor corespunzătoare input-urilor
model.rata_de_invatare = 0.2;  // rata de învățare poate lua orice valoare în (0, 1) , inițial este setată la 0.8
model.structura = "[2, 2, 1]";  // structura rețelei neuronale, în cazul nostru avem 2 neuroni pentru input-uri, 2 pentru primul hidden layer și unul pentru output
model.antreneaza(20000);  // numărul de ”antrenamente” ale structurii
model.verificare();  // verificarea input-urilor după training

```

</p>
</details>  

<details>
<summary> 2. Funcția de antrenare a rețelei </summary>
<p>
   
  > Parametri : <br>
  <p>
   <b>iterații</b> : numărul de iterații atribuite rețelei (tip : int) <br> 
</p> 

  > Returnează : -
   
```c++
// Aceasta functie este extrem de importanta in aceasta biblioteca deoarece antreneaza sinapsele neuronilor in vederea unor rezultate cat mai bune.
void antreneaza(int iteratii)  // primeste un singur parametru, ci anume, numarul de iteratii
{
  int n = structura.length(); // retine in variabila n lungimea structurii
  char s[n + 1]; // declararea unui tablou de char in care o sa fie structura
  strcpy(s, structura.c_str());  // copiaza structura in vectorul de char (pentru a putea utiliza functiile specifice vectorului de char, ci nu string-ului.

  char *p = strtok(s, ", [ ]");  // retine primul numar din strctura, pointeaza la acel caracter. Spre exemplu : daca avem [2, 2, 1], va retine in pointerul p : 2

  int structura_int[1000]; // aici este un vector de int, care va retine fiecare numar de neuroni din fiecare hidden layer
  while(p != NULL)
  {
      structura_int[index] = stoi(p);  // converteste pointerul in int si il retine in vectorul specficic
      p = strtok(NULL, ", [ ]");  // pointeaza la urmatorul string
      index++;  // incrementeaza pozitia vectorului
  }


  Matrice aux;  // o matrice auxiliara pentru a putea folosi functiile din matrice.hpp

  for(int i = 0; i <= index - 2; i++)
  {
      weights.push_back(aux.init(structura_int[i+1], structura_int[i], "random", 2));  // initalizeaza vectorul de sinapse cu valori random in (-2, 2). Iar dimensiunea este stabilita in functie de numarul de pe poztia i + 1 din strctura si numarul de pe pozitia i
      // aceasta initializare este facuta in felul acesta pentru a putea realiza operatiile specifice matricelor, precum : adunare, scadere, produs, etc...
  }

  for(int i = 0; i <= index - 1; i++)
      biases.push_back(aux.init(structura_int[i + 1], 1, "random", 2));  // initializeaza bias-urile in functie de pozitia de pe i + 1 cu valori in (-2, 2)



  vector<Matrice> hidden_layers;  // declararea unui vector de hidden layers
  for(int z = 0; z < iteratii; z++)  // parcurgem numarul de iteratii transmise ca parametru
  {

      input[z].randomizare(input, output, input.size());  // randomizam input-urile pentru a evita o problema frecvent intalnita in ML, ci anume overfit-ul
      vector<Matrice> errori_hidden_layers; // initializare matrice de erori pentru hidden layers
      for(int i = 0 ; i < input.size(); i++)  // parcurgem lungimea input-urilor
      {
          vector<Matrice> hidden_layers;  // initalizare hidden layers
          Matrice rezultat;  // initializarea unei matrice de rezultat care va retine valori diverse in vederea training-ului
          rezultat = weights[0] * input[i];  // calcularea primului hidden layer
          hidden_layers.push_back(rezultat);  // adaugarea primului hidden layer in vector

          hidden_layers[0] = hidden_layers[0] + biases[0];  // adaugarea bias-ului in primul hidden layer

          hidden_layers[0].sigmoid_matrice(hidden_layers[0]);  // aplicarea functiei sigmoidale pentru primul hidden layer


          for(int j = 1; j <= index - 2; j++)  // parcurgerea urmatoarelor layere.
          {
              rezultat = weights[j] * hidden_layers[j - 1];  // calculeaza produsul in functie de sinapsele curente si hidden layer-ul anterior
              hidden_layers.push_back(rezultat);  // adauga in vector rezultatul
              hidden_layers[j] = biases[j] + hidden_layers[j]; // adauga bias-ul hidden layer-ului
              hidden_layers[j].sigmoid_matrice(hidden_layers[j]);  // aplica functia sigmoidala hidden layer-ului de pe pozitia j

          }

          vector<Matrice> erori_hidden_layers;  // declararea vectorului de erori
          for(int j = 0; j <= index - 2; j++)  // parcurgem vectorul pentru a-l putea initializa cu valori nule
              erori_hidden_layers.push_back(aux.init(1, 1, "valoare", 0));

          erori_hidden_layers[index - 2] = output[i] - hidden_layers[index - 2];  // in felul acesta putem calcula eroarea output-ului.
          // Daca facem diferenta intre output-ul pe care il cunoastem si output-ul care a fost prezis de catre program putem calcula eroarea acestuia


          for(int j = index - 2 - 1; j >= 0; j -- )  // parcurgere hidden layers
          {

              weights[j+1] = weights[j+1].transpusa(weights[j + 1]);  // facem transpusa matricei pentru a putea realiza operatiile viitoare

              erori_hidden_layers[j] = weights[j + 1] * erori_hidden_layers[j + 1];  // distribuim erorile pe pozitia j in functie de cele de pe pozitia j+1

              weights[j+1] = weights[j+1].transpusa(weights[j + 1]); // aducem matricea la forma initiala, aplicand inca o data traspusa



          }


          vector<Matrice> hidden_layers_derivate;
          vector<Matrice> gradienturi;
          vector<Matrice> delta_weights;

          for(int j = 0; j <= index - 2; j++)  // parcurgem vectorii declarati anterior si le atribuim valori nule
          {
              hidden_layers_derivate.push_back(aux.init(1, 1, "valoare", 0));
              gradienturi.push_back(aux.init(1, 1, "valoare", 0));
              delta_weights.push_back(aux.init(1, 1, "valoare", 0));
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
              hidden_layers[j - 1] = hidden_layers[j-1].transpusa(hidden_layers[j - 1]); // transpusa matricei
              delta_weights[j] = gradienturi[j] * hidden_layers[j - 1];  // calculam delta weights-urile pentru a putea adauga diferenta necesara in vederea imbunatatirii retelei neuronale, acesta valori sunt relativ mici.
              hidden_layers[j - 1] = hidden_layers[j - 1].transpusa(hidden_layers[j - 1]);  // revenirea la forma initiala a matricei
          }

          input[i] = input[i].transpusa(input[i]);  // transpusa input-ului

          delta_weights[0] = gradienturi[0] * input[i];  // calculam delta weights-urile necesare pentru input-uri 
          input[i] = input[i].transpusa(input[i]);  // revenim la forma initiala a input-urilor


          // folosind acest for actualizam sinapsele in functie de delta_weights (pe care le-am calculat la pasii anteriori)
          for(int j = 0; j<=index-2;j++)
          {
              weights[j] = delta_weights[j] + weights[j];
          }

      }
      cout << endl;
      cout << z << " / " << iteratii;
      cout << endl;
  }

  cout << endl << endl;

}
```

</p>
</details>

<details>
<summary> 3. Funcția de verificare </summary>
<p>

> Parametri : - <br>

> Returnează : nu returnează nimic, ci doar afișează toate predicțiile în funcție de input-urile antrenate

```c++

// Aceasta functie este asemanatoare cu cea de training, doar ca nu antreneaza nimic, ci doar genereaza valorile in functie de sinapsele antrenate pentru input-urile introduse
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

  Matrice aux;

  for(int i = 0; i <= index - 2; i++)
  {
      hidden_layers.push_back(aux.init(1, 1, "valoare", 0));
  }

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

      cout << (hidden_layers[index-2]);
      cout << endl;

  }
}


```

</p>
</details>  

<details>
<summary> 4. Funcția de salvare </summary>
<p>

> Parametri : <br>
<p>
<b>fisier</b> : numele fișierului în care vor fi stocate informațiile (tip : char[]) <br>
</p>

> Returnează : -

```c++

// Aceasta este functia care salveaza datele referitoare la training
void salvare(char fisier[])
{

  char fis[1000];  // un vector de char care stocheaza informatii referitoare la fisierul in care vor fi datele
  strcpy(fis, fisier);  // copiaza numele fisierului in vectorul fis
  char extensie[] = {".odin"};  // creeaza extensia bazei de date
  strcat(fis, extensie); // adauga extensia fisierului

  ofstream o(fis);  // declara fisierul de iesire

  o << index;  // scrie in fisierul de iesire indexul
  o << endl;

  for(int i = 0; i <= index - 2; i++)
  {
      o << weights[i].linii << " " << weights[i].coloane << endl;  // scrie numarul de linii si coloane a tuturor sinapselor
  }
  for(int i = 0; i <= index - 2; i++)
  {
      o << biases[i].linii << " " << biases[i].coloane << endl;  // scrie numarul de linii si coloane a tuturor bias-urilor
  }

  o << endl;


  for(int z = 0; z <= index - 2; z++)  // parcurge toate sinapsele
  {
      for(int i = 0;i < weights[z].linii;i++)  // parcurge liniile pentru sinapsa la pozitia z
      {
          for(int j = 0;j< weights[z].coloane;j++) // parcurge coloanele pentru sinapsa la pozitia z
          {
              o << weights[z].valori[i][j] << " ";  // scrie valorile sinapselor in fisier
          }
          o << endl;
      }
      o << endl;
  }

  o << endl;

  for(int z = 0; z <= index - 2; z++)  // parcurge toate bias-urile
  {
      for(int i = 0;i < biases[z].linii;i++) // parcurge liniile pentru bias-ul la pozitia z
      {
          for(int j = 0;j< biases[z].coloane;j++)  // parcurge coloanele pentru bias-ul la pozitia z
          {
              o << biases[z].valori[i][j] << " ";  // scrie valorile bias-urilor
          }
          o << endl;
      }
      o << endl;
  }

  o << endl;
  o << structura;  // scrie arhitectura retelei neuronale

  o.close();  // inchide fisierul
}



```

</p>
</details>  

<details>
<summary> 5. Funcția de încărcare </summary>
<p>

> Parametri : <br>
<p>
<b>fisier</b> : numele fișierului din care vor fi citite informațiile (tip : char[]) <br>
</p>

> Returnează : nu returnează nimic, doar schimbă variabilele globale care aparțin rețelei neuronale

```c++
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
              Matrice matrice;  // initializam o matrice

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
                  forma(matrice, pct[pos].x, pct[pos].y);  // schimba forma matricei in functie de dimensiunile din vectorul construit anterior
                  weights.push_back(matrice);  // adauga matricea in vectorul de sinapse
              }
              else  // altfel sunt citite bias-urile
              {
                  forma(matrice, pct[pos].x, pct[pos].y); // schimba forma matricei in functie de dimensiunile din vectorul construit anterior
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

```

</p>
</details>  





