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

    vector<string> getname_client() { return name_client; }
    vector<string> getID() { return ID; }

    // Funcion  para registrar cliente
    void RegistryClient();

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

        // variable para el DNI del cliente
        string name_DNI;
        cout << "Ingrese el DNI del cliente: ";
        getline(cin, name_DNI);
        ID.push_back(name_DNI);
    }
}

class shownClient
{
public:
    static void showData(Client &cl)
    {
        size_t size = cl.getname_client().size();
        cout << "Datos registrados de los clientes: ";

        for (size_t i = 0; i < size; i++)
        {
            cout << "CLIENTE: " << cl.getname_client()[i] << " DNI : " << cl.getID()[i] << endl;
            cout << "-----------------------------" << endl;
        }
        system("pause");
    }
};

class saveClient
{
public:
    static void saveData(Client &cl)
    {
        size_t size = cl.getname_client().size();
        ofstream file("Client.txt", ios::out);

        if (file.is_open())
        {
            file << "---------DATOS REGISTRATOS----------" << endl;
            for (size_t i = 0; i < size; i++)
            {
                file << "NOMBRE " << cl.getname_client()[i] << " ID: " << cl.getID()[i] << endl;
                file << "--------------------------" << endl;
            }
            file.close();
        }
        else
        {
            cout << "No se pudo abrir el archivo. " << endl;
        }
        cout << "Se a guardo correctamento los datos. ";
        system("pause");
        system("cls");
    }
};

class loadClient
{
public:
    static void loadData(Client &cl)
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
};

void BusquedaEnlazadaClient()
{
    char choice;
    Client cl;
    shownClient sc;
    saveClient svc;
    loadClient ldc;

    do
    {
        cout << "[1]REGRISTRO DE CLIENTE\n";
        cout << "[2]MOSTRAR CLIENTE\n";
        cout << "[3]VER EL TXT\n";
        cout << "[4]VOLVER AL MENU PRINCIPAL\n";
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
            sc.showData(cl);
            svc.saveData(cl);
            system("cls");
            break;

        case '3':
            system("cls");
            ldc.loadData(cl);
            break;

        case '4':
            system("cls");
            cout << "Saliendo del menu...";
            break;

        default:
            cout << "Opcion no valida. ";
            break;
        }
    } while (choice != '4');
}