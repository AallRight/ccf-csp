#pragma GCC optimize(3)
#include <bits/stdc++.h>
#include <sstream>
#define Problem1 1
#define Problem2 2
#define Problem3 3
#define Problem4 4
#define Problem5 5
#define Problem6 6
#define Problem7 7
#define Problem8 8
/*
1: 100
2: 100
3: 20
4: 100

*/

#define Problem 8

#if Problem == Problem1
int main()
{
    int n, m, p, q;
    std ::cin >> n >> m >> p >> q;

    std ::vector<int> matrix;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int temp;
            std ::cin >> temp;
            matrix.push_back(temp);
        }
    }
    auto it = matrix.begin();
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {

            std ::cout << *it << " ";
            it++;
        }
        std ::cout << std ::endl;
    }
}

#endif

#if Problem == Problem2

void reverse_matrix(std ::vector<int> &matrix, int &n, int &m)
{
    std ::vector<int> temp(n * m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            temp[j * n + i] = matrix[i * m + j];
        }
    }
    matrix.assign(temp.begin(), temp.end());
    std ::swap(n, m);
}

int main()
{
    int n, m;
    int opt_num;
    std ::cin >> n >> m >> opt_num;

    std ::vector<int> matrix;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int temp;
            std ::cin >> temp;
            matrix.push_back(temp);
        }
    }
    for (int i = 0; i < opt_num; i++)
    {
        int opt;
        std ::cin >> opt;
        if (opt == 1)
        {
            int p, q;
            std ::cin >> p >> q;
            if (p * q == m * n)
            {
                n = p, m = q;
            }
        }
        else if (opt == 2)
        {
            int tem;
            std ::cin >> tem;
            std ::cin >> tem;
            reverse_matrix(matrix, n, m);
        }
        else if (opt == 3)
        {
            int p, q;
            std ::cin >> p >> q;
            auto it = matrix.begin() + p * m + q;
            std ::cout << *it << std ::endl;
        }
    }
}

#endif

#if Problem == Problem3

