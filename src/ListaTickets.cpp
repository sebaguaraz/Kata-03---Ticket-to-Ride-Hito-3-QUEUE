#include <ListaTickets.h>


ListaTickets::ListaTickets(){};
ListaTickets::~ListaTickets(){};
void ListaTickets::agregarTicket(shared_ptr<Ticket> ticket){

    listaticket.push_back(ticket);
};
vector<shared_ptr<Ticket>> ListaTickets::ObtenerTickets(shared_ptr<Client> objetocliente){
    vector<shared_ptr<Ticket>>ticketsCliente;//almacena los tickets encontrados

        for (auto& ticket : listaticket) {
            if (ticket->getcliente()->getid() == objetocliente->getid()) {
                ticketsCliente.push_back(ticket);  // Agregar tickets del cliente encontrado
            }
        }
        return ticketsCliente;  // Retorna los tickets encontrados
};
bool ListaTickets::IsEmpty(){
    return listaticket.empty();
};
int ListaTickets::size(){
    return listaticket.size();
    
};


void ListaTickets::MensajesClienteActual(shared_ptr<Client> cliente) {
    // Obtener los tickets del cliente
    vector<shared_ptr<Ticket>> ticketsCliente = ObtenerTickets(cliente);

    if (!ticketsCliente.empty()) {
        // Iterar sobre cada ticket del cliente
        for (const auto& ticket : ticketsCliente) {
            cout << "Mensajes del Ticket " << ticket->getid() << " - Asunto: " << ticket->getincidente()->getasunto() << endl;

            // Obtener y mostrar la lista de mensajes del ticket
            ticket->mostrarmensajes(); 
        }
    } else {
        cout << "El cliente no tiene tickets." << endl;
    }
}


bool ListaTickets::TodosTicketsCerrados(shared_ptr<Client> cliente){
    vector<shared_ptr<Ticket>> ticketsCliente = ObtenerTickets(cliente);//se obtiene los tickets encontrados


    if (!ticketsCliente.empty()) {
        // Verificar si todos los tickets están cerrados, recorriendolos
        for (const auto ticket : ticketsCliente) {
            if (!(ticket->getEstado()=="cerrado")) {//si algun ticket distinto de cerrado...
                return false; // Si hay algún ticket abierto, devolver false
            }
        }
        return true; // Si todos están cerrados, devolver true

    }else {
        cout << "El cliente no tiene tickets aun." << endl;
        return false;
    }
}
