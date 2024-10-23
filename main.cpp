#include <iostream>
#include <vector>
#include <memory>
#include <Client.h>
#include <ColaCliente.h>
#include <Incidente.h>
#include <SupportTechnical.h>
#include <Ticket.h>
#include <ListaTickets.h>
#include <IMessage.h>
#include <Whatsapp.h>
#include <Facebook.h>
#include <string>

using namespace std;

void ingresarCliente(shared_ptr<ColaCliente>& queueclientes, shared_ptr<Client>& objetocliente) {
    string name1;
    int dni;
    
    // Inicializar el cliente si no lo está
    if (!objetocliente) {
        objetocliente = make_shared<Client>();
    }
    
    cout << "Nombre del cliente: "; getline(cin, name1);
    cout << "Dni del cliente: "; cin >> dni;
    cin.ignore();
    objetocliente->setname(name1);
    objetocliente->setdni(dni);
    queueclientes->agregarCliente(objetocliente);
    cout << "Cliente agregado a la cola!" << endl;
}

void ingresarTecnico(shared_ptr<SupportTechnical>& tecnico) {
    string name2, telefono;
    
    // Inicializar el técnico si no lo está
    if (!tecnico) {
        tecnico = make_shared<SupportTechnical>();
    }
    
    cout << "Nombre del tecnico: "; getline(cin, name2);
    cout << "Telefono del tecnico: "; getline(cin, telefono);
    tecnico->setname(name2);
    tecnico->settelefono(telefono);
    cout << "Tecnico creado!" << endl;
}

void crearTicket(shared_ptr<ColaCliente>& queueclientes, shared_ptr<ListaTickets>& listadetickets, shared_ptr<SupportTechnical>& tecnico) {
    if (!queueclientes->IsEmpty()) {
        queueclientes->mostrarClientesPendientes();
        int idCliente;
        cout << "Ingrese el ID del cliente para crear tickets: "; 
        cin >> idCliente;
        cin.ignore();

        shared_ptr<Client> clienteSeleccionado = queueclientes->BuscarClientePorID(idCliente);
        if (clienteSeleccionado != nullptr) {
            string asunto, notificaciones, valor;
            do {
                cout << "Asunto del problema: "; getline(cin, asunto);
                do {
                    cout << "Por donde desea que se envien las notificaciones? (Whatsapp/Facebook): ";
                    getline(cin, notificaciones);
                    if (notificaciones != "Whatsapp" && notificaciones != "Facebook") {
                        cout << "Opcion no valida. Intente nuevamente." << endl;
                    }
                } while (notificaciones != "Whatsapp" && notificaciones != "Facebook");

                shared_ptr<Ticket> ticket = tecnico->CrearTicket(clienteSeleccionado, asunto, notificaciones);
                listadetickets->agregarTicket(ticket);
                ticket->setEstado("abierto");
                cout << "Ticket creado para el cliente!" << endl;

                cout << "Desea crear otro ticket para este cliente? (si/no): "; cin >> valor;
                cin.ignore();  
            } while (valor != "no");
        } else {
            cout << "Cliente no encontrado en la cola." << endl;
        }
    } else {
        cout << "No hay clientes en la cola." << endl;
    }
}

void mostrarClienteParaAtender(shared_ptr<ColaCliente>& queueclientes, shared_ptr<Client>& objetocliente) {
    if (!queueclientes->IsEmpty()) {
        objetocliente = queueclientes->ObtenerClienteDeCola(); 
        queueclientes->mostrarClientesActual(objetocliente);
    } else {
        cout << "No hay clientes en la cola." << endl;
    }
}

void mostrarClientesPendientes(shared_ptr<ColaCliente>& queueclientes) {
    if (!queueclientes->IsEmpty()) {
        queueclientes->mostrarClientesPendientes();
    } else {
        cout << "No hay clientes en la cola." << endl;
    }
}

void mostrarClientesAtendidos(shared_ptr<ColaCliente>& queueclientes) {
    queueclientes->MostrarClienteAtendidos();
}

