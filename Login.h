#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
using namespace std;
// Clase para generar contraseñas aleatorias
class PasswordGenerator
{
public:
    static string generatePassword(int length)
    {
        static const string palabraBase = "unasVivero";
        static const string caracteresAleatorios = "0123456789";
        static random_device rd;
        static mt19937 gen(rd());

        string password;

        // Agregar la palabra base
        password += palabraBase;

        // Agregar caracteres aleatorios para completar la longitud deseada
        for (int i = palabraBase.size(); i < length; ++i)
        {
            int index = uniform_int_distribution<>(0, caracteresAleatorios.size() - 1)(gen);
            password += caracteresAleatorios[index];
        }

        // Mezclar la contraseña
        shuffle(password.begin() + palabraBase.size(), password.end(), gen);

        return password;
    }
};

// Clase para manejar usuarios
class LoginUser
{
public:
    LoginUser(const string &name, const string &password)
        : name(name), password(password) {}

    const string &getName() const { return name; }
    const string &getPassword() const { return password; }

private:
    string name;
    string password;
};

// Clase para manejar operaciones de archivo
class FileManager
{
public:
    static void saveUsers(const vector<LoginUser> &users)
    {
        ofstream file("Users.txt", ios::out | ios ::app);
        if (!file)
        {
            throw runtime_error("Error al abrir el archivo Users.txt");
        }

        for (const auto &user : users)
        {
            file << user.getName() << " " << user.getPassword() << "\n";
        }
    }

    static vector<LoginUser> loadUsers()
    {
        vector<LoginUser> users;
        ifstream file("Users.txt");
        if (!file)
        {
            throw runtime_error("Error al abrir el archivo Users.txt");
        }

        string name, password;
        while (file >> name >> password)
        {
            users.emplace_back(name, password);
        }

        return users;
    }
};