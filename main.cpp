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
#define MAX_NODES 7


void ingresarCliente(shared_ptr<ColaCliente> &queueclientes, shared_ptr<Client> &objetocliente)
{
    string name1;
    int dni;


    
    objetocliente = make_shared<Client>();
    

    cout << "Nombre del cliente: ";
    getline(cin, name1);
    cout << "Dni del cliente: ";
    cin >> dni;
    cin.ignore();
    objetocliente->setname(name1);
    objetocliente->setdni(dni);
    queueclientes->agregarCliente(objetocliente);
    cout << "Cliente agregado a la cola!" << endl;

}

void ingresarTecnico(shared_ptr<SupportTechnical> &tecnico)
{
    string name2, telefono;

    // Inicializar el técnico si no lo está

    tecnico = make_shared<SupportTechnical>();
    

    cout << "Nombre del tecnico: ";
    getline(cin, name2);
    cout << "Telefono del tecnico: ";
    getline(cin, telefono);
    tecnico->setname(name2);
    tecnico->settelefono(telefono);
    cout << "Tecnico creado!" << endl;

}

void crearTicket(shared_ptr<ColaCliente> &queueclientes, shared_ptr<ListaTickets> &listadetickets, shared_ptr<SupportTechnical> &tecnico)
{
    if (!queueclientes->IsEmpty())
    {
        queueclientes->mostrarClientesPendientes();
        int idCliente;
        cout << "Ingrese el ID del cliente para crear tickets: ";
        cin >> idCliente;
        cin.ignore();

        shared_ptr<Client> clienteSeleccionado = queueclientes->BuscarClientePorID(idCliente);
        if (clienteSeleccionado != nullptr)
        {
            string asunto, notificaciones, valor;
            do
            {
                cout << "Asunto del problema: ";
                getline(cin, asunto);
                do
                {
                    cout << "Por donde desea que se envien las notificaciones? (Whatsapp/Facebook): ";
                    getline(cin, notificaciones);
                    if (notificaciones != "Whatsapp" && notificaciones != "Facebook")
                    {
                        cout << "Opcion no valida. Intente nuevamente." << endl;
                    }
                } while (notificaciones != "Whatsapp" && notificaciones != "Facebook");

                shared_ptr<Ticket> ticket = tecnico->CrearTicket(clienteSeleccionado, asunto, notificaciones);
                listadetickets->agregarTicket(ticket);
                ticket->setEstado("abierto");
                cout << "Ticket creado para el cliente!" << endl;

                cout << "Desea crear otro ticket para este cliente? (si/no): ";
                cin >> valor;
                cin.ignore();
            } while (valor != "no");
        }
        else
        {
            cout << "Cliente no encontrado en la cola." << endl;
        }
    }
    else
    {
        cout << "No hay clientes en la cola." << endl;
    }
}

void mostrarClienteParaAtender(shared_ptr<ColaCliente> &queueclientes, shared_ptr<Client> &objetocliente)
{
    if (!queueclientes->IsEmpty())
    {
        objetocliente = queueclientes->ObtenerClienteDeCola();
        queueclientes->mostrarClientesActual(objetocliente);
    }
    else
    {
        cout << "No hay clientes en la cola." << endl;
    }
}

void mostrarClientesPendientes(shared_ptr<ColaCliente> &queueclientes)
{
    if (!queueclientes->IsEmpty())
    {
        queueclientes->mostrarClientesPendientes();
    }
    else
    {
        cout << "No hay clientes en la cola." << endl;
    }
}

void mostrarClientesAtendidos(shared_ptr<ColaCliente> &queueclientes)
{
    queueclientes->MostrarClienteAtendidos();

}

