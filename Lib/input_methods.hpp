#include <iostream>
#include <vector>
#include <string>
#include <opencv.hpp>
#include <filesystem>
namespace fs = std::filesystem;


static std::vector<int> OUTPUT_VECTOR_LFF;

void load_from_file(std::vector<Matrix> &input, std::string path, int images_count)
{

    std::cout << "Loading database from '" << path << "' \n";
    int z_current = 0;
    std::string number = "";
    for(int i = path.size() - 1; i>=0; i--)
        if(path[i] == '\\')
            break;
        else
            number += path[i];

    int number_int = atoi( number.c_str() );


    for (const auto & entry : fs::directory_iterator(path))
    {
        if(z_current < images_count)
        {
            std::string path_string{entry.path().u8string()}; // convert filestream path to string path
            cv::Mat img = cv::imread(path_string, cv::IMREAD_COLOR); // read the current image

            uint8_t* pixelPtr = (uint8_t*)img.data;  // get data from image
            int cn = img.channels();
            cv::Scalar_<uint8_t> bgrPixel;
            double grayscale = 0;


            input.push_back(Matrix());
            // iterate over rows and columns to append values into the input vector
            for(int i = 0; i < img.rows; i++)
            {
                for(int j = 0; j < img.cols; j++)
                {
                    bgrPixel.val[0] = pixelPtr[i*img.cols*cn + j*cn + 0]; // B
                    bgrPixel.val[1] = pixelPtr[i*img.cols*cn + j*cn + 1]; // G
                    bgrPixel.val[2] = pixelPtr[i*img.cols*cn + j*cn + 2]; // R

                    grayscale = (bgrPixel.val[0] + bgrPixel.val[1] + bgrPixel.val[2]) / 3;
                    input[z].add({grayscale / 255});
                }
            }

            OUTPUT_VECTOR_LFF.push_back(number_int);
            std::cout << z_current << " / " << images_count << "\n";
            input[z] = input[z].transpose();  // transpose the column matrix to row matrix
            z++;
            z_current++;
        }

    }
    std::cout << "\n\n";


}
