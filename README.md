# INTROUDCERE
---
<b>ODIN</b> reprezintă începutul primei biblioteci de inteligență artificială din România, a cărui scop este dezvoltarea unor programe de AI cât mai eficiente și utile în viața de zi cu zi. <br><br>
<b>ODIN</b> reprezintă o metodă de familiarizare prin care ar trebui să treacă fiecare persoană pasionată de AI înainte de a face pasul la librării mult mai complexe. <br><br>
<b>ODIN</b> este momentan funcțional doar pentru programe de tip supervised learning. În viitor vor fi adăugate mai multe metode.

# CUM SE INSTALEAZĂ ODIN?
---
Pentru a inițializa ODIN va trebui să descărcați fișierele necesare funcționării acesteia, ci anume : fișierul Lib care conține : matrice.hpp, odin.hpp, client.hpp și GUI.exe. 
Apoi, în fișierul .cpp, includerea bibliotecii poate fi realizată folosind comanda #include "Lib/odin.hpp"

! În cazul în care întampinați o eroare legată de socket : (CodeBlocks) : Settings -> Compiler -> Linker Settings -> Add -> ws2_32 

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



   /// INPUTURI

   /* Aici are loc inițializarea matricelor cu valorile respective programului XOR.
   Adăugăm matricea respectivă în vectorul de input-uri folosind comanda ”push_back()” din biblioteca ”<vector>”. */

   input.push_back(Matrice(2, 1, "valoare", 1));
   input.push_back(Matrice(2, 1, "valoare", 0));
   input.push_back(Matrice(1, 1, "valoare", 0));
   input[2].adauga({1});  /* deoarece input[2] are o singură valoare, va trebui să adăugăm și un 1,
   pentru a avea matricea (0, 1)*/

   input[2] = input[2].sforma(2, 1); /* după această adăugare forma matricei se va schimba într-o matrice de tip coloană.
   Acest lucru poate fi remediat folosind comanda ”forma()”, care va schimba dimensiunea matricei. */

   input.push_back(Matrice(1, 1, "valoare", 1));
   input[3].adauga({0});
   input[3] = input[3].sforma(2, 1);


   /// OUTPUTURI

   /* Aici are loc inițializarea output-urilor, care nu sunt altceva decât 4 valori situate într-o matrice. */
   output.push_back(Matrice(1, 1, "valoare", 0));
   output.push_back(Matrice(1, 1, "valoare", 0));
   output.push_back(Matrice(1, 1, "valoare", 1));
   output.push_back(Matrice(1, 1, "valoare", 1));


   /// RETEA NEURONALA
   ReteaNeuronala model(input, output, "[2, 2, 1]");  // declararea rețelei neuronale în ”model”.
   model.antreneaza(20000);  // antrenarea funcției pentru 20000 de iterații.
   model.verificare(); // această funcție afișează output-ul pentru toate valorile din input.
   model.salvare("model"); // această funcție salvează modelul în fișierul "model.odin".
}



```
# FUNCȚIILE SPECIFICE LUCRULUI CU MATRICE (matrice.hpp)
---

În acest fișier se găsește o clasă cu următoarele metode : 

<details>
   <summary> 1. Constructorul matricei </summary>
    <p>
       
  > Parametri : <br>
  <p>
      <b>numar_linii</b> : numărul de linii a matricei (tip : int)<br>
      <b>numar_coloane</b> : numărul de coloane a matricei (tip : int)<br>
      <b>tip_matrice</b> : tipul matricei, poate lua doar două valori : "valoare" sau "random", pentru valoare va inițializa matricea cu o anumită valoare, pentru random o va   inițializa cu valori random (tip : string) <br>
      <b>valoare</b> : acest parametru stabilește valoarea matricei, în cazul tipului de matrice "valoare" sau intervalul (-valoare, valoare), în cazul numerelor random (tip : double)
</p> 

  > Returnează : construiește matricea

---
       
```c++
Matrice (int numar_linii, int numar_coloane, std::string tip_matrice, double valoare)
{


  /* Aici are loc initializarea seed-ului folosind biblioteca <random>, in defavoarea implementarii functiei rand(),
  din cauza previzibilitatii acesteia */

  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> dist(-valoare, valoare);

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



  this->forma[0] = numar_linii;
  this->forma[1] = numar_coloane;


}


