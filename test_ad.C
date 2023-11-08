#include <iostream>
#include <cmath>
#include <TGraph2D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH3F.h>
#include <TVector3.h>

int test_ad()
{

    string inputfilename = " /lustre/pandax/wangyun/restG4-Angle-Distribution/cos_theta/Cos_Theta2_10W.root ";
    cout << "file name is : " << inputfilename << endl;
    TFile *inputfile = new TFile(inputfilename.c_str(), "READ");
    TTree *eventTree = (TTree *)inputfile->Get("EventTree");
    int num_of_entries = eventTree->GetEntries();
    
    // G4文件使用如下设置
    TRestG4Event *g4Event = new TRestG4Event();
    eventTree->SetBranchAddress("TRestG4EventBranch", &g4Event);

    TRestG4Track *track = new TRestG4Track();
    TRestG4Hits *g4Hits = new TRestG4Hits();

    TH1D* hist1d_theta = new TH1D("histogram_theta", "", 100, -0.2, +4);
    TH1D* hist1d_phi = new TH1D("histogram_phi", "", 100, -1, 7);
    TH3F* h3 = new TH3F("hist3", "3D-Hist", 100, -1, 1, 100, -1, 1, 100, -1, 1);

    TH1F* h1_x = new TH1F("X", "X", 100, -1.1, 1.1);
    TH1F* h1_y = new TH1F("Y", "Y", 100, -1.1, 1.1);
    TH1F* h1_z = new TH1F("Z", "Z", 100, -1.1, 1.1);
    
    for (int i = 0; i < num_of_entries; i++) // num_of_entries
    {
        int eventID = i;
        
        int flag = 0;
        double r = 0.0, cos_phi = 0.0, sin_phi = 0.0, cos_theta = 0.0, theta = 0.0, phi = 0.0;
        float total_e = 0.;
        eventTree->GetEntry(eventID);
        TVector3 priDirection = g4Event->GetPrimaryEventDirection(0);
        // cout << "priDirection : " <<priDirection[0] << ", " << priDirection[1] << ", " << priDirection[2] << endl;
        float x = priDirection[0];
        float y = priDirection[1];
        float z = priDirection[2];
        h3->Fill(x,y,z);
        r = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
        cos_theta = z/r ; 
        theta = acos(cos_theta);
        hist1d_theta->Fill(theta);
        phi = acos(x/(1-pow(cos_theta,2)));
        if(y>0)
        {
            hist1d_phi->Fill(phi);
        }
        else if(y<0)
        {
            hist1d_phi->Fill(2*M_PI-phi);
        }
        else if(y==0 and x>0)
        {
            hist1d_phi->Fill(0);
        }
        else if(y==0 and x<0)
        {
            hist1d_phi->Fill(M_PI);
        }

        h1_x->Fill(priDirection[0]);
        h1_y->Fill(priDirection[1]);
        h1_z->Fill(priDirection[2]);
        
    }
    TCanvas* c1 = new TCanvas("c1", " ", 800, 600);
    h3->SetMarkerStyle(20);
    h3->SetMarkerColor(kBlue);
    h3->SetMarkerSize(0.5);

    h3->SetTitle("Cos_Theta2");
    h3->GetXaxis()->SetTitle("X/mm");
    h3->GetYaxis()->SetTitle("Y/mm");
    h3->GetZaxis()->SetTitle("Z/mm");
    h3->Draw("P");
    c1->Update();
    c1->Print("/lustre/pandax/wangyun/restG4-Angle-Distribution/cos_theta/Cos_Theta2_10W.png");

    TCanvas* c2 = new TCanvas("c2", " ", 800, 600);
    hist1d_theta->SetStats(0);
    hist1d_theta->GetXaxis()->SetTitle("theta");
    hist1d_theta->GetYaxis()->SetTitle("N");
    hist1d_theta->SetTitle("Cos_Theta2-theta");
    hist1d_theta->Draw();
    c2->Print("/lustre/pandax/wangyun/restG4-Angle-Distribution/cos_theta/Cos_Theta2_10W-theta.png");

    hist1d_phi->SetStats(0);
    hist1d_phi->GetXaxis()->SetTitle("phi");
    hist1d_phi->GetYaxis()->SetTitle("N");
    hist1d_phi->SetTitle("Cos_Theta2-phi");
    hist1d_phi->Draw();
    c2->Print("/lustre/pandax/wangyun/restG4-Angle-Distribution/cos_theta/Cos_Theta2_10W-phi.png");

    h1_x->SetStats(0);
    h1_x->SetTitle("Cos_Theta2-X");
    h1_x->Draw();
    c2->Print("/lustre/pandax/wangyun/restG4-Angle-Distribution/cos_theta/Cos_Theta2_10W_X.png");

    h1_y->SetStats(0);
    h1_y->SetTitle("Cos_Theta2-Y");
    h1_y->Draw();
    c2->Print("/lustre/pandax/wangyun/restG4-Angle-Distribution/cos_theta/Cos_Theta2_10W_Y.png");

    h1_z->SetStats(0);
    h1_z->SetTitle("Cos_Theta2-Z");
    h1_z->Draw();
    c2->Print("/lustre/pandax/wangyun/restG4-Angle-Distribution/cos_theta/Cos_Theta2_10W_Z.png");

    return 0;
}