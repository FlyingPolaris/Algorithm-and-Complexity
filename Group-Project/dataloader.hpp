#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>

const int DC_NUM = 13;
const int JOB_NUM = 10;
const int TASK_NUM = 10;

DataCenter DC[DC_NUM];
std::vector<int> source[JOB_NUM][TASK_NUM];
int task_number[JOB_NUM];
double data[JOB_NUM][TASK_NUM][DC_NUM];
double band[DC_NUM][DC_NUM];
double trans_time[JOB_NUM][TASK_NUM][DC_NUM];
double exe_time[JOB_NUM][TASK_NUM][DC_NUM];
bool alloc[JOB_NUM][TASK_NUM][DC_NUM];

struct DataCenter
{
    int slot;
    char *name;
    int band[DC_NUM];
};

void get_trans_time()
{
    for (int k = 0; k < JOB_NUM; ++k)
    {
        for (int i = 0; i < task_number[k]; ++i)
        {
            for (int j = 0; j < DC_NUM; ++j)
            {
                if (source[k][i][0] == j && source[k][i].size() == 1)
                    trans_time[k][i][j] = 0;
                else
                {
                    double max = -1;
                    for (int t = 0; t < source[k][i].size(); ++i)
                    {
                        int s = source[k][i][t];
                        double tmp = data[k][i][s] / band[s][j];
                        if (tmp > max)
                            max = tmp;
                    }
                    trans_time[k][i][j] = max;
                }
            }
        }
    }
}

int dc_band[DC_NUM][DC_NUM] = {{1200, 80, 150, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 500, INT_MAX}, {100, 1200, 120, 160, 200, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, {80, 100, 1200, 200, 50, INT_MAX, INT_MAX, 300, INT_MAX, INT_MAX, 400, INT_MAX, INT_MAX}, {INT_MAX, 150, 180, 1200, 20, 120, INT_MAX, INT_MAX, 200, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, {INT_MAX, 200, 40, 20, 1200, 150, 200, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, {INT_MAX, INT_MAX, INT_MAX, 250, 180, 1200, INT_MAX, 90, INT_MAX, INT_MAX, 50, INT_MAX, 500}, {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 200, INT_MAX, 1200, INT_MAX, INT_MAX, 70, 40, INT_MAX, INT_MAX}, {INT_MAX, INT_MAX, 300, INT_MAX, INT_MAX, 60, INT_MAX, 1200, 20, 90, INT_MAX, INT_MAX, INT_MAX}, {INT_MAX, INT_MAX, INT_MAX, 300, INT_MAX, INT_MAX, INT_MAX, 30, 1200, INT_MAX, 90, 500, INT_MAX}, {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 70, 50, INT_MAX, 1200, INT_MAX, INT_MAX, INT_MAX}, {INT_MAX, INT_MAX, 400, INT_MAX, INT_MAX, 40, 60, INT_MAX, 50, INT_MAX, 1200, INT_MAX, INT_MAX}, {500, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 400, INT_MAX, INT_MAX, 1200, 500}, {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 400, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 500, 1200}};

int dc_slots[DC_NUM] = {2, 1, 3, 2, 1, 5, 2, 2, 2, 1, 2, 4, 4};

double data_trans_time[JOB_NUM][TASK_NUM][DC_NUM];
double data_exe_time[JOB_NUM][TASK_NUM][DC_NUM];


void data_init()
{
    
}