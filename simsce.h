#ifndef SIMSCE_H
#define SIMSCE_H
#include <QString>

static int filePieceNum ;//�ļ�����
static double seedUpLink;//���ӽڵ��ϴ�����

class SimSce
{
public:
    SimSce();
    void setDate(QString str);//���ó�Աֵ
    bool do_insert_DB();//�������ݵ�DB
    void do_query_DB();//��ѯDB


private:

    QString nodeType;//�ڵ�����
    QString peerID;//peer ID
    QString downBandWidth;//���ش���
    QString upBandWidth;//�ϴ�����
};

#endif // SIMSCE_H
