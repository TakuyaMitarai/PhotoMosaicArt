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

//カンマ区切りで読み込む関数
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
    Population* pop;
   
    srand((unsigned int)time(NULL));

    //元画像を2025(=45 * 45)分割して，部分ごとに画素値の中央値を記述したファイルをopen
    ifstream ifs("../OriginalProcessing/OriginalResult.csv");

    //画素値読込
    string line;
    while (getline(ifs, line)) {

        vector<string> strvec = split(line, ',');
       
        OB.push_back(stoi(strvec.at(0)));
        OG.push_back(stoi(strvec.at(1)));
        OR.push_back(stoi(strvec.at(2)));
    }

    //素材画像9000(= 1500 * 6)枚の画素値の中央値を記述したファイルをopen
    ifstream ifs2("../MaterialProcessing/MaterialResult.csv");

    //画素値読込
    string line2;
    while (getline(ifs2, line2)) {

        vector<string> strvec = split(line2, ',');
       
        B.push_back(stoi(strvec.at(0)));
        G.push_back(stoi(strvec.at(1)));
        R.push_back(stoi(strvec.at(2)));
    }

    //素材画像の並べ方を書き込むファイルをopen
    FILE *fp;
    fp = fopen("Result.csv", "w");

    //遺伝的アルゴリズムの試行
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
