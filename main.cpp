#include <iostream>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <string>
#include "Abono.h"
#include "Client.h"
#include "Plants.h"
#include "Login.h"

// Definiciones para cambiar el estilo y color del texto en la consola utilizando secuencias de escape ANSI
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

using namespace std;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función para obtener la posición vertical del cursor
int obtenerPosicionVerticalCursor()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

// Función para obtener el ancho de la ventana de la consola
int obtenerAnchoConsola()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Función para centrar texto horizontalmente en la consola
void centrarTexto1(const string &texto)
{
    int anchoVentana = obtenerAnchoConsola();
    int longitudTexto = texto.length();
    int posicionX = (anchoVentana - longitudTexto) / 2;
    gotoxy(posicionX, obtenerPosicionVerticalCursor());
    cout << BLUE << YELLOW << texto;
    gotoxy(0, obtenerPosicionVerticalCursor() + 1); // Restaurar la posición vertical del cursor
}
void centrarTexto2(const string &texto)
{
    int anchoVentana = obtenerAnchoConsola();
    int longitudTexto = texto.length();
    int posicionX = (anchoVentana - longitudTexto) / 2;
    gotoxy(posicionX, obtenerPosicionVerticalCursor());
    cout << GREEN << BOLD << texto << RESET;
    gotoxy(0, obtenerPosicionVerticalCursor() + 1); // Restaurar la posición vertical del cursor
}

void centrarTexto3(const string &texto)
{
    int anchoVentana = obtenerAnchoConsola();
    int longitudTexto = texto.length();
    int posicionX = (anchoVentana - longitudTexto) / 2;
    gotoxy(posicionX, obtenerPosicionVerticalCursor());
    cout << BLUE << YELLOW << texto;
}
// Funcion para accede a las plantas
void opcion1()
{

    system("cls");
    centrarTexto1("Ha seleccionado la Opcion 1.");
    Sleep(3000);
    system("cls");

    BOLD;
    LinkedSearchPlants();
}

// Funcion para ingresar a la class Abono
void opcion2()
{
    system("cls");
    centrarTexto1("Ha seleccionado la Opcion 2.");
    Sleep(3000);

    system("cls");
    BOLD;
    LinkedSearchAbono();
}

// Funcion para ingresar a la class Client
void opcion3()
{
    system("cls");
    centrarTexto1("Ha seleccionado la Opcion 3.");
    Sleep(3000);

    system("cls");
    BOLD;
    LinkedSearchClient();
}

// Funcion para salir de sistema
void exitSystem()
{
    cout << RED << BOLD << "Saliendo de sistema...";
    Sleep(500);
    exit(0);
}

class ListMenuStart
{
public:
    ListMenuStart() = default;
    void ListMenu()
    {
        char opc;

        do
        {
            system("cls");
            centrarTexto2("     MENU DE OPCIONES         \n\n");
            centrarTexto1(" [1] MENU DE PLANTA       ");
            centrarTexto1(" [2] MENU DE ABONO        ");
            centrarTexto1(" [3] MENU DE CLIENTE      ");
            centrarTexto1(" [4] SALIR MENU PRINCIPAL ");
            cout << endl;
            centrarTexto3("Ingrese su opcion: ");
            cin >> opc;

            switch (opc)
            {
            case '1':
                system("cls");
                opcion1();
                break;

            case '2':
                system("cls");
                opcion2();
                break;

            case '3':
                system("cls");
                opcion3();
                break;

            case '4':
                system("cls");
                exitSystem();
                break;

            default:
                system("cls");
                cout << "Opcion no valida" << endl;
                system("pause");
                break;
            }
        } while (opc != '4');
    }
};

// Clase principal para accerder  al menu del sistema
class StartSesion
{
public:
    StartSesion() = default;
    void StartInterfaz()
    {
        vector<LoginUser> users;
        char choice;

        do
        {
            centrarTexto2("VIVERO UNAS ");
            cout << BLUE << "\n¡Bienvenidos a nuestro vivero!" << RESET << endl;
            cout << YELLOW << UNDERLINE << "Estamos aquí para ayudarte." << RESET << endl;
            cout << RED << "¡No dudes en preguntarnos cualquier cosa!" << RESET << endl;

            centrarTexto1("1. Registrar nuevo usuario");
            centrarTexto1("2. Iniciar sesión        ");
            centrarTexto1("3. Salir                  ");
            centrarTexto3("Ingrese su opción: ");
            cin.getline(&choice, '3');
            switch (choice)
            {
            case '1':
            {
                system("cls");
                string name;

                cin.clear();
                cout << "Ingrese su nombre: ";
                getline(cin, name);

                string password = PasswordGenerator::generatePassword(12);

                cout << "Su contraseña generada es: " << password << "\n";
                users.emplace_back(name, password);
                FileManager::saveUsers(users);

                Sleep(5000);
                getchar();
                system("cls");
                break;
            }
            case '2':
            {
                system("cls");
                string name, password;

                cin.clear();
                cout << "Ingrese su nombre: ";
                getline(cin, name);
                cout << "Ingrese su contraseña: ";
                getline(cin, password);

                try
                {
                    auto userList = FileManager::loadUsers();
                    bool found = false;
                    for (const auto &user : userList)
                    {
                        if (user.getName() == name && user.getPassword() == password)
                        {
                            cout << "Inicio de sesión exitoso\n";
                            found = true;

                            ListMenuStart list;
                            list.ListMenu();
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "Nombre de usuario o contraseña incorrectos\n";
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << "\n";
                }
                system("cls");
                break;
            }
            case '3':
                cout << "Salir";
                break;

            default:
                cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (choice != '3');
    }
};

int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8"); // Establece el locale a español

    StartSesion ss;
    ss.StartInterfaz();
}
