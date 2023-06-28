#include <iostream>
#include <random>
#include <vector>

int main() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 10);

    std::vector<int> numbers;
    while (numbers.size() < 3) {
        int random_num = distribution(generator);
        if (std::find(numbers.begin(), numbers.end(), random_num) == numbers.end()) {
            numbers.push_back(random_num);
        }
    }

    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}