void atenderTicket(shared_ptr<ColaCliente> &queueclientes, shared_ptr<ListaTickets> &listadetickets, shared_ptr<SupportTechnical> &tecnico, shared_ptr<IMessage> &objetomensaje)
{
    if (!queueclientes->IsEmpty())
    {
        shared_ptr<Client> objetocliente = queueclientes->ObtenerClienteDeCola();
        vector<shared_ptr<Ticket>> ticketsCliente = listadetickets->ObtenerTickets(objetocliente);

        shared_ptr<Ticket> ticket = nullptr;
        for (auto &t : ticketsCliente)
        {
            if (t->getEstado() == "abierto")
            {
                ticket = t;
                break;
            }
        }

        if (ticket)
        {
            cout << "Atendiendo al cliente: " << objetocliente->getname() << endl;
            cout << "Ticket " << ticket->getid() << " - Asunto: " << ticket->getincidente()->getasunto() << endl;

            string mensajeTecnico;
            cout << "Ingrese mensaje del tecnico " << tecnico->getname() << ": ";
            getline(cin, mensajeTecnico);

            tecnico->Atender(tecnico, ticketsCliente);
            objetomensaje = tecnico->EnviarMensaje(tecnico, mensajeTecnico);
            ticket->agregarMensaje(objetomensaje);
            ticket->AlertClient();
        }
        else
        {
            cout << "No hay tickets abiertos para el cliente " << objetocliente->getname() << endl;
        }
    }
    else
    {
        cout << "No hay clientes en la cola." << endl;
    }
}

void mostrarTicketsCliente(shared_ptr<ColaCliente> &queueclientes, shared_ptr<ListaTickets> &listadetickets)
{
    if (!queueclientes->IsEmpty())
    {
        shared_ptr<Client> primerCliente = queueclientes->ObtenerClienteDeCola();
        vector<shared_ptr<Ticket>> ticketsCliente = listadetickets->ObtenerTickets(primerCliente);

        if (!ticketsCliente.empty())
        {
            cout << "Tickets del cliente: " << primerCliente->getname() << endl;
            for (const auto &ticket : ticketsCliente)
            {
                ticket->mostrarTicket();
            }
        }
        else
        {
            cout << "El cliente no tiene tickets." << endl;
        }
    }
    else
    {
        cout << "No hay clientes en la cola." << endl;
    }
}

void darBajaCliente(shared_ptr<ColaCliente> &queueclientes, shared_ptr<ListaTickets> &listadetickets)
{
    if (!queueclientes->IsEmpty())
    {
        shared_ptr<Client> objetocliente = queueclientes->ObtenerClienteDeCola();
        if (listadetickets->TodosTicketsCerrados(objetocliente))
        {
            cout << "Todos los tickets del cliente " << objetocliente->getname() << " han sido atendidos." << endl;
            queueclientes->EliminarClienteDeCola();
        }
        else
        {
            cout << "Aun hay tickets abiertos para este cliente." << endl;
        }
    }
    else
    {
        cout << "No hay clientes en la cola." << endl;
    }
}

void enviarMensajeCliente(shared_ptr<ColaCliente> &queueclientes, shared_ptr<Client> &objetocliente,vector<shared_ptr<Ticket>> &ticketsCliente,shared_ptr<ListaTickets>& listadetickets, string notificaciones){
           // Enviar mensaje desde el cliente
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
}

void mostrarMensajesTicket(shared_ptr<ColaCliente> &queueclientes, shared_ptr<Client> &objetocliente, shared_ptr<ListaTickets> &listadetickets){
        if (!queueclientes->IsEmpty()) { // Verificamos si la cola no está vacía
            // Obtener el primer cliente de la cola
            objetocliente = queueclientes->ObtenerClienteDeCola();  // Usamos 'primerCliente' o 'front' para obtener el primero sin eliminarlo
            
            cout << "Cliente actual: " << objetocliente->getname() << endl;
            
            listadetickets->MensajesClienteActual(objetocliente);
            
        } else {
            cout << "No hay clientes en la cola." << endl;
        }
}

