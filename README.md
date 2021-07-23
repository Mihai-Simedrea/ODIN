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
 - neural_gui.hpp <br>
 
Apoi, în fișierul .cpp, includerea bibliotecii poate fi realizată folosind comanda #include "Lib/odin.hpp"

În același timp, această bibliotecă conține 3 programe externe specifice lucrului cu neuroni : 
 -  GUI.exe (permite vizualizarea structurilor neurornale)
 -  DATAPRINT.exe (permite vizualizarea unei matrice)
 -  DRAW.exe (oferă user-ului oportunitatea de a desena o imagine pe un grid, apoi posibilitatea de convertire a acesteia într-o matrice) <br>

**! În cazul în care întampinați o eroare legată de socket : (CodeBlocks) : Settings -> Compiler -> Linker Settings -> Add -> ws2_32**

# UN SCURT EXEMPLU AL UNUI PROGRAM ODIN
---
Problema XOR
```c++

#include <iostream>
#include "Lib/odin.hpp"

using namespace std;
using namespace odin;

int main()
{
    vector<Matrix> input; // inițializarea unui vector de input-uri pentru a stoca informațiile necesare training-ului.
    vector<Matrix> output; // inițializarea unui vector de output-uri pentru a stoca informațiile necesare training-ului.


   /// INPUTURI

   /* Aici are loc inițializarea matricelor cu valorile respective programului XOR.
   Adăugăm matricea respectivă în vectorul de input-uri folosind comanda ”push_back()” din biblioteca ”<vector>”. */

   input.push_back(Matrix(2, 1, "value", 1));
   input.push_back(Matrix(2, 1, "value", 0));
   input.push_back(Matrix(1, 1, "value", 0));
   input[2].add({1});  /* deoarece input[2] are o singură valoare, va trebui să adăugăm și un 1,
   pentru a avea matricea (0, 1)*/

   input[2] = input[2].reshape(2, 1); /* după această adăugare forma matricei se va schimba într-o matrice de tip coloană.
   Acest lucru poate fi remediat folosind comanda ”forma()”, care va schimba dimensiunea matricei. */

   input.push_back(Matrix(1, 1, "value", 1));
   input[3].add({0});
   input[3] = input[3].reshape(2, 1);

   /// OUTPUTURI

   /* Aici are loc inițializarea output-urilor, care nu sunt altceva decât 4 valori situate într-o matrice. */
   output.push_back(Matrix(1, 1, "value", 0));
   output.push_back(Matrix(1, 1, "value", 0));
   output.push_back(Matrix(1, 1, "value", 1));
   output.push_back(Matrix(1, 1, "value", 1));

   NeuralNetwork neuralNet(input, output, "[2, 2, 1]");
   neuralNet.train(20000); // antrenarea funcției pentru 20000 de iterații.
   neuralNet.show(); // această funcție afișează output-ul pentru toate valorile din input.
   neuralNet.save("neuralNet"); // această funcție salvează modelul în fișierul "model.odin".


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
 
<details>
<summary> 12. Funcția de afișare a matricei </summary>
<p>
   
   > Parametri : - <br>
  </br>

  > Returnează : afișează matricea

```c++
void print()
{
    for(int i = 0;i < this->rows;i++) // iterate over rows
    {
        for(int j = 0;j< this->columns;j++) // iterate over columns
        {
            std::cout << this->values[i][j] << " "; // show every element
        }
        std::cout << "\n";
    }
}
```

</p>
</details> 
 
<details>
<summary> 13. Funcția de eliminare elemente din matrice </summary>
<p>
   
   > Parametri : - <br>
   <p>
     <b>elements</b> : numărul de elemente ce vor fi eliminate (tip : int) <br>
  </p> 
  
 
  </br>

  > Returnează : -

```c++
void pop(int elements = 1)
{
    Matrix new_array(1, this->rows * this->columns - elements, "value", 0);  // create a new matrix
    int index = 0;

    for(int i = 0; i < this->rows; i++)  // iterate through the number of rows
    {
        for(int j = 0; j < this->columns; j++)  // iterate through the number of columns
        {
            index = i * this->columns + j;  // create a 1D index from the rows and columns of 2D array

            if(index < this->columns * this->rows - elements)
                new_array.values[0][index] = this->values[i][j];  // add the values to the 1D array
            else
                break;
        }
    }


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
<summary> 14. Funcția de resetare matrice </summary>
<p>
   
   > Parametri : - <br>
 
  </br>

  > Returnează : -

```c++
/* This function will replace every element of a matrix with 0 */
void reset()
{
    int rows, columns;
    rows = this->rows;
    columns = this->columns;



    for(int i = 0;i < rows; i++)
        for(int j = 0; j < columns; j++)
            this->values[i][j] = 0;


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
NeuralNetwork neuralNet(input, output, "[2, 2, 1]", 0.8);

/// Aceasta este functia de antrenare specifica retelei neuronale. Are 2 parametri : 
/// - numarul de iteratii : de cate ori se va antrena programul.
/// - GUI - acest parametru este de tip bool si reprezinta interfata grafica a structurii. 
neuralNet.train(2000, false);

/// Aceasta este functia de salvare. Are un singur parametru :
/// - numele fisierului : este un string ce reprezinta numele fisierului. Fisierul va fi salvat cu extensia odin.
neuralNet.save("model");

/// Aceasta este functia de verificare. Are 2 parametri:
/// - numarul de zecimale : acest numar indica cate cifre sunt dupa virgula in momentul verificarii retelei neuronale.
/// - GUI : acest parametru este de tip bool si reprezinta interfata grafica a structurii. 
neuralNet.show(6, false);

```

</p>
</details>  

<details>
<summary> 2. Funcția de antrenare a rețelei </summary>
<p>
   
  > Parametri : <br>
  <p>
   <b>iterations</b> : numărul de iterații atribuite rețelei (tip : int) <br> 
   <b>drop_out</b> : (tip : bool) <br>
</p> 

  > Returnează : -
   
```c++
/* Train the neural network */
void train(int iterations, bool drop_out = false)
{
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, 10);
    std::string new_architecture = architecture_string;

    // Open GUI
    if(run_gui)
        gui.open_gui(architecture_string);

    char s[1000];
    strcpy(s, architecture_string.c_str());  // convert from string to char array

    char *p = strtok(s, ", [ ]");  // point to the first character of structure

    int architecture_string_int[1000]; // this will store every neuron from structure
    while(p != NULL)
    {
        architecture_string_int[index] = atoi(p);  // convert the pointer to int
        p = strtok(NULL, ", [ ]");
        index++;
    }


    for(int i = 0; i <= index - 2; i++)
        weights.push_back(Matrix(architecture_string_int[i+1], architecture_string_int[i], "random", 2));  // init array with random values from [-2, 2]


    for(int i = 0; i <= index - 1; i++)
        biases.push_back(Matrix(architecture_string_int[i + 1], 1, "random", 2));  // init array with random values from [-2, 2]




    std::vector<Matrix> hidden_layers;  // create a hidden layers array

    for(int z = 0; z < iterations; z++)  // iterate over "iterations"
    {
        input[z].shuffle(input, output, input.size());  // shuffle the inputs because of overfitting

        std::vector<Matrix> he_errors; // init an array for hidden layers errors
        for(int i = 0 ; i < input.size(); i++)  // iterate over input size
        {
            std::vector<Matrix> hidden_layers;

            hidden_layers.push_back(weights[0] * input[i]);  // create the first hidden layer


            hidden_layers[0] = hidden_layers[0] + biases[0];  // add the bias to the first hidden layer

            hidden_layers[0].sigmoid_Matrix(hidden_layers[0]);  // apply sigmoid function

            if(drop_out)  // check if drop-out is true
                if((int)dist(mt) == 1 || (int)dist(mt) == 2 || (int)dist(mt) == 3)  // 30% chances to reset the values from hidden layer
                    hidden_layers[0].reset();

            for(int j = 1; j <= index - 2; j++)  // iterate over the next hidden layers
            {
                hidden_layers.push_back(weights[j] * hidden_layers[j - 1]);  // create the "j" hidden layer
                hidden_layers[j] = biases[j] + hidden_layers[j]; // add bias
                hidden_layers[j].sigmoid_Matrix(hidden_layers[j]);  // apply sigmoid function

                if(drop_out)  // check if drop-out is true
                    if((int)dist(mt) == 1 || (int)dist(mt) == 2 || (int)dist(mt) == 3)  // 30% chances to reset the values from hidden layer
                        hidden_layers[j].reset();
            }

            std::vector<Matrix> hidden_layers_errors;  // init hidden layer errors array
            for(int j = 0; j <= index - 2; j++)  // init the array with NULL values
                hidden_layers_errors.push_back(Matrix(1, 1, "value", 0));


            hidden_layers_errors[index - 2] = output[i] - hidden_layers[index - 2];  // calculate output error


            for(int j = index - 2 - 1; j >= 0; j -- )  // iterate over hidden layers
            {

                weights[j+1] = weights[j+1].transpose();  // transpose the matrix

                hidden_layers_errors[j] = weights[j + 1] * hidden_layers_errors[j + 1];  // share the errors with respect to weights

                weights[j+1] = weights[j+1].transpose(); // transpose the matrix



            }


            std::vector<Matrix> derived_hidden_layers;
            std::vector<Matrix> gradients;
            std::vector<Matrix> delta_weights;

            for(int j = 0; j <= index - 2; j++)
            {
                derived_hidden_layers.push_back(Matrix(1, 1, "value", 0));
                gradients.push_back(Matrix(1, 1, "value", 0));
                delta_weights.push_back(Matrix(1, 1, "value", 0));
            }


            for(int j = index - 2 ; j >= 0; j -- )
            {
                derived_hidden_layers[j] = hidden_layers[j];
                derived_hidden_layers[j].d_sigmoid_Matrix(derived_hidden_layers[j]);  // apply derived sigmoid function

                gradients[j] = hidden_layers_errors[j] % derived_hidden_layers[j];  // calculate the gradients
                gradients[j] = learning_rate * gradients[j];  // apply learning rate

                biases[j] = biases[j] + gradients[j]; // add the gradients to biases

            }


            for(int j = index - 2; j >= 1; j--)
            {
                hidden_layers[j - 1] = hidden_layers[j-1].transpose(); // transpose matrix
                delta_weights[j] = gradients[j] * hidden_layers[j - 1];  // calculate delta weights
                hidden_layers[j - 1] = hidden_layers[j - 1].transpose();  // transpose matrix
            }

            input[i] = input[i].transpose();  // transpose input

            delta_weights[0] = gradients[0] * input[i];  // calulate delta weights for input
            input[i] = input[i].transpose();  // transpose input


            // update weights using the delta weights
            for(int j = 0; j<=index-2;j++)
                weights[j] = delta_weights[j] + weights[j];


            // if GUI is true, send info to server to generate the GUI
            if(run_gui)
                gui.send_gui(z, weights, new_architecture, index, hidden_layers);


        }

        std::cout << "\n";
        std::cout << z << " / " << iterations;
        std::cout << "\n";
    }

    std::cout << "\n\n";

    // Close GUI
    if(run_gui)
        gui.close_gui(weights, new_architecture, hidden_layers);

}

```

</p>
</details>

<details>
<summary> 3. Funcția de verificare </summary>
<p>

> Parametri : <br>
  <p>
   <b>decimals</b> : numărul de zecimale ce vor fi afișate (tip : int) <br> 
</p> 

> Returnează : nu returnează nimic, ci doar afișează toate predicțiile în funcție de input-urile antrenate

```c++
/* This function will display the trained values */
void show(int decimals = 6)
{
   std::string new_architecture = architecture_string;

   // Open GUI
   if(run_after_train)
       gui.open_gui(architecture_string);

   std::vector<Matrix> hidden_layers;
   char s[1000];
   strcpy(s, architecture_string.c_str());

   char *p = strtok(s, ", [ ]");


   int index = 0;
   int architecture_string_int[1000];
   while(p != NULL)
   {
       architecture_string_int[index] = atoi(p);
       p = strtok(NULL, ", [ ]");
       index++;
   }


   for(int i = 0; i <= index - 2; i++)
   {
       hidden_layers.push_back(Matrix(1, 1, "value", 0));
   }

   if(run_after_train)
   {
       bool ok = true;
       HANDLE handle = CreateThread(NULL, 0, thread2, NULL, 0, NULL);  // you can write in console
       while(thread2_start)  // while the second thread is opened
       {

           for(int i = 0 ; i < input.size(); i++)
           {
               hidden_layers[0] = weights[0] * input[i];
               hidden_layers[0] = hidden_layers[0] + biases[0];
               hidden_layers[0].sigmoid_Matrix(hidden_layers[0]);


               for(int j = 1; j <= index - 2; j++)
               {
                   hidden_layers[j] = weights[j] * hidden_layers[j - 1];
                   hidden_layers[j] = hidden_layers[j] + biases[j];
                   hidden_layers[j].sigmoid_Matrix(hidden_layers[j]);

               }

               if(run_after_train)
                   gui.send_gui(i, weights, new_architecture, index, hidden_layers);

               if(ok)
               {
                   std::cout << std::fixed << std::setprecision(decimals) << (hidden_layers[index-2]) << "\n";

                   if(i == input.size() - 1)
                       std::cout << "\n > Write 'stop' for closing the GUI \n\n";
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
           hidden_layers[0].sigmoid_Matrix(hidden_layers[0]);


           for(int j = 1; j <= index - 2; j++)
           {
               hidden_layers[j] = weights[j] * hidden_layers[j - 1];
               hidden_layers[j] = hidden_layers[j] + biases[j];
               hidden_layers[j].sigmoid_Matrix(hidden_layers[j]);

           }

           if(run_after_train)
               gui.send_gui(i, weights, new_architecture, index, hidden_layers);

           std::cout << std::fixed << std::setprecision(decimals) << (hidden_layers[index-2]) << "\n";

       }
   }


   // Close GUI
   if(run_after_train)
       gui.close_gui(weights, new_architecture, hidden_layers);


}
```

</p>
</details>  

<details>
<summary> 4. Funcția de salvare </summary>
<p>

> Parametri : <br>
<p>
<b>file</b> : numele fișierului în care vor fi stocate informațiile (tip : char[]) <br>
</p>

> Returnează : -

```c++

/* This function will save the model in a file (*.odin) */
void save(char file[])
{

    // Create the file

    char file_string[1000];
    strcpy(file_string, file);
    char extension[] = {".odin"};
    strcat(file_string, extension);

    std::ofstream o(file_string);

    o << index << "\n";

    for(int i = 0; i <= index - 2; i++)
        o << weights[i].rows << " " << weights[i].columns << "\n"; // add the number of rows and columns of weights

    for(int i = 0; i <= index - 2; i++)
        o << biases[i].rows << " " << biases[i].columns << "\n"; // add the number of rows and columns of biases

    o << "\n";


    for(int z = 0; z <= index - 2; z++)
    {
        for(int i = 0;i < weights[z].rows;i++)
        {
            for(int j = 0;j< weights[z].columns;j++)
            {
                o << weights[z].values[i][j] << " ";  // add the weights values in file
            }
            o << "\n";
        }
        o << "\n";
    }

    o << "\n";

    for(int z = 0; z <= index - 2; z++)
    {
        for(int i = 0;i < biases[z].rows;i++)
        {
            for(int j = 0;j< biases[z].columns;j++)
            {
                o << biases[z].values[i][j] << " ";  // add the biases values in file
            }
            o << "\n";
        }
        o << "\n";
    }

    o << "\n";
    o << architecture_string;  // add the architecture of the ANN

    o.close();  // close the file
}



```

</p>
</details>  

<details>
<summary> 5. Funcția de încărcare </summary>
<p>

> Parametri : <br>
<p>
<b>file</b> : numele fișierului din care vor fi citite informațiile (tip : char[]) <br>
</p>

> Returnează : nu returnează nimic, doar schimbă variabilele globale care aparțin rețelei neuronale

```c++
void load(char file[])
{

    // get the name of file
    char file_string[1000];
    strcpy(file_string, file);
    char extension[] = {".odin"};
    strcat(file_string, extension);

    std::ifstream f(file_string);

    double x;

    int length = 0;

    std::vector <point> points;
    int k = 0;
    int sum = 0;
    while(f >> x)  // read every value from file
    {
        if(length == 0)
            index = x;
        else  if(length > 0 && length <= (index - 1)* 2 * 2)
        {
            point p;
            if(length % 2 != 0)
            {
                p.x = x;
            }
            else
            {
                p.y = x;
                points.push_back(p);
            }
        }

        length ++;
    }

    for(int i = 0; i < points.size(); i++)
        sum += points[i].x * points[i].y;


    // Reset the pointer to the beginning of the file
    f.clear();
    f.seekg(0, std::ios::beg);


    length = 0;
    int pos = 0;
    std::vector<Matrix> matrix;
    bool ok = true;
    char c;
    std::string str;

    while(ok)
    {
        if(length > points.size() * 2)
        {
            if(pos < points.size())
            {
                Matrix matrix(0, 0, "value", 0);

                matrix.rows = points[pos].x;
                matrix.columns = points[pos].y;

                for(int i = 0; i < points[pos].x; i++)
                {
                    std::vector<double> temp;
                    for(int j = 0; j < points[pos].y; j++)
                    {
                        f >> x;
                        temp.push_back(x);
                    }
                    matrix.values.push_back(temp);
                }

                if(pos < points.size() / 2)
                {
                    matrix = matrix.reshape(points[pos].x, points[pos].y);
                    weights.push_back(matrix);
                }
                else
                {
                    matrix = matrix.reshape(points[pos].x, points[pos].y);
                    biases.push_back(matrix);
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
            length ++ ;
        }
    }

    architecture_string = str;

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
<b>iterations</b> : iterația curentă (tip : int) <br>
<b>weights</b> : vectorul de sinapse (tip : vector<Matrice>) <br>
<b>architecture</b> : numărul de neuroni specific rețelei (tip : string) <br>
<b>hidden_layers</b> : vectorul de hidden_layers (tip : vector<Matrix>) <br>
</p>

> Returnează : -

</p>

```c++
/* This function will send data to the python server */

SOCKET connect_to_server(int iterations, std::vector<Matrix> weights, std::string architecture, int index, std::vector<Matrix> hidden_layers)
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

    std::string valuesMatrix = "";
    valuesMatrix += architecture;
    valuesMatrix += "{";

    for(int z = 0; z <= index - 2; z++)
    {
        for(int i = 0; i<hidden_layers[z].rows; i++)
        {
            for(int j = 0; j<hidden_layers[z].columns; j++)
            {
                valuesMatrix += std::to_string(hidden_layers[z].values[i][j]);

                if(i != hidden_layers[z].rows)
                    valuesMatrix += ",";
            }
        }
    }

    valuesMatrix += "} ";

    for(int z = 0; z <= index-2; z++)
    {
        for(int i = 0; i<weights[z].rows; i++)
        {
            for(int j = 0; j<weights[z].columns; j++)
            {
                valuesMatrix += std::to_string(weights[z].values[i][j]);
                valuesMatrix += " ";
            }
        }
    }


    if(valuesMatrix.size() < 65535)
    {
        if(index == 0)
        {
            int sendOk = sendto(out, "end", 1, 0, (sockaddr*)&server, sizeof(server));
            return out;
            close(out);
        }
        else
            int sendOk = sendto(out, valuesMatrix.c_str(), valuesMatrix.size() + 1, 0, (sockaddr*)&server, sizeof(server));
    }
    else
    {
        std::cout << '\n' << "The amount of information exceeds the limit allowed by a UDP connection ( " << valuesMatrix.size() << " > 65535 )" << '\n' << "The number of layers must be decreased to open the GUI. \n";
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
</p>
</details>  
 
# FUNCȚIILE SPECIFICE INPUT-URILOR (inputs_methods.hpp)
---
 
În acest fișier se găsește următoarea funcție : 

<details>
<summary> 1. Funcția de încărcare matrice din fișier </summary>
<p>


> Parametri : <br>
<p>
<b>input</b> : vectorul de input-uri (tip : vector<Matrix>) <br>
<b>path</b> : calea de unde se vor citi informațiile (tip : string) <br>
<b>images_count</b> : numărul de imagini ce vor fi citite (tip : int) <br>
</p>

> Returnează : -

</p>
 
 ```c++
 
void load_from_file(std::vector<Matrix> &input, std::string path, int images_count)
{

    std::cout << "Loading database from '" << path << "' \n";
    int z_current = 0;
    std::string number = "";
    for(int i = path.size() - 1; i>=0; i--)
        if(path[i] == '\\')
            break;
        else
            number += path[i];

    int number_int = atoi( number.c_str() );


    for (const auto & entry : fs::directory_iterator(path))
    {
        if(z_current < images_count)
        {
            std::string path_string{entry.path().u8string()}; // convert filestream path to string path
            cv::Mat img = cv::imread(path_string, cv::IMREAD_COLOR); // read the current image

            uint8_t* pixelPtr = (uint8_t*)img.data;  // get data from image
            int cn = img.channels();
            cv::Scalar_<uint8_t> bgrPixel;
            double grayscale = 0;


            input.push_back(Matrix());
            // iterate over rows and columns to append values into the input vector
            for(int i = 0; i < img.rows; i++)
            {
                for(int j = 0; j < img.cols; j++)
                {
                    bgrPixel.val[0] = pixelPtr[i*img.cols*cn + j*cn + 0]; // B
                    bgrPixel.val[1] = pixelPtr[i*img.cols*cn + j*cn + 1]; // G
                    bgrPixel.val[2] = pixelPtr[i*img.cols*cn + j*cn + 2]; // R

                    grayscale = (bgrPixel.val[0] + bgrPixel.val[1] + bgrPixel.val[2]) / 3;
                    input[z].add({grayscale / 255});
                }
            }

            OUTPUT_VECTOR_LFF.push_back(number_int);
            std::cout << z_current << " / " << images_count << "\n";
            input[z] = input[z].transpose();  // transpose the column matrix to row matrix
            z++;
            z_current++;
        }

    }
    std::cout << "\n\n";


}

 
 ```
 
 </p>
</details>  
 
# PROGRAME AUXILIARE PYTHON
---
 
 <details>
<summary> 1. Funcția de afișare input (DATAPRINT.exe) </summary>
<p>


> Parametri : - <br>
 
> Returnează : -

</p>
 
 ```python
  
import socket
import numpy as np
import matplotlib.pyplot as plt
import math


localIP = "127.0.0.1"

localPort = 54001

UDPServerSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)

UDPServerSocket.bind((localIP, localPort))
bufferSize = 65535


start = False
shape = ""
start2 = False
clMsg = ""


while True:

    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

    message = bytesAddressPair[0]

    address = bytesAddressPair[1]

    clientMsg = message.decode('utf-8')

    if len(clientMsg) != 0:
        for i in range(0, len(clientMsg)):

            if start:
                shape += clientMsg[i]

            if start2:
                clMsg += clientMsg[i]

            if clientMsg[i] == '(':
                start = True
            elif clientMsg[i] == ')':
                start = False
                start2 = True


        shape = shape[:-1]

        shape_array = shape.split(',')
        arr = np.asarray(shape_array)
        shape_arr = arr.astype(int)



        info = clMsg.split(',')

        array = np.asarray(info)
        y = array.astype(float)

        print(shape_arr[0], shape_arr[1])

        product = int(shape_arr[0]) * int(shape_array[1])

        y = y.reshape(int(math.sqrt(product)), int(math.sqrt(product)))



        plt.imshow(y, interpolation='nearest')
        plt.show()

        clMsg = ''
        product = 0
        shape = ''
        shape_array = ''
        shape_arr = 0
        start = False
        start2 = False



```
  
  </p>
 </details>
 
</p>
 </details>
 
 <details>
<summary> 2. Funcția de desenare input (DRAW.exe) </summary>
<p>


> Parametri : - <br>
 
> Returnează : -

</p>
  
```python
  
import tkinter as tk
from PIL import Image, ImageDraw, ImageOps
import math


image1 = Image.new("RGB", (600, 600), (255, 255, 255))
draw = ImageDraw.Draw(image1)

points = []
points_pixels = []
grid_bool = False


def distance(x0, y0, x1, y1):
    return math.sqrt((x1 - x0)**2 + (y1 - y0)**2)

def find_index(array, val):
    for i in range(0, len(array)):
        if val == array[i]:
            return i
    return -1

def mouse_click(event, canvas):
    global points, draw

    dist = []

    x = event.x / 600
    y = event.y / 600

    for i in range(0, len(points)):
        dist.append(distance(x, y, points[i][0], points[i][1]))

    v1 = min(dist)
    v1_index = find_index(dist, v1)
    dist[v1_index] = 2

    v2 = min(dist)
    v2_index = find_index(dist, v2)
    dist[v2_index] = 2

    v3 = min(dist)
    v3_index = find_index(dist, v3)
    dist[v3_index] = 2

    v4 = min(dist)
    v4_index = find_index(dist, v4)
    dist[v4_index] = 2


    x0 = points_pixels[v1_index][0]
    y0 = points_pixels[v1_index][1]

    x1 = points_pixels[v4_index][0]
    y1 = points_pixels[v4_index][1]


    if x0 != x1 and y0 != y1:
        canvas.create_rectangle(x0, y0, x1, y1, fill = 'black')
        draw.rectangle((x0, y0, x1, y1), fill = 'black')


def print_selection(lb, canvas):
    global points, image1, draw, grid_bool


    ### CANVAS ####

    image1 = Image.new("RGB", (600, 600), (255, 255, 255))
    draw = ImageDraw.Draw(image1)

    points.clear()
    points_pixels.clear()
    canvas.delete("all")
    line = canvas.create_line(600, 0, 600, 650)

    text = lb.get(tk.ANCHOR)
    slices = int(text)
    slice_width = 600 / slices

    ### GENERATE POINT ARRAY ###

    x = 0
    y = 0

    for i in range(0, slices + 1):
        for j in range(0, slices + 1):

            points_pixels.append((x, y))
            points.append((x / 600, y / 600))

            x += slice_width

        x = 0
        y += slice_width


    pos = slice_width

    if grid_bool:

        for i in range(0, slices):
            canvas.create_line(pos, 0, pos, 650)
            pos += slice_width

        pos = slice_width

        for i in range(0, slices):
            canvas.create_line(0, pos, 750, pos)
            pos += slice_width


def SaveCommand(lst, main):
    global draw, image1

    text = lst.get(tk.ANCHOR)
    slices = int(text)

    image1 = image1.resize((slices, slices))

    image1 = ImageOps.invert(image1)
    image1 = image1.convert('1')

    image1.save('pred_image.png', quality = 95)

    main.destroy()

def grid(button):
    global grid_bool
    grid_bool = not grid_bool

    if not grid_bool:
        button['text'] = 'Grid OFF'
    else:
        button['text'] = "Grid ON"


if __name__ == '__main__':
    main = tk.Tk()
    main.geometry("745x600")
    main.title("GUI - Drawing")
    main.resizable(False, False)

    sb = tk.Scrollbar(main)
    sb.pack(side=tk.RIGHT, fill=tk.Y)

    mylist = tk.Listbox(main, yscrollcommand=sb.set)

    for line in range(2, 51):
        mylist.insert(tk.END, str(line) )



    sb.config(command=mylist.yview)


    canvas = tk.Canvas(main, bg = "white", height = 600, width = 700)
    line = canvas.create_line(600, 0, 600, 650)
    canvas.bind("<B1-Motion>", lambda event: mouse_click(event, canvas))


    mylist.pack(side=tk.RIGHT)
    mylist.bind('<Double-1>', lambda lb: print_selection(mylist, canvas))

    saveButton = tk.Button(main, text = "Save", command = lambda: SaveCommand(mylist, main))
    saveButton.pack(side = tk.BOTTOM)

    gridButton = tk.Button(main, text = 'Grid OFF', command = lambda :grid(gridButton))
    gridButton.place(x = 640, y = 390)


    canvas.pack()
    main.mainloop()


```
  </p>
  </details>

