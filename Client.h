#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class Client
{
private:
    vector<string> name_client;
    vector<string> ID;

public:
    Client() : name_client(), ID() {}
    // Funcion  para registrar cliente
    void RegistryClient();
    // Funcion para ver a los clientes registrados
    void ShowClient();
    // Funcion para guardar en un archivo TXT
    void SaveClient();
    // Funcion para cargar el TXT
    void LoadClient();
    // Funcion para agrupar los metodos de cliente
    friend void BusquedaEnlazadaClient();
};
void Client ::RegistryClient()
{
    int cantidad;
    cout << "Ingrese la cantidad de personas: ";
    cin >> cantidad;
    cin.ignore();
    for (int i = 0; i < cantidad; i++)
    {
        // variable para el nombre del cliente al ingresar
        string name;
        cout << "Ingrese el nombre del cliente: ";
        getline(cin, name);
        name_client.push_back(name);
        // variabble para el DNI del cliente
        string name_DNI;
        cout << "Ingrese el DNI del cliente: ";
        getline(cin, name_DNI);
        ID.push_back(name_DNI);
    }
}
// Funcion para ver los clientes
void Client ::ShowClient()
{
    cout << "Datos registrados de los clientes: ";
    for (size_t i = 0; i < name_client.size(); i++)
    {
        cout << "CLIENTE: " << name_client[i] << " DNI : " << ID[i] << endl;
        cout << "-----------------------------" << endl;
    }
    system("pause");
}
void Client::SaveClient()
{
    ofstream file("Client.txt", ios::out);
    if (file.is_open())
    {
        for (size_t i = 0; i < name_client.size(); i++)
        {
            file << "------REGISTRO-------";
            file << "Nombre:" << name_client[i] << endl;
            file << "DNI: " << ID[i] << endl;
            file << "--------------------------\n";
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    cout << "Se a guardo correctamento los datos. ";
    system("pause");
    system("cls");
}
void Client ::LoadClient()
{
    ifstream file("Client.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo de cliente.\n";
    }
    system("pause");
    system("cls");
}
void BusquedaEnlazadaClient()
{
    char choice;
    Client cl;
    do
    {
        cout << "[1]REGRISTRO DE CLIENTE\n";
        cout << "[2]MOSTRAR CLIENTE\n";
        cout << "[3]GUARDAR EN EL TXT\n";
        cout << "[4]VER EL TXT\n";
        cout << "[5]VOLVER AL MENU PRINCIPAL\n";
        cout << "INGRESE SU OPCION: \n\n";
        cin.getline(&choice, 4);
        switch (choice)
        {
        case '1':
            system("cls");
            cl.RegistryClient();
            break;
        case '2':
            system("cls");
            cl.ShowClient();
            break;
        case '3':
            system("cls");
            cl.SaveClient();
            break;
        case '4':
            system("cls");
            cl.LoadClient();
            break;
        case '5':
            cout << "Saliendo del menu...";
            break;
        default:
            cout << "Opcion no valida. ";
            break;
        }
    } while (choice != '5');
}