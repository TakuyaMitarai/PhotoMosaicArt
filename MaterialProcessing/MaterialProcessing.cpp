#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define PhotoNum 3    //素材画像の枚数
#define HeightSize 42    //縦のサイズ変更

vector<int> B, G, R;

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
    if((fp = fopen("MaterialResult.csv", "w")) == NULL) {
		cout << "ファイルがひらけませんでした";
		exit(-1);
	}
    string FolderName = "../material/R";
    string FN;
    cv::Mat img[20000];
    double ResizeRate;

    for(int i = 1; i <= PhotoNum; i++) {
        //画像入力
        if(i < 10) {
            FN = FolderName + "0000" + to_string(i) + ".jpg";
            img[i]= cv::imread(FN, 1);
        } else if(i < 100) {
            FN = FolderName + "000" + to_string(i) + ".jpg";
            img[i] = cv::imread(FN, 0);
        } else if(i < 1000) {
            FN = FolderName + "00" + to_string(i) + ".jpg";
            img[i] = cv::imread(FN, 0);
        } else {
            FN = FolderName + "0" + to_string(i) + ".jpg";
            img[i] = cv::imread(FN, 0);
        }

        //resize
        ResizeRate = (double)HeightSize / (double)img[i].size().height;
        cv::resize(img[i], img[i], cv::Size(), ResizeRate, ResizeRate);

        //画素値抽出
        //初期化
        long long cnt = 0;
        B.resize(img[i].rows * img[i].cols);
        G.resize(img[i].rows * img[i].cols);
        R.resize(img[i].rows * img[i].cols);

        for(int y = 0; y < img[i].rows; ++y){
	        for(int x = 0; x < img[i].cols; ++x){
                B[cnt] = img[i].at<cv::Vec3b>(y, x)[0];
                G[cnt] = img[i].at<cv::Vec3b>(y, x)[1];
                R[cnt] = img[i].at<cv::Vec3b>(y, x)[2];
                cnt++;
	        }
        }
        sortB(0, img[i].rows * img[i].cols - 1);
        sortG(0, img[i].rows * img[i].cols - 1);
        sortR(0, img[i].rows * img[i].cols - 1);

        fprintf(fp, "%d,%d,%d\n", B[img[i].rows * img[i].cols / 2], G[img[i].rows * img[i].cols / 2], R[img[i].rows * img[i].cols / 2]);
        cv::Mat one_img(cv::Size(640, 480), CV_8UC3, cv::Scalar(B[img[i].rows * img[i].cols / 2], G[img[i].rows * img[i].cols / 2], R[img[i].rows * img[i].cols / 2]));
        cv::imshow(FN, one_img);
    }
    cv::waitKey(0);
    return 0;
}