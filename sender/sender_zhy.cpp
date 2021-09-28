#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <sys/socket.h>
#include <jsoncpp/json/json.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//#pragma comment(lib,"ws2_32.lib")
using namespace std;
using namespace Json;

//string config_sample ="{\"server\":{\"domain\":\"www.sjtu.edu.cn\",\"host\":\"202.120.38.38\",\"port\":\"50022\"}";
//字典可以放入变量吗？如果不可，编译之后是否就不可修改了
//Json::Value root;
//Json::Reader read;
//read.parse(config_sample,root);
//cout<<root[" "]<<endl;

class ValueError: public exception{
    const char* what() const noexcept override{return "ValueError";}
};

class Sender {
public:
    Sender(auto init_config): config(init_config){
//        if (domain.empty() && host.empty())
//            throw ValueError();
//        if (host.empty()){
//            return;
//            //host/**/
//        }
    }
    void connect();
    void close();
    void call(string);

private:
    Json::Value config;/**/
    //Json::Reader read;
    //auto logger;/**/
    string domain;
    string host;
    string port;
    int connection=-1;//连接服务器，成功返回0，错误返回-1
    static const int BUF_SIZE = 64;
    int socket_ret;

};

void Sender::connect(){
    socket_ret = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    cout<<config["server"]["port"].asString()<<endl;
    servaddr.sin_port = htons(stoi(config["server"]["port"].asString()));  //服务器端口
    servaddr.sin_addr.s_addr = inet_addr((config["server"]["host"].asString()).c_str());  //服务器ip，inet_addr用于IPv4的IP转换（十进制转换为二进制）
    //127.0.0.1是本地预留地址
    //连接服务器，成功返回0，错误返回-1
    connection=::connect(socket_ret, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (connection < 0)
    {
        cout<<"not connect"<<endl;
        exit(1);
    }

}

void Sender::close(){
    shutdown(socket_ret,SHUT_RDWR); //成功返回0，出错为-1
    connection=0;
}

void Sender::call(string s){
    //向服务器发送数据
    if (connection!=0) {//连接服务器，成功返回0，错误返回-1
        try {
            connect();
            cout << "connect to " << config["server"]["host"] << ":" << config["server"]["port"] << endl;
        }
        catch (const exception e) {
            cout << e.what()<<endl;
            connection=-1;
            cout<<"fail to connect to " << config["server"]["host"] << ":" << config["server"]["port"] << endl;
            return;
        }
    }

    cout<<"send data to "<< config["server"]["host"] << ":" << config["server"]["port"] << endl;
    auto msg=s.c_str();
    send(socket_ret, msg, strlen(msg),0); //发送
    char recvbuf[BUF_SIZE];
    int len;
    len = recv(socket_ret, recvbuf, sizeof(recvbuf),0);
    cout<<recvbuf<<endl;
    if(!strcmp(recvbuf,"bye")) {//==0
        shutdown(socket_ret,SHUT_RDWR);
        connection=0;
    }
    memset(recvbuf, 0, sizeof(recvbuf));
}


int main() {
    string config_sample ="{\"server\":{\"domain\":\"www.sjtu.edu.cn\",\"host\":\"127.0.0.1\",\"port\":\"6666\"}";
    Json::Value root;
    Json::Reader read;
    read.parse(config_sample,root);
    Sender sender(root);
    int i=0;
    while(1){
        sender.call("hello" + to_string(i));
        i++;
        sleep(5);
    }
    return 0;
}