// Cambiar el estado de un ticket específico del primer cliente de la cola
void cambiarestadoTicket(shared_ptr<ColaCliente> &queueclientes, vector<shared_ptr<Ticket>> &ticketsCliente, shared_ptr<ListaTickets> &listadetickets, shared_ptr<Client> &objetocliente){
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
}

int minDistance(int acumuladorDistancia[], bool acumuladorNodosVisitados[])
{
    /**
     * Declaramos variable distancia para saber cual va a ser el de menor distancia
     * Y declaramos que nodo es el de menor distancia
     */
    int distancia = INT_MAX, nodo_menor_distancia;

    /**
     * Valida si el nodo fue visitado y ademas si su distancia es menor a INFINITO (esto lo es un numero muy grande)
     * 
     * Explicación:
     * Empezamos por el nodo 0 entonces:
     * Sabemos que el nodo 0 todavía no fue visitado, así que se valida una condición
     * Al empezar por el nodo 0, como vimos antes, se estableció que la distancia en el nodo 0 es 0,
     * entonces esto genera que se cumpla la segunda condición porque 0 es menor a INFINITO
     * 
     * Ya las siguientes iteraciones no se cumplen porque se seteo que la distancia menor es 0, entonces no hay otro
     * nodo con distancia menor a 0 porque las distancias estan inicializadas en INFINITO ademas de que los otros
     * todavía no fueron visitados
     *  
     */
    for (int nodo = 0; nodo < MAX_NODES; nodo++)
    {
        if (acumuladorNodosVisitados[nodo] == false && acumuladorDistancia[nodo] <= distancia)
        {
            distancia = acumuladorDistancia[nodo];
            nodo_menor_distancia = nodo;
        }
    }

    return nodo_menor_distancia;
}

void printSolution(int acumuladorDistancia[])
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < MAX_NODES; i++)
    {
        cout << i << " \t\t\t\t" << acumuladorDistancia[i] << endl;
    }
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int src)
{
    /*
        Declaración de los acumuladores de distancia
        Y de los nodos que fueron visitados
    */   
    int acumuladorDistancia[MAX_NODES];
    bool acumuladorNodosVisitados[MAX_NODES];

    /**
     * Inicialización de acumuladores en valores predeterminados
     */
    for (int i = 0; i < MAX_NODES; i++)
    {
        acumuladorDistancia[i] = INT_MAX;
        acumuladorNodosVisitados[i] = false;
    }

    /**
     * Se establece en el acumulador que el nodo en el que se inicia es 0 porque no tiene distancia
     * porque el nodo en donde se empieza es siempre 0
     */
    acumuladorDistancia[src] = 0;

    /**
     * Contenedor de toda la lógica de Dijkstra
     */
    for (int count = 0; count < MAX_NODES - 1; count++)
    {
        /**
         * Función que calcula que nodo es el mas cercano, primero siempre va a empezar por el nodo en el que
         * se inició
         */
        int nodoCercano = minDistance(acumuladorDistancia, acumuladorNodosVisitados);

        /**
         * Se establece el nodo como visitado
         */
        acumuladorNodosVisitados[nodoCercano] = true;

        /**
         * Lógica para saber cual es el camino mas corto que puede ir el nodo src hasta el siguiente nodo
         * 
         * Explicación:
         * Sabemos entonces que el primer nodo que se quiere saber es el 0, o sea, de nodo 0 ir a nodo 0
         * 
         * Podemos ver que la primer condición no se cumple, esto porque el nodo 0 fue visitado, entonces pasa a la 
         * siguiente iteración, el nodo 1 sabemos que no fue visitado se cumple primera condición, la segunda tambien se cumple
         * esto porque hay una conexión entre el nodo 0 y el nodo 1 (ver grafo inicializado), la tercera condición se cumple
         * porque sabemos que la distancia del nodo 0 es 0, entonces es diferente a INFINITO, la 4ta condición se cumple porque
         * valida si la suma de la distancia del nodo 0 (que es 0) mas la distancia del nodo 0 al nodo 1 (que es 2), es menor
         * a la distancia acumulada del nodo 1 (que es INFINITO porque no se estableció todavía), entonces lo que hace
         * es inicializar la distancia del nodo 1 como la suma de la distancia del nodo 0 (que es 0) y la distancia del nodo 0 al nodo 1 (que es 2)
         * 
         * Y así verifica todo lo demas nodos. Cabe aclarar que el acumulador de distancias es a partir del nodo en el que se inicialize
         * 
         */
        for (int nodo = 0; nodo < MAX_NODES; nodo++)
        {
            if (
                !acumuladorNodosVisitados[nodo] &&
                graph[nodoCercano][nodo] &&
                acumuladorDistancia[nodoCercano] != INT_MAX &&
                acumuladorDistancia[nodoCercano] + graph[nodoCercano][nodo] < acumuladorDistancia[nodo])
            {
                acumuladorDistancia[nodo] = acumuladorDistancia[nodoCercano] + graph[nodoCercano][nodo];
            }
        }
    }

    /**
     * Muestra por pantalla las distancias a los diferentes nodos
     */
    printSolution(acumuladorDistancia);
}

