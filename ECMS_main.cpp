// this was programmed and tested and compiled using codeblocks
#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <chrono>
#include <sstream>
using namespace std;
////////////////////////////////////////////////////////////
#define BST 0//Change to 1 to use BST, 0 to use AVL
#if BST
#include "ECMS_headers/Network.h"
#else
#include "ECMS_headers/Network_avl.h"
#endif
///////////////////////////////////////////////////////////////
#include "ECMS_headers/weatherData.h"


bool isValidMonth(int month) {
    return month >= 1 && month <= 12;
}

bool isValidYear(int year) {
    return (year>=2000 && year<=2024); // Assuming years greater than or equal to 2000 are valid
}

bool isValidPeriod(int start_month,int start_year,int end_month,int end_year)
{
    if(start_month<1 || start_month>12 || end_month<1 || end_month>12)
        return false;
    else if(start_year<2000 || start_year>2024 || end_year<2000 || end_year>2024)
        return false;
    else if((start_year>end_year) || (start_year==end_year && start_month>end_month))
        return false;
    else return true;
}

bool isValidID(long long int id)
{
    return (id>=100000000000 && id<=999999999999);
}
void addDepartmentInvestment(string& filename, Network& Net) {
    // Ask the user to enter data
    int region_id,city_id,month,year,investment;

    do{
        cout<<"Enter the id of the Region : ";
        cin>>region_id;
    }while(region_id<0  || region_id>99);

    do{
        cout<<"Enter the id of the City : ";
        cin>>city_id;
    }while(city_id<0  || city_id>99);

    do{
        cout<<"please enter the month : ";
        cin>>month;
    }while(!isValidMonth(month));

    do{
        cout<<"please enter the year : ";
        cin>>year;
    }while(!isValidYear(year));

    do{
    cout<<"Enter the investment of this Department : ";
    cin>>investment;
    }while(investment<0);

    std::ofstream outputFile(filename, std::ios::app);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file " << filename << std::endl;
        return;
    }

    outputFile << region_id << "," << city_id << "," << investment << "," << month << "," << year << "\n";

    // Close the file
    outputFile.close();

    Net.insert_investment(region_id,city_id,investment,month,year);
    cout<<"department added successfully"<<endl;
}
void addCustomerData(string& filename, Network& Net) {
    // Ask the user to enter data
    long long int id;
    int consumption,production,month,year;

    do{
    cout<<"please enter the ID : ";
    cin>>id;
    }while(!isValidID(id));

    do{
        cout<<"please enter the month : ";
        cin>>month;
    }while(!isValidMonth(month));

    do{
        cout<<"please enter the year : ";
        cin>>year;
    }while(!isValidYear(year));

    do{
    cout<<"Enter the consumption of this customer : ";
    cin>>consumption;
    }while(consumption<0 );

    do{
    cout<<"Enter the production of this customer : ";
    cin>>production;
    }while(production<0 );

    std::ofstream outputFile(filename, std::ios::app);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file " << filename << std::endl;
        return;
    }

    outputFile << id << "," << consumption << "," << production << "," << month << "," << year << "\n";

    // Close the file
    outputFile.close();

    Net.add_new_cust_data(id,consumption,production,month,year);
    cout<<"customer data added successfully"<<endl;
}
void addCustomer(string& filename, Network& Net) {
    // Ask the user to enter data
    string name,region_name,city_name,district_name;
    long long int id;
    int num_familly;
    int* ages;
    do{
    cout<<"please enter the ID : ";
    cin>>id;
    }while(!isValidID(id));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout<<"Enter the name of the user : ";
    std::getline(std::cin, name);

    cout<<"Enter the region name of the user : ";
    std::getline(std::cin, region_name);

    cout<<"Enter the city name of the user : ";
    std::getline(std::cin, city_name);

    cout<<"Enter the district name of the user : ";
    std::getline(std::cin, district_name);

    do{
        cout<<"enter the number of family member : ";
        cin>>num_familly;
    }while(num_familly<=0 || num_familly>20);

    ages = new int[num_familly];

    int i = 0;

    while(i<num_familly)
    {
        cout<<"enter the age of the "<<i+1<<" member : ";
        cin>>ages[i];
        if(ages[i]>0 && ages[i]<120)
            i++;
        else
            cout<<"invalid"<<endl;
    }

    std::ofstream outputFile(filename, std::ios::app);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file " << filename << std::endl;
        return;
    }

    // Append data to the end of the file in CSV form
    outputFile << id << "," << name << "," << region_name << "," << city_name << "," << district_name << "," << num_familly ;

    for(int i=0;i<num_familly;i++)
        outputFile << "," << ages[i] ;

    outputFile<< "\n";

    // Close the file
    outputFile.close();

    Net.add_new_cust(id,name,num_familly,ages,region_name,city_name,district_name);
    cout<<"customer added successfully"<<endl;
}
void readCustomer(const std::string& filename,Network& Net) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string token;
        // Read the ID
        std::getline(ss, token, ',');
        long long int id = std::stoll(token);

        // Read the name, region, city, and district
        std::getline(ss, token, ',');
        std::string name = token;

        std::getline(ss, token, ',');
        std::string region = token;

        std::getline(ss, token, ',');
        std::string city = token;

        std::getline(ss, token, ',');
        std::string district = token;

        // Read the number of families
        std::getline(ss, token, ',');
        int numOfFamilies = std::stoi(token);

        // Read the family numbers
        int* familyNumbers = new int[numOfFamilies];
        for (int j = 0; j < numOfFamilies; ++j) {
            std::getline(ss, token, ',');
            familyNumbers[j] = std::stoi(token);
        }

        Net.add_new_cust(id,name,numOfFamilies,familyNumbers,region,city,district);
    }

    inputFile.close();
}

