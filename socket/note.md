# 网络套接字
## 套接字的创建和删除
================================================
### 套接字的创建
#include <sys/socket.h><br>
int socket(int domain,int type,int protocol);<br>

**domain**:域；用来确定通信的特性。<br>
        **AF_INET**     代表IPv4英特网域<br>
        **AF_INET6**    代表IPv6英特网域<br>
        **AF_UNIX**     UNIX域<br>
        **AF_UPSPEC**   未指定<br>

**type**:确定套接字的类型；从来进一步确定通信的特性。<br>
        **SOCK_DGRAM**      固定长度，无连接，不可靠的报文传递<br>
        **SOCK_RAW**        IP协议的数据报接口<br>
        **SOCK_SEQPACKET**  固定长度，有序，可靠面向连接的报文传递<br>
        **SOCK_STREAM**     有序的，可靠的，双向的面向连接的字节流<br>

**protocol**：通常为0，表示为给定的域和套接字类型选择默认协议。在AF_INET通信域种，套接字类型SOCK_STREAM的默认协议是TCP，在AF_INET通信中，套接字类型SOCK_DGRAM的默认协议是UDP。<br>
        **IPPROTO_IP**      IPv4网际协议<br>
        **IPPROTO_IPV6**    IPv6网际协议<br>
        **IPPROTO_ICMP**    英特网控制报文协议<br>
        **IPPROTO_RAW**     原始IP数据包协议<br>
        **IPPROTO_TCP**     传输控制协议<br>
        **IPPROTO_UDP**     用户数据报协议<br>
### 套接字的删除
#include <sys/socket.h><br>
int shutdown(int sockfd, int how);<br>

**how**:SHUT_RD关闭读端；那么无法从套接字读取数据；<br>
        SHUT_WR关闭写端；那么无法从套接字发送数据；<br>
        SHUT_RDWR无法读取也无法发送；<br>
=====================================================
## 寻址
### 字节序
举例 一个32位整数赋值0x04030201<br>
        小端：CP【0】指向最低有效字节因而包含1，CP【4】包含4；<br>
        大端：CP【0】指向最高有效字节因而包含4，CP【4】包含1；<br>
不同的测试平台字节序不同，linux为小端，Solaris为大端；<br>
网络协议指定了字节序，TCP/IP使用大端字节序。<br>
#include<arpa/inet.h><br>
uint32_t htonl(uint32_t hostint32);     返回以网络字节序表示的32位整数<br>
uint16_t htons(uint16_t hostint16);     返回以网络字节序表示的16位整数<br>
uint32_t ntohl(uint32_t hostint32);     返回以主机字节序表示的32位整数<br>
uint32_t ntohs(uint16_t hostint16);     返回以主机字节序表示的32位整数<br>

