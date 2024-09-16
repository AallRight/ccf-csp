#include <bits/stdc++.h>
#include <sstream>
#define Problem1 1
#define Problem2 2
#define Problem3 3
#define Problem4 4
#define Problem5 5

#define Problem 4

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
    int n, word_list_length;
    std ::cin >> n >> word_list_length;
    std ::vector<std ::string> alphabet;
    std ::vector<std ::string> words;
    std ::vector<int> words_times;
    for (int i = 0; i < n; i++)
    {
        std ::string temp;
        std ::cin >> temp;
        int times;
        std ::cin >> times;
        alphabet.push_back(temp);
        words_times.push_back(times);
    }
    std ::map<std ::string, int> word_map;
    for (int i = 0; i < n; i++)
    {
        std ::string temp = *(alphabet.begin() + i);
        int times = *(words_times.begin() + i);
        int pos = 0;
        while (temp[pos] != '\0')
        {
            for (int j = 0; j < pos; j++)
            {
                std ::string alpha;
                alpha.assign(temp, j, pos);
                if (word_map.find(alpha) == word_map.end())
                {
                    word_map.insert(std ::pair<std ::string, int>(alpha, 1));
                }
            }
        }
    }
    // std :: istringstream word_list[10];
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
    int **dp = (int **) malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        dp[i] = (int *) calloc(20000, sizeof(int));
    }
    // int dp[1000][20000] = {0};
    // 每个仓库的dp值
    int item_num[1000] = {0};
    // int item[1000][1000];
    int **item = (int **) malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        item[i] = (int *) malloc(sizeof(int) * 1000);
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
            if (item_sold > v){
                break;
            }
        }
    }
    // int dp_first_storage[1000][20000] = {0};
    int **dp_first_storage = (int **) malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        dp_first_storage[i] = (int *) calloc(20000, sizeof(int));
    }
    for (int i = 0; i < 20000; i++)
    {
        dp_first_storage[0][i] = dp[0][i];
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < 20000; j++)
        {
            for (int k = 0; k <= j; k++)
            {
                dp_first_storage[i][j] = std ::max(dp_first_storage[i][j], dp_first_storage[i - 1][j - k] + dp[i][k]);
            }
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

#endif
