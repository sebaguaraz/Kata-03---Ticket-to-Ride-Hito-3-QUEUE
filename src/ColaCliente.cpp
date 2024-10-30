#include <ColaCliente.h>


ColaCliente::ColaCliente() {}
ColaCliente::~ColaCliente() {}

void ColaCliente::agregarCliente(shared_ptr<Client> cliente) {
    ColaClientes.push(cliente);
}

shared_ptr<Client> ColaCliente::ObtenerClienteDeCola() {//obtiene el cliente de la cola
    if (!ColaClientes.empty()) {
        shared_ptr<Client> cliente = ColaClientes.front();
        //ColaClientes.pop();
        //marcarClientesAtendidos(cliente);//se deberia marcar el cliente si el tecnico ya lo atendio

        return cliente;
    } else {
        return nullptr;
    }
}

bool ColaCliente::IsEmpty() {
    return ColaClientes.empty();
}



void ColaCliente::mostrarClientesPendientes() {
    std::queue<std::shared_ptr<Client>> copiaCola = ColaClientes; // Hacer una copia de la cola original

    if (copiaCola.empty()) {
        std::cout << "No hay clientes pendientes." << std::endl;
        return;
    }

    std::cout << "Clientes pendientes:" << std::endl;
    while (!copiaCola.empty()) {
        std::shared_ptr<Client> cliente = copiaCola.front(); // Obtener el cliente en la parte delantera

            cliente->clienteinfo();
            copiaCola.pop(); // Eliminar de la copia
    }
}



//el vector "clientesAtendidos" marca el cliente una vez que se elimino de la cola, pasando el puntero cliente
void ColaCliente::marcarClientesAtendidos(shared_ptr<Client> cliente){
    clientesAtendidos.push_back(cliente);
};

void ColaCliente::EliminarClienteDeCola(){
    
        shared_ptr<Client> cliente = ColaClientes.front();
        ColaClientes.pop();
        marcarClientesAtendidos(cliente);//se deberia marcar el cliente si el tecnico ya lo atendio

        
    


}

void ColaCliente::MostrarClienteAtendidos(){

    if (clientesAtendidos.empty())
    {
        std::cout << "No hay clientes atendidos aun." << std::endl;
        return;
    }
    
     std::cout << "Clientes atendidos:" << std::endl;

    for (const auto clientes : clientesAtendidos)
    {
        clientes->clienteinfo();
    }
}

void ColaCliente::mostrarClientesActual(std::shared_ptr<Client> objetocliente){
    objetocliente->clienteinfo();
}; 




shared_ptr<Client> ColaCliente::BuscarClientePorID(int idCliente) {
    std::queue<shared_ptr<Client>> copiaCola = ColaClientes;  // Hacer una copia de la cola

    while (!copiaCola.empty()) {
        shared_ptr<Client> cliente = copiaCola.front();  // Obtener el primer cliente
        if (cliente->getid() == idCliente) {
            return cliente;  // Cliente encontrado
        }
        copiaCola.pop();  // Eliminar el cliente ya procesado
    }
    return nullptr;  // Si no se encuentra el cliente
}
