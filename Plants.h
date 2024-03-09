#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class Plants
{
private:
    vector<string> name_plants;
    vector<int> quantityplants;
    vector<float> price_plants;

public:
    Plants() : name_plants(), quantityplants(), price_plants() {}

    vector<string> getname_plants() { return name_plants; }
    vector<int> getquantityplants() { return quantityplants; }
    vector<float> getprice_plants() { return price_plants; }

    // Registro de plantas para el sistema de la vivero UNAS
    void RegistryPlants();

    // Funcion para agrupar todos los metodos
    friend void BusquedaEnlazadaPlants();
};

void Plants::RegistryPlants()
{
    int cantidad;
    cout << "Ingrese la cantidad de plantas: ";
    cin >> cantidad;
    cin.ignore();

    for (int i = 0; i < cantidad; i++)
    {
        string name;
        cout << "Ingrese el nombre de la planta: ";
        getline(cin, name);
        name_plants.push_back(name);

        float prc;
        cout << "Ingrese el precio de la planta: ";
        cin >> prc;
        price_plants.push_back(prc);

        int cantidad_plants;
        cout << "Ingrese la cantidad de plantas: ";
        cin >> cantidad_plants;
        while (cantidad_plants <= 0)
        {
            cout << "Error, debe ser mayor a cero.\n";
            cout << "Ingrese la cantidad de plantas: ";
            cin >> cantidad_plants;
        }
        quantityplants.push_back(cantidad_plants);
    }
    system("cls");
}

// Clase  para mostrar lo registrado en el registro de plants
class ShowPlantas
{
public:
    static void showfile(Plants &pl)
    {
        size_t size = pl.getname_plants().size();

        for (size_t i = 0; i < size; i++)
        {
            cout << "Nombre: " << pl.getname_plants()[i] << endl;
            cout << "Precio: $" << pl.getprice_plants()[i] * pl.getquantityplants()[i] << endl;
        }
    }
};

// Clase para guardar los archivos en txt
class SavePlantas
{
public:
    static void savefile(Plants &pl)
    {
        ofstream file("Plantas.txt", ios::out | ios::app);

        if (file.is_open())
        {
            file << "Datos de las plantas registradas: " << endl;
            size_t size = pl.getname_plants().size();

            for (size_t i = 0; i < size; i++)
            {
                file << "------------------------------------------------------\n";
                file << "Plantas: " << pl.getname_plants()[i] << " CANTIDAD: " << pl.getquantityplants()[i] << endl;
                file << "Precio: " << pl.getprice_plants()[i] * pl.getquantityplants()[i] << endl;
                file << "------------------------------------------------------\n";
            }
            file.close();
        }
        else
        {
            cout << "Error no se pudo guardar el archivo. ";
        }
    }
};

// Clase para guardar en el txt
class LoadPlants
{
public:
    static void loadfile(Plants &pl)
    {
        ifstream file("Plantas.txt");
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
            cout << "Nose encrontro el archivo. " << endl;
        }
        system("pause");
        system("cls");
    }
};

// Agrupar a las clase de los distintos datos de busqueda
void BusquedaEnlazadaPlants()
{
    char choice;
    Plants pl;
    ShowPlantas sp;
    SavePlantas sap;
    LoadPlants ld;

    do
    {
        cin.ignore();
        cout << "[1]REGRISTRO DE PLANTAS: \n";
        cout << "[2]MOSTRAR PLANTAS: \n";
        cout << "[3]ARCHIVOS GUARDADOS: \n";
        cout << "[4]VOLVER AL SISTEMA: \n";
        cout << "INGRESE UNA OPCION: \n\n";
        cin.getline(&choice, 4);

        switch (choice)
        {
        case '1':
            system("cls");
            pl.RegistryPlants();
            break;

        case '2':
            system("cls");
            sp.showfile(pl);
            sap.savefile(pl);
            system("pause");
            system("cls");
            break;

        case '3':
            system("cls");
            ld.loadfile(pl);
            break;

        case '4':
            cout << "Volviendo al menu principal... ";
            break;

        default:
            cout << "Opcion no valida.";
            system("pause");
            break;
        }
    } while (choice != '4');
}