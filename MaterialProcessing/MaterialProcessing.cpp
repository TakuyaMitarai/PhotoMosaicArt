#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define PhotoNum 1500    //素材画像の枚数
#define HeightSize 42    //素材画像の縦のサイズ変更

vector<int> B, G, R;

//バブルソートB
void sortB(int m, int M)
{
   int flag = 1;
    while(flag) {
        flag = 0;
        for(int i = M; i > m; i--) {
            if(B[i] < B[i-1]) {
                int b = B[i-1];
                B[i-1] = B[i];
                B[i] = b;
                flag = 1;
            }
        }
    }
}

//バブルソートG
void sortG(int m, int M)
{
   int flag = 1;
    while(flag) {
        flag = 0;
        for(int i = M; i > m; i--) {
            if(G[i] < G[i-1]) {
                int b = G[i-1];
                G[i-1] = G[i];
                G[i] = b;
                flag = 1;
            }
        }
    }
}

//バブルソートR
void sortR(int m, int M)
{
   int flag = 1;
    while(flag) {
        flag = 0;
        for(int i = M; i > m; i--) {
            if(R[i] < R[i-1]) {
                int b = R[i-1];
                R[i-1] = R[i];
                R[i] = b;
                flag = 1;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    double ResizeRate; //resize()の縮小割合
    long long cnt;

    //素材画像の処理
    if((fp = fopen("MaterialResult.csv", "w")) == NULL) {
		cout << "ファイルがひらけませんでした";
		exit(-1);
	}
    string FolderName = "../material/R"; //ファイルパス共通部分
    string FN; //ファイルパス
    cv::Mat img; //画像格納変数

    for(int i = 1; i <= PhotoNum; i++) {
        //画像入力
        if(i < 10) {
            FN = FolderName + "0000" + to_string(i) + ".jpg";
            img= cv::imread(FN, 1);
        } else if(i < 100) {
            FN = FolderName + "000" + to_string(i) + ".jpg";
            img = cv::imread(FN, 1);
        } else if(i < 1000) {
            FN = FolderName + "00" + to_string(i) + ".jpg";
            img = cv::imread(FN, 1);
        } else {
            FN = FolderName + "0" + to_string(i) + ".jpg";
            img = cv::imread(FN, 1);
        }

        //resize
        ResizeRate = (double)HeightSize / (double)img.size().height;
        cv::resize(img, img, cv::Size(), ResizeRate, ResizeRate);

        //初期化
        cnt = 0;
        B.resize(img.rows * img.cols);
        G.resize(img.rows * img.cols);
        R.resize(img.rows * img.cols);

        //全画素値取得
        for(int y = 0; y < img.rows; ++y){
	        for(int x = 0; x < img.cols; ++x){
                B[cnt] = img.at<cv::Vec3b>(y, x)[0];
                G[cnt] = img.at<cv::Vec3b>(y, x)[1];
                R[cnt] = img.at<cv::Vec3b>(y, x)[2];
                cnt++;
	        }
        }

        //各画素値のソート
        sortB(0, img.rows * img.cols - 1);
        sortG(0, img.rows * img.cols - 1);
        sortR(0, img.rows * img.cols - 1);

        //画素値の中央値の書き出し
        for(int j = 0; j < 6; j++) {
            fprintf(fp, "%d,%d,%d\n", B[img.rows * img.cols / 2], G[img.rows * img.cols / 2], R[img.rows * img.cols / 2]);
        }
    }
    fclose(fp);
    //cv::waitKey(0);
    return 0;
}