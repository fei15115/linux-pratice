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
