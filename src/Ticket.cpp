#include <Ticket.h>

int Ticket::contador = 0; // Inicialización del contador

Ticket::Ticket(shared_ptr<Client> objetocliente, string asunto)
{
    this->id = ++contador;
    cliente = objetocliente;
    incidente = make_shared<Incidente>(asunto, objetocliente);
}
Ticket::~Ticket() {
};

void Ticket::AddTecnico(shared_ptr<SupportTechnical> objetotecnico)
{
    tecnico = objetotecnico;
}

void Ticket::setnotificaciones(string notificaciones)
{
    this->notificaciones = notificaciones;
}

string Ticket::getnotificaciones()
{
    return notificaciones;
}

int Ticket::getid()
{
    return id;
}

void Ticket::mostrarTicket()
{
    incidente->Incidenteinfo();
    cliente->clienteinfo();
    if (tecnico != nullptr)
        tecnico->tecnicoinfo();
    else
    {
        cout << "tecnico no asignado todavia. " << endl;
    }
    cout << "estado del ticket: " << getEstado() << endl;

    cout << "------------------" << endl;
}

shared_ptr<SupportTechnical> Ticket::gettecnico()
{
    return tecnico;
};

shared_ptr<Client> Ticket::getcliente()
{
    return cliente;
}

shared_ptr<Incidente> Ticket::getincidente()
{
    return incidente;
}

void Ticket::setEstado(string estado)
{
    this->estado = estado;
}

string Ticket::getEstado()
{
    return estado;
}

void Ticket::agregarMensaje(shared_ptr<IMessage> objetomensajee)
{
    listamensajes.push_back(objetomensajee);
}

void Ticket::mostrarmensajes()
{
    if (listamensajes.empty())
    {
        std::cout << "No hay mensajes para este ticket." << std::endl;
        return;
    }

    for (const auto &msg : listamensajes)
    {
        if (!msg)
        { // Verifica que el mensaje no sea nulo
            std::cerr << "Error: mensaje nulo en la lista de mensajes." << std::endl;
            continue; // Salta a la siguiente iteración
        }

        if (msg->getTecnico() != nullptr)
        { // Verifica que el técnico no sea nulo
            std::cout << "Mensaje de tecnico " << msg->getTecnico()->getname() << ": "
                      << msg->getMessageTecnico() << std::endl;
        }

        if (msg->getClient() != nullptr)
        { // Verifica que el cliente no sea nulo
            std::cout << "Mensaje del cliente " << msg->getClient()->getname() << ": "
                      << msg->getMessageCliente() << std::endl;
        }
        std::cout << msg->notificar();
        std::cout << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}

void Ticket::AlertClient()
{
    cliente->Alert();
}

void Ticket::AlertTechnical()
{
    if (tecnico != nullptr)
        tecnico->Alert();
    else
    {
        cout << "tecnico no asignado todavia. " << endl;
    }
}