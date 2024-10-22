//FALTA AGREGAR PATRONNN PARA VER POR DONDE ENVIAR LOS MENSAJE WHATSAPP, FACEBOOK, INSTAGRAM...
//AGREGAR METODO PARA ACTUALIZAR EL TICKET, YA SEA CLIENTE: ASUNTO, PRIORIDAD ETC o TECNICO: CAMBIAR ESTADO



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

int main() {
    shared_ptr<ColaCliente> queueclientes = make_shared<ColaCliente>();
    shared_ptr<ListaTickets> listadetickets = make_shared<ListaTickets>();
    shared_ptr<IMessage> objetomensaje;


    shared_ptr<Client> objetocliente;
    shared_ptr<SupportTechnical> tecnico;
    shared_ptr<Ticket> ticket;



    int opcion;
    string name1, name2, telefono;
    int dni;
    string asunto, notificaciones;
    string valor,estado;
    vector<shared_ptr<Ticket>> ticketsCliente;


    do {
        cout << ".                                       SISTEMA DE TICKETS              ." << endl;
        cout << "1- Ingrese el cliente." << endl;
        cout << "2- Ingrese el tecnico." << endl;
        cout << "3- Cree el ticket asociado al cliente." << endl;
        cout << "4- Mostrar cliente que esta para atender." << endl;
        cout << "5- Mostrar clientes pendientes para atender." << endl;
        cout << "6- Mostrar clientes ya atendidos." << endl;
        cout << "7- Tecnico atiende Ticket del cliente actual." << endl;
        cout << "8- Mostrar Tickets del cliente actual." << endl;
        cout << "9- Dar de baja cliente una vez que termino de atender los tickets." << endl;
        cout << "10- Cliente envia mensaje desde el Ticket." << endl;
        cout << "11- Mostrar mensajes de los tickets." << endl;
        cout << "12- Cambia el estado de un ticket especifico." << endl;
        cout << "0- Salir." << endl;
        cout << "Opcion: "; cin >> opcion;
        cin.ignore();  // Para evitar que se salte la entrada de getline

        switch (opcion) {
        case 1:
            objetocliente = make_shared<Client>();
            cout << "Nombre del cliente: "; getline(cin, name1);
            cout << "Dni del cliente: "; cin >> dni;
            cin.ignore();  // Para evitar que se salte el asunto
            objetocliente->setname(name1);
            objetocliente->setdni(dni);
            queueclientes->agregarCliente(objetocliente);
            cout << "Cliente agregado a la cola!" << endl;
            break;

        case 2:
            tecnico = make_shared<SupportTechnical>();
            cout << "Nombre del tecnico: "; getline(cin, name2);
            cout << "Telefono del tecnico: "; getline(cin,telefono);
            tecnico->setname(name2);
            tecnico->settelefono(telefono);
            cout << "Tecnico creado!" << endl;
            break;
        case 3:
        if (!queueclientes->IsEmpty()) {
            cout << "Lista de clientes en la cola: " << endl;
            queueclientes->mostrarClientesPendientes(); // Mostrar todos los clientes pendientes en la cola
            
            int idCliente;
            cout << "Ingrese el ID del cliente para crear tickets: "; 
            cin >> idCliente;
            cin.ignore();

            // Buscar al cliente en la cola
            shared_ptr<Client> clienteSeleccionado = queueclientes->BuscarClientePorID(idCliente);
            if (clienteSeleccionado != nullptr) {
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
    

            break;



        case 4:
            if(!queueclientes->IsEmpty()){

            objetocliente = queueclientes->ObtenerClienteDeCola(); 
            queueclientes->mostrarClientesActual(objetocliente);

        }else {
                cout << "No hay clientes en la cola." << endl;
            }

            break;

        case 5:
        if(!queueclientes->IsEmpty()){
            objetocliente = queueclientes->ObtenerClienteDeCola(); 
            queueclientes->mostrarClientesPendientes();

        }else {
                cout << "No hay clientes en la cola." << endl;
            }
        
        

            break;

        case 6:
            queueclientes->MostrarClienteAtendidos();

            break;
        
        
         case 7: // Atender Ticket del cliente
            if (!queueclientes->IsEmpty()) {
                objetocliente = queueclientes->ObtenerClienteDeCola(); // Obtener cliente de la cola
                ticketsCliente = listadetickets->ObtenerTickets(objetocliente); // Obtener los tickets del cliente

                // Buscar el primer ticket que esté abierto
                shared_ptr<Ticket> ticket = nullptr;
                for (auto& t : ticketsCliente) {
                    if (t->getEstado() == "abierto") {
                        ticket = t; // Asignar el ticket abierto
                        break;
                    }
                }

                if (ticket) {
                    cout << "Atendiendo al cliente: " << objetocliente->getname() << endl;
                    cout << "Ticket " << ticket->getid() << " - Asunto: " << ticket->getincidente()->getasunto() << endl;

                    string mensajeTecnico;
                    cout << "Ingrese mensaje del tecnico "<< tecnico->getname()<<  ": ";
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
            break;




        case 8: // Mostrar Tickets del primer cliente de la cola
            if (!queueclientes->IsEmpty()) {
                // Obtener el primer cliente de la cola sin eliminarlo
                shared_ptr<Client> primerCliente = queueclientes->ObtenerClienteDeCola();

                // Obtener los tickets del primer cliente de la cola
                ticketsCliente = listadetickets->ObtenerTickets(primerCliente);

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
            break;


        case 9: // Dar de baja al cliente una vez que terminó de atender los tickets

        if (!queueclientes->IsEmpty()){
             shared_ptr<Client> objetocliente = queueclientes->ObtenerClienteDeCola();
            if (objetocliente && listadetickets->TodosTicketsCerrados(objetocliente)) {
                cout << "Todos los tickets del cliente " << objetocliente->getname() << " han sido atendidos." << endl;

                // Mover a la lista de clientes atendidos
                queueclientes->marcarClientesAtendidos(objetocliente);

                // Eliminar al cliente de la cola
                queueclientes->EliminarClienteDeCola(); 
            } else {
                cout << "Aun hay tickets abiertos para este cliente, no se puede eliminar." << endl;
            }

        }else {
                cout << "No hay clientes en la cola." << endl;
            }
        
        
            break;


        case 10: // Enviar mensaje desde el cliente
        if (!queueclientes->IsEmpty()) { // Verificamos si la cola no está vacía
            // Obtener el primer cliente de la cola
            objetocliente = queueclientes->ObtenerClienteDeCola();  // Usamos 'primerCliente' o 'front' para obtener el primero sin eliminarlo
            
            cout << "Cliente actual: " << objetocliente->getname() << endl;
            
            ticketsCliente = listadetickets->ObtenerTickets(objetocliente);
            for(const auto ticket:ticketsCliente){

                if (ticket && ticket->getEstado() == "abierto") {
                    string mensajeCliente;
                    cout << "Ingrese mensaje del cliente del ticket " <<ticket->getincidente()->getasunto()<< " : " << endl; 
                    getline(cin, mensajeCliente);

                    auto objetomensaje = objetocliente->EnviarMensaje(objetocliente, mensajeCliente, notificaciones);
                    ticket->agregarMensaje(objetomensaje);
                    ticket->AlertTechnical();
                    break;
                    } 
                else {
                    cout << "No hay tickets abiertos para este cliente." << endl;
                }


            }
        } else {
            cout << "No hay clientes en la cola." << endl;
        }
    break;

        case 11:
        if (!queueclientes->IsEmpty()) { // Verificamos si la cola no está vacía
            // Obtener el primer cliente de la cola
            objetocliente = queueclientes->ObtenerClienteDeCola();  // Usamos 'primerCliente' o 'front' para obtener el primero sin eliminarlo
            
            cout << "Cliente actual: " << objetocliente->getname() << endl;
            
            listadetickets->MensajesClienteActual(objetocliente);
            
        } else {
            cout << "No hay clientes en la cola." << endl;
        }

            break;

        case 12: // Cambiar el estado de un ticket específico del primer cliente de la cola
    if (!queueclientes->IsEmpty()) {
        // Obtener el primer cliente de la cola sin eliminarlo
        shared_ptr<Client> primerCliente = queueclientes->ObtenerClienteDeCola();

        // Obtener los tickets del primer cliente de la cola
        ticketsCliente = listadetickets->ObtenerTickets(primerCliente);

        if (!ticketsCliente.empty()) {
            cout << "Tickets del cliente: " << primerCliente->getname() << endl;
            
            // Mostrar los tickets disponibles
            for (const auto& ticket : ticketsCliente) {
                cout << "Ticket " << ticket->getid() << " - Asunto: " << ticket->getincidente()->getasunto() 
                     << " - Estado: " << ticket->getEstado() << endl;
            }

            // Solicitar el ID del ticket que se desea modificar
            int idTicket;
            cout << "Ingrese el ID del ticket que desea modificar: "; 
            cin >> idTicket;

            // Buscar el ticket con el ID ingresado
            bool ticketEncontrado = false;
            for (auto& ticket : ticketsCliente) {
                if (ticket->getid() == idTicket) {
                    ticketEncontrado = true;
                    
                    // Solicitar el nuevo estado del ticket
                    string nuevoEstado;
                    cout << "Ingrese el nuevo estado del ticket ("<< ticket->getincidente()->getasunto()  << ") , (abierto/cerrado): ";
                    cin >> nuevoEstado;

                    // Validar el estado ingresado
                    if (nuevoEstado == "abierto" || nuevoEstado == "cerrado") {
                        ticket->setEstado(nuevoEstado);
                        cout << "Estado del Ticket " << ticket->getid() << " actualizado a " << nuevoEstado << "." << endl;
                    } else {
                        cout << "Estado no válido. Debe ser 'abierto', 'en proceso' o 'cerrado'." << endl;
                    }
                    break;
                }
            }

            if (!ticketEncontrado) {
                cout << "No se encontró el ticket con el ID ingresado." << endl;
            }
        } else {
            cout << "El cliente no tiene tickets." << objetocliente->getname() << endl;
        }
    } else {
        cout << "No hay clientes en la cola." << endl;
    }
    break;


        



        case 0:
            cout << "Saliendo del programa." << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
            break;
        }
    } while (opcion != 0);

    return 0;
}
