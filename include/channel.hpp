#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <set>
#include "clients.hpp"

class Channel {
public:
    Channel(const std::string& name, Client* creator);
    ~Channel();

    std::string getName() const; //channel name
    bool hasClient(const Client* client) const; //look for client
    bool hasOperator(const Client* client) const; // check if client is operator
    bool addClient(Client* client);
    bool removeClient(Client* client);
    bool makeOperator(Client* client);
    bool removeOperator(Client* client);
    bool kickClient(Client* client);
    bool joinChannel(Client* client);
    std::string getClientList() const;
    std::string getOperatorList() const;
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const; // current channel size
    int getMaxSize() const; // channel max size

private:
    std::string name_;
    Client* creator_;
    std::vector<Client*> clients_;
    std::set<Client*> operators_;
    int maxSize_;
};

#endif