int main()
{
    int n, m;
    std ::cin >> n >> m;
    std ::vector<std ::vector<std ::string>> words_in_alphabet(n);
    std ::vector<std ::string> words;
    std ::vector<std ::string> output;
    std ::map<std ::string, int> output_map;
    std ::vector<int> times;
    for (int i = 0; i < n; i++)
    {
        std ::string temp;
        int times_temp;
        std ::cin >> temp >> times_temp;
        words.push_back(temp);
        times.push_back(times_temp);
    }
    std ::map<std ::pair<std ::string, std ::string>, int> alphabet_map;

    // initialize
    for (int i = 0; i < n; i++)
    {
        std::string word_tem = *(words.begin() + i);
        int times_temp = *(times.begin() + i);
        int length = word_tem.size();
        auto it = words_in_alphabet.begin() + i;
        for (int j = 0; j < length; j++)
        {
            // 先添加单个字母
            std ::string alpha_temp = word_tem.substr(j, 1);
            (*it).push_back(alpha_temp);
            if (output_map.find(alpha_temp) == output_map.end())
            {
                output_map.insert(std ::pair<std ::string, int>(alpha_temp, 0));
            }

            // 添加配对
            if (j < length - 1)
            {
                std ::string alpha_temp_next = word_tem.substr(j + 1, 1);
                std ::pair<std ::string, std ::string> alpha_pair = std ::pair<std ::string, std ::string>(alpha_temp, alpha_temp_next);
                if (alphabet_map.find(alpha_pair) == alphabet_map.end())
                {
                    alphabet_map.insert(std ::pair<std ::pair<std ::string, std ::string>, int>(alpha_pair, 0));
                }

                alphabet_map[alpha_pair] += times_temp;
            }
        }
    }
    // 先用map组建配对，统计次数
    // 然后选出最大次数的
    // 删去最大次数的配对并加到输出map中
    // 修改words_in_alphabet，增加新的，删去旧的，然后注意配对的改变，一前一后

    while (output_map.size() < m)
    {
        // 1 2
        std ::pair<std ::pair<std ::string, std ::string>, int> max_pair = std ::pair<std ::pair<std ::string, std ::string>, int>(std ::pair<std ::string, std ::string>("", ""), 0);
        int max_times = 0;
        auto max_pos = alphabet_map.begin();
        for (auto it = alphabet_map.begin(); it != alphabet_map.end(); it++)
        {
            if (it->second > max_times)
            {
                max_times = it->second;
                max_pos = it;
                max_pair.operator=(*it);
            }
        }
        // 3
        alphabet_map.erase(max_pos);
        std::string new_alpha = max_pair.first.first + max_pair.first.second;
        if (output_map.find(new_alpha) == output_map.end())
        {
            output_map.insert(std ::pair<std ::string, int>(new_alpha, 0));
        }
        // 4
        std ::string alpha_temp_first = max_pair.first.first;
        std ::string alpha_temp_second = max_pair.first.second;
        int flag = 1;
        for (int i = 0; i < n; i++)
        {
            auto it = words_in_alphabet.begin() + i;
            int length = (*it).size();
            if (it->size() != 1)
            {
                flag = 0;
            }
            // std :: vector  <std ::string>  pre_word_in_alphabet = *it;
            for (int j = 0; j < length - 1; j++)
            {
                std ::string alpha_temp_1 = (*it)[j];
                std ::string alpha_temp_2 = (*it)[j + 1];
                if (alphabet_map.find(std ::pair<std ::string, std ::string>(alpha_temp_1, alpha_temp_2)) != alphabet_map.end())
                {
                    alphabet_map[std ::pair<std ::string, std ::string>(alpha_temp_1, alpha_temp_2)] -= times[i];
                }
            }
            for (int j = 0; j < length - 1; j++)
            {
                std ::string alpha_temp_1 = (*it)[j];
                std ::string alpha_temp_2 = (*it)[j + 1];
                // // 如果匹配上了，替换掉并减去少掉的次数
                // 如果匹配上了，就记录下来然后对整个单词重新计算次数
                if (alpha_temp_1.compare(alpha_temp_first) == 0 && alpha_temp_2.compare(alpha_temp_second) == 0)
                {
                    // if (j > 0){
                    //     std :: pair <std ::string, std ::string> pre_pair = std ::pair<std ::string, std ::string>((*it)[j - 1], (*it)[j]);
                    //     alphabet_map[pre_pair] -= times[i];
                    // }
                    // if(j < length - 2){
                    //     std :: pair <std ::string, std ::string> next_pair = std ::pair<std ::string, std ::string>((*it)[j + 1], (*it)[j + 2]);
                    //     alphabet_map[next_pair] -= times[i];
                    // }
                    (*it).erase((*it).begin() + j);
                    (*it).erase((*it).begin() + j);
                    (*it).insert((*it).begin() + j, new_alpha);

                    // // 再加上新的匹配
                    // if (j > 0){
                    //     std :: pair <std ::string, std ::string> pre_pair = std ::pair<std ::string, std ::string>((*it)[j - 1], (*it)[j]);
                    //     alphabet_map[pre_pair] -= times[i];
                    // }
                }
                // if(j < (*it).size() - 1){
                //     std :: string alpha_temp = (*it)[j];
                //     std :: string alpha_temp_next = (*it)[j + 1];
                //     if(alpha_temp == max_pair.first.first && alpha_temp_next == max_pair.first.second){
                //         (*it).erase((*it).begin() + j);
                //         (*it).erase((*it).begin() + j);
                //         (*it).insert((*it).begin() + j, new_alpha);
                //     }
                // }
            }

            length = (*it).size();
            for (int j = 0; j < length - 1; j++)
            {
                std ::string alpha_temp_1 = (*it)[j];
                std ::string alpha_temp_2 = (*it)[j + 1];
                if (alphabet_map.find(std ::pair<std ::string, std ::string>(alpha_temp_1, alpha_temp_2)) == alphabet_map.end())
                {
                    alphabet_map.insert(std ::pair<std ::pair<std ::string, std ::string>, int>(std ::pair<std ::string, std ::string>(alpha_temp_1, alpha_temp_2), 0));
                }
                alphabet_map[std ::pair<std ::string, std ::string>(alpha_temp_1, alpha_temp_2)] += times[i];
            }
        }
        if (flag)
        {
            // 全部合成为一个单词
            break;
        }
    }

    // std :: sort (output_map.begin(), output_map.end());
    for (auto it = output_map.begin(); it != output_map.end(); it++)
    {
        output.push_back(it->first);
    }

    std ::sort(output.begin(), output.end());
    // for(auto it = output.begin(); it != output.end(); it++){
    //     std ::cout << *it << std ::endl;
    // }
    auto it = output.begin();
    int alpha_length = 1;
    while (output.size() > 0)
    {
        if (it->size() == alpha_length)
        {
            std ::cout << *it << std ::endl;
            output.erase(it);
        }
        else
        {
            it++;
        }
        if (it == output.end())
        {
            alpha_length++;
            it = output.begin();
        }
    }
}

