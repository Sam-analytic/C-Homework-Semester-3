#include <iostream>
#include <set>
#include <random>
#include<map>
#include<string>
#include<fstream>

class DiscreteState {
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const {
        return s == state;
    }
};

class SegmentState {
private:
    int const beg, end;
    
public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }
    
    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class SetState {
private:
    std::set<int> const states;
    
public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }
    
    bool contains(int s) const {
        return states.count(s) > 0;
    }
};

class ProbabilityTest {
    
public:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;
    
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }
    
    template<typename T> 
    float operator()(T const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        return static_cast<float>((good)/static_cast<float>(test_count));
    }
    friend void test_unit();
};

template<typename T>
void test_unit(T const& s,int min, int max, std::string filename, int test_size)
{
    std::ofstream myfile(filename);
    for (unsigned i =0 ; i != test_size; ++i)
    {
        int seed = std::rand();
        int test_count = i*100;
        ProbabilityTest test_params(seed, min, max, test_count);
        std::default_random_engine rng(test_params.seed);
        std::uniform_int_distribution<int> dstr(test_params.test_min, test_params.test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_params.test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        auto result = static_cast<float>(good)/static_cast<float>(test_params.test_count);
        myfile << result << ", ";
    }
    myfile.close();
}

template<typename T>
void size_test_unit(T const& s,int min, int max, std::string filename, int test_count)
{
    std::ofstream myfile(filename);
    for (unsigned i =0 ; i != test_count; ++i)
    {
        int seed = std::rand();
        int margin = i*10;
        ProbabilityTest test_params(seed, min - margin, max + margin, 100);
        std::default_random_engine rng(test_params.seed);
        std::uniform_int_distribution<int> dstr(test_params.test_min, test_params.test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_params.test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        auto result = static_cast<float>(good)/static_cast<float>(test_params.test_count);
        myfile << result << ", ";
    }
    myfile.close();
}

int main(int argc, const char * argv[]) {
    DiscreteState d(1);
    SegmentState s(0,10);
    SetState ss({1, 3, 5, 7, 23, 48, 57,11,11,11,11,22,22,33,44,12,12,12,13,14,14,25,2,5,5,5,5,5,6,76,7,,8,86,7,5,64,56,4,54,5,4,53,5,3,5,34,5,34,5,34,5,35,34,5,3,4,5,3,5,2,54,6,68,76,9,67,6,78,76,8,67,87,8,67,8,67,86,78,67,8,65,7,86,7,5,6,7,57,57,56,7,67,56,7,56,7,5,63,54,63,45,43,53,53,4,34, 60, 90, 99});
    ProbabilityTest pt(10,0,100,100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
    size_test_unit<SetState> (ss,0,100, "locco_2.csv", 1000);
    return 0;
}
