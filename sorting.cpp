
#include "sorting.h"
#include <iostream>

void merge(std::vector<std::pair<std::string, double>>& arr, int left, int mid, int right) { //adapted from sorting slides cop3530
    int m1 = mid - left + 1;
    int m2 = right - mid;

    std::vector<std::pair<std::string, double>> leftArr(m1); // store in left subarray
    std::vector<std::pair<std::string, double>> rightArr(m2); // store in right subarray

    for (int i = 0; i < m1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < m2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }
    int i, j, k;
    i = 0;
    j = 0;
    k = left;

    while (i < m1 && j < m2) {
        //compare delay likelihood of pair in leftArr with that in rightArr
        if (leftArr[i].second >= rightArr[j].second) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < m1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < m2) {
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
void sortedCityDelay(std::unordered_map<std::string, double>& cityDelayCalc) {
    std::vector<std::pair<std::string, double>> cityDelayVec; //city and delay vector

    cityDelayVec.reserve(cityDelayCalc.size()); //for vector capacity https://cplusplus.com/reference/vector/vector/reserve/
    for (auto& elements : cityDelayCalc) { //insert elements from map to vector for sorting https://www.geeksforgeeks.org/sorting-a-map-by-value-in-c-stl/amp/
        cityDelayVec.push_back(elements);
    }

    mergeSort(cityDelayVec, 0, cityDelayVec.size() - 1); //sort from first to last element

    for (auto& elements : cityDelayVec) { // get city and the delay

        std::cout << "City: " << elements.first << ", Delay Likelihood: " << elements.second << "%" << std::endl;
        std::cout << std::endl;

    }
}


//Airline
void sortedAirlineDelay(std::unordered_map<std::string, double>& airlineDelayCalc) {

    std::vector<std::pair<std::string, double>> airlineDelayVec;

    airlineDelayVec.reserve(airlineDelayCalc.size()); //since it is a large data set

    for (auto& elements : airlineDelayCalc) { //insert elements from map to vector for sorting
        airlineDelayVec.push_back(elements);
    }

    mergeSort(airlineDelayVec, 0, airlineDelayVec.size() - 1); //sorting from the first element to the last element

    std::cout << "Airline Delay Likelihoods:" << std::endl;

    for (auto& pair : airlineDelayVec) {
        std::string& airlineCode = pair.first;
        double delayLikelihood = pair.second;

        std::cout << airlineCode << ": " << delayLikelihood << "%" << std::endl;
        std::cout << std::endl;

    }
    // Print top 5 worst airlines
    std::cout << "Top 5 Worst Airlines to Fly to Based on Delay Likelihood: " << std::endl;
    for(int i = 0; i < 5; i++){
        std::cout << (i+1) << ". " << airlineDelayVec.at(i).first << std::endl;
    }
    std::cout << std::endl;
    // Print top 5 best airlines
    std::cout << "Top 5 Best Airlines to Fly to Based on Delay Likelihood: " << std::endl;
    int size = airlineDelayVec.size();
    for(int i = 0; i < 5; i++){
        std::cout << (i+1) << ". " << airlineDelayVec.at(size - 1 - i).first << std::endl;
    }
    std::cout << std::endl;
}


//Quick uses information from slide 122 of the Graphs ppt
void quickSort(std::vector<std::pair<std::string, double>>&arr, int low, int high)
{
    if (low<high)
    {
        double pivot = partition(arr, low, high);
        quickSort(arr, low, pivot-1);
        quickSort(arr, pivot+1, high);
    }
}

double partition(std::vector<std::pair<std::string, double>>&arr, int low, int high)
{
    double pivot = arr[low].second;
    int up = low, down = high;
    while (up < down)
    {
        for (int j = up; j < high; j++)
        {
            if (arr[up].second < pivot)
            {
                break;
            }
            up++;
        }
        for (int j = high; j > low; j--)
        {
            if (arr[down].second > pivot)
            {
                break;
            }
            down--;
        }
        if (up < down)
        {
            std::string s =arr[up].first;
            double i = arr[up].second;
            arr[up].first = arr[down].first;
            arr[up].second = arr[down].second;
            arr[down].first = s;
            arr[down].second = i;
        }
    }
    std::string s2 =arr[low].first;
    double i2 = arr[low].second;
    arr[low].first = arr[down].first;
    arr[low].second = arr[down].second;
    arr[down].first = s2;
    arr[down].second = i2;
    return down;
}

//City Quick Sort
void sortedCityDelayQ(std::unordered_map<std::string, double>& cityDelayCalc) {
    std::vector<std::pair<std::string, double>> cityDelayVec; //city and delay vector

    cityDelayVec.reserve(cityDelayCalc.size()); //for vector capacity 
    for (auto& elements : cityDelayCalc) { //insert elements from map to vector for sorting 
        cityDelayVec.push_back(elements);
    }

    quickSort(cityDelayVec, 0, cityDelayVec.size() - 1); //sort from first to last element

    for (auto& elements : cityDelayVec) { // get city and the delay

        std::cout << "City: " << elements.first << ", Delay Likelihood: " << elements.second << "%" << std::endl;
        std::cout << std::endl;

    }
    // Print top 5 worst cities
    std::cout << "Top 5 Worst Cities to Fly to Based on Delay Likelihood: " << std::endl;
    for(int i = 0; i < 5; i++){
        std::cout << (i+1) << ". " << cityDelayVec.at(i).first << std::endl;
    }
    std::cout << std::endl;
    // Print top 5 best cities
    std::cout << "Top 5 Best Cities to Fly to Based on Delay Likelihood: " << std::endl;
    int size = cityDelayVec.size();
    for(int i = 0; i < 5; i++){
        std::cout << (i+1) << ". " << cityDelayVec.at(size - 1 - i).first << std::endl;
    }
    std::cout << std::endl;
}

//Airline Quick Sort
void sortedAirlineDelayQ(std::unordered_map<std::string, double>& airlineDelayCalc) {

    std::vector<std::pair<std::string, double>> airlineDelayVec;

    airlineDelayVec.reserve(airlineDelayCalc.size()); //since it is a large data set

    for (auto& elements : airlineDelayCalc) { //insert elements from map to vector for sorting
        airlineDelayVec.push_back(elements);
    }

    quickSort(airlineDelayVec, 0, airlineDelayVec.size() - 1); //sorting from the first element to the last element

    std::cout << "Airline Delay Likelihoods:" << std::endl;

    for (auto& pair : airlineDelayVec) {
        std::string& airlineCode = pair.first;
        double delayLikelihood = pair.second;

        std::cout << airlineCode << ": " << delayLikelihood << "%" << std::endl;
        std::cout << std::endl;

    }
    // Print top 5 worst airlines
    std::cout << "Top 5 Worst Airlines to Fly to Based on Delay Likelihood: " << std::endl;
    for(int i = 0; i < 5; i++){
        std::cout << (i+1) << ". " << airlineDelayVec.at(i).first << std::endl;
    }
    std::cout << std::endl;
    // Print top 5 best airlines
    std::cout << "Top 5 Best Airlines to Fly to Based on Delay Likelihood: " << std::endl;
    int size = airlineDelayVec.size();
    for(int i = 0; i < 5; i++){
        std::cout << (i+1) << ". " << airlineDelayVec.at(size - 1 - i).first << std::endl;
    }
    std::cout << std::endl;
}
