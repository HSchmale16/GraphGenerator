/**\file main.cpp
 * \author Henry J Schmale
 * \date October 2, 2015
 *
 * The graph generator program.
 *
 *      ./graphgen <datafile> <img_format> <outfile>
 */

#include <string>
#include <iostream>
#include <json.hpp>
#include <CImg.h>

namespace cimg = cimg_library;
namespace json = nlohmann;

int main(int argc, char** argv){
    // Parse Command Line Args
    cimg_usage("Generates a graph from json file");
    const char* infile = cimg_option("-i", "graph.json",
            "Graph Definition File");
    const char* outfile = cimg_option("-o", (char*)NULL,
            "The image file to put the generated graph into");

    // begin parse

}
