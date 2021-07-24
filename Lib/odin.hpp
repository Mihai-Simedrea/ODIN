#include <iostream>
#include "matrice.hpp"
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <algorithm>
#include <thread>
#include "neural_gui.hpp"




bool thread2_start = true;

DWORD WINAPI thread2(LPVOID pm)
{
    std::string s;
    std::cin >> s;
    while (s != "stop")  // if "stop" then close the second thread
    {
        if(s == "cls")
            system("cls");
        std::cin >> s;
    }

    thread2_start = false;
    return 0;

}

class NeuralNetwork
{

private:

    struct point
    {
        int x, y;
    };
    int index = 0;
    std::vector<Matrix> weights;
    std::vector<Matrix> biases;
    std::string architecture_string;
    std::vector<Matrix> input;
    std::vector<Matrix> output;
    double learning_rate = 0.8;
    std::random_device rd;
    NeuralGUI gui;

public:

    NeuralNetwork(std::vector<Matrix> input_nn, std::vector<Matrix> output_nn, std::string architecture = "[]", double learning_rate_value = 0.8)
    {
        input = input_nn;
        output = output_nn;
        architecture_string = architecture;
        learning_rate = learning_rate_value;

    }


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

    Matrix predict(Matrix input)
    {
        std::string new_architecture = architecture_string;
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

        hidden_layers[0] = weights[0] * input;
        hidden_layers[0] = hidden_layers[0] + biases[0];
        hidden_layers[0].sigmoid_Matrix(hidden_layers[0]);


        for(int j = 1; j <= index - 2; j++)
        {
            hidden_layers[j] = weights[j] * hidden_layers[j - 1];
            hidden_layers[j] = hidden_layers[j] + biases[j];
            hidden_layers[j].sigmoid_Matrix(hidden_layers[j]);
        }


        return hidden_layers[hidden_layers.size()-1];


    }

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
};

