#include <cstdio>
#include <cstring>
#include <ctime>
#include "DAG.hpp"
#include "dataloader.hpp"

void get_trans_time()
{
    for (int k = 0; k < JOB_NUM; ++k)
    {
        for (int i = 0; i < TASK_NUM; ++i)
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

void filling()
{
    //clear the martix
    for (int k = 0; k < JOB_NUM; ++k)
        for (int i = 0; i < TASK_NUM; ++i)
            for (int j = 0; j < DC_NUM; ++j)
            {
                alloc[k][i][j] = 0;
            }
    int flag = true;
    while (flag)
    {
        //fill the martix with Monte Carlo
        flag = false;
        for (int k = 0; k < JOB_NUM; ++k)
            for (int i = 0; i < TASK_NUM; ++i)
            {
                srand(unsigned(time(NULL)));
                int tmp_dc = rand() % DC_NUM;
                alloc[k][i][tmp_dc] = 1;
            }
        //check
        for (int j = 0; j < DC_NUM; ++j)
        {
            int sum = 0;
            for (int k = 0; k < JOB_NUM; ++k)
                for (int i = 0; i < task_number[k]; ++i)
                    sum += alloc[k][i][j];
            if (sum > DC[j].slot)
            {
                flag = true;
            }
        }
    }
}

double time_calculator()
{
    filling();
    double time;
    double max = -1;
    for (int k = 0; k < JOB_NUM; ++k)
    {
        double max_tmp = -1;
        for (int j = 0; j < DC_NUM; ++j)
        {
            for (int i = 0; i < task_number[k]; ++i)
            {
                time = alloc[k][i][j] * (trans_time[k][i][j] + exe_time[k][i][j]);
                if (max_tmp < time)
                {
                    max_tmp = time;
                }
            }
        }
        if (max_tmp > max)
            max = max_tmp;
    }

    return max;
}
