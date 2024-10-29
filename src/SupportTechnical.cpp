#include <SupportTechnical.h>


SupportTechnical::SupportTechnical() {}
SupportTechnical::~SupportTechnical() {}



void SupportTechnical::settelefono(string telefono) { this->telefono = telefono; }
void SupportTechnical::setname(string name) { this->name = name; }

string SupportTechnical::gettelefono() { return telefono; }
string SupportTechnical::getname() { return name; }
//string SupportTechnical::getnotificaciones() { return notificaciones; }

void SupportTechnical::tecnicoinfo() {
    cout << "**** DATOS TECNICO: " << endl;
    cout << "Nombre: " << getname() << endl;
    cout << "Telefono: " << gettelefono() << endl;
}


shared_ptr<Ticket> SupportTechnical::CrearTicket(shared_ptr<Client> objetocliente, string asunto, string notificaciones){
    //this->notificaciones=notificaciones;
    shared_ptr<Ticket> ticket= make_shared<Ticket>(objetocliente, asunto);
    ticket->setnotificaciones(notificaciones);

    return ticket;
    
};



void SupportTechnical::Atender(shared_ptr<SupportTechnical> objetotecnico, shared_ptr<Ticket> ticket) {//se le pasa el ticket abierto encontrado
    // Lógica para atenders  
        ticket->AddTecnico(objetotecnico);//se le asigna el teccnico
        cout << "El tecnico " << getname() << " esta atendiendo el ticket. " << endl;

    

}


shared_ptr<IMessage> SupportTechnical::EnviarMensaje(shared_ptr<SupportTechnical> tecnico, string mensaje, string notificaciones) {
    // Verificar que el mensaje no esté vacío
    if (mensaje.empty()) {
        cout << "El mensaje no puede estar vacio." << endl;
        return nullptr; // O maneja de otra manera si es necesario
    }

    cout << "Enviando mensaje (" << mensaje << ") de parte de: " << tecnico->getname() << " por " << notificaciones << endl;


    if(notificaciones == "Whatsapp"){

        shared_ptr<IMessage> objeto = make_shared<Whatsapp>();
        objeto->setMessageTecnico(shared_from_this(), mensaje);//se pasa a si mismo el object tecnico
        return objeto;

    }

        if(notificaciones == "Facebook"){

        shared_ptr<IMessage> objeto = make_shared<Facebook>();
        objeto->setMessageTecnico(shared_from_this(), mensaje);
        return objeto;

    }
    cout << "Notificacion desconocida." << endl;
    return nullptr;


}



void SupportTechnical::Alert(){
    cout << "Alertando al tecnico " << getname() << " de un mensaje del cliente..." << endl;
}


/*

shared_ptr<Ticket> SupportTechnical::ActualizarTicket(shared_ptr<Ticket> ticket, string asunto){
    
};

*/


