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
**how**:SHUT_RD关闭读端；那么无法从套接字读取数据;<br>
        SHUT_WR关闭写端；那么无法从套接字发送数据;<br>
        SHUT_RDWR无法读取也无法发送;<br>

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

### 地址格式
======================= ipv4 ======================<br>
struct in_addr{<br>
        &emsp;in_addr_t &ensp;s_addr;<br>
};<br>
<br>
struct sockaddr_in{<br>
        &emsp;sa_family_t &ensp;sin_fanily;         &emsp;//address family<br>
        &emsp;in_port_t   &emsp;sin_port;           &emsp;//port number<br>
        &emsp;struct in_addr &ensp;sin_addr;        &emsp;//ipv4 address<br>
}<br>
数据类型in_port_t定义成uint16_t.<br>
数据类型in_addr_t定义成uint32_t.   &emsp;//在stdint.h中定义并指定了相应的位数<br>
======================= ipv6 ======================<br>
struct_in6_addr{<br>
        &emsp;uint8_t &ensp;s6_addr[16];&emsp;//ipv6 address<br>
};<br><br>
struct sockaddr_in6{<br>
&emsp;sa_family_t &emsp;&emsp;sin6_family;&emsp;//address family<br>
&emsp;in_port_t&emsp;sin6_port;&emsp;//port number<br>
&emsp;uint32_t&emsp;sin6_flowinfo;&emsp;//traffic class and flow info<br>
&emsp;struct in6_addr&emsp;sin6_addr;&emsp;//ipv6 address<br>
&emsp;uint32_t&emsp;sin6_scope_id;&emsp;//set of interfaces for scope<br>
};<br>
======================= 网络地址格式转换 ======================<br>
#include <arpa/inet.h><br>
const char *inet_ntop(int domain,const void *restrict addr,char *restrict str,socklen_t size);<br>
int inet_pton(int domain,const char *restrict str,void *restrict addr);<br><br>
inet_ntop奖网络字节序的二进制地址转换成文本字符串格式。inet_pton将文本字符串格式转换成网络字节序的二进制地址。<br>
domain只支持AF_INET/AF_INET6。<br>
size指定了保存文本字符串的缓冲区大小（str）。INET_ADDRSTRLEN表示一个足够大的空间来存放ipv4的文本字符串。INET6_ADDRSTRLEN表示一个足够大的空间来存放ipv6的文本字符串。<br>
对于inet_pton,如果domain是AF_INET，则缓冲区addr需要足够大的空间来存放一个32位地址，如果domian是AF_INET6，则需要足够大的空间来存放一个128位地址。<br>
