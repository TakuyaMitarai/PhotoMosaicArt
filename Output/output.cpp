#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

#define WidthSize 60
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
    string FolderName = "../material/R";
    string FN;

    ifstream ifs("../GA/Result.csv");

    int cnt;
    vector<int> s;
    vector<string> strvec;
    string line;
    while (getline(ifs, line)) {

        strvec = split(line, ',');
       
    }

    for(int i = 0; i < 2025; i++) {
        s.push_back(stoi(strvec.at(i)));
        //cout << (int)stoi(strvec.at(i)) << " ";
    }
    cv::Mat img;
    cv::Mat x;
    cv::Mat y;
    int d = 1;
    int e = 1;
    cnt = 0;

    /*
    if((s[cnt] / 6) < 10) {
            FN = FolderName + "0000" + to_string(s[cnt] / 6) + ".jpg";
            x = cv::imread(FN, 1);
        } else if((s[cnt] / 6) < 100) {
            FN = FolderName + "000" + to_string(s[cnt] / 6) + ".jpg";
            x = cv::imread(FN, 1);
        } else if((s[cnt] / 6) < 1000) {
            FN = FolderName + "00" + to_string(s[cnt] / 6) + ".jpg";
            x = cv::imread(FN, 1);
        } else {
        FN = FolderName + "0" + to_string(s[cnt] / 6) + ".jpg";
        x = cv::imread(FN, 1);
    }
    double ResizeRate = (double)WidthSize / (double)x.size().width;
    cv::resize(x, x, cv::Size(), ResizeRate, ResizeRate);
    x = cv::Mat(x, cv::Rect(0, 0, 60, 30)).clone();

    cout << x.size().width << " " << x.size().height << endl;

    cnt++;
    if((s[cnt] / 6) < 10) {
            FN = FolderName + "0000" + to_string(s[cnt] / 6) + ".jpg";
            y = cv::imread(FN, 1);
        } else if((s[cnt] / 6) < 100) {
            FN = FolderName + "000" + to_string(s[cnt] / 6) + ".jpg";
            y = cv::imread(FN, 1);
        } else if((s[cnt] / 6) < 1000) {
            FN = FolderName + "00" + to_string(s[cnt] / 6) + ".jpg";
            y = cv::imread(FN, 1);
        } else {
        FN = FolderName + "0" + to_string(s[cnt] / 6) + ".jpg";
        y = cv::imread(FN, 1);
    }
    ResizeRate = (double)WidthSize / (double)y.size().width;
    cv::resize(y, y, cv::Size(), ResizeRate, ResizeRate);
    y = cv::Mat(y, cv::Rect(0, 0, 60, 30)).clone();

    cout << y.size().width << " " << y.size().height << endl;

    cnt++;

    cv::hconcat(x, y, x);
    img = x;

    if((s[cnt] / 6) < 10) {
            FN = FolderName + "0000" + to_string(s[cnt] / 6) + ".jpg";
            x = cv::imread(FN, 1);
        } else if((s[cnt] / 6) < 100) {
            FN = FolderName + "000" + to_string(s[cnt] / 6) + ".jpg";
            x = cv::imread(FN, 1);
        } else if((s[cnt] / 6) < 1000) {
            FN = FolderName + "00" + to_string(s[cnt] / 6) + ".jpg";
            x = cv::imread(FN, 1);
        } else {
        FN = FolderName + "0" + to_string(s[cnt] / 6) + ".jpg";
        x = cv::imread(FN, 1);
    }
    ResizeRate = (double)WidthSize / (double)x.size().width;
    cv::resize(x, x, cv::Size(), ResizeRate, ResizeRate);
    x = cv::Mat(x, cv::Rect(0, 0, 60, 30)).clone();

    cout << x.size().width << " " << x.size().height << endl;

    cnt++;
    if((s[cnt] / 6) < 10) {
            FN = FolderName + "0000" + to_string(s[cnt] / 6) + ".jpg";
            y = cv::imread(FN, 1);
        } else if((s[cnt] / 6) < 100) {
            FN = FolderName + "000" + to_string(s[cnt] / 6) + ".jpg";
            y = cv::imread(FN, 1);
        } else if((s[cnt] / 6) < 1000) {
            FN = FolderName + "00" + to_string(s[cnt] / 6) + ".jpg";
            y = cv::imread(FN, 1);
        } else {
        FN = FolderName + "0" + to_string(s[cnt] / 6) + ".jpg";
        y = cv::imread(FN, 1);
    }
    ResizeRate = (double)WidthSize / (double)y.size().width;
    cv::resize(y, y, cv::Size(), ResizeRate, ResizeRate);
    y = cv::Mat(y, cv::Rect(0, 0, 60, 30)).clone();

    cout << y.size().width << " " << y.size().height << endl;

    cnt++;

    cv::hconcat(x, y, x);

    cv::vconcat(img, x, img);
    */
    
    for(int ys = 0; ys < 45; ys++) {
        for(int xs = 0; xs < 45; xs++) {
            if(d == 1) {
                cout << s[cnt] / 6  + 1 << endl;
                if((s[cnt] / 6  + 1) < 10) {
                    FN = FolderName + "0000" + to_string(s[cnt] / 6  + 1) + ".jpg";
                    x = cv::imread(FN, 1);
                } else if((s[cnt] / 6  + 1) < 100) {
                    FN = FolderName + "000" + to_string(s[cnt] / 6  + 1) + ".jpg";
                    x = cv::imread(FN, 1);
                } else if((s[cnt] / 6  + 1)  < 1000) {
                    FN = FolderName + "00" + to_string(s[cnt] / 6  + 1) + ".jpg";
                    x = cv::imread(FN, 1);
                } else {
                    FN = FolderName + "0" + to_string(s[cnt] / 6  + 1) + ".jpg";
                    x = cv::imread(FN, 1);
                }
                double ResizeRate = (double)WidthSize / (double)x.size().width;
                cv::resize(x, x, cv::Size(), ResizeRate, ResizeRate);

                x = cv::Mat(x, cv::Rect(0, 0, 60, 30)).clone();
                d = 0;
                cnt++;
            }else {
                cout << s[cnt] / 6  + 1 << endl;
                if((s[cnt] / 6  + 1)  < 10) {
                    FN = FolderName + "0000" + to_string(s[cnt] / 6  + 1) + ".jpg";
                    y = cv::imread(FN, 1);
                } else if((s[cnt] / 6  + 1)  < 100) {
                    FN = FolderName + "000" + to_string(s[cnt] / 6  + 1) + ".jpg";
                    y = cv::imread(FN, 1);
                } else if((s[cnt] / 6  + 1)  < 1000) {
                    FN = FolderName + "00" + to_string(s[cnt] / 6  + 1) + ".jpg";
                    y = cv::imread(FN, 1);
                } else {
                    FN = FolderName + "0" + to_string(s[cnt] / 6  + 1) + ".jpg";
                    y = cv::imread(FN, 1);
                }
                double ResizeRate = (double)WidthSize / (double)y.size().width;
                cv::resize(y, y, cv::Size(), ResizeRate, ResizeRate);

                y = cv::Mat(y, cv::Rect(0, 0, 60, 30)).clone();

                //画像の合成
                cv::hconcat(x, y, x);
                cnt++;
            }
        }
        if(e == 1) {
            img = x;
            e = 0;
        } else {
            vconcat(img, x, img);
        }
        d = 1;
    }
    
    cv::imshow("PhotoMosaicArt",img);
    cv::waitKey(0);
}