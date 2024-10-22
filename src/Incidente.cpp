#include <Incidente.h>


Incidente::Incidente(string asunto, shared_ptr<Client> cliente)
    : asunto(asunto), cliente(cliente) {}

Incidente::~Incidente(){}

string Incidente::getasunto(){
    return asunto;
};

void Incidente::Incidenteinfo() {
    cout << "------------- DATOS DEL TICKET---------------------" << endl;
    cout << "Asunto del ticket: " << asunto << endl;
    cout << "Ticket asociado al cliente: " << cliente->getname() << endl;
}
