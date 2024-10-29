#include <ListClientes.h>

ListClientes::ListClientes()
{
}

ListClientes::~ListClientes()
{
}

void ListClientes::addClient(shared_ptr<Client> client)
{
    listClients.push_back(client);
}

shared_ptr<Client> ListClientes::getClient(int idClient)
{
    for (const auto &client : listClients)
    {
        if (client->getid() == idClient)
        {
            return client;
        }
    }
    return nullptr;
}

vector<shared_ptr<Client>> ListClientes::getClients()
{
    return listClients;
}

void ListClientes::showAllClientsInfo()
{
    for (const auto &client : listClients)
    {
        client->clienteinfo();
    }
}

void ListClientes::showAllClientsInfo(int idClient)
{
    for (const auto &client : listClients)
    {
        if (client->getid() == idClient)
        {
            client->clienteinfo();
        }
    }
}