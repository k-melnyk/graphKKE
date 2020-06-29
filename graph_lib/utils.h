#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
#include <random>
#include <numeric>
#include <queue>

size_t NumberOfDigitsInNumber(int number) {
    size_t numberOfDigits = 0;

    while(number >= 1) {
        number /= 10;
        ++numberOfDigits;
    }

    return numberOfDigits;
}

int ConcatenateInts(std::vector<int> vectorToConcatenate) {
    int number = vectorToConcatenate[0];

    for (size_t i = 1; i < vectorToConcatenate.size(); ++i) {
        if (vectorToConcatenate[i] / 10 < 1) {
            number = number * 10 + vectorToConcatenate[i];
        }
        else {
            number = number * static_cast<int>(pow(10, NumberOfDigitsInNumber(vectorToConcatenate[i])) + vectorToConcatenate[i]);
        }
    }

    return number;
}

template <typename TYPE>
void UniqueValuesInVector(std::vector<TYPE>& toFindUnique) {
    std::sort(toFindUnique.begin(), toFindUnique.end());
    typename std::vector<TYPE>::iterator it = std::unique(toFindUnique.begin(), toFindUnique.end());

    toFindUnique.resize(std::distance(toFindUnique.begin(), it));
}

void AliasSetup(const std::vector<double>& vecOfProbs, std::vector<size_t>& J, std::vector<double>& q) {
    const size_t numberOfOutcomes = vecOfProbs.size();

    std::stack<size_t> smallerProbs;
    std::stack<size_t> largerProbs;

    for (size_t i = 0; i < numberOfOutcomes; ++i) {
        q[i] = numberOfOutcomes * vecOfProbs[i];

        if (q[i] < 1.0) {
            smallerProbs.push(i);
        }
        else {
            largerProbs.push(i);
        }
    }

    while (!smallerProbs.empty() && !largerProbs.empty()) {
        size_t smallVal = smallerProbs.top();
        size_t largeVal = largerProbs.top();

        smallerProbs.pop();
        largerProbs.pop();

        J[smallVal] = largeVal;
        q[largeVal] = q[largeVal] - (1.0 - q[smallVal]);

        if (q[largeVal] < 1.0) {
            smallerProbs.push(largeVal);
        }
        else {
            largerProbs.push(largeVal);
        }
    }
}

std::vector<size_t> AliasDraw(size_t numberOfSamples, const std::vector<size_t>& J, const std::vector<double>& q) {
    std::vector<size_t> X;
    X.reserve(numberOfSamples);

    const size_t numberOfOutcomes = J.size();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> uniformDistribution(0.0, 1.0);

    for (size_t i = 0; i < numberOfSamples; ++i) {
        const size_t indexOfOutcome = static_cast<size_t>(floor(numberOfOutcomes * uniformDistribution(generator)));

        if (uniformDistribution(generator) < q[indexOfOutcome]) {
            X.push_back(indexOfOutcome);
        }
        else {
            X.push_back(J[indexOfOutcome]);
        }
    }
    return X;
}


struct HashFunction {
    size_t operator()(const std::pair<size_t, size_t>& pairNodes) const noexcept{
        int concatKey = ConcatenateInts(std::vector<int>{static_cast<int>(pairNodes.first),
                                                         static_cast<int>(pairNodes.second)});

        return static_cast<size_t>(concatKey);
    }
};



#endif // UTILS_H
