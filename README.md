# INTROUDCERE
---
<b>ODIN</b> reprezintă începutul primei biblioteci de inteligență artificială din România, a cărui scop este dezvoltarea unor programe de AI cât mai eficiente și utile în viața de zi cu zi. <br><br>
<b>ODIN</b> reprezintă o metodă de familiarizare prin care ar trebui să treacă fiecare persoană pasionată de AI înainte de a face pasul la librării mult mai complexe. <br><br>
<b>ODIN</b> este momentan funcțional doar pentru programe de tip supervised learning. În viitor vor fi adăugate mai multe metode.

# CUM SE INSTALEAZĂ ODIN?
---
Pentru a inițializa ODIN va trebui să descărcați fișierele necesare funcționării acesteia, ci anume : fișierul Lib care conține : 
 - matrice.hpp 
 - odin.hpp 
 - client.hpp 
 - input_methods.hpp
 - neural_gui.hpp
Apoi, în fișierul .cpp, includerea bibliotecii poate fi realizată folosind comanda #include "Lib/odin.hpp"

În același timp, această bibliotecă conține 3 programe externe specifice lucrului cu neuroni : 
 -  GUI.exe (permite vizualizarea structurilor neurornale)
 -  DATAPRINT.exe (permite vizualizarea unei matrice)
 -  DRAW.exe (oferă user-ului oportunitatea de a desena o imagine pe un grid, apoi posibilitatea de convertire a acesteia într-o matrice)

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
   <summary> 1.1. Constructorul matricei </summary>
    <p>
       
  > Parametri : <br>
  <p>
      <b>rows_number</b> : numărul de linii a matricei (tip : int)<br>
      <b>columns_number</b> : numărul de coloane a matricei (tip : int)<br>
      <b>matrix_type</b> : tipul matricei, poate lua doar două valori : "valoare" sau "random", pentru valoare va inițializa matricea cu o anumită valoare, pentru random o va   inițializa cu valori random (tip : string) <br>
      <b>value</b> : acest parametru stabilește valoarea matricei, în cazul tipului de matrice "valoare" sau intervalul (-valoare, valoare), în cazul numerelor random (tip : double)
</p> 

  > Returnează : construiește matricea

---
       
```c++
// Matrix constructor
Matrix (int rows_number = 0, int columns_number = 0, std::string matrix_type = "value", double value = 0)
{

   /* Seed initialization */

   std::random_device rd;
   std::mt19937 mt(rd());
   std::uniform_real_distribution<double> dist(-value, value);


   bool val = false;
   bool random = false;


   // Check the matrix type
   if(matrix_type == "value")
       val = true;
   if(matrix_type == "random")
       random = true;


   for (int h = 0; h < rows_number; h++)  // iterate through the number of rows
   {
       std::vector<double> temp;  // temporary vector
       for (int w = 0; w < columns_number; w++)  // iterate through the number of columns
       {
           if(val)  // if the matrix type is "value" then you will add the value into temporary vector
               temp.push_back(value);
           else if(random)  // else you will add a random number from [-value, value]
               temp.push_back((dist(mt)));


       }

       this->values.push_back(temp);  // add current row in the matrix

   }

   this->rows = rows_number;  // add the number of rows into matrix class
   this->columns = columns_number;  // add the number of columns into matrix class



   this->shape[0] = rows_number;  // set the shape (rows)
   this->shape[1] = columns_number;  // set the shape (columns)

}


```
    
  </p>
   
</details>
   
   <details>
   <summary> 1.2. Constructorul matricei </summary>
    <p>
       
  > Parametri : <br>
  <p>
      <b>inputs</b> : input-urile ce vor fi adăugate în matrice (tip : vector<Matrix>)<br>
      <b>outputs</b> : output-urile ce se vor genera pe baza input-urilor (tip : vector<Matrix>)<br>
      <b>max_outputs</b> : numărul maxim de output-uri (tip : int) <br>
      <b>max_images</b> : numărul maxim de imagini ce vor fi adăugate în matrice (tip : long)
      <b>print_text</b> : dacă să afișeze numărul imaginii curente (tip : bool)
</p> 

  > Returnează : construiește matricea

---
       
