#include <cmath>
#include <iostream>
#include <numeric>

#include "gtest/gtest.h"
#include "test_utils.h"
#include "test_fixtures.h"

#include "../include/distopia.h"
#include "../lib/calc_bonds.h"
#include "../compare/calc_distances.h"
#include "../compare/vanilla.h"

// constants
#define BOXSIZE 10
#define NRESULTS 10000
#define NINDICIES 1000

using FloatOnly = ::testing::Types<float>;

TYPED_TEST_SUITE(Coordinates, FloatOnly);

// coordinates in this test can overhang the edge of the box by 2 * the box
// size.
TYPED_TEST(Coordinates, CalcBondsMatchesMDA) {
  this->InitCoords(NRESULTS, NINDICIES, BOXSIZE, 3 * BOXSIZE);

  _calc_bond_distance_ortho((coordinate *)this->coords0,
                            (coordinate *)this->coords1, this->nresults,
                            this->box, this->ref);
  CalcBondsOrtho(this->coords0, this->coords1, this->box, this->nresults,
                 this->results);

  for (std::size_t i = 0; i < this->nresults; i++) {
    EXPECT_NEAR(this->results[i], this->ref[i], 0.00001);
    // loss of accuracy somewhere?
  }
}

TYPED_TEST(Coordinates, CalcBondsNoBoxMatchesMDA) {
  this->InitCoords(NRESULTS, NINDICIES, BOXSIZE, 3 * BOXSIZE);

  _calc_bond_distance((coordinate *)this->coords0, (coordinate *)this->coords1,
                      this->nresults, this->ref);
  CalcBondsNoBox(this->coords0, this->coords1, this->nresults, this->results);

  for (std::size_t i = 0; i < this->nresults; i++) {
    EXPECT_NEAR(this->results[i], this->ref[i], 0.00001);
    // loss of accuracy somewhere?
  }
}

TYPED_TEST(Coordinates, VanillaCalcBondsMatchesMDA) {
  this->InitCoords(NRESULTS, NINDICIES, BOXSIZE, 3 * BOXSIZE);

  _calc_bond_distance_ortho((coordinate *)this->coords0,
                            (coordinate *)this->coords1, this->nresults,
                            this->box, this->ref);
  VanillaCalcBonds(this->coords0, this->coords1, this->box, this->nresults,
                   this->results);

  for (std::size_t i = 0; i < this->nresults; i++) {
    EXPECT_NEAR(this->results[i], this->ref[i], 0.00001);
    // loss of accuracy somewhere?
  }
}

TYPED_TEST(Coordinates, VanillaCalcBondsNoBoxMatchesMDA) {
  this->InitCoords(NRESULTS, NINDICIES, BOXSIZE, 3 * BOXSIZE);

  _calc_bond_distance((coordinate *)this->coords0, (coordinate *)this->coords1,
                      this->nresults, this->ref);
  VanillaCalcBondsNoBox(this->coords0, this->coords1, this->nresults,
                        this->results);

  for (std::size_t i = 0; i < this->nresults; i++) {
    EXPECT_NEAR(this->results[i], this->ref[i], 0.00001);
    // loss of accuracy somewhere?
  }
}
