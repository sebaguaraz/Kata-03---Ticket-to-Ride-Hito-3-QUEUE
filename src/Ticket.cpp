#include <Ticket.h>


int Ticket::contador = 0;  // Inicialización del contador

Ticket::Ticket(shared_ptr<Client> objetocliente, string asunto) {
    this->id = ++contador;
    cliente=objetocliente;
    incidente = make_shared<Incidente>(asunto, objetocliente);
}
Ticket::~Ticket(){

};


void Ticket::AddTecnico(shared_ptr<SupportTechnical> objetotecnico) {

    
    tecnico = objetotecnico;
        

    
}



int Ticket::getid(){
    return id;
}

void Ticket::mostrarTicket() {

    incidente->Incidenteinfo();
    cliente->clienteinfo();
    if (tecnico!=nullptr)
        tecnico->tecnicoinfo();
    else{
        cout << "tecnico no asignado todavia. " << endl;

    }
    cout << "estado del ticket: " << getEstado()<<endl;

    cout <<"------------------" << endl;
}

shared_ptr<SupportTechnical> Ticket::gettecnico(){
    return tecnico;
};

shared_ptr<Client> Ticket::getcliente() {

    return cliente;

}


shared_ptr<Incidente> Ticket::getincidente() {

    return incidente;

}



void Ticket::setEstado(string estado) {
    this->estado=estado;
}

string Ticket::getEstado() {

    return estado;

}


void Ticket::agregarMensaje(shared_ptr<IMessage> objetomensajee) {
        listamensajes.push_back(objetomensajee);
    }


void Ticket::mostrarmensajes() {
    if (listamensajes.empty()) {
        std::cout << "No hay mensajes para este ticket." << std::endl;
        return;
    }

    for (const auto& msg : listamensajes) {
        if (msg->getTecnico() != nullptr) {  // Verifica que el técnico no sea nulo
            std::cout << "Mensaje de tecnico " << msg->getTecnico()->getname() << ": " 
                      << msg->getMessageTecnico() << std::endl;
        }

        if (msg->getClient() != nullptr) {  // Verifica que el cliente no sea nulo
            std::cout << "Mensaje del cliente " << msg->getClient()->getname() << ": " 
                      << msg->getMessageCliente() << std::endl;
        }
        cout << msg->notificar();
        std::cout << std::endl;  // Línea separadora
        std::cout << "----------------------------------------" << std::endl;  // Línea separadora
    }
}

void Ticket::AlertClient(){

    cliente->Alert();
}


void Ticket::AlertTechnical(){

    tecnico->Alert();
    

}