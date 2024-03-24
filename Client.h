#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
const string FILECLIENT = "Client.txt";

class ClientDataHandler
{
public:
    virtual void addData(const string &name, const string &id) = 0;
    virtual const vector<string> &getNameClient() const = 0;
    virtual const vector<string> &getID() const = 0;
    virtual ~ClientDataHandler() {}
};

class BasicClientDataHandler : public ClientDataHandler
{
private:
    vector<string> name_client;
    vector<string> ID;

public:
    void addData(const string &name, const string &id) override
    {
        name_client.push_back(name);
        ID.push_back(id);
    }

    const vector<string> &getNameClient() const override
    {
        return name_client;
    }

    const vector<string> &getID() const override
    {
        return ID;
    }

    friend void ModifyClient(BasicClientDataHandler &c);
};

void ModifyClient(BasicClientDataHandler &c)
{
    string nameModificable, idModificable;

    cout << "Ingrese el nombre del Cliente para modificar: ";
    getline(cin, nameModificable);

    cout << "Ingrese el DNI del cliente : ";
    getline(cin, idModificable);

    for (size_t i = 0; i < c.name_client.size(); i++)
    {
        if ((idModificable == c.ID[i]) && (nameModificable == c.name_client[i]))
        {
            cout << "Ingrese el nuevo nombre del Cliente: ";
            getline(cin, c.name_client[i]);
            cout << "Ingrese el nuevo DNI del Cliente: ";
            getline(cin, c.ID[i]);
            cout << "Cliente modificado correctamente." << endl;
            return;
        }
    }
    cout << "No se encontro el nombre y/o DNI ingresado." << endl;

    system("cls");
}

class ClientOperations
{
public:
    virtual void registry(ClientDataHandler &clientDataHandler) = 0;
    virtual void show(const ClientDataHandler &clientDataHandler) const = 0;
    virtual void save(const ClientDataHandler &clientDataHandler) const = 0;
    virtual void load() = 0;
    virtual void modify(BasicClientDataHandler &clientDataHandler) = 0;
    virtual ~ClientOperations() {}
};

class BasicClientOperations : public ClientOperations
{
public:
    void registry(ClientDataHandler &clientDataHandler) override
    {
        string name, id;

        cout << "Ingrese el nombre del cliente: ";
        getline(cin, name);
        cout << "Ingrese el ID del cliente: ";
        getline(cin, id);

        clientDataHandler.addData(name, id);
        system("cls");
    }

    void show(const ClientDataHandler &clientDataHandler) const override
    {
        const vector<string> &names = clientDataHandler.getNameClient();
        const vector<string> &ids = clientDataHandler.getID();
        cout << setw(25) << left << "Nombre" << setw(10) << right << "DNI" << endl;
        cout << "Datos registrados de los clientes: " << endl;

        for (size_t i = 0; i < names.size(); ++i)
        {
            cout << setw(25) << left << names[i] << setw(10) << right << ids[i] << endl;
            cout << "-----------------------------" << endl;
        }
        system("pause/null");
        system("cls");
    }

    void save(const ClientDataHandler &clientDataHandler) const override
    {
        const vector<string> &names = clientDataHandler.getNameClient();
        const vector<string> &ids = clientDataHandler.getID();

        ofstream file(FILECLIENT, ios::out | ios ::app);
        if (file.is_open())
        {
            file << "---------DATOS REGISTRATOS----------" << endl;
            file << setw(25) << left << "Nombre : " << setw(10) << right << "DNI" << endl;
            for (size_t i = 0; i < names.size(); ++i)
            {
                file << setw(25) << left << names[i] << setw(10) << right << ids[i] << endl;
                file << "--------------------------" << endl;
            }
            file.close();
            cout << "Se ha guardado correctamente los datos. ";
        }
        else
        {
            cout << "No se pudo abrir el archivo. " << endl;
        }
        system("cls");
    }

    void load() override
    {
        ifstream file(FILECLIENT);
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

        system("puase > null");
        system("cls");
    }

    void modify(BasicClientDataHandler &clientDataHandler) override
    {
        ModifyClient(clientDataHandler);
    }
};

void LinkedSearchClient()
{
    char choice;

    BasicClientDataHandler clientDataHandler;
    BasicClientOperations basicClientOperations;

    do
    {
        cout << "[1]REGISTRAR DE CLIENTE\n";
        cout << "[2]MOSTRAR CLIENTE\n";
        cout << "[3]VER EL TXT\n";
        cout << "[4]MODIFICAR CLIENTE\n";
        cout << "[5]VOLVER AL MENU PRINCIPAL\n";
        cout << "INGRESE SU OPCION: \n\n";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case '1':
            system("cls");
            basicClientOperations.registry(clientDataHandler);
            break;

        case '2':
            system("cls");
            basicClientOperations.show(clientDataHandler);
            basicClientOperations.save(clientDataHandler);
            break;

        case '3':
            system("cls");
            basicClientOperations.load();
            break;

        case '4':
            system("cls");
            basicClientOperations.modify(clientDataHandler);
            break;

        case '5':
            system("cls");
            cout << "Saliendo del menu...";
            break;

        default:
            cout << "Opcion no valida. ";
            break;
        }
    } while (choice != '5');
}
