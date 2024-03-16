#ifndef rng_h
#define rng_h

#include <random>
#include "helper.hpp"

template <typename t_dist, typename t_val>
class ranged_random_engine{

  private:
    t_val range_min, range_max; /**< Range for generated values */
    std::mt19937 generator; /**< Random number generator (Mersenne Twister) */
    t_dist dist;/**< Random distribution */
    long seed_used;

  public:
    void init_gen(t_val min_range_in, t_val range_in, long seed){
      range_max = range_in;
      range_min = min_range_in;
      seed_used = seed;
      generator = std::mt19937(seed);
      dist = t_dist(range_min, range_max);
    }/**< Generic initialisation code */
    ranged_random_engine(t_val param1){
      std::random_device rd;
      init_gen(static_cast<t_val>(0), param1, rd());
    }/**< Constructor for rng with generator initialised with given param @param param1 For uniform - upper range; for Gaussian std-dev */
    ranged_random_engine(t_val param2, t_val param1){
      std::random_device rd;
      init_gen(param2, param1, rd());
    }/**< Constructor for rng with generator initialised with given param @param param1 For uniform - upper range; for Gaussian- std-dev  @param param2 For uniform - lower range, for Gaussian- mean*/
    ranged_random_engine(t_val param2, t_val param1, long seed){
      init_gen(param2,param1, seed);
    }/**< Constructor for rng with generator initialised with given param @param param1 For uniform - upper range; for Gaussian- std-dev  @param param2 For uniform - lower range, for Gaussian- mean @param seed Seed for generator */

    t_val get_next(){
      return dist(generator);// NOTE: all constructors initialise generator so no need to check
    }/**< Get next random value @return Next random value*/
    long get_seed(){return seed_used;}/**< Get seed used to initialise generator @return Seed used to initialise generator */

};

template <typename t_dist>
class rng{
  // Assuming t_dist is templated, extract the type it is templated on, 
  // hopefully a numeric one and typedef this as t_val
  typedef typename extract_value_type<t_dist>::value_type t_val;
  private:
    ranged_random_engine<t_dist,t_val> engine;

  public:
    rng() : engine(ranged_random_engine<t_dist,t_val>(1000)){}
    rng(t_val param1) : engine(ranged_random_engine<t_dist,t_val>(param1)){}
    rng(t_val param1, t_val param2) : engine(ranged_random_engine<t_dist,t_val>(param1,param2)){}
    rng(t_val param1, t_val param2, long seed) : engine(ranged_random_engine<t_dist,t_val>(param1,param2, seed)){}
 
    t_val next(){return engine.get_next();}
    long seed(){return engine.get_seed();}
};

using dbl_uniform_rng = rng<std::uniform_real_distribution<double>>;
using dbl_gauss_rng = rng<std::normal_distribution<double>>;

#endif
