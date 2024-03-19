#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

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

    friend void ModifyAbono(Abono &ab);
};

// Clase para manejar el almacenamiento de datos de abonos
class AbonoStorage
{
public:
    static void saveAbonosToFile(const vector<Abono> &abonos, const string &filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const auto &abono : abonos)
            {
                file << "Nombre: " << abono.getNombre() << ", Precio: " << abono.getPrecio() << endl;
            }
            cout << "Abonos guardados en " << filename << endl;
        }
        else
        {
            cout << "Error al abrir el archivo " << filename << endl;
        }
    }

    static void loadAbonosFromFile(vector<Abono> &abonos, const string &filename)
    {
        abonos.clear();
        ifstream file(filename);
        if (file.is_open())
        {
            string name;
            float price;
            while (file >> name >> price)
            {
                Abono abono(name, price);
                abonos.push_back(abono);
            }
            cout << "Abonos cargados desde " << filename << endl;
        }
        else
        {
            cout << "Error al abrir el archivo " << filename << endl;
        }
    }
};

// Clase para manejar la lógica de abonos
class AbonoDataHandler
{
public:
    static void registerAbono(vector<Abono> &abonos)
    {
        string name;
        float price;

        cout << "Ingrese el nombre del abono: ";
        cin >> name;
        cout << "Ingrese el precio del abono: ";
        cin >> price;

        Abono abono(name, price);
        abonos.push_back(abono);
    }

    static void showAbonos(const vector<Abono> &abonos)
    {
        cout << "Lista de abonos: " << endl;
        for (const auto &abono : abonos)
        {
            cout << "Nombre: " << abono.getNombre() << ", Precio: " << abono.getPrecio() << endl;
        }
    }
};
// Funcion amiga para modificar la Clase de abono
void ModifyAbono(Abono &ab)
{
    string name_modify;
    cout << "Ingrese el nombre de la planta: ";
    getline(cin, name_modify);

    /* for (size_t i = 0; i < ab.nombre.size(); i++)
    {
        if (ab.nombre[i] == name_modify)
        {
        }
    } */
}
// Función para manejar las operaciones de abonos
void LinkedSearchAbono()
{
    char choice;
    vector<Abono> abonos;

    do
    {
        cout << "[1] Registrar abono" << endl;
        cout << "[2] Mostrar abonos" << endl;
        cout << "[3] Guardar abonos en archivo" << endl;
        cout << "[4] Cargar abonos desde archivo" << endl;
        cout << "[5] Volver al menú principal" << endl;
        cout << "Ingrese su opción: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            AbonoDataHandler::registerAbono(abonos);
            break;
        case '2':
            AbonoDataHandler::showAbonos(abonos);
            break;
        case '3':
            AbonoStorage::saveAbonosToFile(abonos, "abonos.txt");
            break;
        case '4':
            AbonoStorage::loadAbonosFromFile(abonos, "abonos.txt");
            break;
        case '5':
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << "Opción no válida. Inténtalo de nuevo." << endl;
            break;
        }
    } while (choice != '5');
}