void aloritmoDijkstra()
{
    // Inicialización y declaración de grafo
    int graph[MAX_NODES][MAX_NODES] = {
        // Nodo 0 y sus conexiones
        {0, 2, 6, 0, 0, 0, 0},
        // Nodo 1 y sus conexiones
        {2, 0, 0, 5, 0, 0, 0},
        // Nodo 2 y sus conexiones
        {6, 0, 0, 8, 0, 0, 0},
        // Nodo 3 y sus conexiones
        {0, 5, 8, 0, 10, 15, 0},
        // Nodo 4 y sus conexiones
        {0, 0, 0, 10, 0, 6, 2},
        // Nodo 5 y sus conexiones
        {0, 0, 0, 15, 6, 0, 6},
        // Nodo 6 y sus conexiones
        {0, 0, 0, 0, 2, 6, 0}};

    /**
     * Primer parametro el grafo
     * Segundo parámetro el nodo en el que se inicia
     */
    dijkstra(graph, 0);

}










int main() {
    shared_ptr<ColaCliente> queueclientes = make_shared<ColaCliente>();
    shared_ptr<ListaTickets> listadetickets = make_shared<ListaTickets>();
    shared_ptr<IMessage> objetomensaje;


    shared_ptr<Client> objetocliente;
    shared_ptr<SupportTechnical> tecnico;
    shared_ptr<Ticket> ticket;



    int opcion;

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
        cout << "13- Algoritmo Dijsktra." << endl;

        cout << "0- Salir." << endl;
        cout << "Opcion: "; cin >> opcion;
        cin.ignore();  // Para evitar que se salte la entrada de getline

        switch (opcion) {
        case 1:
            ingresarCliente(queueclientes, objetocliente);
            break;


        case 2:
            ingresarTecnico(tecnico);

            
            break;
        case 3:
            crearTicket(queueclientes, listadetickets, tecnico);
            break;

        case 4:
            mostrarClienteParaAtender(queueclientes, objetocliente);
            break;
        case 5:
            mostrarClientesPendientes(queueclientes);
            break;
        case 6:
            mostrarClientesAtendidos(queueclientes);
            break;
        case 7:
            atenderTicket(queueclientes, listadetickets, tecnico, objetomensaje);
            break;
        case 8:
            mostrarTicketsCliente(queueclientes, listadetickets);
            break;
        case 9:
            darBajaCliente(queueclientes, listadetickets);
            break;
        case 10:
        enviarMensajeCliente(queueclientes, objetocliente,ticketsCliente,listadetickets, notificaciones);
            break;

        case 11:
        mostrarMensajesTicket(queueclientes, objetocliente, listadetickets);

            break;

        case 12: 
        cambiarestadoTicket(queueclientes,ticketsCliente, listadetickets, objetocliente);
    
    break;

        case 13: 
            aloritmoDijkstra();
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
