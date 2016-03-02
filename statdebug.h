#ifndef __STATDEBUG_H
#define __STATDEBUG_H

class cStatData {
    int len, min, max, winSize;
    double sum;
    const char *name;
    int *buf;
    int bufSize;
public:
    cStatData(const char *Name, int WinSize, int BufSize = 32) {name = Name, winSize = WinSize; bufSize = BufSize; buf = new int[BufSize]; Reset();}
    ~cStatData() { delete[] buf; }
    void Reset() {len = 0; min = 1000000000; max = 0; sum = 0.0; }
    void Update(int Value) { 
        if (len < bufSize) buf[len] = Value;
        len++;
        sum += Value;
        if (Value > max) max = Value;
        if (Value < min) min = Value;
        if (len >= winSize) {
            esyslog("== %s == %d %d %f", name, min, max, sum/len);
            for (int i = 0; i < bufSize; i+=8) {
                esyslog("        %8d %8d %8d %8d %8d %8d %8d %8d", buf[i+0], buf[i+1], buf[i+2], buf[i+3], buf[i+4], buf[i+5], buf[i+6], buf[i+7]);
            }
            Reset();
        }
    }
};

#endif


