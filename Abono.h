#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// Clase para representar un abono
class Abono
{
private:
    string nombre;
    float precio;

public:
    Abono(const string &n = "", float p = 0) : nombre(n), precio(p) {}

    const string &getNombre() const { return nombre; }
    float getPrecio() const { return precio; }
};

// Interfaz para operaciones de abono
class AbonoOperations
{
public:
    virtual void registrarAbono() = 0;
    virtual void mostrarAbonos() const = 0;
    virtual ~AbonoOperations() {}
};

// Repositorio de abonos
class AbonoRepository
{
public:
    virtual void saveFertilizers(const vector<Abono> &abonos) const = 0;
    virtual vector<Abono> loadFertilizers() const = 0;
    virtual ~AbonoRepository() {}
};

// Implementación del manejador de operaciones de abonos
class AbonoManager : public AbonoOperations
{
private:
    vector<Abono> &abonos;

public:
    AbonoManager(vector<Abono> &ab) : abonos(ab) {}

    void registrarAbono() override
    {
        int quantity;
        cout << "Ingrese la cantidad de abono: ";
        cin >> quantity;

        for (int i = 0; i < quantity; i++)
        {
            string name_abono;
            float price_abono;

            cin.ignore();
            cout << "Ingrese el nombre del abono: ";
            getline(cin, name_abono);

            cout << "Ingrese el precio del abono: ";
            cin >> price_abono;

            abonos.push_back(Abono(name_abono, price_abono));
        }

        system("cls");
    }

    void mostrarAbonos() const override
    {
        cout << "\n\tLista de fertilizantes" << endl;
        cout << setw(25) << left << "Nombre" << setw(10) << right << "Precio" << endl;
        for (const auto &abono : abonos)
        {
            cout << setw(25) << left << abono.getNombre() << setw(10) << right << abono.getPrecio() << endl;
        }
        system("pause > null");
    }
};

// Implementación del repositorio de abonos basado en archivos
class FileAbonoRepository : public AbonoRepository
{
public:
    void saveFertilizers(const vector<Abono> &abonos) const override
    {
        ofstream archivo("Abono.txt", ios::out | ios::app);
        if (archivo.is_open())
        {
            for (const auto &abono : abonos)
            {
                archivo << "Registro de abono " << endl;
                archivo << "Nombre del abono: " << abono.getNombre() << endl;
                archivo << "Precio del abono: " << abono.getPrecio() << endl;
                archivo << "----------------------------------------" << endl;
            }
            cout << "Datos de abonos guardados en Abono.txt" << endl;
        }
        else
        {
            cerr << "Error al abrir el archivo Abono.txt" << endl;
        }
        system("pause > null");
        system("cls");
    }

    vector<Abono> loadFertilizers() const override
    {
        vector<Abono> abonos;
        ifstream archivo("Abono.txt");
        if (archivo.is_open())
        {
            string line;
            while (getline(archivo, line))
            {
                cout << line << endl;
            }
            archivo.close();
            cout << "Abonos cargados desde Abono.txt" << endl;
        }
        else
        {
            cerr << "No se pudo abrir el archivo Abono.txt" << endl;
        }
        return abonos;
        system("cls");
    }
};

void LinkedSearchAbono()
{
    vector<Abono> abonos;
    FileAbonoRepository repository;
    AbonoManager abonoManager(abonos);

    char opcion;
    do
    {
        cout << "[1] REGISTRAR ABONO" << endl;
        cout << "[2] MOSTRAR ABONO" << endl;
        cout << "[3] VER TXT DE ABONO" << endl;
        cout << "[4] SALIR" << endl;
        cout << "INGRESA UNA OPCION: ";
        cin >> opcion;

        switch (opcion)
        {
        case '1':
            system("cls");
            abonoManager.registrarAbono();
            break;
        case '2':
            system("cls");
            abonoManager.mostrarAbonos();
            repository.saveFertilizers(abonos);
            break;
        case '3':
            system("cls");
            repository.loadFertilizers();
            break;
        case '4':
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
