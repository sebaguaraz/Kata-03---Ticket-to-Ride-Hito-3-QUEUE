#ifndef WHATSAPP_H
#define WHATSAPP_H

#include <string>
#include <memory>
#include <IMessage.h>

using namespace std;

class Client;  // Declaración anticipada
class SupportTechnical;  // Declaración anticipada

class Whatsapp : public IMessage {
private:
    shared_ptr<Client> cliente;
    shared_ptr<SupportTechnical> tecnico;
    string mensaje1,mensaje2;


public:
    Whatsapp();
    ~Whatsapp();

    void setMessageClient(shared_ptr<Client> objetocliente, string mensaje);
    void setMessageTecnico(shared_ptr<SupportTechnical> objetotecnico, string mensaje);
    shared_ptr<Client> getClient();
    shared_ptr<SupportTechnical> getTecnico();

    string getMessageTecnico();
    string getMessageCliente();
    string notificar();


};

#endif
