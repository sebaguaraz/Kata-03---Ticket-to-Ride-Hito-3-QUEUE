#ifndef TICKET_H
#define TICKET_H

#include <Client.h>
#include <Incidente.h>
#include <SupportTechnical.h>
#include <IMessage.h>

#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class Client;
class Incidente;
class SupportTechnical;
class IMessage;

class Ticket {
private:
    int id;
    static int contador;
    string estado;
    shared_ptr<Client> cliente;
    shared_ptr<SupportTechnical> tecnico;
    shared_ptr<Incidente> incidente;
    vector<shared_ptr<IMessage>> listamensajes;

public:
    Ticket(shared_ptr<Client> objetocliente, string asunto);
    ~Ticket();
    //void AddClient(shared_ptr<Client> objetocliente);
    void AddTecnico(shared_ptr<SupportTechnical> objetotecnico);
    void mostrarTicket();
    void setEstado(string estado);
    string getEstado();
    shared_ptr<Client> getcliente();
    shared_ptr<Incidente> getincidente();
    shared_ptr<SupportTechnical> gettecnico();


    int getid();
    void agregarMensaje(shared_ptr<IMessage> objetomensaje);
    void mostrarmensajes();
    void AlertClient();
    void AlertTechnical();
};

#endif
