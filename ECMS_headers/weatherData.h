#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;

class WeatherData {
public:
                int year, month, day, sun_hours, high_temp, low_temp;
                string weather;

                //parameterized constructor
                WeatherData(int y, int m, int d, string w, int sun_h, int high_t, int low_t)
                        : year(y), month(m), day(d), weather(std::move(w)), sun_hours(sun_h), high_temp(high_t), low_temp(low_t) {}

                //default constructor
                WeatherData() : year(0), month(0), day(0), weather(" "), sun_hours(0), high_temp(0), low_temp(0) {}

                // Move constructor
                WeatherData(WeatherData&& other) noexcept
                        : year(other.year), month(other.month), day(other.day),
                        sun_hours(other.sun_hours), high_temp(other.high_temp), low_temp(other.low_temp),
                        weather(std::move(other.weather)) {
                    // Reset the other object to a valid state
                    other.year = other.month = other.day = other.sun_hours = other.high_temp = other.low_temp = 0;
                    other.weather.clear();}

                // Copy constructor
                WeatherData(const WeatherData& other)= default;

                // Read weather data from file
                static std::vector<WeatherData> readDataFromFile(const std::string& filename);

                // Weather calculations
                static double calculateAverageInMonth(const std::vector<WeatherData>& data, int year, int month);
                static double calculateAverageInYear(const std::vector<WeatherData>& data, int year);
                static int findMinHighTemperature(const std::vector<WeatherData>& data, int year, int month);
                static int findMaxHighTemperature(const std::vector<WeatherData>& data, int year, int month);
                static double calculateAverageHighTemperature(const std::vector<WeatherData>& data, int year, int month);
                static int findMinLowTemperature(const std::vector<WeatherData>& data, int year, int month);
                static int findMaxLowTemperature(const std::vector<WeatherData>& data, int year, int month);
                static double calculateAverageLowTemperature(const std::vector<WeatherData>& data, int year, int month);

};

#endif // WEATHERDATA_H



//weather.cpp

                    vector<WeatherData> WeatherData::readDataFromFile(const string& filename) {
                        vector<WeatherData> data;

                        ifstream inputFile(filename);

                        if (!inputFile.is_open()) {
                            cerr << "Error opening the file " << filename << endl;
                            return data;
                        }

                        string line;
                        while (getline(inputFile, line)) {
                            stringstream ss(line);

                            string token;
                            vector<string> tokens;

                            while (getline(ss, token, ',')) {
                                tokens.push_back(token);
                            }

                            if (tokens.size() != 7) {
                                cerr << "Invalid number of fields in the line: " << line << endl;
                                continue;
                            }

                            int year = stoi(tokens[0]);
                            int month = stoi(tokens[1]);
                            int day = stoi(tokens[2]);
                            string weather = tokens[3];
                            int sun_h = stoi(tokens[4]);
                            int high_temp = stoi(tokens[5]);
                            int low_temp = stoi(tokens[6]);

                            //for test purposes only: cout<<weather<<","<<sun_h<<","<<high_temp<<","<<low_temp<<endl;

                            if (month < 1 || month > 12 || day < 1 || day > 31) {
                                cerr << "Invalid date found in the file: " << line << endl;
                                continue;
                            }

                            WeatherData weatherEntry{year, month, day, weather, sun_h, high_temp, low_temp};
                            data.push_back(weatherEntry);
                        }

                        inputFile.close();
                        return data;
                    }

                    double WeatherData::calculateAverageInMonth(const vector<WeatherData>& data, int year, int month) {
                        double totalSunHours = 0.0;
                        int entriesCount = 0;
                        for (const auto& entry : data) {
                            if (entry.year == year && entry.month == month) {
                                totalSunHours += entry.sun_hours;
                                entriesCount++;
                            }
                        }

                        return entriesCount > 0 ? totalSunHours / entriesCount : 0.0;
                    }

                    double WeatherData::calculateAverageInYear(const vector<WeatherData>& data, int year) {
                        double totalSunHours = 0.0;
                        int entriesCount = 0;
                        for (const auto& entry : data) {
                            if (entry.year == year) {
                                totalSunHours += entry.sun_hours;
                                entriesCount++;
                            }
                        }
                        return entriesCount > 0 ? totalSunHours / entriesCount : 0.0;
                    }

                    int WeatherData::findMinHighTemperature(const vector<WeatherData>& data, int year, int month) {
                        int minTemp = numeric_limits<int>::max();
                        for (const auto& entry : data) {
                            if (entry.year == year && entry.month == month) {
                                minTemp = min(minTemp, entry.high_temp);
                            }
                        }

                        return minTemp;
                    }

                    int WeatherData::findMaxHighTemperature(const vector<WeatherData>& data, int year, int month) {
                        int maxTemp = numeric_limits<int>::min();
                        for (const auto& entry : data) {
                            if (entry.year == year && entry.month == month) {
                                maxTemp = max(maxTemp, entry.high_temp);
                            }
                        }
                        return maxTemp;
                    }

                    double WeatherData::calculateAverageHighTemperature(const vector<WeatherData>& data, int year, int month) {
                        double totalTemp = 0.0;
                        int entriesCount = 0;
                        for (const auto& entry : data) {
                            if (entry.year == year && entry.month == month) {
                                totalTemp += entry.high_temp;
                                entriesCount++;
                            }
                        }
                        return entriesCount > 0 ? totalTemp / entriesCount : 0.0;
                    }

                    int WeatherData::findMinLowTemperature(const vector<WeatherData>& data, int year, int month) {
                        int minTemp = numeric_limits<int>::max();
                        for (const auto& entry : data) {
                            if (entry.year == year && entry.month == month) {
                                minTemp = min(minTemp, entry.low_temp);
                            }
                        }
                        return minTemp;
                    }

                    int WeatherData::findMaxLowTemperature(const vector<WeatherData>& data, int year, int month) {
                        int maxTemp = numeric_limits<int>::min();
                        for (const auto& entry : data) {
                            if (entry.year == year && entry.month == month) {
                                maxTemp = max(maxTemp, entry.low_temp);
                            }
                        }
                        return maxTemp;
                    }

                    double WeatherData::calculateAverageLowTemperature(const vector<WeatherData>& data, int year, int month) {
                        double totalTemp = 0.0;
                        int entriesCount = 0;
                        for (const auto& entry : data) {
                            if (entry.year == year && entry.month == month) {
                                totalTemp += entry.low_temp;
                                entriesCount++;
                            }
                        }
                        return entriesCount > 0 ? totalTemp / entriesCount : 0.0;
                    }
