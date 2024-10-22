#ifndef FACEBOOK_H
#define FACEBOOK_H

#include <string>
#include <memory>
#include <IMessage.h>

using namespace std;

class Client;  // Declaración anticipada
class SupportTechnical;  // Declaración anticipada


class Facebook : public IMessage {
private:
    shared_ptr<Client> cliente;
    shared_ptr<SupportTechnical> tecnico;
    string mensaje1,mensaje2;


public:
    Facebook();
    ~Facebook();

    void setMessageClient(shared_ptr<Client> objetocliente, string mensaje);
    void setMessageTecnico(shared_ptr<SupportTechnical> objetotecnico, string mensaje);
    shared_ptr<Client> getClient();
    shared_ptr<SupportTechnical> getTecnico();

    string getMessageTecnico();
    string getMessageCliente();
    string notificar();


};

#endif