void readCustomerData(const std::string& filename,Network& Net) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file " << filename << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);

        long long int id;
        double consumption, production;
        int  month, year;

        char comma; // to consume the commas between values
        ss >> id >> comma >> consumption >> comma >> production >> comma >> month >> comma >> year;

        Net.add_new_cust_data(id,consumption,production,month,year);
    }

    inputFile.close();
}

void readDepartmentData(const std::string& filename,Network& Net) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int regionId = std::stoi(token);

        std::getline(ss, token, ',');
        int cityId = std::stoi(token);

        std::getline(ss, token, ',');
        int investment = std::stoi(token);

        std::getline(ss, token, ',');
        int month = std::stoi(token);

        std::getline(ss, token, '\n');
        int year = std::stoi(token);

        // Now you have the individual data items (regionId, cityId, investment, month, year)
        // Perform any processing or store the data as needed

        Net.insert_investment(regionId,cityId,investment,month,year);
    }

    inputFile.close();
}
void displaymenu() {
    cout<<"========================================================================================================================\n";
    cout<<"                                               welcome to the ECMS                                             \n";
    cout<<"========================================================================================================================\n";
    cout<<"                    1. Display Bill of a Customer\n";
    cout<<"                    2. Display Bills of all Customers in a District\n";
    cout<<"                    3. Display Bills of all Customers in a  City\n";
    cout<<"                    4. Display Bills of all Customers in a  Region\n";
    cout<<"                    5. Display Bills of all Customers in the Country\n";
    cout<<"                    6. Display Department Performance Ranking\n";
    cout<<"                    7. Display Best Customer in the Country\n";
    cout<<"                    8. Display weather Data\n";
    cout<<"                    9. Add New Customer\n";
    cout<<"                   10. add New Customer Data\n";
    cout<<"                   11. Display list of customers\n";
    cout<<"                   12. Display informations of a customer\n";
    cout<<"                   13. Add Departement data\n";
    cout<<"                                                      0. EXIT\n";
    cout<<"========================================================================================================================\n";
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now() ;

    WeatherData Wdata;
    Network NET("ALGERIA");

    string filename = "./data/Customer_data.csv";
    readCustomer(filename,NET);

    string filename2 = "./data/Customer_electricity.csv";
    readCustomerData(filename2,NET);

    std::string filename3 = "./data/Department_data.csv";
    readDepartmentData(filename3,NET);

// Specify the file name with your weather data
    std::string weatherFilename;
    weatherFilename = "./data/weather_data.csv";


// Read weather data from the file
    std::vector<WeatherData> weatherData = WeatherData::readDataFromFile(weatherFilename);
            int month,year;
            long long int id;
            int start_month,start_year,end_month,end_year;
            int timeChoice;
            int region_id,city_id,district_id;
            int day;
            int ch=-1;
            double averageMonth,averageYear,averageHighTemp,averageLowTemp ;
            int minHighTemp,maxHighTemp,maxLowTemp ,minLowTemp;
    int choice=-1;
    do {
        displaymenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:{ // display bill of a customer
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;
                do{
                std::cout << "Enter 1 for Bill in Month\n 2 for Bills in a Year\n 3 for Bills in a Period\n 0 to cancel  : ";
                std::cin >> timeChoice;
                }while((timeChoice<0 || timeChoice>3));

                switch (timeChoice) {
                    case 1:
                        do{
                        cout<<"please enter the month : ";
                        cin>>month;
                        }while(!isValidMonth(month));

                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        do{
                        cout<<"please enter the customer ID : ";
                        cin>>id;
                        }while(!isValidID(id));

                        NET.show_bill_m(id,month,year);

                        break;

                    case 2:
                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        do{
                        cout<<"please enter the ID : ";
                        cin>>id;
                        }while(!isValidID(id));

                        NET.show_bill_y(id,year);

                        break;

                    case 3:
                        do{
                        cout<<"please enter the starting month : ";
                        cin>>start_month;
                        cout<<"please enter the starting year : ";
                        cin>>start_year;
                        cout<<"please enter the end month : ";
                        cin>>end_month;
                        cout<<"please enter the end year : ";
                        cin>>end_year;
                        }while(!isValidPeriod(start_month,start_year,end_month,end_year));

                        do{
                        cout<<"please enter the ID : ";
                        cin>>id;
                        }while(!isValidID(id));

                        NET.show_bill_period(id,start_month,start_year,end_month,end_year);

                        break;

                    case 0:
                        cout<<"operation canceled"<<endl;
                        break;

                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }

              cout<<endl;//end timing for case
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);

                std::cout << "Processing Time for Displaying Bill of a Customer: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;


                break;}
            case 2:{ // bills of a district
                //to start timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;
                do{
                std::cout << "Enter 1 for Month, 2 for Year, 3 for Period or 0 to cancel: ";
                std::cin >> timeChoice;
                }while((timeChoice<0 || timeChoice>3));

                switch (timeChoice) {
                    case 1:
                        do{
                        cout<<"please enter the month : ";
                        cin>>month;
                        }while(!isValidMonth(month));

                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        do{
                        cout<<"please enter the ID of its region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        do{
                        cout<<"please enter the ID of its City : ";
                        cin>>city_id;
                        }while(city_id<0 || city_id>99);

                        do{
                        cout<<"please enter the ID of the district : ";
                        cin>>district_id;
                        }while(district_id<0 || district_id>99);

                        NET.show_ALL_DISTRICT_bill_m(region_id,city_id,district_id,month,year);

                        break;

                    case 2:
                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        do{
                        cout<<"please enter the ID of its region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        do{
                        cout<<"please enter the ID of its City : ";
                        cin>>city_id;
                        }while(city_id<0 || city_id>99);

                        do{
                        cout<<"please enter the ID of the district : ";
                        cin>>district_id;
                        }while(district_id<0 || district_id>99);

                        NET.show_ALL_DISTRICT_bill_y(region_id,city_id,district_id,year);

                        break;

                    case 3:
                        do{
                        cout<<"please enter the starting month : ";
                        cin>>start_month;
                        cout<<"please enter the starting year : ";
                        cin>>start_year;
                        cout<<"please enter the end month : ";
                        cin>>end_month;
                        cout<<"please enter the end year : ";
                        cin>>end_year;
                        }while(!isValidPeriod(start_month,start_year,end_month,end_year));

                        do{
                        cout<<"please enter the ID of its region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        do{
                        cout<<"please enter the ID of its City : ";
                        cin>>city_id;
                        }while(city_id<0 || city_id>99);

                        do{
                        cout<<"please enter the ID of the district : ";
                        cin>>district_id;
                        }while(district_id<0 || district_id>99);

                        NET.show_ALL_DISTRICT_bill_period(region_id,city_id,district_id,start_month,start_year,end_month,end_year);

                        break;

                    case 0:
                        cout<<"canceled"<<endl;
                        break;

                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }
              cout<<endl;//end timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Displaying Bill of a District: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;
                break;}


            case 3:{ //bills of a city
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;
                do{
                std::cout << "Enter 1 for Bill in Month\n 2 for Bills in a Year\n 3 for Bills in a Period\n 0 to cancel  : ";
                std::cin >> timeChoice;
                }while((timeChoice<0 || timeChoice>3));

                switch (timeChoice) {
                    case 1:
                        do{
                        cout<<"please enter the month : ";
                        cin>>month;
                        }while(!isValidMonth(month));

                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        do{
                        cout<<"please enter the ID of its region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        do{
                        cout<<"please enter the ID of the City : ";
                        cin>>city_id;
                        }while(city_id<0 || city_id>99);

                        NET.show_ALL_CITY_bill_m(region_id,city_id,month,year);

                        break;

                    case 2:
                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        do{
                        cout<<"please enter the ID of its region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        do{
                        cout<<"please enter the ID of the City : ";
                        cin>>city_id;
                        }while(city_id<0 || city_id>99);

                        NET.show_ALL_CITY_bill_y(region_id,city_id,year);

                        break;

                    case 3:
                        do{
                        cout<<"please enter the starting month : ";
                        cin>>start_month;
                        cout<<"please enter the starting year : ";
                        cin>>start_year;
                        cout<<"please enter the end month : ";
                        cin>>end_month;
                        cout<<"please enter the end year : ";
                        cin>>end_year;
                        }while(!isValidPeriod(start_month,start_year,end_month,end_year));

                        do{
                        cout<<"please enter the ID of its region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        do{
                        cout<<"please enter the ID of the City : ";
                        cin>>city_id;
                        }while(city_id<0 || city_id>99);

                        NET.show_ALL_CITY_bill_period(region_id,city_id,start_month,start_year,end_month,end_year);

                        break;

                    case 0:
                        cout<<"canceled"<<endl;
                        break;

                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }

              cout<<endl;//end timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Displaying Bill of a City: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;
                break;}
            case 4:{ //bills of a region
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;

                do{
                std::cout <<"Enter 1 for Bill in Month\n 2 for Bills in a Year\n 3 for Bills in a Period\n 0 to cancel  : ";
                std::cin >> timeChoice;
                }while((timeChoice<0 || timeChoice>3));

                switch (timeChoice) {
                    case 1:
                        do{
                        cout<<"please enter the month : ";
                        cin>>month;
                        }while(!isValidMonth(month));

                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        do{
                        cout<<"please enter the ID of the region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        NET.show_ALL_region_bill_m(region_id,month,year);

                        break;

                    case 2:
                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        do{
                        cout<<"please enter the ID of the region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        NET.show_ALL_region_bill_y(region_id,year);

                        break;

                    case 3:
                        do{
                        cout<<"please enter the starting month : ";
                        cin>>start_month;
                        cout<<"please enter the starting year : ";
                        cin>>start_year;
                        cout<<"please enter the end month : ";
                        cin>>end_month;
                        cout<<"please enter the end year : ";
                        cin>>end_year;
                        }while(!isValidPeriod(start_month,start_year,end_month,end_year));

                        do{
                        cout<<"please enter the ID of its region : ";
                        cin>>region_id;
                        }while(region_id<0 || region_id>99);

                        NET.show_ALL_region_bill_period(region_id,start_month,start_year,end_month,end_year);

                        break;

                    case 0:
                        cout<<"canceled"<<endl;
                        break;

                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }

              cout<<endl;//end timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Displaying Bill of a Region: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;

                break;}
            case 5:{ //bills of the network
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;


                do{
                std::cout << "Enter 1 for Bill in Month\n 2 for Bills in a Year\n 3 for Bills in a Period\n 0 to cancel  : ";
                std::cin >> timeChoice;
                }while((timeChoice<0 || timeChoice>3));

                switch (timeChoice) {
                    case 1:
                        do{
                        cout<<"please enter the month : ";
                        cin>>month;
                        }while(!isValidMonth(month));

                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        NET.show_ALL_Network_bill_m(month,year);

                        break;

                    case 2:
                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        NET.show_ALL_Network_bill_y(year);

                        break;

                    case 3:
                        do{
                        cout<<"please enter the starting month : ";
                        cin>>start_month;
                        cout<<"please enter the starting year : ";
                        cin>>start_year;
                        cout<<"please enter the end month : ";
                        cin>>end_month;
                        cout<<"please enter the end year : ";
                        cin>>end_year;
                        }while(!isValidPeriod(start_month,start_year,end_month,end_year));

                        NET.show_ALL_Network_bill_period(start_month,start_year,end_month,end_year);

                        break;

                    case 0:
                        cout<<"canceled"<<endl;
                        break;

                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }

              cout<<endl;//end timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Displaying Bill of a Country: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;
                break;}
            case 8:{   //weather
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;

                do{
                    std::cout << "Please enter a date: \n";
                    cout<<" day: ";cin>>day;
                    cout<<" month: ";cin>>month;
                    cout<<" year: ";cin>>year;
                    }while(!isValidMonth(month) || !isValidYear(year) || day<0 || day>31);
                    cout<<endl;
                    cout<<"options :"<<endl;
                    cout<<"1.display the average sun hours on :"<<day<<"/"<<month<<"/"<<year<<endl;
                    cout<<"2.display the average sun hours in :"<<year<<endl;
                    cout<<"3.display the min, max, and average high temperatures in :"<<month<<"/"<<year<<endl;
                    cout<<"4.display the min, max, and average low temperatures in :"<<month<<"/"<<year<<endl;
                    cout<<"enter your choice:";cin>>ch;
                     switch(ch){
                        case 1:{
                            double averageInMonth = WeatherData::calculateAverageInMonth(weatherData, year, month);
                            std::cout << "Average Sunny Hours in " << year << "/" << month << ": " << averageInMonth << std::endl;

                            break;}
                        case 2:{
                            double averageInYear = WeatherData::calculateAverageInYear(weatherData, year);
                            std::cout << "Average Sunny Hours in " << year << ": " << averageInYear << std::endl;

                            break;}
                        case 3:{
                            int minHighTemp = WeatherData::findMinHighTemperature(weatherData, year, month);
                            int maxHighTemp = WeatherData::findMaxHighTemperature(weatherData, year, month);
                            double averageHighTemp = WeatherData::calculateAverageHighTemperature(weatherData, year, month);

                            std::cout << "High Temperatures in " << year << "/" << month << ": Min=" << minHighTemp << ", Max="
                                      << maxHighTemp << ", Average=" << averageHighTemp << std::endl;
                            break;}

                        case 4:{
                            int minLowTemp = WeatherData::findMinLowTemperature(weatherData, year, month);
                            int maxLowTemp = WeatherData::findMaxLowTemperature(weatherData, year, month);
                            double averageLowTemp = WeatherData::calculateAverageLowTemperature(weatherData, year, month);

                            std::cout << "Low Temperatures in " << year << "/" << month << ": Min=" << minLowTemp << ", Max="
                                      << maxLowTemp << ", Average=" << averageLowTemp << std::endl;
                            break;}
                        case 0:
                            cout<<"canceled"<<endl;
                                break;
                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                                break;
                }
              cout<<endl;//end timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Displaying Weather Data : " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;

                break;}
            case 6: {  //deps ranking
                // To start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now();

                do {
                    std::cout << "Enter 1 for Year, 2 for Period or 0 to cancel: ";
                    std::cin >> timeChoice;
                } while (timeChoice < 0 || timeChoice > 2);

                switch (timeChoice) {
                    case 1:
                        do {
                            cout << "please enter the year : ";
                            cin >> year;
                        } while (!isValidYear(year));

                        NET.departement_ranking(year);
                        break;
                    case 2:
                        do {
                            cout << "please enter the start year : ";
                            cin >> start_year;
                            cout << "please enter the end year : ";
                            cin >> end_year;
                        } while ((!isValidYear(start_year)) && (!isValidYear(end_year)) && start_year <= end_year);

                        for (int i = start_year; i <= end_year; i++) {
                            cout << "departements ranking for year: " << i << endl;
                            NET.departement_ranking(i);
                        }
                        break;
                    case 0:
                        cout << "canceled" << endl;
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }

              cout<<endl;// End timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Displaying Departement Performance: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;
                break;
            }

            case 7:{ //best customer
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;

                do{
                std::cout << "Enter\n 1 for Best Customer in Month\n 2 for list of best customers in a Year\n 3 for list of best customers in a period\n 0 to cancel  : ";
                std::cin >> timeChoice;
                }while((timeChoice<0 || timeChoice>3));

                switch (timeChoice) {
                    case 1:
                        do{
                        cout<<"please enter the month : ";
                        cin>>month;
                        }while(!isValidMonth(month));

                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        NET.show_best_customer_m(month,year);

                        break;

                    case 2:
                        do{
                        cout<<"please enter the year : ";
                        cin>>year;
                        }while(!isValidYear(year));

                        NET.show_best_customers_y(year);

                        break;

                    case 3:
                        do{
                        cout<<"please enter the starting month : ";
                        cin>>start_month;
                        cout<<"please enter the starting year : ";
                        cin>>start_year;
                        cout<<"please enter the end month : ";
                        cin>>end_month;
                        cout<<"please enter the end year : ";
                        cin>>end_year;
                        }while(!isValidPeriod(start_month,start_year,end_month,end_year));

                        NET.show_best_customers_period(start_month,start_year,end_month,end_year);

                        break;

                    case 0:
                        cout<<"canceled"<<endl;
                        break;

                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }
              cout<<endl;//end timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Displaying Best Customer in the Country: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;

                break;}
            case 9:{ //add new customer
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;
                addCustomer(filename,NET);
                //end timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Adding a new customer: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;
                break;}

            case 10:{ //add new customer data
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;

                addCustomerData(filename2,NET);
                //end timing for case 10
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Adding Customer data: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;

                break;}
            case 11: {
                // Show list of customers
                // To start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now();

                int did, cid, rid;
                int h = -1;
                do {
                    cout << "Choose the list of customers you want to display:\n";
                    cout << "1.List of the customers of a district\n";
                    cout << "2.List of the customers of a City\n";
                    cout << "3.List of the customers of a region\n";
                    cout << "4.List of customers of the country\n";
                    cout << "Enter your choice :";
                    cin >> h;
                } while (h < 0 && h > 5);

                switch (h) {
                    case 1: {
                        do {
                            cout << "Enter the id of the district: ";
                            cin >> did;
                            cout << "Enter the id of its city :";
                            cin >> cid;
                            cout << "Enter the id of its region : ";
                            cin >> rid;
                        } while (did < 0 || did > 99 || cid < 0 || cid > 99 || rid > 99 || rid < 0);
                        NET.print_ALL_DISTRICT_customers(rid, cid, did);
                        break;
                    }
                    case 2: {
                        do {
                            cout << "Enter the id of the city :";
                            cin >> cid;
                            cout << "Enter the id of its region : ";
                            cin >> rid;
                        } while (cid < 0 || cid > 99 || rid > 99 || rid < 0);
                        NET.print_ALL_CITY_customers(rid, cid);
                        break;
                    }
                    case 3: {
                        do {
                            cout << "Enter the id of the region : ";
                            cin >> rid;
                        } while (rid > 99 || rid < 0);
                        NET.print_ALL_REGION_customers(rid);
                        break;
                    }
                    case 4: {
                        NET.print_customers();
                        break;
                    }
                    case 0: {
                        cout << "canceled" << endl;
                        break;
                    }
                    default: {
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                } // end of switch

              cout<<endl;// End timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Displaying List of Customers: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;

                break;
            }

            case 0:{
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;
                std::cout << "Exiting...\n";
              cout<<endl;//end timing for case 0
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Exiting: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;
                break;}
            default:{
                std::cout << "Invalid choice. Please try again.\n";
                break;}
            case 12:{ //show customer information
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;

                long long int id;
                  cout<<"Enter customer id: ";cin>>id;
                  NET.print_customer(id);

              cout<<endl;//end timing
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);

                std::cout << "Processing Time for Displaying Information of a Customer: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;

                break;}
            case 13:{//add departement data
                //to start the timing
                auto start_time_case = std::chrono::high_resolution_clock::now() ;

                addDepartmentInvestment(filename3,NET);
              cout<<endl;//end timing for case
                auto end_time_case = std::chrono::high_resolution_clock::now();
                auto duration_case = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_case - start_time_case);
                std::cout << "Processing Time for Adding Departement Data: " << duration_case.count() << " milliseconds\n";
                std::cout<<endl;

                break;}
            }
     cout<<endl;
    } while (choice != 0);
    cout<<endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    cout << "Processing Time for the Program: " << duration.count() << " milliseconds\n";
    return 0;
}
