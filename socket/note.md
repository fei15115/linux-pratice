# �����׽���
## �׽��ֵĴ�����ɾ��
================================================
### �׽��ֵĴ���
#include <sys/socket.h><br>
int socket(int domain,int type,int protocol);<br>

**domain**:������ȷ��ͨ�ŵ����ԡ�<br>
        **AF_INET**     ����IPv4Ӣ������<br>
        **AF_INET6**    ����IPv6Ӣ������<br>
        **AF_UNIX**     UNIX��<br>
        **AF_UPSPEC**   δָ��<br>

**type**:ȷ���׽��ֵ����ͣ�������һ��ȷ��ͨ�ŵ����ԡ�<br>
        **SOCK_DGRAM**      �̶����ȣ������ӣ����ɿ��ı��Ĵ���<br>
        **SOCK_RAW**        IPЭ������ݱ��ӿ�<br>
        **SOCK_SEQPACKET**  �̶����ȣ����򣬿ɿ��������ӵı��Ĵ���<br>
        **SOCK_STREAM**     ����ģ��ɿ��ģ�˫����������ӵ��ֽ���<br>

**protocol**��ͨ��Ϊ0����ʾΪ����������׽�������ѡ��Ĭ��Э�顣��AF_INETͨ�����֣��׽�������SOCK_STREAM��Ĭ��Э����TCP����AF_INETͨ���У��׽�������SOCK_DGRAM��Ĭ��Э����UDP��<br>
        **IPPROTO_IP**      IPv4����Э��<br>
        **IPPROTO_IPV6**    IPv6����Э��<br>
        **IPPROTO_ICMP**    Ӣ�������Ʊ���Э��<br>
        **IPPROTO_RAW**     ԭʼIP���ݰ�Э��<br>
        **IPPROTO_TCP**     �������Э��<br>
        **IPPROTO_UDP**     �û����ݱ�Э��<br>
### �׽��ֵ�ɾ��
#include <sys/socket.h><br>
int shutdown(int sockfd, int how);<br>
**how**:SHUT_RD�رն��ˣ���ô�޷����׽��ֶ�ȡ����;<br>
        SHUT_WR�ر�д�ˣ���ô�޷����׽��ַ�������;<br>
        SHUT_RDWR�޷���ȡҲ�޷�����;<br>

=====================================================
## Ѱַ
### �ֽ���
���� һ��32λ������ֵ0x04030201<br>
        С�ˣ�CP��0��ָ�������Ч�ֽ��������1��CP��4������4��<br>
        ��ˣ�CP��0��ָ�������Ч�ֽ��������4��CP��4������1��<br>
��ͬ�Ĳ���ƽ̨�ֽ���ͬ��linuxΪС�ˣ�SolarisΪ��ˣ�<br>
����Э��ָ�����ֽ���TCP/IPʹ�ô���ֽ���<br>
#include<arpa/inet.h><br>
uint32_t htonl(uint32_t hostint32);     �����������ֽ����ʾ��32λ����<br>
uint16_t htons(uint16_t hostint16);     �����������ֽ����ʾ��16λ����<br>
uint32_t ntohl(uint32_t hostint32);     �����������ֽ����ʾ��32λ����<br>
uint32_t ntohs(uint16_t hostint16);     �����������ֽ����ʾ��32λ����<br>

### ��ַ��ʽ
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
��������in_port_t�����uint16_t.<br>
��������in_addr_t�����uint32_t.   &emsp;//��stdint.h�ж��岢ָ������Ӧ��λ��<br>
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
======================= �����ַ��ʽת�� ======================<br>
#include <arpa/inet.h><br>
const char *inet_ntop(int domain,const void *restrict addr,char *restrict str,socklen_t size);<br>
int inet_pton(int domain,const char *restrict str,void *restrict addr);<br><br>
inet_ntop�������ֽ���Ķ����Ƶ�ַת�����ı��ַ�����ʽ��inet_pton���ı��ַ�����ʽת���������ֽ���Ķ����Ƶ�ַ��<br>
domainֻ֧��AF_INET/AF_INET6��<br>
sizeָ���˱����ı��ַ����Ļ�������С��str����INET_ADDRSTRLEN��ʾһ���㹻��Ŀռ������ipv4���ı��ַ�����INET6_ADDRSTRLEN��ʾһ���㹻��Ŀռ������ipv6���ı��ַ�����<br>
����inet_pton,���domain��AF_INET���򻺳���addr��Ҫ�㹻��Ŀռ������һ��32λ��ַ�����domian��AF_INET6������Ҫ�㹻��Ŀռ������һ��128λ��ַ��<br>
