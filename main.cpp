#include "NumberSeries.h"
#include "benchmark.h"
#include "dynamic_NumberSeries.h"
using namespace std;
int main() {

    auto b = benchmark{};
    vector<NumberSeries> stackSeries(100000);

    b.mark();
    auto m = NumberSeries::MakeRandom(100);
    for(auto& v : stackSeries){
        v = NumberSeries::MakeRandom(100);
        v += m;
    }
    b.mark();
    sort(stackSeries.begin(), stackSeries.end());
    b.mark();

    vector<dynamic_NumberSeries> seriesVec(100000);

    b.mark();
    auto n = dynamic_NumberSeries::MakeRandom(100);
    for(auto& v : seriesVec){
        v = dynamic_NumberSeries::MakeRandom(100);
        v += n;
    }
    b.mark();
    sort(seriesVec.begin(), seriesVec.end());
    b.mark();
    b.report();
    return 0;
}
