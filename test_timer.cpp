#include <iostream>

#include "rng_engine.hpp"
#include "timer_decorator.hpp"

double func(int a, float b){

  dbl_uniform_rng rng(0, 1);
  double num=0.0;
  for(int i = 0; i < 10000000; i++){
    num += rng.next();
  }
  std::cout << num << std::endl;
  return num;

};

int main(){

  func(1, 2.0);
  auto tt = time_and_run(func, 1, 2.0);
  tt.print_current_time();

  auto tf = timed_func<decltype(&func)>(func);
  tf(1, 2.0);
  tf.print_time();

  auto tf2 = add_timer(func);
  tf2(1, 2.0);
  tf2.print_time();

  return 0;


}

