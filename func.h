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
    double avg_seed_uplink_utilization();//平均种子带宽利用率
    void seed_uplink_utilization(double *xval,double *yval,int *pointNum);//种子带宽利用率曲线图
    double seed_normalization();//种子归一化负载
    double avg_peer_download_time();//平均节点下载时间
    double avg_peer_uplink_utilization();//平均节点上传带宽利用率
    double avg_peer_downlink_utilization();//平均节点下载带宽利用率
    double avg_peer_normalization();//平均节点归一化负载
    void interest_conct(double *xval,double *yval,int *pointNum);//感兴趣连接曲线图
    void rcdpiece();//RcdPiece曲线图



private:

};

#endif // FUNC_H
