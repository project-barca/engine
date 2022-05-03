#ifndef GEN_H
#define GEN_H
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

class Gen {
  public:
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
};

#endif
