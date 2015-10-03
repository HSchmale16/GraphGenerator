/**\file main.cpp
 * \author Henry J Schmale
 * \date October 2, 2015
 *
 * The graph generator program.
 *
 *      ./graphgen <datafile> <img_format> <outfile>
 */

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <json.hpp>
#include <CImg.h>

namespace cimg = cimg_library;
namespace json = nlohmann;

int main(int argc, char** argv){
    // Parse Command Line Args and do init
    cimg_usage("Generates a graph from json file");
    const char* infile_name = cimg_option("-i", "graph.json",
            "Graph Definition File");
    const char* outfile_name = cimg_option("-o", (char*)NULL,
            "The image file to put the generated graph into");

    if(!outfile_name){
        std::cerr << "Outfile must be specified" << std::endl;
        return 0;
    }

    std::ifstream infile(infile_name);
    if((!infile_name) or (!infile)){
        std::cerr << "Infile could not be opened" << std::endl;
        return 0;
    }
    std::string indata((std::istreambuf_iterator<char>(infile)),
                        std::istreambuf_iterator<char>());

    json::json j_complete = json::json::parse(indata);

    infile.close();
}
