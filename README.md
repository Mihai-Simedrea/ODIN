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




