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
