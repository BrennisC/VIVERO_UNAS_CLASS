#include <iostream>
#include <stdexcept>
using namespace std;
class MyException
{
private:
    string name_exception;
    float value_exception;
    int line_number;

public:
    MyException(string n, float ve, int ln) : name_exception(n), value_exception(ve), line_number(ln) {}
    string getName() const { return name_exception; }
    float getValue() { return value_exception; }
    int getLineNumber() const { return line_number; }
};

class MyExceptionRepository
{
public:
    virtual void numberNegaty() = 0;
};