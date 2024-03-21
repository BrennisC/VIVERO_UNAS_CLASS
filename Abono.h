#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// Constantes para mensajes
const string FILENAME = "Abono.txt";

// Clase para representar un abono
class Abono;
class Abono
{
private:
    vector<string> nombre;
    vector<float> precio;

public:
    Abono() = default; // Constructor por defecto
    Abono(vector<string> &n, vector<float> p) : nombre(n), precio(p) {}

    vector<string> getNombre() const { return nombre; }
    vector<float> getPrecio() const { return precio; }

    friend void ModifyAbono(Abono &abonos);
};

// Repositorio de abonos
class AbonoRepository : public Abono
{
public:
    void saveFertilizers(Abono &abonos) const
    {
        ofstream archivo(FILENAME, ios ::out | ios ::app);
        if (archivo.is_open())
        {
            for (size_t i = 0; i < abonos.getNombre().size(); ++i)
            {
                archivo << "Registro de abono ";
                archivo << "Nombre del abono : " << abonos.getNombre()[i] << endl;
                archivo << "Precio del abono : " << abonos.getPrecio()[i] << endl;
                archivo << "----------------------------------------" << endl;
            }
        }
        else
        {
            cerr << "Error al abrir el archivo " << FILENAME << endl;
        }
        system("cls");
    }

    void loadFertilizers()
    {
        ifstream file(FILENAME);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();

            cout << "Abonos cargados desde " << FILENAME << endl;
        }
        else
        {
            cout << "No se pudo abrir el archivo plantas ." << endl;
        }
    }
};

// Manejador de operaciones de abonos
class AbonoManager
{
private:
    Abono &abonos;

public:
    AbonoManager(Abono abono) : abonos(abono) {}
    void registrarAbono(Abono abono)
    {
        int quantity;

        cout << "Ingrese la cantidad de abono: ";
        cin >> quantity;

        for (int i = 0; i < quantity; i++)
        {
            string name_abono;
            float price_abono;

            cin.ignore();
            cout << "Ingrese el nombre del abono :  ";
            getline(cin, name_abono);

            cout << "Ingrese el " << name_abono << " : ";
            try
            {
                cin >> price_abono;
                if (price_abono < 0)
                    throw "Precio no valido";
                else
                {
                    cout << "El precio es valido ";
                }
            }
            catch (const char *e)
            {
                cerr << "Error " << e << endl;
            }

            abono.getNombre().push_back(name_abono);
            abono.getPrecio().push_back(price_abono);
        }
    }

    void showFertilizers(Abono abonos)
    {
        cout << "\n\tLista de fertilizantes" << endl;
        cout << setw(25) << left << "Nombre" << setw(10) << right << "Cantidad" << endl;
        for (int i = 0; i < abonos.getNombre().size(); i++)
        {
            cout << setw(25) << left << abonos.getNombre()[i] << setw(10) << right << abonos.getPrecio()[i] << endl;
        }
    }
};

void ModifyAbono(Abono &abonos)
{
    string nombre;
    cin.ignore();
    cout << "Ingrese el nombre del abono que quieres modificar: ";
    getline(cin, nombre);
    for (int i = 0; i < abonos.getNombre().size(); ++i)
    {
        if (abonos.getNombre()[i] == nombre)
        {
            string nuevoNombre;
            cout << "Ingrese el nuevo nombre del abono: ";
            cin >> nuevoNombre;
            abonos.getNombre().push_back(nuevoNombre);
            cout << "Nombre del abono modificado exitosamente." << endl;
        }
    }
    cout << "El nombre del abono especificado no fue encontrado." << endl;
}
void LinkedSearchAbono()
{

    char opcion;
    Abono abonos;
    AbonoManager *abonomanger;
    AbonoRepository *abonorepository;

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
            abonomanger->registrarAbono(abonos);
            break;
        }
        case '2':
            system("cls");
            abonomanger->showFertilizers(abonos);
            abonorepository->saveFertilizers(abonos);
            break;

        case '3':
            system("cls");
            abonorepository->loadFertilizers();
            break;

        case '4':
            system("cls");

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
