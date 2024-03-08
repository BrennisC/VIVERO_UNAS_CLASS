#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
using namespace std;
class LoginUser
{
private:
    vector<string> nombre;
    vector<string> correo_institucional;
    vector<int> id;
    vector<string> contrasena;

public:
    LoginUser() = default;
    void registerUser();
    vector<string> getNombre() { return nombre; }
    vector<string> getcorreo_institucional() { return correo_institucional; }
    vector<int> getid() { return id; }
    vector<string> getcontrasena() { return contrasena; }
};

// GenerarContraseñasAutomaticas
class GenerarContasenasAutomaticas
{
public:
    static string generarContrasena(int longitud)
    {
        const string caracteresPermitidos = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!";
        string contrasena;

        srand(time(nullptr));

        for (int i = 0; i < longitud; ++i)
        {
            int indice = rand() % caracteresPermitidos.length();
            contrasena += caracteresPermitidos[indice];
        }

        return contrasena;
    }
};
// Verificar si el usuario se encuentra en el txt para poder iniciar  sesión o registrarse

void LoginUser ::registerUser()
{
    for (int i = 0; i < 2; i++)
    {
        int numero_aletorio = rand() % 300 + 1;
        string name_user, correo, contrasena_actual;

        cout << "Ingrese su nombre para el registro: \n";
        getline(cin, name_user);
        nombre.push_back(name_user);

        cout << "Ingrese su direccion de correo institucional: \n";
        getline(cin, correo);
        correo_institucional.push_back(correo);

        cout << "Id: " << numero_aletorio << endl;

        cout << "Ingrese su contraseña: " << endl;
        GenerarContasenasAutomaticas gr;
        contrasena_actual = gr.generarContrasena(9);
        cout << contrasena_actual << endl;
        contrasena.push_back(contrasena_actual);
    }
}
class saveTxt
{
public:
    static string saveUser(LoginUser &usuarios)
    {
        size_t size = usuarios.getNombre().size();
        ofstream file("Users.txt");
        if (file.is_open())
        {
            for (size_t i = 0; i < size; i++)
            {
                file << "NOOMBRE : " << usuarios.getNombre()[i];
                file << " CORREO VIVERO: " << usuarios.getcorreo_institucional()[i];
                file << " ID: " << usuarios.getid()[i];
                file << " CONTRASEÑA: " << usuarios.getcontrasena()[i];
                file << "\n";
            }
            file.close();
        }
        else
        {
            cout << "Error guardar en el txt " << endl;
        }
        return "Usuario Guardado Correctamente!";
    }
};
class verifyUser
{
};