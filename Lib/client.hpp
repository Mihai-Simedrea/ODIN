#include <iostream>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#include <string>

using std::to_string;

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
