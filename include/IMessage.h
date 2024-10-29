#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <string>
#include <memory>

using namespace std;

class SupportTechnical;
class Client;

class IMessage
{

public:
    virtual void setMessageClient(shared_ptr<Client> objetocliente, string mensaje) = 0;
    virtual void setMessageTecnico(shared_ptr<SupportTechnical> objetotecnico, string mensaje) = 0;
    virtual shared_ptr<Client> getClient() = 0;
    virtual shared_ptr<SupportTechnical> getTecnico() = 0;

    virtual string getMessageTecnico() = 0;
    virtual string getMessageCliente() = 0;
    virtual string notificar() = 0;
};

#endif
