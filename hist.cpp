{
  // Create a Histogram
  TH1F * h_random = new TH1F
    (
     "h_random", // name
     "Randomly Sampled Gaussian Distribution", // title
     120, // number of bins (integer)
     -3., // minimum (float)
     3. // maximum (float)
     );

  // Change Histogram Attributes
  h_random->SetLineColor(kAzure);
  h_random->SetLineWidth(2);
  h_random->GetXaxis()->SetTitle("Random Number");
  h_random->GetYaxis()->SetTitle("Number of Entries");

  // Fill
  for(int i=0; i<1000; ++i)
    {
      double x = gRandom->Gaus(0,1);
      h_random->Fill(x);
    }

  //Check Number of Entries
  h_random->GetEntries();

  // Draw
  TCanvas * c_random = new TCanvas
    (
     "c_random", // name
     "Random Gaussian", // title (used on pop-up window)
     1 // default size
     );
  c_random->cd(); // point ROOT's attention to the canvas
  c_random->SetGrid(); // make x, y grid

  // Paint histogram on canvas
  h_random->Draw();
}
