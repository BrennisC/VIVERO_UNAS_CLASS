#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Constantes para mensajes
const string FILENAME = "Abono.txt";

// Clase para representar un abono
class Abono
{
private:
    string nombre;
    float precio;

public:
    Abono(const string &n, float p) : nombre(n), precio(p) {}

    const string &getNombre() const { return nombre; }
    float getPrecio() const { return precio; }

    friend ostream &operator<<(ostream &os, const Abono &abono);
};

ostream &operator<<(ostream &os, const Abono &abono)
{
    os << "Nombre: " << abono.getNombre() << ", Precio: " << abono.getPrecio();
    return os;
}

// Repositorio de abonos
class AbonoRepository
{
private:
    vector<pair<string, float>> abonos;

public:
    void saveFertilizers() const
    {
        ofstream archivo(FILENAME);
        if (archivo.is_open())
        {
            for (const auto &abono : abonos)
            {
                archivo << abono.first << " " << abono.second << endl;
            }
            cout << "Abonos guardados en " << FILENAME << endl;
        }
        else
        {
            cerr << "Error al abrir el archivo " << FILENAME << endl;
        }
        system("cls");
    }

    void loadFertilizers()
    {
        ifstream archivo(FILENAME);
        if (archivo.is_open())
        {
            string nombre;
            float precio;
            while (archivo >> nombre >> precio)
            {
                abonos.push_back(make_pair(nombre, precio));
            }
            cout << "Abonos cargados desde " << FILENAME << endl;
        }
        else
        {
            cerr << "Error al abrir el archivo " << FILENAME << endl;
        }
    }

    const vector<pair<string, float>> &getAbonos() const { return abonos; }

    void agregarAbono(const string &nombre, float precio)
    {
        abonos.push_back(make_pair(nombre, precio));
    }
};

// Manejador de operaciones de abonos
class AbonoManager
{
private:
    AbonoRepository *abonoRepository;

public:
    AbonoManager(AbonoRepository *repo) : abonoRepository(repo) {}

    void registrarAbono(const string &nombre, float precio)
    {
        if (precio <= 0)
        {
            cerr << "El precio del abono debe ser mayor que cero." << endl;
            return;
        }

        abonoRepository->agregarAbono(nombre, precio);
        abonoRepository->saveFertilizers();
    }

    void showFertilizers() const
    {
        abonoRepository->loadFertilizers();
        const vector<pair<string, float>> &abonos = abonoRepository->getAbonos();
        cout << "Lista de abonos: " << endl;
        for (const auto &abono : abonos)
        {
            cout << "Nombre: " << abono.first << ", Precio: " << abono.second << endl;
        }
        system("pause/null");
        system("cls");
    }

    void modifyFertilizers()
    {
        string nombre;
        float nuevoPrecio;
        cout << "Ingrese el nombre del abono que desea modificar: ";
        getline(cin, nombre);
        cout << "Ingrese el nuevo precio del abono: ";
        cin >> nuevoPrecio;

        if (nuevoPrecio <= 0)
        {
            cerr << "El precio del abono debe ser mayor que cero." << endl;
            return;
        }

        const vector<pair<string, float>> &abonos = abonoRepository->getAbonos();
        for (auto &abono : abonos)
        {
            if (abono.first == nombre)
            {
                abono.second == nuevoPrecio;
                abonoRepository->saveFertilizers();
                cout << "Abono modificado correctamente." << endl;
                return;
            }
        }

        cout << "El abono '" << nombre << "' no fue encontrado." << endl;
        system("cls");
    }
};

void LinkedSearchAbono()
{
    AbonoRepository abonoRepository;
    AbonoManager abonoManager(&abonoRepository);

    char opcion;
    do
    {
        cout << "[1] REGISTRAR ABONO " << endl;
        cout << "[2] MOSTRAR ABONO " << endl;
        cout << "[3] VER TXT DE ABONO " << endl;
        cout << "[4] MODIFICAR ABONO " << endl;
        cout << "[5] SALIR: " << endl;
        cout << "INGRESA UNA OPCION: ";
        cin >> opcion;

        switch (opcion)
        {
        case '1':
        {
            system("cls");
            string nombre;
            float precio;

            cin.ignore();
            cout << "Ingrese el nombre del abono: ";
            getline(cin, nombre);
            cout << "Ingrese el precio del abono: ";
            cin >> precio;

            abonoManager.registrarAbono(nombre, precio);
            break;
        }
        case '2':
            system("cls");
            abonoManager.showFertilizers();
            abonoRepository.saveFertilizers();
            break;

        case '3':
            system("cls");
            abonoManager.modifyFertilizers();
            break;

        case '4':
            system("cls");
            abonoRepository.loadFertilizers();
            break;

        case '5':
            system("cls");
            cout << "Volviendo al menu principal..." << endl;
            break;

        default:
            system("cls");
            cout << "Opción no válida. Inténtalo de nuevo." << endl;
            break;
        }
    } while (opcion != '4');
}
