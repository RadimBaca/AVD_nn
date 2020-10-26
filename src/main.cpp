#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


void sift_test();

int main(void)
{
    sift_test();

    return 0;
}



void sift_test() {
    size_t node_count = 1000000;
    size_t qsize = 10000;
    //size_t qsize = 1000;
    //size_t vecdim = 4;
    size_t vecdim = 128;
    size_t answer_size = 100;
    uint32_t k = 10;

    float* mass = new float[node_count * vecdim];
    std::ifstream input("../sift1M/sift1M.bin", std::ios::binary);
    if (!input.is_open()) std::runtime_error("Input data file not opened!");
    input.read((char*)mass, node_count * vecdim * sizeof(float));
    input.close();

    float* massQ = new float[qsize * vecdim];
    //ifstream inputQ("../siftQ100k.bin", ios::binary);
    std::ifstream inputQ("../sift1M/siftQ1M.bin", std::ios::binary);
    if (!input.is_open()) std::runtime_error("Input query file not opened!");
    //ifstream inputQ("../../1M_d=4q.bin", ios::binary);
    inputQ.read((char*)massQ, qsize * vecdim * sizeof(float));
    inputQ.close();

    unsigned int* massQA = new unsigned int[qsize * answer_size];
    //ifstream inputQA("../knnQA100k.bin", ios::binary);
    std::ifstream inputQA("../sift1M/knnQA1M.bin", std::ios::binary);
    if (!input.is_open()) std::runtime_error("Input result file not opened!");
    inputQA.read((char*)massQA, qsize * answer_size * sizeof(int));
    inputQA.close();


    /////////////////////////////////////////////////////// QUERY PART
    std::cout << "Start querying\n";
    std::vector<std::pair<float, float>> precision_time;
    

    int sum = 0;
    int min_time;
    for (int i = 0; i < 3; i++)
    {
#ifdef COLLECT_STAT
        hnsw.stat_.clear();
#endif
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < qsize; i++)
        {
            //hnsw.aproximateKnn(&massQ[i * vecdim], k, ef);
        }
        auto end = std::chrono::steady_clock::now();
        int time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        sum += time;
        min_time = i == 0 ? time : std::min(min_time, time);
#ifdef COLLECT_STAT
        std::cout << (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / qsize << " [us]; ";
#endif
    }
    std::cout << "avg: " << (float)sum / (qsize * 3) << " [us]; " << "min: " << min_time / qsize<< " [us]; \n";
    


    delete[] mass;
    delete[] massQ;
    delete[] massQA;
}