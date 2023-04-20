#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <set>
#include "clients.hpp"

class Channel {
public:
    Channel(const std::string& name, Clients* creator);
    ~Channel();

    std::string getName() const; //channel name
    bool hasClient(const Clients* client) const; //look for client
    bool hasOperator(const Clients* client) const; // check if client is operator
    bool addClient(Clients* client);
    bool removeClient(Clients* client);
    bool makeOperator(Clients* client);
    bool removeOperator(Clients* client);
    bool kickClient(Clients* client);
    bool joinChannel(Clients* client);
    std::string getClientList() const;
    std::string getOperatorList() const;
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const; // current channel size
    int getMaxSize() const; // channel max size

private:
    std::string name_;
    Clients* creator_;
    std::vector<Clients*> clients_;
    std::set<Clients*> operators_;
    int maxSize_;
};

#endif