void atenderTicket(shared_ptr<ColaCliente>& queueclientes, shared_ptr<ListaTickets>& listadetickets, shared_ptr<SupportTechnical>& tecnico, shared_ptr<IMessage>& objetomensaje) {
    if (!queueclientes->IsEmpty()) {
        shared_ptr<Client> objetocliente = queueclientes->ObtenerClienteDeCola();
        vector<shared_ptr<Ticket>> ticketsCliente = listadetickets->ObtenerTickets(objetocliente);

        shared_ptr<Ticket> ticket = nullptr;
        for (auto& t : ticketsCliente) {
            if (t->getEstado() == "abierto") {
                ticket = t;
                break;
            }
        }

        if (ticket) {
            cout << "Atendiendo al cliente: " << objetocliente->getname() << endl;
            cout << "Ticket " << ticket->getid() << " - Asunto: " << ticket->getincidente()->getasunto() << endl;

            string mensajeTecnico;
            cout << "Ingrese mensaje del tecnico " << tecnico->getname() << ": ";
            getline(cin, mensajeTecnico);

            tecnico->Atender(tecnico, ticketsCliente);
            objetomensaje = tecnico->EnviarMensaje(tecnico, mensajeTecnico);
            ticket->agregarMensaje(objetomensaje);
            ticket->AlertClient();
        } else {
            cout << "No hay tickets abiertos para el cliente " << objetocliente->getname() << endl;
        }
    } else {
        cout << "No hay clientes en la cola." << endl;
    }
}

void mostrarTicketsCliente(shared_ptr<ColaCliente>& queueclientes, shared_ptr<ListaTickets>& listadetickets) {
    if (!queueclientes->IsEmpty()) {
        shared_ptr<Client> primerCliente = queueclientes->ObtenerClienteDeCola();
        vector<shared_ptr<Ticket>> ticketsCliente = listadetickets->ObtenerTickets(primerCliente);

        if (!ticketsCliente.empty()) {
            cout << "Tickets del cliente: " << primerCliente->getname() << endl;
            for (const auto& ticket : ticketsCliente) {
                ticket->mostrarTicket();
            }
        } else {
            cout << "El cliente no tiene tickets." << endl;
        }
    } else {
        cout << "No hay clientes en la cola." << endl;
    }
}

void darBajaCliente(shared_ptr<ColaCliente>& queueclientes, shared_ptr<ListaTickets>& listadetickets) {
    if (!queueclientes->IsEmpty()) {
        shared_ptr<Client> objetocliente = queueclientes->ObtenerClienteDeCola();
        if (listadetickets->TodosTicketsCerrados(objetocliente)) {
            cout << "Todos los tickets del cliente " << objetocliente->getname() << " han sido atendidos." << endl;
            queueclientes->marcarClientesAtendidos(objetocliente);
        } else {
            cout << "Aun hay tickets abiertos para este cliente." << endl;
        }
    } else {
        cout << "No hay clientes en la cola." << endl;
    }
}

int main() {
    shared_ptr<ColaCliente> queueclientes = make_shared<ColaCliente>();
    shared_ptr<ListaTickets> listadetickets = make_shared<ListaTickets>();
    shared_ptr<IMessage> objetomensaje;

    shared_ptr<Client> objetocliente;
    shared_ptr<SupportTechnical> tecnico;

    int opcion;

    do {
        cout << ".   SISTEMA DE TICKETS   ." << endl;
        cout << "1- Ingrese el cliente." << endl;
        cout << "2- Ingrese el tecnico." << endl;
        cout << "3- Cree el ticket asociado al cliente." << endl;
        cout << "4- Mostrar cliente que esta para atender." << endl;
        cout << "5- Mostrar clientes pendientes para atender." << endl;
        cout << "6- Mostrar clientes ya atendidos." << endl;
        cout << "7- Tecnico atiende Ticket del cliente actual." << endl;
        cout << "8- Mostrar Tickets del cliente actual." << endl;
        cout << "9- Dar de baja cliente una vez que termino de atender los tickets." << endl;
        cout << "0- Salir." << endl;
        cout << "Opcion: "; cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: ingresarCliente(queueclientes, objetocliente); break;
            case 2: ingresarTecnico(tecnico); break;
            case 3: crearTicket(queueclientes, listadetickets, tecnico); break;
            case 4: mostrarClienteParaAtender(queueclientes, objetocliente); break;
            case 5: mostrarClientesPendientes(queueclientes); break;
            case 6: mostrarClientesAtendidos(queueclientes); break;
            case 7: atenderTicket(queueclientes, listadetickets, tecnico, objetomensaje); break;
            case 8: mostrarTicketsCliente(queueclientes, listadetickets); break;
            case 9: darBajaCliente(queueclientes, listadetickets); break;
            case 0: cout << "Saliendo del programa." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
