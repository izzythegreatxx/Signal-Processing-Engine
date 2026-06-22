#include <vector>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main()
{
    std::vector<double> x{0, 1, 2, 3, 4};
    std::vector<double> y{0, 1, 4, 9, 16};

    plt::plot(x, y);
    plt::title("Test Plot");
    plt::save("test.png");

    return 0;
}
