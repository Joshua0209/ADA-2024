#include "p8_4.h"
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include <iostream>

std::unordered_map<std::string, int> file2id;
std::vector<long long> end_time;

void dfs(int s, std::vector<std::tuple<std::string, std::vector<std::string>, int>> &makefile)
{
    end_time[s] = 0;
    for (int i = 0; i < std::get<1>(makefile[s]).size(); i++)
    {
        std::string dep_name = std::get<1>(makefile[s])[i];
        if (dep_name.find(".cpp") != -1 && dep_name.size() - dep_name.find(".cpp") == 4)
        {
            continue;
        }
        int v = file2id[dep_name];
        if (end_time[v] == -1)
        {
            dfs(v, makefile);
        }
        end_time[s] = std::max<long long>(end_time[s], end_time[v]);
    }
    end_time[s] += std::get<2>(makefile[s]);
    return;
}

long long Minimum_Build_Time(std::vector<std::tuple<std::string, std::vector<std::string>, int>> &makefile)
{
    std::vector<int> exe_file;
    for (int i = 0; i < makefile.size(); i++)
    {
        std::string name = std::get<0>(makefile[i]);
        file2id[name] = i;
        if (name.find(".exe") != -1 && name.size() - name.find(".exe") == 4)
        {
            exe_file.push_back(i);
        }
    }

    end_time.resize(makefile.size(), -1);
    long long total_time = 0;
    for (int i = 0; i < exe_file.size(); i++)
    {
        if (end_time[exe_file[i]] == -1)
        {
            dfs(exe_file[i], makefile);
        }
        total_time = std::max<long long>(total_time, end_time[exe_file[i]]);
    }

    return total_time;
}
