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

**how**:SHUT_RD�رն��ˣ���ô�޷����׽��ֶ�ȡ���ݣ�<br>
        SHUT_WR�ر�д�ˣ���ô�޷����׽��ַ������ݣ�<br>
        SHUT_RDWR�޷���ȡҲ�޷����ͣ�<br>
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

