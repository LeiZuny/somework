#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* ackMsg = "Message received";

    // 创建socket文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 绑定socket到地址和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // 接受连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    bool isRunning = true;
    while (isRunning) {
        memset(buffer, 0, 1024); // 清空缓冲区
        // 读取数据
        int bytesRead = read(new_socket, buffer, 1024);
        if (bytesRead == 0) {
            break; // 客户端关闭了连接
        }
        std::cout << "Message from client: " << buffer << std::endl;

        if (strcmp(buffer, "exit") == 0) {
            isRunning = false; // 收到退出信号
        } else {
            // 发送数据
            send(new_socket, ackMsg, strlen(ackMsg), 0);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}