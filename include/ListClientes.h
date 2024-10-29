#ifndef LISTCLIENTES_H
#define LISTCLIENTES_H

#include <memory>
#include <vector>
#include <Client.h>

class ListClientes
{
private:
    vector<shared_ptr<Client>> listClients;

public:
    ListClientes();
    ~ListClientes();

    void addClient(shared_ptr<Client> client);
    shared_ptr<Client> getClient(int idClient);
    vector<shared_ptr<Client>> getClients();
    void showAllClientsInfo();
    void showAllClientsInfo(int idClient);};

#endif
