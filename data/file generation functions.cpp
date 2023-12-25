// file generators

//generator customer_electricity file

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <string>

std::vector<long long int> extractIds(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return {};
    }

    std::vector<long long int> ids;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr;

        // Read the first value before the comma
        if (std::getline(ss, idStr, ',')) {
            long long int id;
            std::stringstream idStream(idStr);
            idStream >> id;
            ids.push_back(id);
        }
    }

    file.close();

    return ids;
}

void generateOutputFile(const std::vector<long long int>& ids, const std::string& outputFilename) {
    std::ofstream outputFile(outputFilename);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening the output file." << std::endl;
        return;
    }

    std::default_random_engine generator;
    std::uniform_int_distribution<int> consumptionDistribution(10, 100);
    std::uniform_int_distribution<int> productionDistribution(5, 50);

    for (long long int id : ids) {
        for(int year=2023;year<=2024;year++)
            for (int month = 1; month <= 12; ++month) {
                int consumption = consumptionDistribution(generator);
                int production = productionDistribution(generator);

                outputFile << id << "," << consumption << "," << production << "," << month << "," << year << std::endl;
            }
    }

    outputFile.close();
}

int main() {
    std::string filename = "Customer_data.csv";
    std::vector<long long int> ids = extractIds(filename);

    std::string outputFilename = "Customer_electricity.csv";
    generateOutputFile(ids, outputFilename);

    std::cout << "Output file generated successfully: " << outputFilename << std::endl;

    return 0;
}



//generator departement_investement file


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void generateCityDataFile(const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the output file!" << std::endl;
        return;
    }

    const int numRegions = 100; // Adjust as needed
    const int numCitiesPerRegion = 100; // Adjust as needed

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int regionId = 0; regionId < numRegions; ++regionId) {
        for (int cityId = 0; cityId < numCitiesPerRegion; ++cityId) {
            for (int year = 2023; year <= 2024; ++year) {
                for (int month = 1; month <= 12; ++month) {
                    int investment = generateRandomNumber(10000, 50000); // Adjust the investment range

                    outputFile << regionId << "," << cityId << "," << investment << "," << month << "," << year << "\n";
                }
            }
        }
    }

    outputFile.close();
    std::cout << "City data generated and saved to '" << filename << "'" << std::endl;
}

int main() {
    std::string filename = "Department_data.csv";
    generateCityDataFile(filename);

    return 0;
}








//generator customer_data file

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

unsigned long long generateRandomNumber(unsigned long long min, unsigned long long max) {
    return rand() % (max - min + 1) + min;
}

unsigned long long generateRandomNumber(int numDigits) {
    unsigned long long min = pow(10, numDigits - 1);
    unsigned long long max = pow(10, numDigits) - 1;
    return generateRandomNumber(min, max);
}

