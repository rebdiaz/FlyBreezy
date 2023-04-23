#pragma once

#include <vector>
#include <utility>
#include <unordered_map>
#include <string>

void merge(std::vector<std::pair<std::string, double>>& arr, int left, int mid, int right);
void mergeSort(std::vector<std::pair<std::string, double>>& arr, int left, int right);
//city
void sortedCityDelay(std::unordered_map<std::string, double>& cityDelayLikelihoods);
//airline
void sortedAirlineDelay(std::unordered_map<std::string, double>& airlineDelayLikelihoods);

void quickSort(std::vector<std::pair<std::string, double>>&arr, int low, int high);
int partition(std::vector<std::pair<std::string, double>>&arr, int low, int high);

//city quick sort
void sortedCityDelayQ(std::unordered_map<std::string, double>& cityDelayCalc);
//airline quick sort
void sortedAirlineDelayQ(std::unordered_map<std::string, double>& airlineDelayLikelihoods);
