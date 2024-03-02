//#import <string>
// #import "TFile.h"
#import "TTree.h"
#import "TH1.h"

int mandelroot
(
 // no arguments: you'd need to supply these at the command line
   )
{

  // Make a TTree
  TTree * t = new TTree
    (
     "t", // name
     "TTree of Mandelbrot Set Calculation" // title
     );
  t->ReadFile("mandelcpp.dat"); // populate TTree

  // Make some histograms
  // Setup
  int pixels_per_bin = 10;

  int x_pixels = 3000;
  int x_bins = x_pixels/pixels_per_bin;
  double x_lo = -2.5;
  double x_hi = 0.5;

  int y_pixels = 3000;
  int y_bins = y_pixels/pixels_per_bin;
  double y_lo = -1.5;
  double y_hi = 1.5;

  int iter_bins = 1000; // 1 iteration per bin
  double iter_lo = 0;
  double iter_hi = 1000;

  // 1D
  TH1D * h_iter = new TH1D
    (
     "h_iter", // name
     "Distribution of N_iterations", // title
     iter_bins, iter_lo, iter_hi // binning
     );
  // 2D
  TH2D * h_x_iter = new TH2D
    (
     "h_x_iter", // name
     "N_{Iter} vs. x;x;N_{Iter}", // title
     x_bins, x_lo, x_hi, // x binning
     iter_bins, iter_lo, iter_hi // n_iter binning
     );
  TH2D * h_y_iter = new TH2D
    (
     "h_y_iter", // name
     "N_{Iter} vs. y;y;N_{Iter}", // title
	 y_bins, y_lo, y_hi, // y binning
	 iter_bins, iter_lo, iter_hi // n_iter binning
	 );
  // 3D
  TH3D * h_tree = new TH3D
    (
     "h_tree", // name
     "h_tree", // title
     x_bins, x_lo, x_hi, // x binning
     y_bins, y_lo, y_hi, // y binning
     iter_bins, iter_lo, iter_hi // iter binning
     );

  // Fill histograms from Tree
  t->Draw("iter>>h_iter","","goff"); // histogram without graphics
  t->Draw("x:iter>>h_x_iter","","goff"); // histogram w/o graphics
  t->Draw("y:iter>>h_y_iter","","goff"); // histogram w/o graphics
  t->Draw("x:y:iter>>h_tree","","goff"); // histogram w/o graphics

  // Histogram Arithmetic to Create "invariant"
  TH1D * h_iter_invar = (TH1D*)h_iter->Clone("h_iter_invar");
  h_iter_invar->Sumw2();
  h_iter_invar->Scale(1./h_iter_invar->GetBinWidth(1));
  h_iter_invar->Scale(1./2*3.14159265358979);
  h_iter_invar->Scale(1./(x_pixels*y_pixels));
  for(int i = 1; i<=h_iter_invar->GetNbinsX(); ++i) {
    h_iter_invar->SetBinContent
      (
       i,
       h_iter_invar->GetBinContent(i)/h_iter_invar->GetXaxis()->GetBinCenter(i)
       );
  } // closes for(int i = 1; i<=h_iter_invar->GetNbinsX(); ++i) {
  h_iter_invar->GetYaxis()->SetTitle("#frac{1}{2#pi} #times #frac{1}{N_{pixels}} #times #frac{1}{N_{iterations}} #times #frac{dN}{dN_{iterations}}");
  h_iter_invar->GetXaxis()->SetTitle("N_{iterations}");
  h_iter_invar->Rebin(10); // 10 iterations per bin: now up to 100
  h_iter_invar->SetLineColor(kAzure-4);
  h_iter_invar->SetMarkerColor(kAzure-4);
  h_iter_invar->SetMarkerStyle(kFullCircle);

  // Fit Histograms
  TF1 * fit_pow = new TF1
    (
     "fit_pow", // name
     "[0]*x^(-[1])", // relation
     0.01,1000. // range
     );
  fit_pow->SetParName(0,"Coefficient");
  fit_pow->SetParName(1,"Exponent (Neg.)");
  fit_pow->SetLineColor(kPink-4);
  fit_pow->SetLineWidth(2);

  TFitResultPtr frp_iter_invar_pow =  h_iter_invar->Fit
    (
     fit_pow, // fit function
     "SR0+", // fit options 
     "goff", // graphics options
     10., 990. // fit limits
     );

     gStyle->SetOptFit(1111);

     // Ratio
     TH1D * h_ratio = (TH1D*)h_iter_invar->Clone("h_ratio");
     h_ratio->Divide(fit_pow);
     h_ratio->GetXaxis()->SetTitle("N_{Iterations}");
     h_ratio->GetYaxis()->SetTitle("Ratio #left(#frac{data}{fit}#right)");
     h_ratio->SetStats(0);

     // Plotting

     TH1F * h_frame = new TH1F("hframe","",1000,0.,1000.); // frame
     h_frame->GetXaxis()->SetRangeUser(1.,1000.);
     h_frame->GetYaxis()->SetRangeUser(1.E-9,1.E1);
     h_frame->GetXaxis()->SetTitle(h_iter_invar->GetXaxis()->GetTitle());
     h_frame->GetYaxis()->SetTitle(h_iter_invar->GetYaxis()->GetTitle());
     h_frame->SetStats(0);
     TCanvas * c_iter_invar = new TCanvas
       (
	"c_iter_invar",
	"c_iter_invar",
	1
	);
     c_iter_invar->SetLogy();

     h_frame->Draw();
     h_iter_invar->Draw("same");
     fit_pow->Draw("same");

     TLine * l_one = new TLine(0.,1.,1000.,1.);
     l_one->SetLineStyle(kDashed);
     l_one->SetLineStyle(kGray);
     TH1F * h_frame_ratio = new TH1F("h_frame_ratio","",1000,0.,1000.); // frame
     h_frame_ratio->GetXaxis()->SetRangeUser(1.,1000.);
     h_frame_ratio->GetYaxis()->SetRangeUser(0.,9.);
     h_frame_ratio->GetXaxis()->SetTitle(h_ratio->GetXaxis()->GetTitle());
     h_frame_ratio->GetYaxis()->SetTitle(h_ratio->GetYaxis()->GetTitle());
     h_frame_ratio->SetStats(0);
     TCanvas * c_data_fit = new TCanvas
       (
	"c_data_fit",
	"c_data_fit",
	1
	);
     h_frame_ratio->Draw();
     h_ratio->Draw("same");
     l_one->Draw("same");

     //Save Graphs
     c_iter_invar->SaveAs("iter_invar_lin_log.pdf");
     c_iter_invar->SetLogx();
     c_iter_invar->SaveAs("iter_invar_log_log.pdf");
     c_data_fit->SaveAs("data_fit.pdf");

     // Return statement
      return 0;
    } // closes function definition (mandelroot)
