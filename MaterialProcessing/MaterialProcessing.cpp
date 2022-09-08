#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define PhotoNum 1500    //素材画像の枚数
#define HeightSize 42    //素材画像の縦のサイズ変更
#define OriginalHeightSize 270 //元画像の縦のサイズ変更
#define OriginalPhotoSplit 45 //モザイクアートの縦横の画像の枚数

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
    //元画像の処理
    FILE *fp;
    double ResizeRate;
    long long cnt;

    if((fp = fopen("OriginalResult.csv", "w")) == NULL) {
		cout << "ファイルがひらけませんでしたoriginal";
		exit(-1);
	}
    //読込
    cv::Mat original = cv::imread("../original/original.jpg", 1);

    //resize
    ResizeRate = (double)OriginalHeightSize / (double)original.size().width;
    cv::resize(original, original, cv::Size(), ResizeRate, ResizeRate);

    //画素値の取得
    //初期化
    B.resize(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit);
    G.resize(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit);
    R.resize(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit);

    for(int sy = 0; sy < OriginalPhotoSplit; ++sy){
	    for(int sx = 0; sx < OriginalPhotoSplit; ++sx){
            cnt = 0;
            for(int y = sy * (original.rows / OriginalPhotoSplit); y < (sy + 1) * (original.rows / OriginalPhotoSplit); y++){
                for(int x = sx * (original.cols / OriginalPhotoSplit); x < (sx + 1) * (original.cols / OriginalPhotoSplit); x++){
                    B[cnt] = (int)original.at<cv::Vec3b>(y, x)[0];
                    G[cnt] = (int)original.at<cv::Vec3b>(y, x)[1];
                    R[cnt] = (int)original.at<cv::Vec3b>(y, x)[2];
                    cnt++;
	            }
            }
            //ソート
            sortB(0, original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1);
            sortG(0, original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1);
            sortR(0, original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1);

            //出力
            fprintf(fp, "%d,%d,%d\n", B[(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1) / 2], G[(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1) / 2], R[(original.rows / OriginalPhotoSplit * original.cols / OriginalPhotoSplit - 1) / 2]);
        }
    }
    fclose(fp);

    //素材画像の処理
    if((fp = fopen("MaterialResult.csv", "w")) == NULL) {
		cout << "ファイルがひらけませんでした";
		exit(-1);
	}
    string FolderName = "../material/R";
    string FN;
    cv::Mat img;
    cv::Mat one_img;

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

        //画素値取得
        //初期化
        cnt = 0;
        B.resize(img.rows * img.cols);
        G.resize(img.rows * img.cols);
        R.resize(img.rows * img.cols);

        for(int y = 0; y < img.rows; ++y){
	        for(int x = 0; x < img.cols; ++x){
                B[cnt] = img.at<cv::Vec3b>(y, x)[0];
                G[cnt] = img.at<cv::Vec3b>(y, x)[1];
                R[cnt] = img.at<cv::Vec3b>(y, x)[2];
                cnt++;
	        }
        }
        sortB(0, img.rows * img.cols - 1);
        sortG(0, img.rows * img.cols - 1);
        sortR(0, img.rows * img.cols - 1);

        fprintf(fp, "%d,%d,%d\n", B[img.rows * img.cols / 2], G[img.rows * img.cols / 2], R[img.rows * img.cols / 2]);
        for(int j = 0; j < 5; j++) {
            fprintf(fp, "%d,%d,%d\n", B[img.rows * img.cols / 2], G[img.rows * img.cols / 2], R[img.rows * img.cols / 2]);
        }
        /*cv::Mat one_img(cv::Size(640, 480), CV_8UC3, cv::Scalar(B[img[i].rows * img[i].cols / 2], G[img[i].rows * img[i].cols / 2], R[img[i].rows * img[i].cols / 2]));
        cv::imshow(FN, one_img);*/
    }
    fclose(fp);
    //cv::waitKey(0);
    return 0;
}