```
    
  </p>
   
</details>

<details>
<summary> 2. Funcția de adăugare element în matrice </summary>
   
<p>
   
   > Parametri : <br>
  <p>
   <b>valoare</b> : primește valoarea ce va fi adăugată în matrice (tip : double) <br>
</p> 

  > Returnează : - 
   
```c++

void v_adauga(double valoare)  /* unicul parametru al functiei este de tip double,
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

  this->forma[0] = this->linii;
  this->forma[1] = this->coloane;


}
```
</p>
</details>

<details>
<summary> 3. Funcția de adăugare a unei liste de valori în matrice </summary>
   
<p>
   
   > Parametri : <br>
  <p>
   <b>valoare</b> : primește ca parametru un vector de valori <br>
</p> 

  > Returnează : - 
   
```c++

// Functia ce adauga o lista de valori in matrice
void adauga(vector<double> valoare)
{
  for(int i = 0; i < valoare.size(); i++)
      this->v_adauga(valoare[i]);
}
```
</p>
</details>


<details>
<summary> 4. Funcția de vectorizare </summary>
<p>
   
  > Parametri : - <br>
  > Returnează : returnează matricea de tip coloana

```c++
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

  this->forma[0] = this->linii;
  this->forma[1] = this->coloane;

  return vector_nou;  // returnam noua matrice de tip coloana
}
```

</p>
</details>

<details>
<summary> 5. Functia de randomizare </summary>
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
      std::swap(input[i], input[random]);  // schimbam valorile de pe pozitia curenta, cu cele de pe pozitia generata random
      std::swap(output[i], output[random]);  // schimbam valorile de pe pozitia curenta, cu cele de pe pozitia generata random

  }
}

```

</p>
</details>

<details>
<summary> 6. Funcția de schimbare de formă </summary>
<p>
   
  > Parametri : <br>
  <p>
   <b>dimensiune1</b> : numărul de linii ale viitoarei matrice (tip : int) <br> 
   <b>dimensiune2</b> : numărul de coloane ale viitoarei matrice (tip : int) <br>
</p> 

  > Returnează : returnează matricea 
   
```c++
Matrice sforma(int dimensiune1, int dimensiune2)
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

      this->forma[0] = this->linii;
      this->forma[1] = this->coloane;

      return vn;  // returnam matricea

  }
  else  // daca dimensiunile nu sunt corespunzatoare operatia nu poate fi realizata
  {
      std::cout << " > Dimensiunea matricei nu poate fi schimbata deoarece valorile introduse nu corespund cu numarul de linii si coloane ale matricei introduse. \n";
      throw int(6);
  }

}
```

</p>
</details>

<details>
<summary> 7. Funcția de transpunere a unei matrice </summary>
<p>
   
  > Parametri : - <br> 

  > Returnează : returnează matricea transpusă

```c++
/* Aceasta functie calculeaza transpusa matricei, exemplu : pentru o matrice de (3, 1), o va converti in (1, 3) */
Matrice transpusa()
{

  int linii, coloane;
  linii = this->linii;
  coloane = this->coloane;

  Matrice vector_nou(0,0,"valoare",0), vn(coloane, linii, "valoare", 0);  // initializarea unui nou vector, in care sunt copiate informatiile matricei
  vector_nou = this->vectorizare();  // transformarea matricei intr-o matrice de tip coloana

  int index = 0;  // initializam un index care va fi pozitia in functie de linii si coloane
  for(int i = 0;i < coloane; i++)  // parcurgerea liniilor in functie de dimensiunea introdusa
  {
      for(int j = 0; j < linii; j++)  // parcurgerea liniilor in functie de dimensiunea introdusa
      {
          vn.valori[i][j] = vector_nou.valori[0][index];  // atribuirea noului vector cu valorile din matricea coloana principala
          index++;
      }
  }

  this->forma[0] = this->linii;
  this->forma[1] = this->coloane;

  return vn;  // returnam matricea

}



