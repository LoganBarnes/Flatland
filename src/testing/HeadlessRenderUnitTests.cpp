// HeadlessRenderUnitTests.cpp
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
{}



} // namespace
