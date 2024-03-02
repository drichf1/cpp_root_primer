//This file is really -*- C++ -*-.
// compile: g++ -o mand mandel.cpp [ENTER]
// run: ./mand [ENTER]

// Import C++ Function Collections
#import <fstream> // file input/output
#import <iostream> // terminal input/output
#import <cmath> // abs (), sqrt()

// Variable for terminal output
short talk = 0; // no terminal output at all
// short talk = 1; // full terminal output incl. debugging
// short talk = 2; // start/end messages in terminal

// Utility Function: Mandelbrot per pixel
int is_in_mandelbrot_set
(
 double c_real,
 double c_imag,
 int max_iterations,
 double condition
 )
{
  // create a return value
  double n_iterations = 0.;
  // create number for checking (z)
  double z_real = 0.;
  double z_imag = 0.;
  double z_real_temp = 0.; // container for new Re() part, needed because old Re() part used for calculation of Im(); matter of taste whether to calculate Im() or Re() first, but temporary container needed

  for(int i=0;i<max_iterations;++i) {
    z_real_temp = z_real*z_real-z_imag*z_imag + c_real;
    z_imag = 2*z_real*z_imag + c_imag;
    z_real = z_real_temp;
    if(z_real*z_real+z_imag*z_imag>=condition*condition) {
      return i; // number of iterations
      } // closes if(z_real*z_real+z_imag*z_imag<=condition*condition) {
  }  // closes for(int i=0;i<max_iterations;++i) {
  return 0;
} // closes function definition

//
int main()
{
  // initialize
  const double xlo = -2.5;
  const double xhi = 0.5;
  const double x_step = 0.001;
  const double ylo = -1.5;
  const double yhi = 1.5;
  const double y_step = x_step;

  const int max_iterations = 1000;
  const double condition = 2.;

  const int color_depth = 255;
  const int color_red_multiplier = 1;
  const int color_green_multiplier = 10;
  const int color_blue_multiplier = 100;

  // open output file (PPM) & write header
  std::ofstream fout("mandelcpp.ppm");

  if(!fout) {std::cerr << "output file not open" << std::endl; return 1;}
  fout << "P3" << "\n"; // 3D color (RBG: [0,depth-1])
  fout << (abs(xlo)+abs(xhi))/x_step+1 << " " // x_height
       << (abs(ylo)+abs(yhi))/y_step << " " << "\n"; // y_height
  fout << color_depth << "\n"; // color depth (zeroed)

  // open data file (.dat) & write ROOT TTree header
  std::ofstream dout("mandelcpp.dat");
  if(!dout) {std::cerr << "output file not open" << std::endl; return 2;}
  dout << "x/D:y/D:iter/D" << "\n";

  if(talk==2){std::cout << "starting loop!" << "\n";}
  // Loop over each pixel and calculate the Mandelbrot algorithm
  int n_iterations_this_step = 0; // pointer to hold our result
  for (double j = ylo; j < yhi; j+=y_step){ // loop over rows
    for (double i = xlo; i < xhi; i+=x_step) { // loop over columns
      n_iterations_this_step = is_in_mandelbrot_set
	(
	 i, j,
	 max_iterations,
	 condition
	 );

      // Write out each pixel's Red-Green-Blue color sextet, modulo color depth
      // different color-type multipliers yield prettier images
      fout << color_red_multiplier*n_iterations_this_step % color_depth
	   << " " << color_green_multiplier*n_iterations_this_step % color_depth
	   << " " << color_blue_multiplier*n_iterations_this_step % color_depth
	   << "\n";

      // Write out X, Y, N_Iter to data file
      dout << i << " " << j << " " << n_iterations_this_step << "\n";

      // Verbose message to terminal for debugging purposes.
      if (talk==1) {
	std::cout << "(" << i
		  << "," << j << "): "
		  << n_iterations_this_step
		  << " " << (color_red_multiplier*n_iterations_this_step) % color_depth
		  << " " << (color_green_multiplier*n_iterations_this_step) % color_depth
		  << " " << (color_blue_multiplier*n_iterations_this_step) % color_depth
		  << "\n";}

    } // closes for (int i = 0; i < image_width; ++i) { // loop over columns
  } // closes for (int j = 0; j < image_height; ++j){ // loop over rows
  if(talk==2) {std::cout << "done!" << std::endl;}
  fout.close();
  dout.close();
  return 0;
}