```

</p>
</details>

<details>
<summary> 8. Funcția sigmoidală </summary>
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
<summary> 9. Funcția sigmoidală aplicată matricei </summary>
<p>
   
   
   > Parametri : - <br> 

  > Returnează : returnează matricea

```c++
/* Aceasta metoda aplica functia sigmoidala pentru o matrice */
Matrice sigmoid_matrice()
{
  Matrice matrice(0, 0, "valoare", 0);
  int coloane = this->coloane;  // retine numarul de coloane
  int linii = this->linii;  // retine numarul de linii

  matrice = this->vectorizare();  // vectorizeaza matricea

  for(int i = 0; i < coloane * linii; i++)  // parcurge toate elementele matricei
      matrice.valori[0][i] = sigmoid(matrice.valori[0][i]);  // aplica functia sigmoidala pentru fiecare valoare

  matrice = matrice.forma(linii, coloane);  // schimba forma matricei la cea initiala
  return matrice;  // returneaza matricea
}
```

</p>
</details>  

<details>
<summary> 10. Funcția sigmoidală (derivata) </summary>
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
<summary> 11. Funcția sigmoidală (derivata) aplicată matricei </summary>
<p>
   
   > Parametri : - <br>

  > Returnează : returnează matricea

```c++
// Derivata functiei sigmoidale aplicata matricei
Matrice d_sigmoid_matrice()
{
  Matrice matrice(0, 0, "valoare", 0);
  int coloane = this->coloane;  // retine numarul de coloane
  int linii = this->linii;  // retine numarul de linii

  matrice = this->vectorizare();  // vectorizeaza matricea

  for(int i = 0; i < coloane * linii; i++)  // parcurge toate elementele matricei
      matrice.valori[0][i] = d_sigmoid(matrice.valori[0][i]);  // aplica derivata sigmoidalei pentru fiecare valoare din matrice

  matrice = matrice.forma(linii, coloane);  // schimba forma matricei la cea initiala
  return matrice; // returneaza matricea
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
  Matrice rezultat(matrice.linii, matrice.coloane, "valoare", 0);  // declararea unei matrice care va stoca noile informatii din inmultirea matricei cu scalarul
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
  Matrice rezultat(matrice1.linii, matrice2.coloane, "valoare", 0); // declararea unei matrice care va stoca noile informatii din inmultirea celor doua matrice

  bool ok = false;

  if(matrice1.coloane == matrice2.linii)  // daca numarul de coloane a primei matrice e egal cu cel de linii a celei de a doua matrice se poate realiza inmultirea
      ok = true;


  if (ok)
  {

      for(int i = 0; i < matrice1.linii; i++)  // parcurgerea liniilor
      {
          int k = 0;
          for(int z = 0; z < matrice1.coloane; z++)  // parcurgerea elementelor pentru a putea realiza dot product-ul
          {
              for(int j = 0;j < matrice2.coloane; j++)  // parcurgerea coloanelor
              {
                  rezultat.valori[i][j] += matrice1.valori[i][z] * matrice2.valori[z][j];  // realizeaza dot product-ul
                  k ++ ;
              }
          }

      }


      return rezultat;  // returneaza produsul dintre cele doua matrice
  }
  else
  {
      std::cout << " > Nu se poate realiza produsul intre cele doua matrice deoarece " << matrice1.coloane << " != " << matrice2.linii << ". \n";
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

```

</p>
</details>  

<details>
<summary> 7. Funcția de afișare a formei unei matrice </summary>
<p>

> Parametri : - <br>


> Returnează : forma matricei

```c++

// Acesta este operatorul pentru afisarea formei matricei
ostream& operator<<(ostream &out, int f_vector[])
{
  out << "(" << f_vector[0] << ", " << f_vector[1] << ")";
  return out;
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

/// Acesta este constructorul retelei. Are 4 parametri : 
/// - input-ul : reprezinta vectorul de input-uri.
/// - output-ul : reprezinta vectorul de output-uri (POATE FI OMIS, doar in cazul in care se incarca o structura din fisier)
/// - structura : structura specifica retelei neuronale (POATE FI OMISA, doar in cazul in care se incarca o structura din fisier)
/// - rata de invatare : POATE FI OMISA (default : 0.8)
ReteaNeuronala model(input, output, "[2, 2, 1]", 0.8);

/// Aceasta este functia de antrenare specifica retelei neuronale. Are 2 parametri : 
/// - numarul de iteratii : de cate ori se va antrena programul.
/// - GUI - acest parametru este de tip bool si reprezinta interfata grafica a structurii. 
model.antreneaza(2000, false);

/// Aceasta este functia de salvare. Are un singur parametru :
/// - numele fisierului : este un string ce reprezinta numele fisierului. Fisierul va fi salvat cu extensia odin.
model.salvare("model");

/// Aceasta este functia de verificare. Are 2 parametri:
/// - numarul de zecimale : acest numar indica cate cifre sunt dupa virgula in momentul verificarii retelei neuronale.
/// - GUI : acest parametru este de tip bool si reprezinta interfata grafica a structurii. 
model.verificare(6, false);

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
          sleep(1);
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
      close(out);
      system("taskkill /F /T /IM GUI.exe");
  }

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
          sleep(1);
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
      close(out);
      system("taskkill /F /T /IM GUI.exe");
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
                  matrice = matrice.forma(pct[pos].x, pct[pos].y);  // schimba forma matricei in functie de dimensiunile din vectorul construit anterior
                  weights.push_back(matrice);  // adauga matricea in vectorul de sinapse
              }
              else  // altfel sunt citite bias-urile
              {
                  matrice = matrice.forma(pct[pos].x, pct[pos].y); // schimba forma matricei in functie de dimensiunile din vectorul construit anterior
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

# FUNCȚIILE SPECIFICE LUCRULUI CU SERVERUL (client.hpp)
---

În acest fișier se găsește următoarea funcție : 

<details>
<summary> 1. Funcția de conectare la server </summary>
<p>


> Parametri : <br>
<p>
<b>iteratii</b> : iterația curentă (tip : int) <br>
<b>weights</b> : vectorul de sinapse (tip : vector<Matrice>) <br>
<b>structura</b> : numărul de neuroni specific rețelei (tip : string) <br>
<b>hidden_layers</b> : vectorul de hidden_layers (tip : vector<Matrice>) <br>
</p>

> Returnează : -

</p>

```c++
// Aceasta functie a fost creata pentru a putea trimite date serverului
// In momentul in care serverul primeste informatii despre WEIGHTS si HIDDEN LAYERS, le prelucreaza pentru a realiza interfata grafica specifica structurii

SOCKET conectare_server(int iteratii, vector<Matrice> weights, string structura, int index, vector<Matrice> hidden_layers)
{
    WSADATA data;
    WORD version = MAKEWORD(2, 2);

    int wsOk = WSAStartup(version, &data);

    if(wsOk != 0)
        return 0 ;

    sockaddr_in server;
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);

    inet_ntoa(server.sin_addr);

    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    if(index == 0)
        close(out);

    string valoriMatrice = "";
    valoriMatrice += structura;
    valoriMatrice += "{";

    for(int z = 0; z <= index - 2; z++)
    {
        for(int i = 0; i<hidden_layers[z].linii; i++)
        {
            for(int j = 0; j<hidden_layers[z].coloane; j++)
            {
                valoriMatrice += to_string(hidden_layers[z].valori[i][j]);

                if(i != hidden_layers[z].linii)
                    valoriMatrice += ",";
            }
        }
    }

    valoriMatrice += "} ";

    for(int z = 0; z <= index-2; z++)
    {
        for(int i = 0; i<weights[z].linii; i++)
        {
            for(int j = 0; j<weights[z].coloane; j++)
            {
                valoriMatrice += to_string(weights[z].valori[i][j]);
                valoriMatrice += " ";
            }
        }
    }


    if(valoriMatrice.size() < 65535)
    {
        if(index == 0)
        {
            int sendOk = sendto(out, "end", 1, 0, (sockaddr*)&server, sizeof(server));
            return out;
            close(out);
        }
        else
            int sendOk = sendto(out, valoriMatrice.c_str(), valoriMatrice.size() + 1, 0, (sockaddr*)&server, sizeof(server));
    }
    else
    {
        std::cout << '\n' << "Cantitatea de informatii depaseste limita permisa de o conexiune UDP ( " << valoriMatrice.size() << " > 65535 )" << '\n' << "Numarul de layere ale structurii trebuie redus pentru a vizualiza structura neuronala \n";
        exit(0);
    }




    closesocket(out);
    WSACleanup();
    return 0;

}



```

</details>

<details>
<summary> 2. SERVER-UL + INTERFAȚA GRAFICĂ</summary>

```python

import socket
import tkinter as tk
import os

root = tk.Tk()
root.title("ODIN - GUI")
root.geometry("1280x720")
canvas = tk.Canvas(root, width=1280, height=720, bg='white')
canvas.pack()



localIP = "127.0.0.1"

localPort = 54000

bufferSize = 65535


UDPServerSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)

UDPServerSocket.bind((localIP, localPort))


def draw_circle(posX, posY, size, color):
    canvas.create_oval(posX - size/2, posY - size/2, posX + size / 2, posY + size / 2, fill = color)

def draw_line(posX, posY, posX_e, posY_e, color):
    canvas.create_line(posX, posY, posX_e, posY_e, fill = color, width = 1)


def connect_layers(center_list, weights_values):

    index = 0
    values = []

    try:
        for i in range(1, len(weights_values)):
            values.append(weights_values[i])
    except:
        pass

    for k in range(0, len(val)):

        for i in range(0, len(center_list)):

            x_c_start = center_list[i][1]
            y_c_start = center_list[i][2]

            for j in range(0, len(center_list)):

                x_c_end = center_list[j][1]
                y_c_end = center_list[j][2]


                if center_list[i][0] == k and center_list[j][0] == k+1:

                    color = 'white'


                    try:

                        if float(values[index]) >= 0:
                            r = 0
                            g = 255
                            b = 68

                            g *= (float(values[index]) / 2)
                            g = int(g)
                            g = abs(g)

                            if g > 255:
                                g = 255

                            color = '#%02x%02x%02x' % (r, g, b)
                        else:

                            r = 255
                            g = 0
                            b = 0

                            r *= (float(values[index]) / 2)
                            r = int(r)
                            r = abs(r)

                            if r > 255:
                                r = 255

                            color = '#%02x%02x%02x' % (r, g, b)
                    except:
                        pass

                    draw_line(x_c_start, y_c_start, x_c_end, y_c_end, color)
                    index += 1





ok = True
size = 100
center_points = []

def on_closing():
    os.system("TASKKILL /F /IM GUI.exe")
    root.quit()
    root.destroy()

while True:


    try:
        bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

        message = bytesAddressPair[0]

        address = bytesAddressPair[1]

        clientMsg = message.decode('utf-8')
    except:
        clientMsg = 'end'

    if clientMsg == 'end':
        UDPServerSocket.close()

    step = 5
    step2 = 0
    padding = 20

    indexHL = 0
    structure = ''
    for i in range(0, len(clientMsg)):
        if clientMsg[i] == ']':
            break
        else:
            indexHL += 1
            structure += clientMsg[i]

    structure += ']'
    structureHL = ''

    for i in range(indexHL + 1, len(clientMsg)):
        if clientMsg[i] == '}':
            break
        else:
            structureHL += clientMsg[i]

    val = structure.strip(', ] [').split(',')
    vmax = -3000000

    valHL = structureHL.strip(', } {').split(',')

    for i in range(0, len(val)):
        v = int(val[i])
        if v > vmax:
            vmax = v

    if ok == True:
        size = 1280/(len(val) * vmax)
        padding = padding/(vmax/5)
        size_increment = size


        for i in range(0, len(val)):

            if int(val[i]) == 1:
                x_c = (size/2) + step
                y_c = 720/2

                center_points.append((i, x_c , y_c ))

            else:
                for j in range(0, int(val[i])):
                    x_c = (size/2) + step
                    y_c = 720/2 - (int(val[i]) - 1 )*size/2 + step2 - (int(val[i]) - 1)*padding/2

                    center_points.append((i, x_c , y_c ))

                    step2 += size + padding

            step2 = 0
            step += 1280 / (len(val))


        ok = False

        connect_layers(center_points, clientMsg.split(' '))

        step = 5
        step2 = 0
        padding = 20
        size = 1280 / (len(val) * vmax)
        padding = padding / (vmax / 5)
        size_increment = size

        for i in range(0, len(val)):

            if int(val[i]) == 1:
                draw_circle((size / 2) + step, 720 / 2, size, 'white')

            else:
                for j in range(0, int(val[i])):
                    draw_circle((size / 2) + step,
                                720 / 2 - (int(val[i]) - 1) * size / 2 + step2 - (int(val[i]) - 1) * padding / 2, size, 'white')
                    step2 += size + padding

            step2 = 0
            step += 1280 / (len(val))




    try:
        canvas.delete('all')
        connect_layers(center_points, clientMsg.split(' '))

        step = 5
        step2 = 0
        padding = 20
        size = 1280 / (len(val) * vmax)
        padding = padding / (vmax / 5)
        size_increment = size
        color = 'white'

        s = 0

        indexHL = 0
        for i in range(0, len(val)):
            if int(val[i]) == 1:

                color = 'white'

                if i != 0:
                    try:

                        if float(valHL[indexHL]) >= 0.5:
                            r = 0
                            g = 255
                            b = 68

                            g *= (float(valHL[indexHL]))
                            g = int(g)
                            g = abs(g)

                            if g > 255:
                                g = 255

                            color = '#%02x%02x%02x' % (r, g, b)
                        else:

                            r = 255
                            g = 0
                            b = 0

                            r *= (float(valHL[indexHL]) + 0.5)
                            r = int(r)
                            r = abs(r)

                            if r > 255:
                                r = 255

                            color = '#%02x%02x%02x' % (r, g, b)
                    except:
                        pass

                    indexHL += 1
                draw_circle((size / 2) + step, 720 / 2, size, color)


            else:
                color = 'white'
                for j in range(0, int(val[i])):


                    color = 'white'

                    if i != 0:
                        try:

                            if float(valHL[indexHL]) >= 0.5:
                                r = 0
                                g = 255
                                b = 68

                                g *= (float(valHL[indexHL]))
                                g = int(g)
                                g = abs(g)

                                if g > 255:
                                    g = 255

                                color = '#%02x%02x%02x' % (r, g, b)
                            else:

                                r = 255
                                g = 0
                                b = 0

                                r *= ((float(valHL[indexHL]) + 0.5) )
                                r = int(r)
                                r = abs(r)

                                if r > 255:
                                    r = 255

                                color = '#%02x%02x%02x' % (r, g, b)
                        except:
                            pass

                        indexHL += 1

                    draw_circle((size / 2) + step,
                                720 / 2 - (int(val[i]) - 1) * size / 2 + step2 - (int(val[i]) - 1) * padding / 2, size, color)
                    step2 += size + padding



            step2 = 0
            step += 1280 / (len(val))

        root.protocol("WM_DELETE_WINDOW", on_closing)
        root.update()
    except:
        pass



```

