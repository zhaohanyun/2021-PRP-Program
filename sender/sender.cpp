#include <iostream>
#include <string>

using namespace  std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

class CONFIG{
public:
    string domain;
    string host;
    string port;

};

class ValueError: public exception{
    const char* what() const noexcept override{return "ValueError";}
};

class Sender{
private:
    CONFIG config;
    string domain;
    string host;
    string port;
    bool connection;
public:
    explicit Sender(const CONFIG& config){
        this->config=config;
        this->domain=config.domain;
        this->host=config.host;
        this->port=config.port;
        if(this->domain.empty() && this->host.empty()) throw ValueError();
        if (this->host.empty()) return;
        this->connection= false;
    }

    void connect(){
        connection
    }
};
