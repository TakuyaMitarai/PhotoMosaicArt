#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define OriginalHeightSize 270 //元画像の縦のサイズ変更
#define OriginalPhotoSplit 45 //モザイクアートの縦横の画像の枚数

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
int main()
{
    //元画像の処理
    FILE *fp;
    double ResizeRate;
    long long cnt;

    //書き出しファイルの読込
    if((fp = fopen("OriginalResult.csv", "w")) == NULL) {
		cout << "ファイルがひらけませんでしたoriginal";
		exit(-1);
	}
    //元画像の読込
    cv::Mat original = cv::imread("../original/original.jpg", 1);

    //resize
    ResizeRate = (double)OriginalHeightSize / (double)original.size().width;
    cv::resize(original, original, cv::Size(), ResizeRate, ResizeRate);

    //初期化
    B.resize(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit);
    G.resize(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit);
    R.resize(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit);

    //画素値の取得
    for(int sy = 0; sy < OriginalPhotoSplit; ++sy){
	    for(int sx = 0; sx < OriginalPhotoSplit; ++sx){
            cnt = 0;
            for(int y = sy * (original.rows / OriginalPhotoSplit); y < (sy + 1) * (original.rows / OriginalPhotoSplit); y++){
                for(int x = sx * (original.cols / OriginalPhotoSplit); x < (sx + 1) * (original.cols / OriginalPhotoSplit); x++){
                    //OriginalPhotoSplit（今回の場合45 * 45 = 2025)分割したうちの一マス分の画素値((270 / 45) * (180 / 45) = 24個分)を取得
                    B[cnt] = (int)original.at<cv::Vec3b>(y, x)[0];
                    G[cnt] = (int)original.at<cv::Vec3b>(y, x)[1];
                    R[cnt] = (int)original.at<cv::Vec3b>(y, x)[2];
                    cnt++;
	            }
            }
            //OriginalPhotoSplit（今回の場合45 * 45 = 2025)分割したうちの一マス分の画素値((270 / 45) * (180 / 45) = 24個分)のソート
            sortB(0, original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1);
            sortG(0, original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1);
            sortR(0, original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1);

            //中央値出力
            fprintf(fp, "%d,%d,%d\n", B[(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1) / 2], G[(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1) / 2], R[(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1) / 2]);
        }
    }
    fclose(fp);
}