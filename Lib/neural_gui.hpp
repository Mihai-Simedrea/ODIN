#include <iostream>
#include <string.h>
#include <windows.h>
#include "client.hpp"
#include <cstdlib>
#include <tlhelp32.h>
#include <tchar.h>

static bool run_gui = false;
static bool run_after_train = false;
static bool run_server = false;

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // CTRL-CLOSE: confirm that the user wants to exit.
        case CTRL_CLOSE_EVENT:
            system("taskkill /F /T /IM DATAPRINT.exe");
            system("taskkill /F /T /IM GUI.exe");
            Beep(600, 200);
            return TRUE;
    }
}
bool IsProcessRunning(const TCHAR* const executableName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return false;
    }

    do {
        if (!_tcsicmp(entry.szExeFile, executableName)) {
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}


class NeuralGUI
{
public:


    void show_while_training()
    {
        run_gui = true;
    }

    void open_gui(std::string architecture_string)
    {
        std::string new_architecture = architecture_string;
        new_architecture.erase( remove( new_architecture.begin(), new_architecture.end(), ' ' ), new_architecture.end()); // remove white spaces from string

        system("start GUI.exe"); // open GUI

        system("cls");
        int i = 10;
        while(i > 0)
        {
            if(i > 1 && i < 20)
                std::cout << "The process will begin in " << i << " seconds.";
            else if(i == 1)
                std::cout << "The process will begin in a second.";

            i--;
            sleep(1);
            system("cls");
        }
        std::cout << '\n';
    }

    void close_gui(std::vector<Matrix> weights, std::string new_architecture, std::vector<Matrix> hidden_layers)
    {
        SOCKET out = connect_to_server(0, weights, new_architecture, 0, hidden_layers);
        close(out);
        system("taskkill /F /T /IM GUI.exe");
    }

    void send_gui(int z, std::vector<Matrix> weights, std::string new_architecture, int index, std::vector<Matrix> hidden_layers)
    {
        connect_to_server(z, weights, new_architecture, index, hidden_layers);
    }

    void exit()
    {
        if (SetConsoleCtrlHandler(CtrlHandler, TRUE))
        {
            while (1) {}
        }


    }

    void show_after_training()
    {
        run_after_train = true;
    }


    Matrix draw()
    {

        Matrix m(0, 0, "value", 0);

        system("start DRAW.exe"); // open GUI
        sleep(5);

        while(IsProcessRunning("DRAW.exe"))
        {
            // waiting
        }


        cv::Mat img = cv::imread("pred_image.png", cv::IMREAD_COLOR); // read the current image

        uint8_t* pixelPtr = (uint8_t*)img.data;  // get data from image
        int cn = img.channels();
        cv::Scalar_<uint8_t> bgrPixel;
        double grayscale = 0;


        // iterate over rows and columns to append values into the input vector
        for(int i = 0; i < img.rows; i++)
        {
            for(int j = 0; j < img.cols; j++)
            {
                bgrPixel.val[0] = pixelPtr[i*img.cols*cn + j*cn + 0]; // B
                bgrPixel.val[1] = pixelPtr[i*img.cols*cn + j*cn + 1]; // G
                bgrPixel.val[2] = pixelPtr[i*img.cols*cn + j*cn + 2]; // R

                grayscale = (bgrPixel.val[0] + bgrPixel.val[1] + bgrPixel.val[2]) / 3;
                m.add({grayscale / 255});
            }
        }

        m = m.transpose();  // transpose the column matrix to row matrix


        return m;
    }

    void show(Matrix matrix)
    {
        std::string values = "";

        values += "(" + std::to_string(matrix.shape[0]) + ", " + std::to_string(matrix.shape[1]) + ")";

        if(!run_server)
        {
            system("start DATAPRINT.exe"); // open GUI
            run_server = true;
            sleep(10);

        }

        matrix = matrix.flatten();

        for(int i = 0; i < matrix.rows * matrix.columns; i++)
            if(i == matrix.rows * matrix.columns - 1)
                values += std::to_string(matrix.values[0][i]);
            else
                values += std::to_string(matrix.values[0][i]) + ",";


        SOCKET out = send_string_show(values);
    }

};