```c++
// Matrix constructor
Matrix(std::vector<Matrix> &inputs, std::vector<Matrix> &outputs, int max_outputs, std::string path, long max_images = -1, bool print_text = false)
{
   std::cout << "Loading database from : '" << path << "' \n";

   std::string global_path = "";
   std::string current_folder = "";

   bool ok = false;


   // Get the parent folder path of the current path
   for(int i = path.size(); i>=0; i--)
   {
       if(path[i] == '\\')
           ok = true;
       else if(!ok)
           current_folder += path[i];
       if(ok)
           global_path += path[i];
   }
   reverse(global_path.begin(), global_path.end());  // reverse the string
   reverse(current_folder.begin(), current_folder.end()); // reverse the string

   global_path[global_path.size()-1] = '\0';
   current_folder[current_folder.size()-1] = '\0';

   int number_of_file_gp = 0;

   for (const auto &entry : fs::directory_iterator(global_path))
       number_of_file_gp ++;

   Matrix output(max_outputs, 1, "value", 0);

   int z_current = 1;

   long global_len = 0;
   if(max_images == -1)
   {
       for(const auto & entry : fs::directory_iterator(path))
           global_len ++ ;

       max_images = global_len;
   }

   for (const auto & entry : fs::directory_iterator(path))
   {

       if(z_current < max_images)
       {

           std::string path_string{entry.path().u8string()}; // convert filestream path to string path
           cv::Mat img = cv::imread(path_string, cv::IMREAD_COLOR); // read the current image

           uint8_t* pixelPtr = (uint8_t*)img.data;  // get data from image
           int cn = img.channels();
           cv::Scalar_<uint8_t> bgrPixel;
           double grayscale = 0;

           inputs.push_back(Matrix());


           output.values[target][0] = 1;
           outputs.push_back(output);

           // iterate over rows and columns to append values into the input vector
           for(int i = 0; i < img.rows; i++)
           {
               for(int j = 0; j < img.cols; j++)
               {
                   bgrPixel.val[0] = pixelPtr[i*img.cols*cn + j*cn + 0]; // B
                   bgrPixel.val[1] = pixelPtr[i*img.cols*cn + j*cn + 1]; // G
                   bgrPixel.val[2] = pixelPtr[i*img.cols*cn + j*cn + 2]; // R

                   grayscale = (bgrPixel.val[0] + bgrPixel.val[1] + bgrPixel.val[2]) / 3;
                   inputs[inputs.size() - 1].add({grayscale / 255});
               }
           }

           if(print_text)
               std::cout << z_current << " / " << max_images << "\n";


           inputs[inputs.size() - 1] = inputs[inputs.size() - 1].transpose();
           z_current ++ ;
       }
       else if(z_current == max_images)
       {
           std::string path_string{entry.path().u8string()}; // convert filestream path to string path
           cv::Mat img = cv::imread(path_string, cv::IMREAD_COLOR); // read the current image

           uint8_t* pixelPtr = (uint8_t*)img.data;  // get data from image
           int cn = img.channels();
           cv::Scalar_<uint8_t> bgrPixel;
           double grayscale = 0;


           output.values[target][0] = 1;
           outputs.push_back(output);



           // iterate over rows and columns to append values into the input vector
           for(int i = 0; i < img.rows; i++)
           {
               for(int j = 0; j < img.cols; j++)
               {
                   bgrPixel.val[0] = pixelPtr[i*img.cols*cn + j*cn + 0]; // B
                   bgrPixel.val[1] = pixelPtr[i*img.cols*cn + j*cn + 1]; // G
                   bgrPixel.val[2] = pixelPtr[i*img.cols*cn + j*cn + 2]; // R

                   grayscale = (bgrPixel.val[0] + bgrPixel.val[1] + bgrPixel.val[2]) / 3;
                   this->add({grayscale / 255});
               }
           }

           if(print_text)
               std::cout << z_current << " / " << max_images << "\n";

           *this = this->transpose();
           z_current ++ ;
       }

   }
   if(print_text)
       std::cout << "\n\n";
   else
       std::cout << "";

   target += 1;

}


```
    
  </p>
   
</details>

