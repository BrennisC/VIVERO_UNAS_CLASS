#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;
class Abono
{
private:
    vector<string> name_fertilizan;
    vector<float> price_fertilizan;

public:
    // Constructores de la clase
    Abono() : name_fertilizan(), price_fertilizan() {}
    Abono(vector<string> n, vector<float> p) : name_fertilizan(n), price_fertilizan(p) {}

    //  Crear los get para poder acceder a los atributos de la clase
    vector<string> getNombre_Fertilizan() { return name_fertilizan; }
    vector<float> getPrice_Fertilizan() { return price_fertilizan; }

    // Registro de plantas para el sistema de la vivero UNAS
    void RegistarFertilizan();

    // Funcion para agrupar todos los metodos
    friend void BusquedaEnlazadaAbono();
};

// Implementacion del metodo RegistrarPlantas
void Abono::RegistarFertilizan()
{
    int cantidad;
    cout << "Ingresa la cantidad de abonos: ";
    cin >> cantidad;
    cin.ignore();
    for (int i = 0; i < cantidad; i++)
    {
        string name;
        cout << "Ingrese el nombre del  fertilizante: ";
        getline(cin, name);
        name_fertilizan.push_back(name);

        float precio;
        cout << "Ingrese el precio del abono : ";
        cin >> precio;
        price_fertilizan.push_back(precio);
    }
}

// CLASE PARA MOSTRAR LOS ELEMENTOS REGISTRADOS
class ShownFertilizan
{
public:
    static void shown(Abono &ab)
    {
        size_t size = ab.getNombre_Fertilizan().size();
        for (size_t i = 0; i < size; i++)
        {
            cout << "Nombre de los abonos : " << ab.getNombre_Fertilizan()[i] << endl;
            cout << "Precio de los abonos: " << ab.getPrice_Fertilizan()[i] << endl;
        }
    }
};

class SaveFertilizan
{
public:
    static void saveFile(Abono &ab)
    {
        ofstream file("Abono.txt", ios::out | ios::app);
        if (file.is_open())
        {
            size_t size = ab.getNombre_Fertilizan().size();
            for (size_t i = 0; i < size; i++)
            {
                file << "REGISTRO DE ABONO : ";
                file << "\nNOMBRE DEL FERTILIZANTE : " << ab.getNombre_Fertilizan()[i];
                file << "\nPRECIO DEL FERTILIZANTE : " << ab.getPrice_Fertilizan()[i];
                file << "\n\n";
            }
            file.close();
        }
        else
        {
            cout << "Error no se pudo guardar el archivo. ";
        }
    }
};

class loadFertilizan
{
public:
    static void loadfile(Abono &ab)
    {
        ifstream file("Abono.txt");
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
void BusquedaEnlazadaAbono()
{
    char choice;
    Abono ab;
    ShownFertilizan sf;
    SaveFertilizan sfe;
    loadFertilizan lf;

    do
    {
        cin.ignore();
        cout << "[1]REGISTRAR EL ABONO: \n";
        cout << "[2]MOSTRAR ABONO: \n";
        cout << "[3]VER EN EL TXT: \n";
        cout << "[4]VOLVER AL MENU PRINCIPAL \n";
        cout << "INGRESAR UNA OPCION: \n";
        cin.getline(&choice, 3);
        switch (choice)
        {
        case '1':
            system("cls");
            ab.RegistarFertilizan();
            break;

        case '2':
            system("cls");
            sf.shown(ab);
            sfe.saveFile(ab);
            getchar();
            break;

        case '3':
            system("cls");
            lf.loadfile(ab);
            break;
        case '4':
            system("cls");
            cout << "Volviendo al menu principal. ";
            break;
        default:
            cout << "Ocpion no valida intentalo de nuevo ";
            break;
        }
    } while (choice != '4');
}