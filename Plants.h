#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
const string FILEPLANTS = "Plants.txt";

class BasicPlantDataHandler;
void ModifyPlant(BasicPlantDataHandler &p);

class PlantDataHandler
{
public:
    virtual void addPlant(const string &name, int quantity, float price) = 0;
    virtual const vector<string> &getNames() const = 0;
    virtual const vector<int> &getQuantities() const = 0;
    virtual const vector<float> &getPrices() const = 0;
    virtual ~PlantDataHandler() {}
};

class BasicPlantDataHandler : public PlantDataHandler
{
private:
    vector<string> names;
    vector<int> quantities;
    vector<float> prices;

public:
    void addPlant(const string &name, int quantity, float price) override
    {
        names.push_back(name);
        quantities.push_back(quantity);
        prices.push_back(price);
    }

    const vector<string> &getNames() const override
    {
        return names;
    }

    const vector<int> &getQuantities() const override
    {
        return quantities;
    }

    const vector<float> &getPrices() const override
    {
        return prices;
    }

    friend void ModifyPlant(BasicPlantDataHandler &p);
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

class PlantOperations
{
public:
    virtual void registerPlant(PlantDataHandler &plantDataHandler) = 0;
    virtual void showPlants(const PlantDataHandler &plantDataHandler) const = 0;
    virtual void savePlants(const PlantDataHandler &plantDataHandler) const = 0;
    virtual void loadPlants() = 0;
    virtual void modifyPlant(BasicPlantDataHandler &plantDataHandler) = 0;
    virtual ~PlantOperations() {}
};

class BasicPlantOperations : public PlantOperations
{
public:
    void registerPlant(PlantDataHandler &plantDataHandler) override
    {
        string name;
        int quantity;
        float price;

        cout << "Ingrese el nombre de la planta: ";
        getline(cin, name);
        cout << "Ingrese la cantidad de plantas de " << name << " que deseas: ";
        cin >> quantity;
        cout << "Ingrese el precio de la planta: ";
        cin >> price;

        plantDataHandler.addPlant(name, quantity, price);
    }

    void showPlants(const PlantDataHandler &plantDataHandler) const override
    {
        const vector<string> &names = plantDataHandler.getNames();
        const vector<int> &quantities = plantDataHandler.getQuantities();
        const vector<float> &prices = plantDataHandler.getPrices();

        cout << "Datos de las plantas registradas: " << endl;
        for (size_t i = 0; i < names.size(); ++i)
        {
            cout << "Nombre: " << names[i] << endl;
            cout << "Cantidad: " << quantities[i] << endl;
            cout << "Precio: " << prices[i] << endl;
        }
        system("cls");
    }

    void savePlants(const PlantDataHandler &plantDataHandler) const override
    {
        ofstream file(FILEPLANTS, ios::out);

        if (file.is_open())
        {
            const vector<string> &names = plantDataHandler.getNames();
            const vector<int> &quantities = plantDataHandler.getQuantities();
            const vector<float> &prices = plantDataHandler.getPrices();

            file << "Datos de las plantas registradas: " << endl;
            for (size_t i = 0; i < names.size(); ++i)
            {
                file << "Nombre: " << names[i] << endl;
                file << "Cantidad: " << quantities[i] << endl;
                file << "Precio: " << prices[i] << endl;
                file << "-----------------------------" << endl;
            }
            cout << "Datos de las plantas guardados en 'FILEPLANTS'" << endl;
        }
        else
        {
            cout << "Error al abrir el archivo 'FILEPLANTS'." << endl;
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
            cout << "No se pudo abrir el archivo 'FILEPLANTS'." << endl;
        }
    }

    void modifyPlant(BasicPlantDataHandler &plantDataHandler) override
    {
        ModifyPlant(plantDataHandler);
    }
};

void LinkedSearchPlants()
{
    char choice;
    BasicPlantDataHandler plantDataHandler;
    BasicPlantOperations plantOperations;

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
            plantOperations.registerPlant(plantDataHandler);
            break;
        case '2':
            system("cls");
            plantOperations.showPlants(plantDataHandler);
            plantOperations.savePlants(plantDataHandler);
            break;
        case '3':
            system("cls");
            plantOperations.loadPlants();
            break;
        case '4':
            system("cls");
            plantOperations.modifyPlant(plantDataHandler);
            break;
        case '5':
            system("cls");
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }
    } while (choice != '5');
}