std::string generateRandomName(const std::vector<std::string>& names) {
    int index = rand() % names.size();
    return names[index];
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<std::string> names = {"Mohammed", "Fatima", "Ali", "Layla", "Ahmed", "Nour", "Khaled", "Zahraa", "Hassan", "Sara",
                                       "Abdullah", "Reem", "Omar", "Zeinab", "Youssef", "Mariam", "Jaafar", "Safa", "Ameer", "Rana",
                                       "Luei", "Maysa", "Jamal", "Aya", "Tarek", "Nadia", "Osama", "Hala", "Hossam", "Latifa",
                                       "Mustafa", "Samia", "Saleem", "Soha", "Adel", "Nader", "Haleema", "Yaser", "Najwa", "Salah"};


    std::vector<std::string> randomRegionNames = {
        "Oran", "Los Angeles", "New York", "Tokyo", "London", "Paris", "Beijing", "Sydney", "Rio de Janeiro", "Cairo",
        "Adrar", "Chlef", "Laghouat", "Oum El Bouaghi", "Batna", "B�ja�a", "Biskra", "B�char", "Blida", "Bouira",
        "Tamanrasset", "T�bessa", "Tlemcen", "Tiaret", "Tizi Ouzou", "Algiers", "Djelfa", "Jijel", "S�tif", "Sa�da",
        "Skikda", "Sidi Bel Abb�s", "Annaba", "Guelma", "Constantine", "M�d�a", "Mostaganem", "M'Sila", "Mascara", "Ouargla",
        "Oran", "El Bayadh", "Illizi", "Bordj Bou Arr�ridj", "Boumerd�s", "El Taref", "Tindouf", "Tissemsilt", "El Oued", "Khenchela",
        "Souk Ahras", "Tipaza", "Mila", "A�n Defla", "Naama", "A�n T�mouchent", "Gharda�a", "Relizane", "Mangrove", "Thicket",
        "Vale", "Pond", "Rapids", "Quagmire", "Mire", "Knoll", "Spring", "Cataract", "Moraine", "Crescent",
        "Slope", "Outcrop", "Ravine", "Delta", "Woodland", "Highland", "Lowland", "Jungle", "Bog", "Crag",
        "Chasm", "Cavern", "Chaparral", "Fen", "Grove", "Dune", "Culvert", "Karst", "Landslide", "Escarpment",
        "Cranny", "Chine", "Nook", "Panhandle", "Corridor", "Redoubt", "Veld", "Wold", "Warp", "Cwm" ,
    };

    std::vector<std::string> randomCityNames = {
        "Oran", "Los Angeles", "New York", "Tokyo", "London", "Paris", "Beijing", "Sydney", "Rio de Janeiro", "Cairo",
        "Mumbai", "Moscow", "Berlin", "Rome", "Toronto", "Seoul", "Bangkok", "Dubai", "Nairobi", "Mexico City",
        "Buenos Aires", "Istanbul", "Marrakech", "Barcelona", "Amsterdam", "Cape Town", "Singapore", "Hanoi", "Kyoto", "Stockholm",
        "Vienna", "Prague", "Budapest", "Dublin", "Edinburgh", "Vancouver", "San Francisco", "Seattle", "Austin", "Chicago",
        "Miami", "Dallas", "Phoenix", "Denver", "Atlanta", "Boston", "Sydney", "Melbourne", "Auckland", "Wellington",
        "Christchurch", "Osaka", "Copenhagen", "Helsinki", "Oslo", "Zurich", "Geneva", "Madrid", "Lisbon", "Athens",
        "Brussels", "Warsaw", "Dublin", "Riga", "Tallinn", "Vilnius", "Helsinki", "Oslo", "Reykjavik", "Anchorage",
        "Honolulu", "Juneau", "Montreal", "Quebec City", "Ottawa", "Edmonton", "Calgary", "Vancouver", "Winnipeg", "Halifax",
        "St. John's", "Yellowknife", "Whitehorse", "Iqaluit", "Ulaanbaatar", "Astana", "Bishkek", "Dushanbe", "Ashgabat", "Tashkent",
        "Tbilisi", "Yerevan", "Baku", "Almaty", "Nur-Sultan", "Dhaka", "Kathmandu", "Thimphu", "Male", "Colombo",
    };

    std::vector<std::string> randomDistrictNames = {
        "Downtown", "Suburbia", "Historic", "Financial", "Industrial", "Residential", "Commercial", "Waterfront", "Greenbelt", "Cultural",
        "Old Town", "Market", "Chinatown", "Little Italy", "The Loop", "The Square", "Midtown", "Uptown", "Docks", "The Wharf",
        "Mill District", "Warehouse District", "Arts District", "Science Park", "Tech Hub", "Garden District", "Fashion District", "Medical Quarter", "Education Zone", "Sports Arena",
        "Business Park",         "Business Park", "Entertainment Zone", "Silicon Valley", "Financial District", "Historic Quarter", "Government Center", "Innovation District", "Artistic Quarter", "Civic Center", "Research Park",
        "Waterfront District", "Technology Park", "Knowledge Park", "Harbor District", "Cultural Quarter", "Nature Reserve", "Heritage District", "University Campus", "Medical Campus", "Sports District",
        "Fashion Quarter", "Resort Area", "Village Center", "Oceanfront", "Riverside", "Mountain View", "Sunnyvale", "Meadowlands", "Lakefront", "Skyline", "Sunset Heights",
        "Parkside", "Gateway", "Historic Village", "Civic Square", "City Center", "Promenade", "Metroplex", "Bayside", "Township", "Promontory Point",
        "Highland Park", "Riverfront", "Capitol Hill", "Crescent Heights", "Echo Valley", "Grandview", "Hillcrest", "Jubilee Hills", "Lighthouse Point", "Oceanview",
        "Pinnacle Heights", "Quay", "Regency Park", "Sapphire Shores", "Terrace Heights", "Vista Del Mar", "Willow Creek", "Xanadu Heights", "Yorkshire Downs", "Zenith Gardens",
        "Avalon", "Blue Ridge", "Cascade Springs", "Dolphin Bay", "Emerald Hills", "Falcon Crest", "Golden Meadows", "Ivory Tower", "Jasmine Grove", "Kaleidoscope",
        "Lemon Grove", "Mystic Pines", "Nightingale Heights", "Olive Branch", "Peachtree Plaza", "Quantum Quarters", "Riviera Heights", "Sundance Springs", "Tranquil Terrace", "Utopia Gardens",
        "Velvet Valley", "Whispering Pines", "Xanadu Gardens", "Yellowstone", "Zephyr Hills"

    };

    std::ofstream outputFile("Customer_data.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the output file!" << std::endl;
        return 1;
    }

    for (int i = 0; i < 2000; ++i) {
        unsigned long long id = generateRandomNumber(100000000000, 999999999999); // Positive 12-digit random number
        int multiplier = generateRandomNumber(1, 5);
        id = id * multiplier;

        int region_num = id%100;
        int city_num = (id%10000)/100;
        int district_num = (id%1000000)/10000;

        std::string name = generateRandomName(names);
        std::string region = randomRegionNames[region_num];
        std::string city = randomCityNames[city_num];
        std::string district = randomDistrictNames[district_num];
        int numOfFamilies = generateRandomNumber(1, 10);

        outputFile << id << "," << name << "," << region << "," << city << "," << district << "," << numOfFamilies;

        for (int j = 0; j < numOfFamilies; ++j) {
            outputFile << "," << rand()%100;
        }

        outputFile << "\n";
    }

    outputFile.close();

    std::cout << "Data generated and saved to 'generated_data.csv'" << std::endl;

    return 0;
}




