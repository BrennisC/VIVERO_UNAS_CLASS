#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
const string FILEPLANTS = "Plants.txt";

class BasicPlantDataHandler
{
private:
    vector<string> names;
    vector<int> quantities;
    vector<float> prices;

public:
    BasicPlantDataHandler() = default;
    BasicPlantDataHandler(vector<string> n, vector<int> qa, vector<float> pr) : names(n), quantities(qa), prices(pr) {}

    vector<string> &getNames() { return names; }
    vector<int> &getQuantities() { return quantities; }
    vector<float> &getPrices() { return prices; }

    friend void ModifyPlant(BasicPlantDataHandler &p);
};

class PlantOperations
{
public:
    virtual void registerPlant(BasicPlantDataHandler &plantbasic) = 0;
    virtual void showPlants(BasicPlantDataHandler &plantbasic) = 0;
    virtual void savePlants(BasicPlantDataHandler &plantbasic) = 0;
    virtual void loadPlants() = 0;
    virtual void modifyPlant() = 0;
    virtual ~PlantOperations() {}
};

class BasicPlantOperations : public PlantOperations, public BasicPlantDataHandler
{
public:
    void registerPlant(BasicPlantDataHandler &plantDataHandler) override
    {
        int x;
        cout << "Ingresa el numero de plantas: ";
        cin >> x;

        for (int i = 0; i < x; i++)
        {
            string name_plant;
            int quantity;
            float price;
            cout << "Ingrese el nombre de la planta: ";
            getline(cin, name_plant);

            cout << "Ingrese la cantidad de " << name_plant << " : ";
            cin >> quantity;

            cout << "Ingrese el precio de " << name_plant << " : ";
            cin >> price;

            plantDataHandler.getNames().push_back(name_plant);
            plantDataHandler.getQuantities().push_back(quantity);
            plantDataHandler.getPrices().push_back(price);
        }
    }

    void showPlants(BasicPlantDataHandler &plantDataHandler) override
    {
        cout << "Datos de las plantas registradas: " << endl;
        size_t size = plantDataHandler.getNames().size();
        for (size_t i = 0; i < size; ++i)
        {
            cout << "Nombre: " << plantDataHandler.getNames()[i] << endl;
            cout << "Cantidad: " << plantDataHandler.getQuantities()[i] << endl;
            cout << "Precio: " << plantDataHandler.getQuantities()[i] * plantDataHandler.getPrices()[i] << endl;
        }

        system("pause>null");
        system("cls");
    }

    void savePlants(BasicPlantDataHandler &plantDataHandler) override
    {
        ofstream file(FILEPLANTS, ios::out | ios::app);

        if (file.is_open())
        {
            file << "Datos de las plantas registradas: " << endl;
            for (size_t i = 0; i < plantDataHandler.getNames().size(); ++i)
            {
                file << "Nombre: " << plantDataHandler.getNames()[i] << endl;
                file << "Cantidad: " << plantDataHandler.getQuantities()[i] << endl;
                file << "Precio: " << plantDataHandler.getQuantities()[i] * plantDataHandler.getPrices()[i] << endl;
                file << "-----------------------------" << endl;
            }
            cout << "Datos de las plantas guardados en plantas " << endl;
        }
        else
        {
            cout << "Error al abrir el archivo plantas ." << endl;
        }
        system("cls");
    }

    void loadPlants() override
    {
        ifstream file(FILEPLANTS);
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
            cout << "No se pudo abrir el archivo plantas ." << endl;
        }
    }
};

void ModifyPlant(BasicPlantDataHandler &p)
{
    cout << "Ingrese el índice de la planta que desea modificar: ";
    size_t index;
    cin >> index;

    if (index < p.names.size())
    {
        cout << "Ingrese el nuevo nombre de la planta: ";
        getline(cin, p.names[index]);

        cout << "Ingrese la nueva cantidad de la planta: ";
        cin >> p.quantities[index];

        cout << "Ingrese el nuevo precio de la planta: ";
        cin >> p.prices[index];
    }
    else
    {
        cout << "Índice inválido. No se pudo modificar la planta." << endl;
    }
    system("cls");
}
void LinkedSearchPlants()
{
    char choice;
    BasicPlantOperations *basicPlantOperations;
    BasicPlantDataHandler plantDataHandler;

    do
    {
        cout << "[1] REGISTRAR PLANTAS\n";
        cout << "[2] MOSTRAR PLANTAS\n";
        cout << "[3] VER EN TXT PLANTAS\n";
        cout << "[4] MODIFICAR PLANTA\n";
        cout << "[5] VOLVER AL SISTEMA\n";
        cout << "INGRESE UNA OPCION: ";

        cin >> choice;

        switch (choice)
        {
        case '1':
            system("cls");
            basicPlantOperations->registerPlant(plantDataHandler);
            break;

        case '2':
            system("cls");
            basicPlantOperations->showPlants(plantDataHandler);
            basicPlantOperations->savePlants(plantDataHandler);
            break;

        case '3':
            system("cls");
            basicPlantOperations->loadPlants();
            break;

        case '4':
            system("cls");
            ModifyPlant(plantDataHandler);
            break;

        case '5':
            system("cls");
            cout << "Volviendo al menu principal..." << endl;
            break;

        default:
            system("cls");
            cout << "Opcion no valida." << endl;
            break;
        }
    } while (choice != '5');
}
