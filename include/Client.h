#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include <IMessage.h>
#include <memory>
#include <Facebook.h>
#include <Whatsapp.h>

using namespace std;

class IMessage;
//hereda de la clase para obtener obtiene un shared_ptr que apunta al propio objeto (this)
class Client : public enable_shared_from_this<Client> {
private:
    int id;
    static int idCounter;
    string name;
    int dni;

public:
    Client();
    ~Client();
    void setname(string name);
    void setdni(int dni);
    int getid();
    string getname();
    int getdni();
    void clienteinfo();
    shared_ptr<IMessage> EnviarMensaje(shared_ptr<Client>& objetocliente, const string& mensajeTexto, string notificaciones);
    void Alert();
};

#endif
