#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
using namespace std;
// Clase para generar contraseñas aleatorias
class PasswordGenerator
{
public:
    static string generatePassword(int length)
    {
        static const string chars = "unas2024";
        static random_device rd;
        static mt19937 gen(rd());

        string password(length, '\0');
        uniform_int_distribution<> dis(0, chars.size() - 1);
        for (int i = 0; i < length; ++i)
        {
            password[i] = chars[dis(gen)];
        }
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
        ofstream file("Users.txt", ios::out);
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