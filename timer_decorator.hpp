#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <iostream>
#include <string>

/** A simple microsecond timer*/
class timer{

    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    std::string name="";
    bool is_running=false;

    void pretty_print_me(long duration){
      if(name != ""){std::cout << "Time taken by " << name << " is ";
      }else{std::cout << "Time taken is ";}
      std::cout << (float)duration/1.0e6 << " seconds\n";
    }
 
  public:
  
    void begin(std::string name = ""){
      this->name = name;
      is_running=true;
      start = std::chrono::high_resolution_clock::now();
    }
    void pause(){
      stop = std::chrono::high_resolution_clock::now();
      is_running=false;
    }
    void end(){
      stop = std::chrono::high_resolution_clock::now();
      is_running=false;
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      pretty_print_me(duration.count());
    }
   long get_current_time(){
      // If running, get current count, else get count when stopped. Count in microseconds
      std::chrono::time_point<std::chrono::high_resolution_clock> now;
      if(is_running){now = std::chrono::high_resolution_clock::now();
      }else{now = stop;}

      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
      return duration.count();
    }
    void print_current_time(){pretty_print_me(get_current_time());}
 
};

/** Takes a function and its args, and runs it within a timing call*/
template <typename func, typename... Args>
timer time_and_run(func f, Args... args){
  timer t;
  t.begin();
  f(args...);
  t.end();
  return t;
};

// Actual "decorator" class for functions returning NON VOID type
template <typename func>
class timed_func{
    timer t;
    func f;
    public:
    timed_func(func f_in):f(f_in){}
    using return_type = typename callableTraits<func>::type;
    template <typename... Args>
    return_type operator()(Args... args ){
      t.begin();
      if constexpr(std::is_same_v<return_type, void>){
        f(args...);
        t.end();
        return;
      }else{
        auto ret = f(args...);
        t.end();
        return ret;
      }
    }
    long get_time(){return t.get_current_time();}
    void print_time(){t.print_current_time();}

};

// Shortcut to do the decorating
template <typename func>
timed_func<func> add_timer(func f){
    return timed_func<func>(f);
}

template <typename ret, typename... Args>
auto add_timer_overloaded(ret(*f)(Args...)){
    return timed_func<ret(*)(Args...)>(f);
}


#endif