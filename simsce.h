#ifndef SIMSCE_H
#define SIMSCE_H
#include <QString>

static int filePieceNum ;//文件块数
static double seedUpLink;//种子节点上传带宽

class SimSce
{
public:
    SimSce();
    void setDate(QString str);//设置成员值
    bool do_insert_DB();//插入数据到DB
    void do_query_DB();//查询DB


private:

    QString nodeType;//节点类型
    QString peerID;//peer ID
    QString downBandWidth;//下载带宽
    QString upBandWidth;//上传带宽
};

#endif // SIMSCE_H
