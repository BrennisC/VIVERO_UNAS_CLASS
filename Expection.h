#include <iostream>
#include <stdexcept>
using namespace std;

class MyExceptionRepository
{
public:
    virtual int numberNegaty() = 0;
    virtual float zeroDivision() = 0;
    virtual float stringNot() = 0;
    virtual ~MyExceptionRepository() {}
};

class ExceptionsInMemory : public MyExceptionRepository
{
private:
    string name_exception;
    float value_exception;
    int line_number;

public:
    ExceptionsInMemory(string ne, float ve, int ln) : name_exception(ne), value_exception(ve), line_number(ln) {}

    int numberNegaty()
    {
        cout << "Ingrese la cantidad que vas a registrar : ";
        cin >> value_exception;

        try
        {
            if (value_exception < 0)
                throw logic_error("No es valido la cantidad es negativa ");
            else
            {
                cout << "Puedes continuar ";
            }
        }
        catch (const logic_error &e)
        {
            cerr << e.what() << '\n';
        }
    }
};