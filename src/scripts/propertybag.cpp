#include "propertybag.h"

#include <fstream>
#include <iostream>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/algorithm/string.hpp>

void PropertyBag::addPropertiesFromFile(const std::string fileName) {
  std::ifstream infile(fileName.c_str());
  if (infile.fail()) {
    throw "Failed to open input file '" + fileName + "'";
  }

  std::string name, value;
  while(!infile.eof() && infile >> name >> value) {
    mProperties[name] = value;
  }
  
  infile.close();
}

void PropertyBag::addProperty(const std::string& key, const std::string& value) {
  mProperties[key] = value;
}

void PropertyBag::addPropertiesFromLine(const std::string& line) {
  std::vector<std::string> keyValues;
  boost::split(keyValues, line, boost::is_any_of("\t "), boost::token_compress_on);

  for (auto keyValue : keyValues) {
    std::vector<std::string> splitted;
    boost::split(splitted, keyValue, boost::is_any_of(":,="));
    if (splitted.size() != 2) {
      throw "Cannot parse key-value pair '" + keyValue + "'";
    } else {
      mProperties[splitted[0]] = splitted[1];
    }
  }
}

std::string PropertyBag::getProperty(const std::string& key) {
  if (mProperties.find(key) != mProperties.end()) {
    return mProperties[key];
  } else {
    throw "Key does not exist in property bag";
  }
}

void PropertyBag::replacePropertiesInFile(const std::string& inputFileName, const std::string& outputFileName) {
  std::ifstream infile(inputFileName.c_str());
  if (infile.fail()) {
    throw "Failed to open input file '" + inputFileName + "'";
  }

  std::ofstream outfile(outputFileName.c_str());
  if (outfile.fail()) {
    infile.close();
    throw "Cannot write to output file '" + outputFileName + "'";
  }

  std::string line;
  while( std::getline(infile, line) ) {    
    for (auto prop : mProperties) {  
      boost::replace_all(line, "$"+prop.first, prop.second);
    }
    
    outfile << line << std::endl;
  }

  outfile.close();
  infile.close();
}

void PropertyBag::writePropertiesToFile(const std::string& fileName) {
  std::ofstream outfile(fileName.c_str());
  if (outfile.fail()) {
    throw "Cannot open file '" + fileName + "' to write properties";
  }

  for (auto keyValuePair : mProperties) {
    outfile << keyValuePair.first << " " << keyValuePair.second << std::endl;
  }

  outfile.close();
}