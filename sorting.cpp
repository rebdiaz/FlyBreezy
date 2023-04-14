#include "sorting.h"
#include <iostream>

//Taking in a vector of pairs, each pair represents a city or airline and its delay likelihood
void merge(std::vector<std::pair<std::string, double>>& arr, int left, int mid, int right) {
    int sizeLeft = mid - left + 1; //calculate the size of the left subarray 
    int sizeRight = right - mid;   //calculate the size of the right subarray

    std::vector<std::pair<std::string, double>> leftArr(sizeLeft); // store the left subarray
    std::vector<std::pair<std::string, double>> rightArr(sizeRight); // store the right subarray

    for (int i = 0; i < sizeLeft; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < sizeRight; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < sizeLeft && j < sizeRight) {
        //compare the second element (delay likelihood) of current pair in leftArr with that of current pair in rightArr
        if (leftArr[i].second >= rightArr[j].second) { 
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < sizeLeft) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < sizeRight) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<std::pair<std::string, double>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
//City
void printSortedCityDelayLikelihoods(const std::unordered_map<std::string, double>& cityDelayLikelihoods) {
    //vector of pairs;each pair consists of std::string(the city) & double (the delay likelihood)
    std::vector<std::pair<std::string, double>> cityDelayLikelihoodsVec;

    cityDelayLikelihoodsVec.reserve(cityDelayLikelihoods.size()); //since it is large data set
    //Inserting the elements from the unordered_map cityDelayLikelihoods into the vector to pass into the sorting function
    cityDelayLikelihoodsVec.insert(cityDelayLikelihoodsVec.end(), cityDelayLikelihoods.begin(), cityDelayLikelihoods.end());

    //sorting from first element to last element
    mergeSort(cityDelayLikelihoodsVec, 0, cityDelayLikelihoodsVec.size() - 1);
    //iterate through vector
    //'entry' reps each std::pair<std::string, double> element in the cityDelayLikelihoodsVec vector
    for (const auto& entry : cityDelayLikelihoodsVec) {
        //entry.first refers to city name, entry.second refers to delay likelihood
        std::cout << "City: " << entry.first << ", Delay Likelihood: " << entry.second << "%" << std::endl;
        std::cout << std::endl; 

    }
}


//Airline
//std::string keys (representing airline names) and double values (delay likelihoods)
void printSortedAirlineDelayLikelihoods(const std::unordered_map<std::string, double>& airlineDelayLikelihoods) {
    
    std::vector<std::pair<std::string, double>> airlineDelayLikelihoodsVector;

    airlineDelayLikelihoodsVector.reserve(airlineDelayLikelihoods.size());
    //Inserting the elements from the unordered_map airlineDelayLikelihoods into the vector for sorting
    airlineDelayLikelihoodsVector.insert(airlineDelayLikelihoodsVector.end(), airlineDelayLikelihoods.begin(), airlineDelayLikelihoods.end());
    
    //sorting from the first element to the last element
    mergeSort(airlineDelayLikelihoodsVector, 0, airlineDelayLikelihoodsVector.size() - 1);

    std::cout << "Airline Delay Likelihoods:" << std::endl;
    for (const auto& pair : airlineDelayLikelihoodsVector) {
        const std::string& airlineCode = pair.first;
        double delayLikelihood = pair.second;

        std::cout << airlineCode << ": " << delayLikelihood << "%" << std::endl;
        std::cout << std::endl; 

    }
}
