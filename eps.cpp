//This file is really -*- C++ -*-.
#include <iostream>
#include <iomanip> // setw
#include <limits> // setprecision(int)

void machine_epsilon_int(int value){
  int prev_epsilon; // container for our answer
  // repeatedly divide by 2:
  while ((1+value) != 1){
    prev_epsilon = value; // copy value into prior assessment
    value /= 2;
    }
  std::cout << "Machine epsilon (int) = " << prev_epsilon << "\n";
  }
void machine_epsilon_float(float value){
  float prev_epsilon; // container for our answer
  // repeatedly divide by 2:
  while ((1+value) != 1){
    prev_epsilon = value; // copy value into prior assessment
    value /= 2;
    }
  std::cout << "Machine epsilon (float) = " << prev_epsilon << "\n";
  }
  void machine_epsilon_double(double value){
  double prev_epsilon; // container for our answer
  // repeatedly divide by 2:
  while ((1+value) != 1){
    prev_epsilon = value; // copy value into prior assessment
    value /= 2;
    }
  std::cout << "Machine epsilon (double) = " << prev_epsilon <<"\n";
  }
    void machine_epsilon_long_double(long double value){
  long double prev_epsilon; // container for our answer
  // repeatedly divide by 2:
  while ((1+value) != 1){
    prev_epsilon = value; // copy value into prior assessment
    value /= 2;
    }
  std::cout << "Machine epsilon (long double) = " << prev_epsilon <<"\n";
  }

void sol()
  {
    int ci = 299792458; // m/s
    float cf = 299792458.; // m/s
    double cd = 299792458.; // m/s
    long double cld = 299792458.; // m/s

    ci= (ci * 100 * 1e-9) / (2.54 * 12); // 100 cm/m 1/2.54 in/cm 1e9 ns/s
    cf = (cf * 100 * 1e-9) / (2.54 * 12); // 100 cm/m 1/2.54 in/cm 1e9 ns/s
    cd = (cd * 100 * 1e-9) / (2.54 * 12); // 100 cm/m 1/2.54 in/cm 1e9 ns/s
    cld = (cld * 100 * 1e-9) / (2.54 * 12); // 100 cm/m 1/2.54 in/cm 1e9 ns/s

    std::cout << "SOL: 299,792,458 m/s" << "\n"
	      << "int: " << std::setprecision(64) << ci << " ft/ns" << "\n"
	      << "flt: " << cf << " ft/ns" << "\n"
	      << "dbl: " << cd << " ft/ns" << "\n"
	      << "ldl: " << cld << " ft/ns" << "\n";
      }
int main() {
  machine_epsilon_int(4);
  machine_epsilon_float(0.5);
  machine_epsilon_double(0.5);
  machine_epsilon_long_double(0.5);
  sol();
  return 0;
  }
