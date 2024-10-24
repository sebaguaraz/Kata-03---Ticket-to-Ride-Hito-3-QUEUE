#include <SupportTechnical.h>


SupportTechnical::SupportTechnical() {}
SupportTechnical::~SupportTechnical() {}



void SupportTechnical::settelefono(string telefono) { this->telefono = telefono; }
void SupportTechnical::setname(string name) { this->name = name; }

string SupportTechnical::gettelefono() { return telefono; }
string SupportTechnical::getname() { return name; }

void SupportTechnical::tecnicoinfo() {
    cout << "**** DATOS TECNICO: " << endl;
    cout << "Nombre: " << getname() << endl;
    cout << "Telefono: " << gettelefono() << endl;
}


shared_ptr<Ticket> SupportTechnical::CrearTicket(shared_ptr<Client> objetocliente, string asunto, string notificaciones){
    this->notificaciones=notificaciones;
    shared_ptr<Ticket> ticket= make_shared<Ticket>(objetocliente, asunto);



    return ticket;
    
};



void SupportTechnical::Atender(shared_ptr<SupportTechnical> objetotecnico, vector<shared_ptr<Ticket>> ticketsCliente) {
    // Lógica para atender
    for (const auto ticket: ticketsCliente){
        
        ticket->AddTecnico(objetotecnico);
        cout << "El tecnico " << getname() << " esta atendiendo el ticket. " << endl;

    }

}

//ACA HAY ACOPLAMIENTO FUERTE PORQUE EL ALTO NIVEL(TECNICO) DEPENDE DE LAS IMPLEMENTACIONES(WHATSAPP)
//DEBERIA SER UN POCO MAS GENERICO ESTE METODO PORQUE SI EL ALGUN MOMENTO SE DESEA ENVIAR POR INSTAGRAM, HAY Q MODIFICAR LO EXISTENTE
shared_ptr<IMessage> SupportTechnical::EnviarMensaje(shared_ptr<SupportTechnical> tecnico, string mensaje) {
    // Verificar que el mensaje no esté vacío
    if (mensaje.empty()) {
        cout << "El mensaje no puede estar vacio." << endl;
        return nullptr; // O maneja de otra manera si es necesario
    }

    if(notificaciones == "Whatsapp"){

        shared_ptr<IMessage> objeto = make_shared<Whatsapp>();
        objeto->setMessageTecnico(shared_from_this(), mensaje);
        return objeto;

    }

        if(notificaciones == "Facebook"){

        shared_ptr<IMessage> objeto = make_shared<Facebook>();
        objeto->setMessageTecnico(shared_from_this(), mensaje);
        return objeto;

    }
    cout << "Notificación desconocida: " << notificaciones << endl;
     return nullptr; // Retorna nullptr si la notificación no es válida

}



void SupportTechnical::Alert(){
    cout << "Alertando al tecnico " << getname() << " de un mensaje del cliente..." << endl;
}


/*

shared_ptr<Ticket> SupportTechnical::ActualizarTicket(shared_ptr<Ticket> ticket, string asunto){
    
};

*/


