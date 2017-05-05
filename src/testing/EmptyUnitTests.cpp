// EmptyUnitTests.cpp
#include "shared/core/ContinuousDriver.hpp"
#include "world/FlatlandWorld.hpp"
#include "io/FlatlandIOHandler.hpp"

#include "gmock/gmock.h"


namespace
{

constexpr double epsilon = 1.0e-8;
constexpr float epsilonf = 1.0e-8f;


///
/// \brief The EmptyUnitTests class
///
class EmptyUnitTests : public ::testing::Test
{

protected:

  /////////////////////////////////////////////////////////////////
  /// \brief EmptyUnitTests
  /////////////////////////////////////////////////////////////////
  EmptyUnitTests( )
  {}


  /////////////////////////////////////////////////////////////////
  /// \brief ~EmptyUnitTests
  /////////////////////////////////////////////////////////////////
  virtual
  ~EmptyUnitTests( )
  {}

};


MATCHER_P( FloatNearPointwise, eps, "Out of range" )
{
  return std::abs( std::get< 0 >( arg ) - std::get< 1 >( arg ) ) < eps;
}


/////////////////////////////////////////////////////////////////
/// \brief TestNothing
/////////////////////////////////////////////////////////////////
TEST_F( EmptyUnitTests, TestNothing )
{}



} // namespace
