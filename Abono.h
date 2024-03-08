#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
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
    // Mostrar los elementos registratos
    void ShowFertilizan();
    // Guardar los plantas en un TXT
    void SaveFertilizan();
    // Cargar para ver en el TXT
    void LoadFertilizan();
    // Funcion para agrupar todos los metodos
    friend void BusquedaEnlazadaAbono();
};
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
void Abono::ShowFertilizan()
{
    for (size_t i = 0; i < name_fertilizan.size(); i++)
    {
        float total;
        cout << "NOMBRE PLANTA: " << name_fertilizan[i];
        cout << "\nPRECIO PLANTA: $" << price_fertilizan[i] << endl;
        for (auto price : price_fertilizan)
        {
            total = static_cast<float>(price);
        }
        cout << "TOTAL DEL ABONO: $" << total << endl;
        cout << "-----------------------------" << endl;
    }
}
void BusquedaEnlazadaAbono()
{
    char choice;
    Abono ab;
    ShownFertilizan sf;
    do
    {
        cin.ignore();
        cout << "[1]REGISTRAR EL ABONO: \n";
        cout << "[2]MOSTRAR ABONO: \n";
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
            getchar();
            break;
        case '3':
            cout << "saliendo...";
            break;
        default:
            cout << "Ocpion no valida intentalo de nuevo ";
            break;
        }
    } while (choice != '3');
}