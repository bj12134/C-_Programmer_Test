#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

class UdpSocket{
public:
	UdpSocket()
		:_sockfd(-1)
    {}
    // 1.创建套接字
    bool Socket(){
		// socket(地址域, 套接字类型, 协议类型) 
		_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(_sockfd < 0){
			perror("socket error");
			return false;
		}
		return true;
    }
    // 2.为套接字绑定地址信息
    bool Bind(const std::string& ip, u_int32_t port){
		// 1-定义ipv4的地址结构
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip.c_str());
		// 2-绑定地址信息
		socklen_t len = sizeof(struct sockaddr_in);
		// bind(描述符, 统一地址结构sockaddr*, 地址信息长度)
		int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
		if(ret < 0){
			perror("bind error");
			return false;
		}
		return true;
    }
    // 3.发送数据
    bool Send(const std::string& data, const std::string& ip, uint16_t port){
		// sendto(描述符, 发送数据, 数据长度, 选项参数, 对端地址信息, 地址长度)
		// 1-定义对端地址信息的ipv4地址结构
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip.c_str());
		// 2-向这个地址发送数据
		socklen_t len = sizeof(struct sockaddr_in);
		int ret = sendto(_sockfd, data.c_str(), data.size(), 0, (struct sockaddr*)&addr, len);
		if(ret < 0){
			perror("sendto error");
			return false;
		}
		return true;
    } 
    // 4.接收数据
    bool Recv(std::string* buf, std::string* ip = NULL, uint16_t* port = NULL){
		// recvfrom(描述符, 缓冲区, 数据长度, 选项参数, 对端地址, 地址长度)
		struct sockaddr_in addr;
		socklen_t len = sizeof(struct sockaddr_in);
		char tmp_buf[4096] = {0};
		int ret = recvfrom(_sockfd, tmp_buf, 4096, 0, (struct sockaddr*)&addr, &len);
		if(ret < 0){
			perror("recvfrom error");
			return false;
		}
		// 给buf申请ret大小的空间,从tmp中拷贝ret长度的数据进去
		buf->assign(tmp_buf, ret);
		// inet_ntoa:将网络字节序整数ip地址转换为点分十进制的string字符串地址并返回
		if(ip != NULL){
			*ip = inet_ntoa(addr.sin_addr);
		}
		if(port != NULL){
			*port = ntohs(addr.sin_port);
		}
		return true;
    }
    // 5.关闭套接字
    void Close(){
		close(_sockfd);
		_sockfd = -1;
    } 
private:
	int _sockfd;
};

// 客户端要给服务端发送数据，必须知道服务端的地址信息
// 所以程序运行时需要将通过运行参数传入服务端的地址信息
int main(int argc, char* argv[]){
	if(argc != 3){
		// argv[0] = "./udp_cli"
		// argv[1] = "192.168.122.132"
		// argv[2] = "9000"
		std::cout << "em: ./udp_cli 192.168.122.132 9000" << std::endl;
		return -1;
	}
  
	std::string ip_addr = argv[1];
	uint16_t port_addr = atoi(argv[2]);
	UdpSocket sock;
	// 创建套接字
	sock.Socket();
	// 为套接字绑定地址信息
	sock.Bind(&ip, &port_addr);
	while(1){
		// 获取一个标准输入的数据,进行发送
		std::cout << "client say: ";
		fflush(stdout);
		std::string buf;
		std::cin >> buf;
		sock.Send(buf, ip_addr, port_addr);

		buf.clear();
		sock.Recv(&buf);
		std::cout << "server say: " << buf << std::endl;
	}
	sock.Close();
	return 0;
}
