#ifndef BUILDINGINFORMATIONFORMATSTRING_H
#define BUILDINGINFORMATIONFORMATSTRING_H

#include <string>

/**Building information Format String
 * 
 * This class holds information and methods for House nodes in the city grid.
 * This class inherits the Residential class, which inherits the Node class.
 * 
 */

// String used when no road type node in the neighboring cell
const std::string NO_ROAD_WARNING = "Warning: No road nearby!";

// String Information for Apartment 
const std::string APARTMENT_HEADER = "Apartment";
const std::string APARTMENT_1_1 = "Population: ";
const std::string APARTMENT_2_1 = "Max Population: ";
const std::string APARTMENT_3_1 = "250 * (1 + Neighboring Residential Buildings)";
const std::string APARTMENT_4_1 = "Contribution to Population Growth Rate: ";
const std::string APARTMENT_5_1 = "-population";
const std::string APARTMENT_6_1 = "Population Growth: ";
const std::string APARTMENT_6_2 = " (Limited by Quota: ";
const std::string APARTMENT_6_3 = ")";
const std::string APARTMENT_7_1 = "(Population Growth Rate of the City * (Neighboring Health Buildings - Neighboring Gold Mines)) / 10";

// String Information for House
const std::string HOUSE_HEADER = "House";
const std::string HOUSE_1_1 = "Population: ";
const std::string HOUSE_2_1 = "Max Population: ";
const std::string HOUSE_3_1 = "50 * (1 + Neighboring Residential Buildings)";
const std::string HOUSE_4_1 = "Contribution to Population Growth Rate: ";
const std::string HOUSE_5_1 = "-population";
const std::string HOUSE_6_1 = "Population Growth: ";
const std::string HOUSE_6_2 = " (Limited by Quota: ";
const std::string HOUSE_6_3 = ")";
const std::string HOUSE_7_1 = "(Population Growth Rate of the City * (Neighboring Health Buildings - Neighboring Gold Mines)) / 10";

// String Information for Clinic
const std::string CLINIC_HEADER = "Clinic";
const std::string CLINIC_1_1 = "Contribution to Population Growth Rate: ";
const std::string CLINIC_2_1 = "60 / (1 + Neighboring Health Buildings)";

// String Information for Hospital
const std::string HOSPITAL_HEADER = "Hospital";
const std::string HOSPITAL_1_1 = "Contribution to Population Growth Rate: ";
const std::string HOSPITAL_2_1 = "360 / (1 + Neighboring Health Buildings)";

// String Information for Gold Mine
const std::string GOLD_HEADER = "Gold Mine";
const std::string GOLD_1_1 = "Revenue: ";
const std::string GOLD_2_1 = "2 * (Total Population + Neighboring Population)";

// String Information for Silver Mine
const std::string SILVER_HEADER = "Silver Mine";
const std::string SILVER_1_1 = "Revenue: ";
const std::string SILVER_2_1 = "1 * (Total Population + Neighboring Population)";

// String Information for Street / Avenue
const std::string STREET_HEADER = "Street";
const std::string AVENUE_HEADER = "Avenue";
const std::string ROAD_1_1 = "Maximum Traffic Flow: ";
const std::string ROAD_2_1 = "Traffic Flow: ";
const std::string ROAD_2_2 = "(Can be greater than maximum traffic flow)";
const std::string ROAD_3_1 = "Travel Time: ";
const std::string ROAD_4_1 = "Free Flow Travel Time * ( 1 + 0.15 * (Traffic Flow / Max Traffic Flow) ^ 4)";

#endif // BUILDINGINFORMATIONFORMATSTRING_H
