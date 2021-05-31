#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>

const int DC_NUM = 13;
const int JOB_NUM = 10;
const int TASK_NUM = 10;


DataCenter DC[DC_NUM];
std::vector<int> source[JOB_NUM][TASK_NUM];
double data[JOB_NUM][TASK_NUM][DC_NUM];
double band[DC_NUM][DC_NUM];
double trans_time[JOB_NUM][TASK_NUM][DC_NUM];
double exe_time[JOB_NUM][TASK_NUM][DC_NUM];

struct DataCenter
{
    int slot;
    char *name;
};




