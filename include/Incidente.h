#ifndef INCIDENTE_H
#define INCIDENTE_H

#include <Client.h>
#include <string>
#include <memory>
using namespace std;

class Client; // Declaración adelantada

class Incidente
{
private:
    string asunto, gravedad;
    shared_ptr<Client> cliente;

public:
    Incidente(string asunto, shared_ptr<Client> cliente);
    ~Incidente();
    void Incidenteinfo();
    string getasunto();
};

#endif
