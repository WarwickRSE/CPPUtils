#include <iostream>

#include "rng_engine.hpp"
#include "timer_decorator.hpp"

void func(int a, float b){

  dbl_uniform_rng rng(0, 1);
  double num;
  for(int i = 0; i < 10000000; i++){
    num += rng.next();
  }
  std::cout << num << std::endl;

};

int main(){

  func(1, 2.0);
  auto tt = time_and_run(func, 1, 2.0);
  tt.print_current_time();

  return 0;


}

