/*#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>*/
#include "Population.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> B, G, R;
vector<int> OB, OG, OR;

vector<string> split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

int main()
{
    int i;
    float comptime;
    Population* pop;
   
    srand((unsigned int)time(NULL));

    ifstream ifs("../MaterialProcessing/OriginalResult.csv");

    string line;
    while (getline(ifs, line)) {

        vector<string> strvec = split(line, ',');
       
        OB.push_back(stoi(strvec.at(0)));
        OG.push_back(stoi(strvec.at(1)));
        OR.push_back(stoi(strvec.at(2)));
    }
    /*for (int i=0; i< OB.size();i++){
        cout << OB[i] << " " << OG[i] << " " << OR[i] << endl;
    }*/

    ifstream ifs2("../MaterialProcessing/MaterialResult.csv");

    string line2;
    while (getline(ifs2, line2)) {

        vector<string> strvec = split(line2, ',');
       
        B.push_back(stoi(strvec.at(0)));
        G.push_back(stoi(strvec.at(1)));
        R.push_back(stoi(strvec.at(2)));
    }
    /*for (i=0; i<B.size();i++){
        cout << B[i] << " " << G[i] << " " << R[i] << endl;
    }*/

    /*cv::Mat image(cv::Size(270 ,180), CV_8UC3);
    int cnt = 0;
    for(int ys = 0; ys < 45; ys++) {
        for(int xs = 0; xs < 45; xs++) {
            for(int y = ys * 4; y < ys * 4 + 4; y++) {
                for(int x = xs * 6; x < xs * 6 + 6; x++) {
                    image.at<cv::Vec3b>(y, x)[0] = OB[cnt];
                    image.at<cv::Vec3b>(y, x)[1] = OG[cnt];
                    image.at<cv::Vec3b>(y, x)[2] = OR[cnt];
                }
            }
            cnt++;
        }
    }
    cv::imshow("original", image);
    cv::waitKey(0);
    */
    FILE *fp;
    fp = fopen("Result.csv", "w");

    pop = new Population();
    for(i = 1; i <= GEN_MAX; i++) {
        pop->alternate();
        printf("試行回数%d 誤差%f\n", i, pop->ind[0]->fitness);
    }
    pop->printResult();
    for(i = 0; i < N; i++) {
        fprintf(fp, "%d,", pop->ind[0]->chrom[i]);
    }
    delete pop;
    fclose(fp);

    return 0;
}