<details>
<summary> 2. Funcția de adăugare element în matrice </summary>
   
<p>
   
   > Parametri : <br>
  <p>
   <b>value</b> : primește valoarea ce va fi adăugată în matrice (tip : double) <br>
</p> 

  > Returnează : - 
   
```c++

void v_add(double value)
{
   Matrix new_array(1, this->rows * this->columns + 1, "value", 0);  // create a new matrix

   int index = 0;

   for(int i = 0; i < this->rows; i++)  // iterate through the number of rows
   {
       for(int j = 0; j < this->columns; j++)  // iterate through the number of columns
       {
           index = i * this->columns + j;  // create a 1D index from the rows and columns of 2D array
           new_array.values[0][index] = this->values[i][j];  // add the values to the 1D array
       }
   }

   new_array.values[0][this->columns * this->rows ] = value;

   this->rows = new_array.rows;  // set the number of rows to the new matrix
   this->columns = new_array.columns;  // set the number of columns to the new matrix
   this->values = new_array.values;  // set the values to the new matrix

   this->shape[0] = this->rows;
   this->shape[1] = this->columns;


}
```
</p>
</details>

<details>
<summary> 3. Funcția de adăugare a unei liste de valori în matrice </summary>
   
<p>
   
   > Parametri : <br>
  <p>
   <b>value</b> : primește ca parametru un vector de valori <br>
</p> 

  > Returnează : - 
   