//generator of weather_data file


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

void generateRandomWeather(string& weather, int& sunnyHours, double& highestTemp, double& lowestTemp) {
    sunnyHours = rand() % 13;  // 0 to 12 hours
    highestTemp = rand() % 41 + 12.0;  // 13 to 53 degrees
    lowestTemp = rand() % 33 - 20.0;   // -20 to 12 degrees

    if (sunnyHours <= 6) {
        weather = "cloudy";
    } else {
        if (lowestTemp <= 3 && highestTemp >= 13) {
            weather = "snowy";
        } else if (lowestTemp > 3 && highestTemp >= 13) {
            weather = "rainy";
        } else {
            weather = "sunny";
        }
    }
}


int main() {
ofstream outputFile("weather_data.csv");

    if (!outputFile) {
        cerr << "Error creating the file." << endl;
        return 1;
    }

    for (int year = 2023; year <= 2024; ++year) {
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        for (int month = 1; month <= 12; ++month) {
            for (int dayOfMonth = 1; dayOfMonth <= daysInMonth[month]; ++dayOfMonth) {
                int sunnyHours;
                double highestTemp, lowestTemp;
                string weather;

                generateRandomWeather(weather, sunnyHours, highestTemp, lowestTemp);

                outputFile << year << "," << month << "," << dayOfMonth << ","<<weather<<","
                            << sunnyHours << "," << highestTemp << "," << lowestTemp << endl;
            }
        }
    }

    outputFile.close();

    cout << "CSV file has been generated." << endl;

    return 0;
}
