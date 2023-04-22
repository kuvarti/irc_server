#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <unistd.h>
#include "clients.hpp"

class Channel {
public:
    Channel(const std::string& name, const std::string& topic, Clients* creator);
    ~Channel();

    void joinClient(Clients* client);
    void leaveClient(Clients* client);
    void sendMsg(const std::string& message, Clients* sender);

    const std::string& getName() const;
    void setName(const std::string& name);

    Clients* getCreator() const;
    void setCreator(Clients* creator);

    const std::vector<Clients*>& getClients() const;
    void setClients(const std::vector<Clients*>&);

    const std::set<Clients*>& getOperators() const;
    void setOperators(const std::set<Clients*>& operators);

    int getMaxSize() const;
    void setMaxSize(int maxSize);

    static Channel* getChannelByName(const std::string& name);

private:
    static std::vector<Channel> channels;
    std::string name_;
    std::string topic_;
    Clients* creator_;
    std::vector<Clients*> clients_;
    std::set<Clients*> operators_;
    int maxSize_;
};

#endif
