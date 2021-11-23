#ifndef BUILDINGINFORMATIONFORMATSTRING_H
#define BUILDINGINFORMATIONFORMATSTRING_H

#include <string>

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

const std::string CLINIC_HEADER = "Clinic";
const std::string CLINIC_1_1 = "Contribution to Population Growth Rate: ";
const std::string CLINIC_2_1 = "60 / (1 + Neighboring Health Buildings)";

const std::string HOSPITAL_HEADER = "Hospital";
const std::string HOSPITAL_1_1 = "Contribution to Population Growth Rate: ";
const std::string HOSPITAL_2_1 = "360 / (1 + Neighboring Health Buildings)";

const std::string GOLD_HEADER = "Gold Mine";
const std::string GOLD_1_1 = "Revenue: ";
const std::string GOLD_2_1 = "2 * (Total Population + Neighboring Population)";

const std::string SILVER_HEADER = "Silver Mine";
const std::string SILVER_1_1 = "Revenue: ";
const std::string SILVER_2_1 = "1 * (Total Population + Neighboring Population)";

#endif // BUILDINGINFORMATIONFORMATSTRING_H
