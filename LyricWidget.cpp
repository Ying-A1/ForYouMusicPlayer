#include "LyricWidget.h"
#include "ui_LyricWidget.h"

#include <algorithm>
#include <QTextCodec>


LyricWidget::LyricWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LyricWidget)
{
    ui->setupUi(this);
    clear();//清空用于排版时的测试内容(.ui文件中)
}

LyricWidget::~LyricWidget()
{
    delete ui;
}


//重载比较（歌词按时间排序）
bool operator <(const LyricLine& A, const LyricLine& B){
    return A.time<B.time;
}

//将歌词文件的内容处理为歌词结构的QList
bool LyricWidget::process(QString filePath)
{

    //QTextCodec * codec = QTextCodec::codecForName("GBK");
    QFile lyricFile(filePath);
    lyricFile.open(QFile::ReadOnly);
    //若文件本身为utf-8 编码不需要从gbk转为utf-8
    //QString content(QString::fromLocal8Bit(lyricFile.readAll()));
    QString content(lyricFile.readAll());
    //qDebug() << content;
    lyricFile.close();

    //先清空歌词
    lines.clear();

    const QRegExp rx("\\[(\\d+):(\\d+(\\.\\d+)?)\\]"); //用来查找时间标签的正则表达式

    // ※步骤1 拿到匹配成功的第一个索引位置
    // indexIn返回首次匹配成功的字符串的位置索引，若没有匹配成功，返回-1
    int pos = rx.indexIn(content);
    if (pos == -1) {
        return false;
    }
    else {
        int lastPos;
        // Qlist timeLabels 储存时间
        // 后面的Vector lines 储存歌词
        QList<int> timeLabels;
        do {
            // ※步骤2
            // Qlist可以使用 << 操作符添加元素
            // cap(0)为查到的整个正则段的内容，cap(1)、cap(2)依次为各个捕获段的内容，这个函数与pos函数是一一对应的，pos返回位置，cap返回内容
            timeLabels << (rx.cap(1).toInt() * 60 + rx.cap(2).toDouble()) * 1000 + 4500;//计算该时间点毫秒数
            // lastPos储存匹配的位置+匹配的内容后该位置的索引
            lastPos = pos + rx.matchedLength();
            // 下面对content从lastPos开始，继续往后匹配
            pos = rx.indexIn(content, lastPos);

            // 匹配不到时间格式，自然是文本
            if (pos == -1) {
                // mid函数返回从0~lastPos字符串
                // trimmed()函数移除字符串两端的空白字符
                QString text = content.mid(lastPos).trimmed();
                foreach (const int& time, timeLabels)
                    // lines 储存（一个时间点+对应的歌词文本）
                    lines.push_back(LyricLine(time, text));
                break;
            }

            // ※步骤3
            QString text = content.mid(lastPos, pos - lastPos);
            if (!text.isEmpty()) {
                foreach (const int& time, timeLabels)
                    lines.push_back(LyricLine(time, text.trimmed()));
                timeLabels.clear();
            }
        }
        while (true);
        // ※步骤4 歌词按时间排序
        stable_sort(lines.begin(), lines.end());

    }
    if (lines.size()) {
        return true;
    }
    return false;
}


/**
 * @brief 根据时间找到对应位置的歌词
 * @param position：获取当前歌曲的时间位置
 * @return
 */
int LyricWidget::getIndex(qint64 position)
{
    if(!lines.size()){
        return -1;
    }else{
        if(lines[0].time>=position){
            return 0;
        }
    }
    int i=1;
    for(i=1;i<lines.size();i++){
        if(lines[i-1].time<position && lines[i].time>=position){
            return i-1;
        }
    }
    return lines.size()-1;
}

void LyricWidget::show(qint64 position)
{
    int index=getIndex(position);
    if(index==-1){
        ui->label_3i->setText("");
        ui->label_2i->setText("");
        ui->label_1i->setText("");
        ui->label_i->setText(u8"当前歌曲无歌词");
        ui->label_i1->setText("");
        ui->label_i2->setText("");
        ui->label_i3->setText("");
    }else{
        ui->label_3i->setText(getLyricText(index-3));
        ui->label_2i->setText(getLyricText(index-2));
        ui->label_1i->setText(getLyricText(index-1));
        ui->label_i->setText(getLyricText(index));
        ui->label_i1->setText(getLyricText(index+1));
        ui->label_i2->setText(getLyricText(index+2));
        ui->label_i3->setText(getLyricText(index+3));
    }
}

QString LyricWidget::getLyricText(int index)
{
    if(index<0 || index>=lines.size()){
        return "";
    }else{
        return lines[index].text;
    }
}

void LyricWidget::clear()
{
    ui->label_3i->setText("");
    ui->label_2i->setText("");
    ui->label_1i->setText("");
    ui->label_i->setText("");
    ui->label_i1->setText("");
    ui->label_i2->setText("");
    ui->label_i3->setText("");
}
