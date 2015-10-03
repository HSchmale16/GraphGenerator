/**\file main.cpp
 * \author Henry J Schmale
 * \date October 2, 2015
 *
 * The graph generator program.
 *
 *      ./graphgen <datafile> <img_format> <outfile>
 */

#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <cstdint>
#include <cstdio>
#include <map>
#include <json.hpp>
#include <CImg.h>


// Rename Namespaces to make it shorter for me to type
namespace cimg = cimg_library;
namespace json = nlohmann;

typedef void (*funcPointer)(json::json&);

// forward declare graph drawing functions
void pieGraph(json::json&);
void barGraph(json::json&);

// declare function pointer map
std::map<std::string, funcPointer> stringFunctionMap ={
    {"pie", &pieGraph},
    {"bar", &barGraph}
}; 

// Just make this global
cimg::CImg<uint8_t> image;

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

    json::json j_object = json::json::parse(indata);

    auto it_graph   = j_object.find("graph");
    auto it_type    = it_graph->find("type");
    auto it_width   = it_graph->find("width");
    auto it_height  = it_graph->find("height");
    int w, h;
    if(!it_width->is_number()){
        // throw a hissy fit
        std::cerr << "Width in json NOT A NUMBER" << std::endl;
        return 0;
    }else{
        if(!it_height->is_number()){
            std::cerr << "Height in json NOT A NUMBER" << std::endl;
            return 0;
        }else{
            w = it_width->get<int>();
            h = it_height->get<int>();
        } 
    }
    image.assign(w, h, 1, 3, 255);

    // call the appropite function pointer
    stringFunctionMap[*it_type](j_object);

    // clean up
    infile.close();
    image.save(outfile_name);
}

void pieGraph(json::json& j){
    double dR = 100, r1 = 0, r2 = dR;
    double radians = 0;
    double oldRads = 0;
    auto it_maindata = j.find("data");
    if(!it_maindata->is_array()){
        return; 
    }
    uint8_t color[] = {255, 0, 0};
    uint8_t color2[] = {0, 0, 0}; // text color
    uint8_t sect[] = {255, 255, 0};
    int cx = image.width() / 2.0;
    int cy = image.height() / 2.0;
    auto it_graph = j.find("graph");
    image.draw_text(10, 10,
            it_graph->find("title")->get<std::string>().c_str(),
            color2, NULL, 1.0, 18);
    image.draw_circle(cx, cy, dR, color);
    color[1] = 255;
    color[2] = 255;
    int i = 1;
    for(auto it = it_maindata->begin(); it != it_maindata->end(); ++it){
        auto it_val = it->find("val");
        double size = ((double)*it_val / 100.0) * 2 * M_PI;
        oldRads = radians;
        radians += size;
        int x1 = cx + cos(radians) * r2;
        int y1 = cy + sin(radians) * r2;
        int xf = cx + cos(radians - size / 2.0) * r2 * .80;
        int yf = cy + sin(radians - size / 2.0) * r2 * .80;
        image.draw_line(cx, cy, x1, y1, color);
        image.draw_fill(xf, yf, sect);
        image.draw_text(xf, yf,
                it->find("name")->get<std::string>().c_str(),
                color2, NULL, 1.0, 13);
        sect[i % 3] += rand() % 255;
        i++;
        printf("DrawLine(%d,%d,%d,%d)\n",cx,cy,x1,y1);
    }
}

void barGraph(json::json& j){}

