#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <random>
#include <filesystem>
#include <opencv.hpp>
namespace fs = std::filesystem;
static int target = 0;

namespace odin
{
    class Matrix
    {
    public:

        int rows = 0, columns = 0;
        std::vector<std::vector<double>> values;
        int shape[2];



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


        // This function adds a list of values to a matrix
        void add(std::vector<double> value)
        {
            for(int i = 0; i < value.size(); i++)
                this->v_add(value[i]);
        }


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

        /* Sigmoid function */
        double sigmoid(double x)
        {
            return 1 / (1 + exp(-x));
        }

        /* Derived sigmoid function*/
        double d_sigmoid(double x)
        {
            return x * (1 - x);
        }


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

    // Display the shape of a matrix
    std::ostream& operator<<(std::ostream &out, int shape_array[])
    {
        out << "(" << shape_array[0] << ", " << shape_array[1] << ")";
        return out;
    }

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

    // Scalar operator (value * Matrix)
    Matrix operator*(double value_scalar, Matrix matrix)
    {
        Matrix result(matrix.rows, matrix.columns, "value", 0);
        for(int i = 0; i < matrix.rows; i++)
            for(int j = 0;j < matrix.columns; j++)
                result.values[i][j] = value_scalar * matrix.values[i][j];  // calculate the scalar product and store it into a new matrix
        return result;

    }


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

};


