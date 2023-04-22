#include "channel.hpp"

Channel::Channel(const std::string& name, const std::string& topic, Clients* creator) :
    name_(name),
    creator_(creator),
    maxSize_(10)
{
    topic_ = topic;
}

Channel::~Channel() {
    for (std::vector<Clients*>::iterator it = clients_.begin(); it != clients_.end(); ++it) {
        delete (*it);
    }
    clients_.clear();
    operators_.clear();
}

void Channel::joinClient(Clients* client) {
    bool clientExists = false;
    for (std::vector<Clients*>::iterator it = clients_.begin(); it != clients_.end(); ++it) {
        if ((*it) == client) {
            clientExists = true;
            break;
        }
    }
    if (clientExists) {
        return;
    }
    clients_.push_back(client);
    std::string joinMsg = ":" + client->getnickname() + " JOIN " + name_ + "\r\n";
    for (std::vector<Clients*>::iterator it = clients_.begin(); it != clients_.end(); ++it) {
        write((*it)->getclient()->fd, joinMsg.c_str(), joinMsg.length());
    }
}

void Channel::leaveClient(Clients* client) {
    auto it = std::find(clients_.begin(), clients_.end(), client);
    if (it != clients_.end()) {
        clients_.erase(it);
    }
    operators_.erase(client);
}

void Channel::sendMsg(const std::string &message, Clients *sender) {
    for (auto client : clients_) {
        if (client != sender) {
            client->getclient()->fd = client->getclientsock();
            std::string response = ":" + sender->getnickname() + "!" + sender->getuserinf().username + "@" + sender->getuserinf().hostname + " " + message + "\r\n";
            send(client->getclientsock(), response.c_str(), response.length(), 0);
        }
    }
}

Channel* Channel::getChannelByName(const std::string& name) {
    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if (it->name_ == name) {
            return &(*it);
        }
    }
    return nullptr;
}


const std::string& Channel::getName() const {
    return name_;
}

void Channel::setName(const std::string& name)
{
    name_ = name;
}

Clients* Channel::getCreator() const
{
    return creator_;
}

void Channel::setCreator(Clients* creator)
{
    creator_ = creator;
}

const std::vector<Clients*>& Channel::getClients() const {
    return clients_;
}

void Channel::setClients(const std::vector<Clients*>& clients) {
    clients_ = clients;
}

const std::set<Clients*>& Channel::getOperators() const {
    return operators_;
}

void Channel::setOperators(const std::set<Clients*>& operators)
{
    operators_ = operators;
}

int Channel::getMaxSize() const
{
    return maxSize_;
}

void Channel::setMaxSize(int maxSize)
{
    maxSize_ = maxSize;
}
