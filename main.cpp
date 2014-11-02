#include <QFile>
#include <QString>
#include <QList>
#include <QDebug>
#include <QTime>
void MergeAndCount(int list[],int start,int mid,int end,qint64 &count)
{
    int left[mid-start+1];
    for(int i=0;i<mid-start+1;i++)
        left[i]=list[start+i];

    int leftIndex=0,rightIndex=mid+1;
    for(int i=0;i<=end-start;i++)
    {
        if(rightIndex<=end&& list[rightIndex]<left[leftIndex])
        {
            list[start+i]=list[rightIndex];
            rightIndex++;
        }
        else
        {
            list[start+i]=left[leftIndex];
            count=count+(i-leftIndex);
            leftIndex++;
        }
        if(leftIndex==mid-start+1) break;
    }
}
void SortAndCount(int list[],int start,int end,qint64 &count)
{
    if(start<end)
    {
        int mid;
        mid=(start+end)/2;
        SortAndCount(list,start,mid,count);
        SortAndCount(list,mid+1,end,count);
        MergeAndCount(list,start,mid,end,count);
    }
}
int main(int argc, char *argv[])
{
    QFile file;
    QList<int> list;
    file.setFileName("Q5.txt");
    file.open(QIODevice::ReadOnly);
    QString line;
    while(!file.atEnd())
    {
        line=file.readLine();
        list.append(line.toInt());
    }
    file.close();
    int intList[list.size()];
    for(int i=0;i<list.size();i++) intList[i]=list[i];
    qint64 count=0;
    qDebug()<<"start to sort";
    QTime start,end;
    start=QTime::currentTime();
    SortAndCount(intList,0,list.size()-1,count);
    end=QTime::currentTime();
    qDebug()<<"the number of inversions is"<<count<<"using time:"<<start.msecsTo(end)<<"ms";
    return 0;
}
