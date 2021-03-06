#ifndef GEN_H
#define GEN_H
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream> 
#include "json.hpp"

using json = nlohmann::json;

class Gen {
  public:
    // WRITE FILE JSON
    int writeJSON(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset) {
      
      return EXIT_SUCCESS;
    }
    // READ FILE JSON
    int readJSON(std::string fileName) {
      std::ifstream f(fileName, std::ifstream::in);
      //create unitiialized json object
      json fileJSON; 
      // initialize json object with what was received
      f >> fileJSON; 
      // show data json
      std::cout << fileJSON << std::endl; 

      return EXIT_SUCCESS;
    }
    // WRITE FILE CSV
    int writeCSV(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset) {
    // each column of data is represented by the pair <column name, column data>
    // as std::pair<std::string, std::vector<int>>
    // create an output filestream object
    std::ofstream myFile(filename);
    // send column names to the stream
    for (int k = 0; k < dataset.size(); ++k) {
      myFile << dataset.at(k).first;
      if(k != dataset.size() - 1) myFile << ",";
    }
    myFile << "\n";
    // send data to the stream
    for (int i = 0; i < dataset.at(0).second.size(); ++i) {
      for(int k = 0; k < dataset.size(); ++k) {
        myFile << dataset.at(k).second.at(i);
        if(k != dataset.size() - 1) myFile << ",";
      }
      myFile << "\n";
    }
    // close the file
    myFile.close();

    return EXIT_SUCCESS;
  }
  // READ FILE CSV
  std::vector<std::pair<std::string, std::vector<int>>> readCSV(std::string filename) {
    // reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>
    // create a vector of <string, int vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<int>>> result;
    // create an input filestream
    std::ifstream myFile(filename);
    // make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("N??o foi poss??vel encontrar o arquivo");
    // helper vars
    std::string line, colname;
    int val;
    // read the column names
    if(myFile.good()) {
      // extract the first line in the file
      std::getline(myFile, line);
      // create a stringstream from line
      std::stringstream ss(line);
      // extract each column name
      while(std::getline(ss, colname, ',')){
        // initialize and add <colname, int vector> pairs to result
        result.push_back({colname, std::vector<int> {}});
      }
    }
    // read data, line by line
    while(std::getline(myFile, line)) {
      // create a stringstream of the current line
      std::stringstream ss(line);
      // keep track of the current column index
      int colIdx = 0;
      // extract each integer
      while(ss >> val) {      
        // add the current integer to the 'colIdx' column's values vector
        result.at(colIdx).second.push_back(val);
        // if the next token is a comma, ignore it and move on
        if(ss.peek() == ',') ss.ignore();
        // increment the column index
        colIdx++;
      }
    }
    // close file
    myFile.close();

    return result;
  }
  // READ FILE JSON
};

#endif
