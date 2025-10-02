#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <locale>

using namespace std;
using namespace std::chrono;

struct sort_stats
{
    long long comparisons = 0;
    long long swaps = 0;
    long long duration = 0;
};

void read_file_to_vector(string filename, vector<int>& output)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Не удалось открыть файл" << filename << endl;
    }

    int num;

    while(file >> num)
    {
        output.push_back(num);
    }

    file.close();
}

void print_vec(vector<int> nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
}

void print_stats(sort_stats& stats, string sort_name, vector<int> vec_name)
{
    cout << sort_name << endl;
    cout << "Результат работы" << endl;
    print_vec(vec_name);
    cout << "Время работы: " << stats.duration << " наносекунд" <<endl;
    cout << "Сравнений: " << stats.comparisons << endl;
    cout << "Обменов: " << stats.swaps << endl;
    cout << endl;
}

void selection_sort(vector<int>& nums, bool mode = true, sort_stats& stats = *(new sort_stats()))
{
    auto st = high_resolution_clock::now();
    stats.comparisons = 0;
    stats.swaps = 0;

    if (nums.size() <= 1)
    {
        auto en = high_resolution_clock::now();
        stats.duration = duration_cast<nanoseconds>(en - st).count();
        return;
    }

    for (int i = 0; i < nums.size() - 1; i++)
    {
        int idx = i;

        for (int j = i + 1; j < nums.size(); j++)
        {
            stats.comparisons++;
            if(mode ? nums[j] < nums[idx] : nums[j] > nums[idx])
            {
                idx = j;
            }
        }
        if (idx != i)
        {
           stats.swaps++;
           swap(nums[i], nums[idx]);
        }
    }

    auto en = high_resolution_clock::now();
    stats.duration = duration_cast<nanoseconds>(en - st).count();
}

void insertion_sort(vector<int>& nums, bool mode = true, sort_stats& stats = *(new sort_stats()))
{
    auto st = high_resolution_clock::now();
    stats.comparisons = 0;
    stats.swaps = 0;

    if (nums.size() <= 1)
    {
        auto en = high_resolution_clock::now();
        stats.duration = duration_cast<nanoseconds>(en - st).count();
        return;
    }

    for (int i = 1; i < nums.size(); i++)
    {
        int c = nums[i];
        int j = i - 1;

        while (j >= 0 && mode ? nums[j] > c : nums[j] < c)
        {
           stats.comparisons++;
           stats.swaps++;
           nums[j + 1] = nums[j];
                j --;
        }

        nums[j + 1] = c;
    }

    auto en = high_resolution_clock::now();
    stats.duration = duration_cast<nanoseconds>(en - st).count();
}

void bubble_sort(vector<int>& nums, bool mode = true, sort_stats& stats = *(new sort_stats()))
{
    auto st = high_resolution_clock::now();
    stats.comparisons = 0;
    stats.swaps = 0;

    if (nums.size() <= 1)
    {
        auto en = high_resolution_clock::now();
        stats.duration = duration_cast<nanoseconds>(en - st).count();
        return;
    }

    for (int i = 0; i < nums.size() - 1; i++)
    {
        for (int j = 0; j < nums.size() - i - 1; j++)
        {
            stats.comparisons++;
            if (mode ? nums[j] > nums[j + 1] : nums[j] < nums[j + 1])
            {
                stats.swaps++;
                swap(nums[j], nums[j + 1]);
            }
        }
    }

    auto en = high_resolution_clock::now();
    stats.duration = duration_cast<nanoseconds>(en - st).count();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    vector<int> vec;

    read_file_to_vector("mass.txt", vec);

    vector<int> nums1 = vec, nums2 = vec, nums3 = vec;
    sort_stats stats1, stats2, stats3;

    selection_sort(nums1, false, stats1);
    print_stats(stats1, "Сортировка выбором", nums1);

    insertion_sort(nums2, false, stats2);
    print_stats(stats2, "Сортировка вставками", nums2);

    bubble_sort(nums3, false, stats3);
    print_stats(stats3, "Сортировка обменом", nums3);

    return 0;
}
