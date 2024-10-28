#include <Client.h>

int Client::idCounter = 0;

Client::Client() {
    id = ++idCounter;
}
Client::~Client(){};

void Client::setname(string name) { this->name = name; }
void Client::setdni(int dni) { this->dni = dni; }

int Client::getid() { return id; }
string Client::getname() { return name; }
int Client::getdni() { return dni; }

void Client::clienteinfo() {
    cout << "**** DATOS CLIENTE: " << endl;
    cout << "Id: " << getid() << endl;
    cout << "Nombre: " << getname() << endl;
    cout << "DNI: " << getdni() << endl;
}

shared_ptr<IMessage> Client::EnviarMensaje(shared_ptr<Client> cliente, const string& mensajeTexto, string notificaciones) {
        // Crear un nuevo mensaje
        if (mensajeTexto.empty()) {
        cout << "El mensajeTexto no puede estar vacio." << endl;
        return nullptr; // O maneja de otra manera si es necesario
    }

    cout << "Enviando mensaje (" << mensajeTexto << ") de parte de: " << cliente->getname() << " por " << notificaciones << endl;

    if(notificaciones == "Whatsapp"){

        shared_ptr<IMessage> objeto = make_shared<Whatsapp>();
        objeto->setMessageClient(shared_from_this(), mensajeTexto);
        return objeto;

    }

        if(notificaciones == "Facebook"){

        shared_ptr<IMessage> objeto = make_shared<Facebook>();
        objeto->setMessageClient(shared_from_this(), mensajeTexto);
        return objeto;

    }
     cout << "Notificacion desconocida: " << notificaciones << endl;
     return nullptr; // Retorna nullptr si la notificación no es válida
    
}

void Client::Alert(){
    cout << "Alertando al cliente " << getname() << " de un mensaje del tecnico..." << endl;
}