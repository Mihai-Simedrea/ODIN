#include <iostream>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#include <string>

using namespace odin;

SOCKET send_string(std::string msg)
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

    int sendOk = sendto(out, msg.c_str(), msg.size() + 1, 0, (sockaddr*)&server, sizeof(server));

    closesocket(out);
    WSACleanup();
    return 0;



}

SOCKET send_string_show(std::string msg)
{
    WSADATA data;
    WORD version = MAKEWORD(2, 2);

    int wsOk = WSAStartup(version, &data);

    if(wsOk != 0)
        return 0 ;

    sockaddr_in server;
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(54001);

    inet_ntoa(server.sin_addr);

    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    int sendOk = sendto(out, msg.c_str(), msg.size() + 1, 0, (sockaddr*)&server, sizeof(server));

    closesocket(out);
    WSACleanup();
    return 0;



}

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

SOCKET connect_to_server_show(int iterations, std::vector<Matrix> weights, std::string architecture, int index, std::vector<Matrix> hidden_layers)
{
    WSADATA data;
    WORD version = MAKEWORD(2, 2);

    int wsOk = WSAStartup(version, &data);

    if(wsOk != 0)
        return 0 ;

    sockaddr_in server;
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(54001);

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
