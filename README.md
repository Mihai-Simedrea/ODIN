# INTROUDCERE
---
ODIN reprezintă începutul primei biblioteci de inteligență artificială din România, a cărui scop este dezvoltarea unor programe de AI cât mai eficiente și utile în viața de zi cu zi.

# CUM SE INSTALEAZA ODIN?
---
Pentru a inițializa ODIN va trebui să descărcați fișierele necesare funcționării acesteia, ci anume : fișierul Lib care conține : matrice.hpp și odin.hpp. 
Apoi, în fișierul .cpp, includerea bibliotecii poate fi realizată folosind comanda #include "Lib/odin.hpp"

# UN SCURT EXEMPLU AL UNUI PROGRAM ODIN
---
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
