// HeadlessRenderUnitTests.cpp
#include "shared/core/ContinuousDriver.hpp"
#include "world/FlatlandWorld.hpp"
#include "io/FlatlandIOHandler.hpp"

#include "gmock/gmock.h"


namespace
{

constexpr double epsilon = 1.0e-8;
constexpr float epsilonf = 1.0e-8f;


///
/// \brief The HeadlessRenderUnitTests class
///
class HeadlessRenderUnitTests : public ::testing::Test
{

protected:

  /////////////////////////////////////////////////////////////////
  /// \brief HeadlessRenderUnitTests
  /////////////////////////////////////////////////////////////////
  HeadlessRenderUnitTests( )
  {}


  /////////////////////////////////////////////////////////////////
  /// \brief ~HeadlessRenderUnitTests
  /////////////////////////////////////////////////////////////////
  virtual
  ~HeadlessRenderUnitTests( )
  {}

};


MATCHER_P( FloatNearPointwise, eps, "Out of range" )
{
  return std::abs( std::get< 0 >( arg ) - std::get< 1 >( arg ) ) < eps;
}


/////////////////////////////////////////////////////////////////
/// \brief TestNothing
/////////////////////////////////////////////////////////////////
TEST_F( HeadlessRenderUnitTests, TestNothing )
{
  //
  // create world to handle physical updates
  // and ioHandler to interface between the
  // world and the user
  //
  rel::FlatlandWorld world;
  rel::FlatlandIOHandler io( world );

  //
  // pass world and ioHandler to driver
  // to manage event loop
  //
  shs::ContinuousDriver driver( world, io );
}



} // namespace
