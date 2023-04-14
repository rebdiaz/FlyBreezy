#include <vector>
#include <utility>
#include <unordered_map>
#include <string>

void merge(std::vector<std::pair<std::string, double>>& arr, int left, int mid, int right);
void mergeSort(std::vector<std::pair<std::string, double>>& arr, int left, int right);
//city
void printSortedCityDelayLikelihoods(const std::unordered_map<std::string, double>& cityDelayLikelihoods);
//airline
void printSortedAirlineDelayLikelihoods(const std::unordered_map<std::string, double>& airlineDelayLikelihoods);
