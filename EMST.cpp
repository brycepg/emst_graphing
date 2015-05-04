#include <iostream>
#include <cstdlib>

// Mlpack Includes
#include <mlpack/methods/emst/dtb.hpp>
#include <mlpack/core.hpp> 

// Core Root Framework
#include "TROOT.h"

// Root utility classes
#include "TApplication.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TGaxis.h"

using namespace mlpack;
using namespace mlpack::metric;
using namespace mlpack::emst;

struct ReturnComputeData {
    arma::mat data;
    arma::mat tree; 
};
struct ReturnComputeData compute_emst(int, char**);
void draw_canvas(arma::mat, TCanvas*);
void draw_edges(arma::mat, arma::mat);
void draw_nodes(arma::mat);

int main(int argc, char** argv){

    // Do MLpack EMST computation on input data
    struct ReturnComputeData returnComputeData;
    returnComputeData = compute_emst(argc, argv);
    arma::mat tree = returnComputeData.tree;
    arma::mat data = returnComputeData.data;


    // Setup Root App
    // Needs to be declared to apply any Draw() 
    //    functions
    TApplication RootApplication("EMST Graph", 0, nullptr);
    TCanvas* c1 = new TCanvas("EMST Graph");


    draw_canvas(data, c1);
    draw_edges(tree, data);
    draw_nodes(data);

    // Display application
    RootApplication.Run();

    // Note: I do not free any dynamically allocated data because all of it is
    //  used until the end of the program run time and because of how root globally
    //  accesses application elements

	return 0;
}

void draw_canvas(arma::mat data, TCanvas* c1) {
    // Determine bounds based on scale and data
    arma::Row<double> xval = data.row(0);
    arma::Row<double> yval = data.row(1);
    double min_x = arma::min(xval);
    double min_y = arma::min(yval);
    double max_x = arma::max(xval);
    double max_y = arma::max(yval);
    // Add buffer to see edge data points
    double bufferx = (max_x - min_x)/100.0;
    double buffery = (max_y - min_y)/100.0;
    c1->Range(min_x - 4*bufferx, min_y - 4*buffery, 
                max_x + bufferx, max_y + buffery);
    TGaxis *haxis = new TGaxis(min_x, min_y, max_x, min_y, min_x, max_x, 50510, "+L");
    TGaxis *vaxis = new TGaxis(min_x, min_y, min_x, max_y, min_y, max_y, 50510, "-L");

    haxis->Draw();
    vaxis->SetLabelOffset(.03);
    vaxis->Draw();
}

void draw_edges(arma::mat tree, arma::mat data) {
    TLine* arrow = nullptr;
  for(size_t tree_cols = 0; tree_cols < tree.n_cols; tree_cols++) {
      double x1 = data(0, tree(0,tree_cols));
      double y1 = data(1, tree(0,tree_cols));
      double x2 = data(0, tree(1,tree_cols));
      double y2 = data(1, tree(1,tree_cols));
      std::cout << "x1: " << x1 << ", y1: " 
                << y1 << " to " "x2: " << x2 
                << ", y2: " << y2 << "\n";
      arrow = new TLine(x1, y1, x2, y2);
      arrow->Draw();

  }
}

void draw_nodes(arma::mat data) {
    const int MARKER_SHAPE = 7;
    TMarker* marker = nullptr;
    for(size_t data_cols = 0; data_cols < data.n_cols; data_cols++) {
      double x1 = data(0, data_cols);
      double y1 = data(1, data_cols);
      marker = new TMarker(x1, y1, MARKER_SHAPE);
      marker->Draw();

    }
}

struct ReturnComputeData compute_emst(int argc, char **argv) {
	// Our dataset matrix, which is column-major
    arma::mat data;
    switch(argc) {
        case 1:
            data::Load("data.csv", data, true);
            break;
        case 2:
            data::Load(argv[1], data, true);
            break;
        default:
            std::cerr << "Must have either one or no arguments. See README.txt"
                << std::endl;
            exit(EXIT_FAILURE);
            break;
    }
	
	//set up variables
	arma::mat tree;
	DualTreeBoruvka<> dtb(data);	
    if(data.n_rows != 2) {
        std::cerr << "This program only accepts 2d data points";
        exit(EXIT_FAILURE);
    }

	//do the calculations
	dtb.ComputeMST(tree);

    data::Save("emst_tree.csv", tree);

    ReturnComputeData returnComputeData;
    returnComputeData.data = data;
    returnComputeData.tree = tree;

    return returnComputeData;
}
