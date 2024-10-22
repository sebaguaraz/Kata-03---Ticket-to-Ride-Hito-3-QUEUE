#include <Facebook.h>



Facebook::Facebook(){

};
Facebook::~Facebook(){

};

void Facebook::setMessageClient(shared_ptr<Client> objetocliente, string mensaje){
    cliente = objetocliente;
    mensaje2 = mensaje;
};
void Facebook::setMessageTecnico(shared_ptr<SupportTechnical> objetotecnico, string mensaje){
    tecnico = objetotecnico;
    mensaje1=mensaje;

};


string Facebook::getMessageTecnico(){
    return mensaje1;


};

string Facebook::getMessageCliente(){
    return mensaje2;


};

string Facebook::notificar(){
    return "notificando por Facebook. ";

};
shared_ptr<Client> Facebook::getClient(){
    return cliente;
};
shared_ptr<SupportTechnical> Facebook::getTecnico(){
    return tecnico;

};



