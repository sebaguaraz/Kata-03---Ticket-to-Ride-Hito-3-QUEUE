#include <Whatsapp.h>



Whatsapp::Whatsapp(){

};
Whatsapp::~Whatsapp(){

};

void Whatsapp::setMessageClient(shared_ptr<Client> objetocliente, string mensaje){
    cliente = objetocliente;
    mensaje2 = mensaje;
};
void Whatsapp::setMessageTecnico(shared_ptr<SupportTechnical> objetotecnico, string mensaje){
    tecnico = objetotecnico;
    mensaje1=mensaje;

};


string Whatsapp::getMessageTecnico(){
    return mensaje1;


};

string Whatsapp::getMessageCliente(){
    return mensaje2;


};

string Whatsapp::notificar(){
    return "notificando por Whatsapp. ";

};

shared_ptr<Client> Whatsapp::getClient(){
    return cliente;
};
shared_ptr<SupportTechnical> Whatsapp::getTecnico(){
    return tecnico;

};



