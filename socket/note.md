# 网络套接字
## 套接字的创建和删除
================================================
### 套接字的创建
#include <sys/socket.h>
int socket(int domain,int type,int protocol);
domain:域；用来确定通信的特性。
        **AF_INET**     代表IPv4英特网域
        **AF_INET6**    代表IPv6英特网域
        **AF_UNIX**     UNIX域
        **AF_UPSPEC**   未指定
type:确定套接字的类型；从来进一步确定通信的特性。
        **SOCK_DGRAM**      固定长度，无连接，不可靠的报文传递
        **SOCK_RAW**        IP协议的数据报接口
        **SOCK_SEQPACKET**  固定长度，有序，可靠面向连接的报文传递
        **SOCK_STREAM**     有序的，可靠的，双向的面向连接的字节流
protocol：通常为0，表示为给定的域和套接字类型选择默认协议。在AF_INET通信域种，套接字类型SOCK_STREAM的默认协议是TCP，在AF_INET通信中，套接字类型SOCK_DGRAM的默认协议是UDP。
        **IPPROTO_IP**      IPv4网际协议
        **IPPROTO_IPV6**    IPv6网际协议
        **IPPROTO_ICMP**    英特网控制报文协议
        **IPPROTO_RAW**     原始IP数据包协议
        **IPPROTO_TCP**     传输控制协议
        **IPPROTO_UDP**     用户数据报协议
        