#endif

#if Problem == Problem4

int main()
{
    int n, m, v;
    std ::cin >> n >> m >> v;
    int b[1000];
    int c[1000];
    for (int i = 0; i < n; i++)
    {
        std ::cin >> b[i];
        std ::cin >> c[i];
    }
    int **dp = (int **)malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        dp[i] = (int *)calloc(20000, sizeof(int));
    }
    // int dp[1000][20000] = {0};
    // 每个仓库的dp值
    int item_num[1000] = {0};
    // int item[1000][1000];
    int **item = (int **)malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        item[i] = (int *)malloc(sizeof(int) * 1000);
        memset(item[i], 0, sizeof(int) * 1000);
    }
    for (int i = 0; i < m; i++)
    {
        int a, t;
        std ::cin >> a >> t;
        item[t][item_num[t]++] = a;
    }
    for (int i = 0; i < n; i++)
    {
        std ::sort(item[i], item[i] + item_num[i]);
    }
    for (int i = 0; i < n; i++)
    {
        // int item_max = 0;
        int item_sold = -b[i];
        for (int j = 0; j < item_num[i]; j++)
        {
            // item_max += item[i][item_num[i]-j-1];
            item_sold = item_sold + item[i][item_num[i] - j - 1] - c[i];
            for (int k = 0; k < c[i]; k++)
            {
                // 一段都是一个值

                dp[i][b[i] + c[i] * (j + 1) + k] = item_sold;
            }
            if (item_sold > v)
            {
                break;
            }
        }
    }
    // int dp_first_storage[1000][20000] = {0};
    int **dp_first_storage = (int **)malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        dp_first_storage[i] = (int *)calloc(20000, sizeof(int));
    }
    for (int i = 0; i < 20000; i++)
    {
        dp_first_storage[0][i] = dp[0][i];
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < 20000; j++)
        {
            dp_first_storage[i][j] = dp_first_storage[i - 1][j];
            for (int k = 0; k <= item_num[i]; k++)
            {
                int k_new = b[i] + c[i] * k;
                if (k_new > j)
                {
                    break;
                }
                dp_first_storage[i][j] = std ::max(dp_first_storage[i][j], dp_first_storage[i - 1][j - k_new] + dp[i][k_new]);
            }

            // for (int k = 0; k <= j; k++)
            // {
            //     dp_first_storage[i][j] = std ::max(dp_first_storage[i][j], dp_first_storage[i - 1][j - k] + dp[i][k]);
            // }
            if (dp_first_storage[i][j] > v)
            {
                break;
            }
        }
    }
    for (int i = 0; i < 20000; i++)
    {
        if (dp_first_storage[n - 1][i] >= v)
        {
            std ::cout << i << std ::endl;
            break;
        }
    }
}

#endif

#if Problem == Problem5
// void v_function(int x, int y, int v, int &V_x_y)
// {
//     V_x_y = std ::max(v, V_x_y);
//     return;
// }

int Vx[500000], Vy[500000];
// int x_1[500000], y_1[500000], x_2[500000], y_2[500000], v[500000];
typedef struct Area
{
    int x1, y1, x2, y2, v;
    Area()
    {
    }
    bool operator<(const Area &a) const
    {
        return v > a.v;
    }
} Area;
Area Point[500000];
int x_1_i[500000], y_1_i[500000], x_2_i[500000], y_2_i[500000];
// int Dpx[5000][5000], Dpy[5000][5000];
int Dpx2[50000][20], Dpy2[50000][20]; // 这个用传统的RMQ算法
int Vx10[50000], Vy10[50000];