```c++

// This function adds a list of values to a matrix
void add(std::vector<double> value)
{
   for(int i = 0; i < value.size(); i++)
       this->v_add(value[i]);
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
Matrix flatten()  // this function will convert a 2D array to 1D
{
   Matrix new_array(1, this->rows * this->columns, "value", 0);  // init a 1D matrix

   int index = 0;

   for(int i = 0; i < this->rows; i++)  // iterate through the number of rows
   {
       for(int j = 0; j < this->columns; j++)  // iterate through the number of columns
       {
           index = i * this->columns + j;  // create a 1D index from the rows and columns of 2D array
           new_array.values[0][index] = this->values[i][j];   // add the values to the 1D array
       }
   }

   this->shape[0] = this->rows;
   this->shape[1] = this->columns;

   return new_array;  // return the new matrix
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
     <b>input_size</b> : numărul de elemente supuse randomizării (tip : int) <br>
   </p>

  > Returnează : - 
      
```c++
/* This function will suffle every element from a matrix */
void shuffle(std::vector<Matrix> &input, std::vector<Matrix> &output, int input_size)
{

   /* Seed initialization */
   std::random_device rd;
   std::mt19937 mt(rd());
   std::uniform_real_distribution<double> dist(0, input_size);


   for(int i = 0; i < input_size; i++)  // iterate through the number of inputs
   {
       int random = dist(mt);
       std::swap(input[i], input[random]);  // swap the elements from "i" with the elements from "random"
       std::swap(output[i], output[random]);  // swap the elements from "i" with the elements from "random"

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
   <b>dim1</b> : numărul de linii ale viitoarei matrice (tip : int) <br> 
   <b>dim2</b> : numărul de coloane ale viitoarei matrice (tip : int) <br>
</p> 

  > Returnează : returnează matricea 
   
```c++
// This function will change the dimensions of a matrix
Matrix reshape(int dim1, int dim2)
{
   if(dim1 * dim2 == this->columns * this->rows)  // check if dimensions are equal
   {

       Matrix new_array(0,0,"value",0), vn(dim1, dim2, "value", 0);  //init a 1D matrix
       new_array = this->flatten();  // reshape the matrix from 2D to 1D

       int index = 0;
       for(int i = 0;i < dim1; i++)  // iterate through the first dimension
       {
           for(int j = 0; j < dim2; j++)  // iterate through the second dimension
           {
               vn.values[i][j] = new_array.values[0][index];  // add the values
               index++;
           }
       }

       this->shape[0] = this->rows;
       this->shape[1] = this->columns;

       return vn;  // return the new matrix

   }
   else  // if the dimensions are't equal, you can't reshape the matrix
   {
       std::cout << " > The dimensions of the matrix cannot be modified because the values that have been introduced do not match the number of rows and columns of the created matrix. \n";
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
/* This function will transpose a matrix */
Matrix transpose()
{

   int rows, columns;
   rows = this->rows;
   columns = this->columns;

   Matrix new_array(0,0,"value",0), vn(columns, rows, "value", 0);
   new_array = this->flatten();

   int index = 0;
   for(int i = 0;i < columns; i++)
   {
       for(int j = 0; j < rows; j++)
       {
           vn.values[i][j] = new_array.values[0][index];
           index++;
       }
   }

   this->shape[0] = this->rows;
   this->shape[1] = this->columns;

   return vn;

}

};
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
/* Sigmoid function */
double sigmoid(double x)
{
   return 1 / (1 + exp(-x));
}

```

</p>
</details>  
 
 
<details>
<summary> 9. Funcția sigmoidală aplicată matricei </summary>
<p>
   
   
   > Parametri : <br>
   <p>
     <b>Matrix</b> : Matricea căreia i se va aplica funcția sigmoidală (tip : Matrix) <br>
   </p>

  > Returnează : returnează matricea

```c++
/* This function will apply the sigmoid function to every element of a matrix */
void sigmoid_Matrix(Matrix &Matrix)
{
   int columns = Matrix.columns;
   int rows = Matrix.rows;

   Matrix = Matrix.flatten();

   for(int i = 0; i < columns * rows; i++)
       Matrix.values[0][i] = sigmoid(Matrix.values[0][i]);

   Matrix = Matrix.reshape(rows, columns);
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
/* Derived sigmoid function*/
double d_sigmoid(double x)
{
   return x * (1 - x);
}

```

</p>
</details>  


<details>
<summary> 11. Funcția sigmoidală (derivata) aplicată matricei </summary>
<p>
   
   > Parametri : <br>
   <p>
     <b>Matrix</b> : Matricea căreia i se va aplica derivata funcției sigmoidale (tip : Matrix) <br>
   </p>
   </br>

  > Returnează : returnează matricea

```c++
/* This function will apply the derived sigmoid function to every element of a matrix */
void d_sigmoid_Matrix(Matrix &Matrix)
{
   int columns = Matrix.columns;  // retine numarul de columns
   int rows = Matrix.rows;  // retine numarul de rows

   Matrix = Matrix.flatten();  // vectorizeaza Matrixa

   for(int i = 0; i < columns * rows; i++)  // parcurge toate elementele Matrixi
       Matrix.values[0][i] = d_sigmoid(Matrix.values[0][i]);  // aplica derivata sigmoidalei pentru fiecare value din Matrix

   Matrix = Matrix.reshape(rows, columns);  // schimba shape Matrixi la cea initiala
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
<b>matrix : </b> matrice ce urmează să fie afișată (tip : Matrix) <br>
</p>

> Returnează : "afișarea"

```c++

// We can use cout << MATRIX ;
std::ostream& operator<<(std::ostream &out, Matrix matrix)
{

    for(int i = 0;i < matrix.rows;i++) // parcurge numarul de rows
    {
        for(int j = 0;j< matrix.columns;j++) // parcurge numarul de columns
        {
            out << matrix.values[i][j] << " "; // afiseaza fiecare element
        }
        out << "\n";
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
<b>matrix1 : </b> prima matrice (tip : Matrix) <br>
<b>matrix2 : </b> a doua matrice (tip : Matrix) <br>
</p>

> Returnează : suma dintre cele două matrice

```c++

// Adding operator : (Matrix1 + Matrix2)
Matrix operator+(Matrix Matrix1, Matrix Matrix2)
{
    Matrix result(Matrix1.rows, Matrix1.columns, "value", 0);

    if(!(Matrix1.columns == Matrix2.columns && Matrix1.rows == Matrix2.rows))
    {
        std::cout << " > The sum between the two matrix cannot be made because their dimensions do not match. \n";
        throw int(2);
    }
    else
    {
        for(int i = 0; i < Matrix1.rows; i++)
            for(int j = 0;j < Matrix1.columns; j++)
                result.values[i][j] = Matrix1.values[i][j] + Matrix2.values[i][j];  // calculate the sum and store it into a new matrix

        return result;
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
<b>matrix1 : </b> prima matrice (tip : Matrix) <br>
<b>matrix2 : </b> a doua matrice (tip : Matrix) <br>
</p>

> Returnează : diferența dintre cele două matrice

```c++

// Subtracting operator (Matrix1 - Matrix2)
Matrix operator-(Matrix Matrix1, Matrix Matrix2)
{
    Matrix result(Matrix1.rows, Matrix1.columns, "value", 0);
    if(!(Matrix1.columns == Matrix2.columns && Matrix1.rows == Matrix2.rows))
    {
        std::cout << " > The difference between the two matrix cannot be made because their dimensions do not match. \n";
        throw int(3);
    }

    else
    {
        for(int i = 0; i < Matrix1.rows; i++)
            for(int j = 0;j < Matrix1.columns; j++)
                result.values[i][j] = Matrix1.values[i][j] - Matrix2.values[i][j];  // calculate the difference and store it into a new matrix
        return result;
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
<b>value_scalar : </b> valoarea cu care vom înmulți fiecare element din matrice (tip : double) <br>
<b>matrix : </b> matrice căruia i se va aplica scalarul (tip : Matrix) <br>
</p>

> Returnează : matricea înmulțită cu valoarea scalarului

```c++

// Scalar operator (value * Matrix)
Matrix operator*(double value_scalar, Matrix matrix)
{
    Matrix result(matrix.rows, matrix.columns, "value", 0);
    for(int i = 0; i < matrix.rows; i++)
        for(int j = 0;j < matrix.columns; j++)
            result.values[i][j] = value_scalar * matrix.values[i][j];  // calculate the scalar product and store it into a new matrix
    return result;

}
```

</p>
</details>  

<details>
<summary> 5. Funcția de înmulțire între două matrice </summary>
<p>

> Parametri : <br>
<p>
<b>Matrix1 : </b> prima matrice (tip : Matrix) <br>
<b>Matrix2 : </b> a doua matrice (tip : Matrix) <br>
</p>

> Returnează : produsul dintre cele două matrice

```c++
// Dot product (Matrix1 * Matrix2)
Matrix operator*(Matrix Matrix1, Matrix Matrix2)
{
    Matrix result(Matrix1.rows, Matrix2.columns, "value", 0);

    bool ok = false;

    if(Matrix1.columns == Matrix2.rows)
        ok = true;


    if (ok)
    {

        for(int i = 0; i < Matrix1.rows; i++)
        {
            int k = 0;
            for(int z = 0; z < Matrix1.columns; z++)
            {
                for(int j = 0;j < Matrix2.columns; j++)
                {
                    result.values[i][j] += Matrix1.values[i][z] * Matrix2.values[z][j];  // calculate the dot product
                    k ++ ;
                }
            }

        }


        return result;
    }
    else
    {
        std::cout << " > The product between the two matrix cannot be made because their dimensions do not match " << Matrix1.columns << " != " << Matrix2.rows << ". \n";
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
<b>Matrix1 : </b> prima matrice (tip : Matrix) <br>
<b>Matrix2 : </b> a doua matrice (tip : Matrix) <br>
</p>

> Returnează : produsul dintre cele două matrice (înmulțirea are loc element cu element)

```c++

// Cross product (Matrix1 % Matrix2)
Matrix operator%(Matrix Matrix1, Matrix Matrix2)
{
    Matrix result(Matrix1.rows, Matrix2.columns, "value", 0);
    bool ok = false;

    if(Matrix1.columns == Matrix2.columns && Matrix1.rows == Matrix2.rows)
        ok = true;


    if (ok)
    {
        for(int i = 0; i < Matrix1.rows; i++)
        {
            for(int j = 0;j < Matrix2.columns; j++)
            {
                result.values[i][j] = Matrix1.values[i][j] * Matrix2.values[i][j];  // calculate cross product
            }
        }
        return result;
    }
    else
    {
        std::cout << " > The product between the two matrix cannot be made because their dimensions do not match. \n";
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

// Display the shape of a matrix
std::ostream& operator<<(std::ostream &out, int shape_array[])
{
    out << "(" << shape_array[0] << ", " << shape_array[1] << ")";
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

