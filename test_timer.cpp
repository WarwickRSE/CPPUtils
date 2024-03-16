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

double func2(){
  std::cout<<"nothing"<<std::endl;
  return 0.0;
}
double func2(int a, float b){
  return func(a, b);
}

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


// Options for overloaded versions

  // Specify the signature
  auto tff2 = timed_func<double(*)(int, float)>(func2);
  tff2(1, 2.0);
  tff2.print_time();
  // Ditto but via return type then param types
  auto tff3 = add_timer_overloaded<double, int, float>(func2);
  tff3(1, 2.0);
  tff3.print_time();

  return 0;


}

