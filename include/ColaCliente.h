#ifndef COLACLIENTE_H
#define COLACLIENTE_H

#include <queue>
#include <memory>
#include <Client.h>
class Client;

class ColaCliente {
private:
    queue<shared_ptr<Client>> ColaClientes;
    vector<shared_ptr<Client>> clientesAtendidos;

    

public:
    ColaCliente();
    ~ColaCliente();
    void agregarCliente(shared_ptr<Client> cliente);
    shared_ptr<Client> ObtenerClienteDeCola();
    void EliminarClienteDeCola();
    void MostrarClienteAtendidos(); // Método para mostrar clientes atendidos a partir de los que marca
    void marcarClientesAtendidos(shared_ptr<Client> cliente);//marcar clientes ya atendidos
    void mostrarClientesPendientes();//mostrar clientes pendientes
    void mostrarClientesActual(std::shared_ptr<Client> objetocliente); //mostrar cliente para atender


    shared_ptr<Client> BuscarClientePorID(int idCliente);


    bool IsEmpty();

};

#endif
