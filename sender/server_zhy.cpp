#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <sys/socket.h>
#include <jsoncpp/json/json.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

//#pragma comment(lib,"ws2_32.lib")
using namespace std;
using namespace Json;

class Socketserver{
public:
    Socketserver(){
        socket_ret = socket(AF_INET, SOCK_STREAM, 0);
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(50022);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        if(bind(socket_ret, (struct sockaddr* ) &servaddr, sizeof(servaddr))==-1)
        {
            perror("bind");
            exit(1);
        }
        if(listen(socket_ret, 20) == -1)
        {
            perror("listen");
            exit(1);
        }
    }
    void start_server(){
        while(1){
            int conn = accept(socket_ret, (struct sockaddr*)&servaddr, &len);
            cout<<"connect to "<<conn<<endl;
            //li.push_back(conn);

        }
    }
    void receive(){
        while(1){
            char buf[64];
            memset(buf, 0 ,sizeof(buf));
            recv(socket_ret, buf, sizeof(buf), 0);
            cout<<buf<<endl;
        }
    };

private:
    int socket_ret;
    struct sockaddr_in servaddr;
    //std::list<int> li;
    socklen_t len;
};

int main(){
    Socketserver server;
    thread th1=thread(server.start_server);
}