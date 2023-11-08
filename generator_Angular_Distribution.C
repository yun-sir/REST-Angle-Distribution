#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <TRandom3.h>

int generator_Angular_Distribution()
{
    TFile* file = new TFile("my.root", "RECREATE");
    // 创建一个具有10个bin的TH1D图像
    TH1D *histogram = new TH1D("histogram", "My Histogram", 100, -0.1, 0.3);
    
    // 使用TRandom3生成一些随机数据填充直方图
    TRandom3 random;
    for (int i = 0; i < 1000; ++i) {
        double value = random.Uniform(0.0, 0.1); // 以均值5和标准差1生成高斯分布的随机数
        histogram->Fill(value);
    }
    double sum = histogram->Integral();
    histogram->Scale(1.0/sum);
    // 创建一个画布并绘制直方图
    TCanvas *canvas = new TCanvas("canvas", "My Canvas");
    histogram->Draw();
    canvas->Print("myroot.png");
    histogram->Write();
    file->Close();

    return 0;
}
