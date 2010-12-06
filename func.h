#ifndef FUNC_H
#define FUNC_H
#include <QStringList>

class func
{
public:
    func();
    bool do_load_file(QStringList fileNames);
    bool saveFile(const QString& fileName);
    void do_file_Save();

private:

};

#endif // FUNC_H