void Vf_x(int x1, int x2, int v)
{
    if (x1 > x2)
    {
        std ::swap(x1, x2);
    }
    for (int i = x1; i <= x2; i++)
    {
        Vx[i] = std ::max(v, Vx[i]);
    }
}

void Vf_y(int y1, int y2, int v)
{
    if (y1 > y2)
    {
        std ::swap(y1, y2);
    }
    for (int i = y1; i <= y2; i++)
    {
        Vy[i] = std ::max(v, Vy[i]);
    }
}
void rmq_init()
{
    for (int i = 0; i < 50000; i++)
    {
        Dpx2[i][0] = Vx10[i];
        Dpy2[i][0] = Vy10[i];
    }
    for (int j = 1; (1 << j) < 50000; j++)
    {
        for (int i = 0; i + (1 << j) < 50000; i++)
        {
            Dpx2[i][j] = std ::max(Dpx2[i][j - 1], Dpx2[i + (1 << (j - 1))][j - 1]);
            Dpy2[i][j] = std ::max(Dpy2[i][j - 1], Dpy2[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int rmq_request(int r, int l)
{
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1)
    {
        k++;
    }
    return std ::max(Dpx2[l][k], Dpx2[r - (1 << k) + 1][k]);
}
bool judge_cross(int x1, int y1, int x2, int y2, int x1_i, int y1_i, int x2_i, int y2_i)
{
    if (x2_i < x1 || x1_i > x2 || y2_i < y1 || y1_i > y2)
    {
        return false;
    }
    return true;
}

int main()
{
    int n, m;
    std ::cin >> n >> m;
    // // int x_1[n], y_1[n], x_2[n], y_2[n], v[n];
    // // int x_1_i[m], y_1_i[m], x_2_i[m], y_2_i[m];
    // // memset(Dpx, 0, sizeof(Dpx));
    // // memset(Dpy, 0, sizeof(Dpy));
    // memset(Vx, 0, sizeof(Vx));
    // memset(Vy, 0, sizeof(Vy));
    // memset(Vx10, 0, sizeof(Vx10));
    // memset(Vy10, 0, sizeof(Vy10));
    // memset(Dpx2, 0, sizeof(Dpx2));
    // memset(Dpy2, 0, sizeof(Dpy2));
    for (int i; i < n; i++)
    {
        int v_tem;
        int x1_tem, y1_tem, x2_tem, y2_tem;
        std ::cin >> x1_tem >> x2_tem >> y1_tem >> y2_tem >> v_tem;
        // Vf_x(x1_tem, x2_tem, v_tem);
        // Vf_y(y1_tem, y2_tem, v_tem);
        Point[i].x1 = x1_tem;
        Point[i].y1 = y1_tem;
        Point[i].x2 = x2_tem;
        Point[i].y2 = y2_tem;
        Point[i].v = v_tem;
    }
    for (int i = 0; i < m; i++)
    {
        std ::cin >> x_1_i[i] >> x_2_i[i] >> y_1_i[i] >> y_2_i[i];
    }
    // for (int i = 0; i < 50000; i += 10)
    // {
    //     for (int j = i; j < i + 10; j++)
    //     {
    //         Vx10[i] = std ::max(Vx[j], Vx10[i]);
    //         Vy10[i] = std ::max(Vy[j], Vy10[i]);
    //     }
    // }
    // // 分别构建x,y的区间最大值，然后取max即可
    // rmq_init();
    std::sort(Point, Point + n);
    for (int i = 0; i < m; i++)
    {
        int flag = 1;
        for (int j = 0; j < n; j++)
        {
            if (judge_cross(Point[j].x1, Point[j].y1, Point[j].x2, Point[j].y2, x_1_i[i], y_1_i[i], x_2_i[i], y_2_i[i]))
            {
                std ::cout << Point[j].v << std ::endl;
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            std::cout << 0 << std ::endl;
        }
    }
}
#endif

#if Problem == Problem6

int Vx[500000], Vy[500000];
int x_1_i[500000], y_1_i[500000], x_2_i[500000], y_2_i[500000];
// int Dpx[5000][5000], Dpy[5000][5000];
int Dpx2[50000][20], Dpy2[50000][20]; // 这个用传统的RMQ算法
int Vx10[50000], Vy10[50000];

void Vf_x(int x1, int x2, int v)
{
    if (x1 > x2)
    {
        std ::swap(x1, x2);
    }
    for (int i = x1; i <= x2; i++)
    {
        Vx[i] = std ::max(v, Vx[i]);
    }
}

void Vf_y(int y1, int y2, int v)
{
    if (y1 > y2)
    {
        std ::swap(y1, y2);
    }
    for (int i = y1; i <= y2; i++)
    {
        Vy[i] = std ::max(v, Vy[i]);
    }
}
void rmq_init()
{
    for (int i = 0; i < 50000; i++)
    {
        Dpx2[i][0] = Vx10[i];
        Dpy2[i][0] = Vy10[i];
    }
    for (int j = 1; (1 << j) < 50000; j++)
    {
        for (int i = 0; i + (1 << j) < 50000; i++)
        {
            Dpx2[i][j] = std ::max(Dpx2[i][j - 1], Dpx2[i + (1 << (j - 1))][j - 1]);
            Dpy2[i][j] = std ::max(Dpy2[i][j - 1], Dpy2[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int rmq_request(int r, int l)
{
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1)
    {
        k++;
    }
    return std ::max(Dpx2[l][k], Dpx2[r - (1 << k) + 1][k]);
}

int main()
{
    int n, m;
    std ::cin >> n >> m;
    // int x_1[n], y_1[n], x_2[n], y_2[n], v[n];
    // int x_1_i[m], y_1_i[m], x_2_i[m], y_2_i[m];
    // memset(Dpx, 0, sizeof(Dpx));
    // memset(Dpy, 0, sizeof(Dpy));
    memset(Vx, 0, sizeof(Vx));
    memset(Vy, 0, sizeof(Vy));
    memset(Vx10, 0, sizeof(Vx10));
    memset(Vy10, 0, sizeof(Vy10));
    memset(Dpx2, 0, sizeof(Dpx2));
    memset(Dpy2, 0, sizeof(Dpy2));
    for (int i; i < n; i++)
    {
        int v_tem;
        int x1_tem, y1_tem, x2_tem, y2_tem;
        std ::cin >> x1_tem >> y1_tem >> x2_tem >> y2_tem >> v_tem;
        Vf_x(x1_tem, x2_tem, v_tem);
        Vf_y(y1_tem, y2_tem, v_tem);
    }
    for (int i = 0; i < m; i++)
    {
        std ::cin >> x_1_i[i] >> x_2_i[i] >> y_1_i[i] >> y_2_i[i];
    }
    for (int i = 0; i < 50000; i += 10)
    {
        for (int j = i; j < i + 10; j++)
        {
            Vx10[i] = std ::max(Vx[j], Vx10[i]);
            Vy10[i] = std ::max(Vy[j], Vy10[i]);
        }
    }
    // 分别构建x,y的区间最大值，然后取max即可
    rmq_init();
}

#endif

#if Problem == Problem7
typedef struct Area
{
    int x1, y1, x2, y2, v;
    int mark;
    Area()
    {
        mark = 0;
    }
    bool operator<(const Area &a) const
    {
        if (mark == 0 && a.mark == 0)
        {
            return x1 < a.x1;
        }
        else if (mark == 0 && a.mark == 1)
        {
            return x2 < a.x1;
        }
        else if (mark == 1 && a.mark == 0)
        {
            return a.operator<(*this);
        }
        // else if (mark == 1 && a.mark == 0)
        // {
        //     return x1 <= a.x2;
        // }
        else if (mark == 0 && a.mark == -1)
        {
            return x1 <= a.x2;
        }
        else if (mark == -1 && a.mark == 0)
        {
            return a.operator<(*this);
        }
        // else if (mark == -1 && a.mark == 0)
        // {
        //     return x2 < a.x1;
        // }
    }
} Area;
typedef struct Area2
{
    int x1, y1, x2, y2, v;
    int mark;
    Area2()
    {
        mark = 0;
    }
    bool operator<(const Area2 &a) const
    {
        return v > a.v;
    }
} Area2;
typedef struct Area3
{
    int x1, y1, x2, y2, v;
    int mark;
    Area3()
    {
        mark = 0;
    }
    bool operator<(const Area3 &a) const
    {
        if (mark == 0 && a.mark == 0)
        {
            return x2 < a.x2;
        }
        else if (mark == 0 && a.mark == 1)
        {
            return x2 < a.x1;
        }
        else if (mark == 1 && a.mark == 0)
        {
            return a.operator<(*this);
        }
        else if (mark == 0 && a.mark == -1)
        {
            return x1 <= a.x2;
        }
        else if (mark == -1 && a.mark == 0)
        {
            return a.operator<(*this);
        }
    }
} Area3;
// lower_bound
bool judge_cross(int x1, int y1, int x2, int y2, int x1_i, int y1_i, int x2_i, int y2_i)
{
    if (x2_i < x1 || x1_i > x2 || y2_i < y1 || y1_i > y2)
    {
        return false;
    }
    return true;
}
Area Point[500000];
Area3 Point3[500000];
Area2 Point2[500000];
// std::vector <Area> Point(500000);
// int x_1_i[500000], y_1_i[500000], x_2_i[500000], y_2_i[500000];
int head[1000], tail[5000];
// 宽度5000
int main()
{
    int n, m;
    std ::cin >> n >> m;
    for (int i; i < n; i++)
    {
        int v_tem;
        int x1_tem, y1_tem, x2_tem, y2_tem;
        std ::cin >> x1_tem >> x2_tem >> y1_tem >> y2_tem >> v_tem;
        Point[i].x1 = x1_tem;
        Point[i].y1 = y1_tem;
        Point[i].x2 = x2_tem;
        Point[i].y2 = y2_tem;
        Point[i].v = v_tem;
    }
    // for (int i = 0; i < m; i++)
    // {
    //     std ::cin >> x_1_i[i] >> x_2_i[i] >> y_1_i[i] >> y_2_i[i];
    // }
    std::sort(Point, Point + n);
    for (int i = 0; i < m; i++)
    {
        Area temp1;
        int x_1_i, y_1_i, x_2_i, y_2_i;
        std ::cin >> x_1_i >> x_2_i >> y_1_i >> y_2_i;
        temp1.x1 = x_1_i;
        temp1.x2 = x_2_i;
        temp1.y1 = y_1_i;
        temp1.y2 = y_2_i;
        temp1.mark = 1;
        Area3 temp2;
        temp2.x1 = x_1_i;
        temp2.x2 = x_2_i;
        temp2.y1 = y_1_i;
        temp2.y2 = y_2_i;
        temp2.mark = -1;
        int left = std ::lower_bound(Point, Point + n, temp1) - Point;

        if (left > 0)
        {
            left--;
        }
        memcpy(Point3, Point + left, sizeof(Area2) * (n - left));
        std ::sort(Point3, Point3 + n - left);
        int right = std ::lower_bound(Point3, Point3 + n - left, temp2) - Point3;
        if (right < n - 1)
        {
            right++;
        }
        int length = right - left + 1;
        // Area2 *Point2 = (Area2 *)malloc(sizeof(Area2) * length);
        if (length > 10000)
        {
            int flag = 1;
            for (int j = 0; j < n; j++)
            {
                if (judge_cross(Point[j].x1, Point[j].y1, Point[j].x2, Point[j].y2, x_1_i, y_1_i, x_2_i, y_2_i))
                {
                    std ::cout << Point[j].v << std ::endl;
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                std::cout << 0 << std ::endl;
            }
            continue;
        }
        memcpy(Point2, Point + left, sizeof(Area2) * length);
        std ::sort(Point2, Point2 + length);
        int flag = 1;
        for (int j = 0; j < length; j++)
        {
            if (judge_cross(Point2[j].x1, Point2[j].y1, Point2[j].x2, Point2[j].y2, x_1_i, y_1_i, x_2_i, y_2_i))
            {
                std ::cout << Point2[j].v << std ::endl;
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            std::cout << 0 << std ::endl;
        }
    }

    // for (int i =0; i < m; i++){
    //     int flag = 1;
    //     for(int j = 0; j <n; j ++){
    //         if(judge_cross(Point[j].x1, Point[j].y1, Point[j].x2, Point[j].y2, x_1_i[i], y_1_i[i], x_2_i[i], y_2_i[i])){
    //             std ::cout << Point[j].v << std ::endl;
    //             flag = 0;
    //             break;
    //         }
    //     }
    //     if(flag){
    //         std:: cout << 0 << std ::endl;
    //     }
    // }
}

#endif

#if Problem == Problem8
typedef struct Area
{
    int x1, y1, x2, y2, v;
    int mark;
    Area()
    {
        mark = 0;
    }
    bool operator<(const Area &a) const
    {
        return x1 < a.x1 || (x1 == a.x1 && x2 < a.x2);
    }
} Area;
typedef struct Area3
{
    int x1, y1, x2, y2, v;
    int mark;
    Area3()
    {
        mark = 0;
    }
    bool operator<(const Area3 &a) const
    {
        return v > a.v;
    }
} Area3;
typedef struct Area2
{
    int x1, y1, x2, y2, v;
    int mark;
    Area2()
    {
        mark = 0;
    }
    bool operator<(const Area2 &a) const
    {
        if (mark == 0 && a.mark == 0)
        {
            return x2 < a.x2 || (x2 == a.x2 && x1 < a.x1);
        }
    }
} Area2;
// lower_bound
bool judge_cross(int x1, int y1, int x2, int y2, int x1_i, int y1_i, int x2_i, int y2_i)
{
    if (x2_i < x1 || x1_i > x2 || y2_i < y1 || y1_i > y2)
    {
        return false;
    }
    return true;
}
Area Point[500000];
Area2 Point2[500000];
Area3 Point3[500000];

// std::vector <Area> Point(500000);
// int x_1_i[500000], y_1_i[500000], x_2_i[500000], y_2_i[500000];
int head[5000];
// 宽度5000
/*
n, k
? < k
klgk < n
*/
int main()
{
    int n, m;
    std ::cin >> n >> m;
    for (int i; i < n; i++)
    {
        int v_tem;
        int x1_tem, y1_tem, x2_tem, y2_tem;
        std ::cin >> x1_tem >> x2_tem >> y1_tem >> y2_tem >> v_tem;
        Point[i].x1 = x1_tem;
        Point[i].y1 = y1_tem;
        Point[i].x2 = x2_tem;
        Point[i].y2 = y2_tem;
        Point[i].v = v_tem;
        // Point2[i].x1 = x1_tem;
        // Point2[i].y1 = y1_tem;
        // Point2[i].x2 = x2_tem;
        // Point2[i].y2 = y2_tem;
        // Point2[i].v = v_tem;
    }

    std::sort(Point, Point + n);
    for (int i = n - 1; i >= 0; i--)
    {
        int tem_x2 = Point[i].x2;
        head[tem_x2 / 100] = i;
    }
    for (int i = 0; i < m; i++)
    {
        Area temp1;
        int x_1_i, y_1_i, x_2_i, y_2_i;
        std ::cin >> x_1_i >> x_2_i >> y_1_i >> y_2_i;
        temp1.x1 = x_2_i;
        temp1.x2 = x_2_i;
        temp1.y1 = y_1_i;
        temp1.y2 = y_2_i;
        temp1.mark = 0;
        int right = std ::upper_bound(Point, Point + n, temp1) - Point - 1;
        int left = head[x_1_i / 100];
        int length = right - left + 1;
        if (length > 50000)
        {
            int flag = 1;
            for (int j = 0; j < n; j++)
            {
                if (judge_cross(Point[j].x1, Point[j].y1, Point[j].x2, Point[j].y2, x_1_i, y_1_i, x_2_i, y_2_i))
                {
                    std ::cout << Point[j].v << std ::endl;
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                std::cout << 0 << std ::endl;
            }
            continue;
        }
        else
        {
            int v_max = 0;
            for (int j = left; j <= right; j++)
            {
                if (judge_cross(Point[j].x1, Point[j].y1, Point[j].x2, Point[j].y2, x_1_i, y_1_i, x_2_i, y_2_i))
                {
                    v_max = std ::max(v_max, Point[j].v);
                }
            }
            std :: cout << v_max << std :: endl;
        }
    }
}

#endif
