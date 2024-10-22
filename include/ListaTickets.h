#ifndef LISTATICKETS_H
#define LISTATICKETS_H

#include <vector>
#include <memory>
#include <Ticket.h>
#include <Client.h>

class Ticket;
class Client;

class ListaTickets {
private:
    vector<shared_ptr<Ticket>> listaticket;

public:
    ListaTickets();
    ~ListaTickets();
    void agregarTicket(shared_ptr<Ticket> ticket);
    vector<shared_ptr<Ticket>> ObtenerTickets(shared_ptr<Client> objetocliente);
    bool TodosTicketsCerrados(shared_ptr<Client> cliente);
    void MensajesClienteActual(shared_ptr<Client> cliente);
    bool IsEmpty();
    int size();
};

#endif