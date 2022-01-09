#include <vector>
#include <numeric>
#include <iostream>

class Person
{
    public:
    
        Person(double const w)
        : weight(w)
        {}
        
        double getWeight() const
        {
            return weight;
        }
    
    private:
        double weight;
};

int main() {
    std::vector<Person> group {Person(50.0), Person(80.0)};
    std::vector<double> weights{};
    
    std::accumulate(begin(group), end(group), &weights,
                [](std::vector<double>* currentWeights, Person const& person)
                {
                    currentWeights->push_back(person.getWeight());
                    return currentWeights;
                });
    
    for (auto const& i: weights)
    {
        std::cout << i << ",";   
    }   
    
    return 0;
}
