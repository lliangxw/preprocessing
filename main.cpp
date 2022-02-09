#include<iostream>
#include "opencv2/opencv.hpp"
#include <math.h>
#include <cmath>
using namespace std;
using namespace cv;

float calc_alpha(float m)
{
    float alpha;
    if (m<128)
    {
        alpha = log(exp(m/255))/log(exp(0.5));
    }
    else{
        alpha = log(exp(0.5))/log(exp(m/255));
    }

    return alpha;
}

// int main()
// {
//     for (int video_nb=2;video_nb<3;video_nb++)
//     {
//         string video_nb_ = to_string(video_nb);
//         for (int img_nb=0; img_nb<25; img_nb++)
//         {
//             string img_nb_ = to_string(img_nb);
//             string img_path="/home/xiaowen/Documents/result/preprocessing/denoising/denoising_4/"+video_nb_+"/bl/"+img_nb_+".png";
//             Mat img = imread(img_path, IMREAD_GRAYSCALE);
//             Mat img_cp =  img.clone();
//             int iCol = img.cols;
//             int iRow = img.rows;
//             Mat img_out = Mat::zeros(iRow, iCol, CV_8UC1);
//             Mat inv = 255 - img_cp;
//             Mat mask; 
//             Scalar mean, stddev;
//             meanStdDev(img, mean, stddev);
//             // cout<<"before "<<stddev<<endl;
//             // cout<<mean<<endl;
//             // GaussianBlur(inv, mask, Size(15,15),0);
//             bilateralFilter(inv, mask, -1, 30, 30);
//             float alpha = calc_alpha(mean.val[0]);
//             // cout<<alpha<<endl;
//             for (int i=0; i<iRow;i++)
//             {
//                 for (int j=0;j<iCol;j++)
//                 {
//                     float pix_img = (float)img.at<uchar>(i,j);
//                     float pix_mask = (float)mask.at<uchar>(i,j);
//                     int out_pix = 255*pow((pix_img/255), pow(alpha, (128-pix_mask)/128));
//                     img_out.at<uchar>(i,j) = out_pix;

//                 }
//             }
//             // meanStdDev(img_out, mean, stddev);
//             // cout<<"after "<<mean<<endl;
//             imwrite("/home/xiaowen/Documents/result/preprocessing/denoising/denoising_4/"+video_nb_+"/adjust_bis/"+img_nb_+".png", img_out);
//         }
//     }
// }

//// step 1, bilateral filtering
// int main()
// {

//     for (int video_nb=25;video_nb<55;video_nb++)
//     {
//         string video_nb_ = to_string(video_nb);
//         for (int img_nb=0; img_nb<256; img_nb++)
//         {
//             string img_nb_ = to_string(img_nb);
//             string img_path="/home/xiaowen/Documents/images/sous_echan/" + video_nb_ + "/"+img_nb_+".png";
//             Mat img = imread(img_path, IMREAD_GRAYSCALE);
//             Scalar mean, stddev;
//             meanStdDev(img, mean, stddev);
//             double stddev_pxl = stddev.val[0];
//             Mat img_out(img.size(), CV_8UC1);
//             // cout<<video_nb_<<":"<<stddev_pxl<<endl;
//             // GaussianBlur(img, img_out, Size(5,5),0);
//             int sigma_c = pow(2,sqrt((stddev_pxl+10)*0.5));
//             // cout<<"sigma_c:"<<sigma_c<<endl;
//             bilateralFilter(img, img_out, -1, sigma_c, 50);
//             imwrite("/home/xiaowen/Documents/result/preprocessing/denoising/denoising_4/"+video_nb_+"/bl/"+img_nb_+".png", img_out);
//         }
//     }
// }

//// step 2 , normalization 
// int main()
// {
//     for (int video_nb=0;video_nb<14;video_nb++)
//     {
//         string video_nb_ = to_string(video_nb);
//         for (int img_nb=0; img_nb<256; img_nb++)
//         {
//             string img_nb_ = to_string(img_nb);
//             string img_path="/home/xiaowen/Documents/result/preprocessing/denoising/denoising_4/"+video_nb_+"/bl/"+img_nb_+".png";
//             Mat img = imread(img_path, IMREAD_GRAYSCALE);
//             Mat img_out(img.size(), CV_8UC1);
//             Scalar mean, stddev;
//             meanStdDev(img, mean, stddev);
//             double mean_pxl = mean.val[0];
//             double stddev_pxl = stddev.val[0];

//             int m0 = 128, f0 = 40;
//             if (stddev_pxl>=f0)
//             {
//                 f0 = stddev_pxl;
//             }

//             for (int i=0; i<img.rows;i++)
//             {
//                 for (int j=0; j<img.cols;j++)
//                 {   int temp=0;
//                     temp = m0+(f0/(stddev_pxl))*((img.at<uchar>(i,j)-mean_pxl));
//                     if (temp>255)
//                     {
//                         temp = 255;
//                     }
//                     if (temp<0)
//                     {
//                         temp = 0;
//                     }
//                     img_out.at<uchar>(i,j) = temp;
//                 }
//             }
            
//             // cout<<"after "<<stddev<<endl;
//             imwrite("/home/xiaowen/Documents/result/preprocessing/denoising/denoising_4/"+video_nb_+"/adjust/"+img_nb_+".png", img_out);
//         }
//     }
// }

/// step 3, non-local means denoising 

int main()
{
    for (int video_nb=0;video_nb<14;video_nb++)
    {
        string video_nb_ = to_string(video_nb);
        for (int img_nb=0; img_nb<10; img_nb++)
        {
            string img_nb_ = to_string(img_nb);
            string img_path="/home/xiaowen/Documents/result/preprocessing/denoising/denoising_4/"+video_nb_+"/adjust/"+img_nb_+".png";
            Mat img = imread(img_path, IMREAD_GRAYSCALE);
            Mat img_out_1(img.size(), CV_8UC1);
            Mat img_out_2(img.size(), CV_8UC1);
            // Scalar mean, stddev;
            // meanStdDev(img, mean, stddev);
            // double mean_pxl = mean.val[0];
            // double stddev_pxl = stddev.val[0];
            fastNlMeansDenoising(img, img_out_1, 20, 7, 21);
            fastNlMeansDenoising(img_out_1, img_out_2, 10, 7, 21);
            // cout<<"after "<<stddev<<endl;
            imwrite("/home/xiaowen/Documents/result/preprocessing/denoising/denoising_4/"+video_nb_+"/nlm_1/"+img_nb_+".png", img_out_1);
            imwrite("/home/xiaowen/Documents/result/preprocessing/denoising/denoising_4/"+video_nb_+"/nlm_2/"+img_nb_+".png", img_out_2);
        }
    }
}
