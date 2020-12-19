/*********************************************************************************
**
** Copyright (c) 2020 University of California, Berkeley
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without specific
** prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
** SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
** IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
**
***********************************************************************************/

// Contributors:
// Ajay B Harish, Post-Doc @ SimCenter, UC Berkeley

//*********************************************************************************
// Include library headers
//*********************************************************************************
#include <iostream>
#include <fstream>
#include <math.h>
#include "include/Eigen/Dense"

//*********************************************************************************
// Declare functions
//*********************************************************************************
int getfiletype(int num);
Eigen::MatrixXd adcirc_tp01(std::string fname,Eigen::MatrixXd data,int nrows,int tsteps);
bool printmatrix(std::string fname, Eigen::MatrixXd mat);

//*********************************************************************************
// Start of routine
//*********************************************************************************
int main(int argc, char *argv[])
{   

    // Message to show that computation has started
    std::cout << "Parsing started" << std::endl;
    
    // Checking for the number of arguments and file existence
    if(argc<4) 
    {
        // Not enough input arguments available
        std::cout << "Error: File type and/or file names not provided" << std::endl;
        return(1);
    }
    else
    {
        // Print out the input arguments
        std::cout << "File type: " << argv[1] << "\nFile name: " << argv[2] << "\nO/p file name: " << argv[3] << std::endl;

        // Check if file exists. Else return error
        std::ifstream is(argv[2]);
        if (is.fail()) return 1;
    }

    // Get file type
    int filetype = getfiletype(atoi(argv[1]));

    // Call the appropriate file reader
    if(filetype == 1)
    {
        // Initialize data
        std::string line;
        int nrows,tsteps;

        // Create a file stream
        std::ifstream adCFile(argv[2]);
        getline(adCFile,line); //Ignoring line 1
        getline(adCFile,line); //Get data for number of poitns from line 2
        std::istringstream iss(line);
        iss >> tsteps; // Get the number of time steps
        iss >> nrows; // Number of points

        // Initialize the data structure
        Eigen::MatrixXd data = Eigen::MatrixXd::Zero(nrows+1,2*tsteps);

        // Get the parsed data
        data = adcirc_tp01(argv[2],data,nrows,tsteps);
    }

    std::cout << "Parsing complete" << std::endl;    
    return 0;
}
//*********************************************************************************
// End of routine
//*********************************************************************************

//*********************************************************************************
// Get file type
//*********************************************************************************
int getfiletype(int num)
{
    int type;
    if(num == 62)
    {
        return 1;
    }
    else if (num == 64)
    {
        return 1;
    }

    return 0;    
}

//*********************************************************************************
// Filetype: 62 / 64
//*********************************************************************************
Eigen::MatrixXd adcirc_tp01(std::string fname,Eigen::MatrixXd data,int nrows,int tsteps)
{
    // Create a file stream
    std::ifstream adCFile(fname);
    
    // Initialize the data
    std::string line;
    int temp;

    // Skip the first two lines
    getline(adCFile, line);
    getline(adCFile, line);

    // Loop over the entire file
    for (int ii=0;ii<2;ii++) //tsteps
    {
        getline(adCFile, line);
        std::istringstream iss(line);
        iss >> data(0,2*ii);
        iss >> data(0,2*ii+1);

        for (int jj=1;jj<nrows+1;jj++) // Num of points
        {
            getline(adCFile, line);
            std::istringstream iss(line);
            iss >> temp; //First index (ignored)
            iss >> data(jj,2*ii); //x-quantity
            iss >> data(jj,2*ii+1); //y-quantity
        }        
    }

    // Close the input file
    adCFile.close();

    // Return
    return data;
}



//*********************************************************************************
// Print Eigen matrix
//*********************************************************************************
bool printmatrix(std::string fname, Eigen::MatrixXd mat)
{
    std::ofstream checkFile(fname);
    checkFile << std::setprecision(20) << mat <<  "\n" ;
    checkFile.close();

    return 1;
}