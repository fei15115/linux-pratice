# �����׽���
## �׽��ֵĴ�����ɾ��
================================================
### �׽��ֵĴ���
#include <sys/socket.h>
int socket(int domain,int type,int protocol);
domain:������ȷ��ͨ�ŵ����ԡ�
        **AF_INET**     ����IPv4Ӣ������
        **AF_INET6**    ����IPv6Ӣ������
        **AF_UNIX**     UNIX��
        **AF_UPSPEC**   δָ��
type:ȷ���׽��ֵ����ͣ�������һ��ȷ��ͨ�ŵ����ԡ�
        **SOCK_DGRAM**      �̶����ȣ������ӣ����ɿ��ı��Ĵ���
        **SOCK_RAW**        IPЭ������ݱ��ӿ�
        **SOCK_SEQPACKET**  �̶����ȣ����򣬿ɿ��������ӵı��Ĵ���
        **SOCK_STREAM**     ����ģ��ɿ��ģ�˫����������ӵ��ֽ���
protocol��ͨ��Ϊ0����ʾΪ����������׽�������ѡ��Ĭ��Э�顣��AF_INETͨ�����֣��׽�������SOCK_STREAM��Ĭ��Э����TCP����AF_INETͨ���У��׽�������SOCK_DGRAM��Ĭ��Э����UDP��
        **IPPROTO_IP**      IPv4����Э��
        **IPPROTO_IPV6**    IPv6����Э��
        **IPPROTO_ICMP**    Ӣ�������Ʊ���Э��
        **IPPROTO_RAW**     ԭʼIP���ݰ�Э��
        **IPPROTO_TCP**     �������Э��
        **IPPROTO_UDP**     �û����ݱ�Э��
        