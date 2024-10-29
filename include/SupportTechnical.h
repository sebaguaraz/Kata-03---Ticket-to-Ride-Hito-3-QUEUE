#ifndef SUPPORTTECHNICAL_H
#define SUPPORTTECHNICAL_H

#include <string>
#include <Ticket.h>
#include <memory>
#include <IMessage.h>
#include <Client.h>
#include <Facebook.h>
#include <Whatsapp.h>
#include <ColaCliente.h>



using namespace std;

class Ticket;
class ColaCliente;
class Client;
class IMessage;


class SupportTechnical : public enable_shared_from_this<SupportTechnical> {
//una forma de obtener un shared_ptr al propio objeto desde dentro de un método.
private:
    string telefono;
    string name;

public:
    SupportTechnical();
    ~SupportTechnical();
    void settelefono(string telefono);
    void setname(string name);
    string gettelefono();
    string getname();
    //string getnotificaciones();
    void tecnicoinfo();
    void Atender(shared_ptr<SupportTechnical> objetotecnico,  shared_ptr<Ticket> ticket);
    shared_ptr<Ticket> CrearTicket(shared_ptr<Client> objetocliente, string asunto, string notificaciones);
    //shared_ptr<Ticket> ActualizarTicket(shared_ptr<Ticket> ticket, string asunto);
    shared_ptr<IMessage> EnviarMensaje( shared_ptr<SupportTechnical> tecnico,  string mensaje, string notificaciones);
    void Alert();
};

#endif
