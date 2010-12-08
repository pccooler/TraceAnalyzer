#ifndef FUNC_H
#define FUNC_H
#include <QStringList>

#define MaxValue 10000

static double xval[MaxValue];
static double yval[MaxValue];
static int pointNum;

class func
{
public:
    func();
    bool do_load_file(QStringList fileNames);
    bool saveFile(const QString& fileName);
    void do_file_Save();
    double avg_seed_uplink_utilization();//ƽ�����Ӵ���������
    void seed_uplink_utilization(double *xval,double *yval,int *pointNum);//���Ӵ�������������ͼ
    double seed_normalization();//���ӹ�һ������
    double avg_peer_download_time();//ƽ���ڵ�����ʱ��
    double avg_peer_uplink_utilization();//ƽ���ڵ��ϴ�����������
    double avg_peer_downlink_utilization();//ƽ���ڵ����ش���������
    double avg_peer_normalization();//ƽ���ڵ��һ������
    void interest_conct(double *xval,double *yval,int *pointNum);//����Ȥ��������ͼ
    void rcdpiece();//RcdPiece����ͼ



private:

};

#endif // FUNC_H
