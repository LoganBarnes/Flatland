// Relativity.cpp
#include "shared/core/ContinuousDriver.hpp"
#include "world/RelativityWorld.hpp"
#include "io/RelativityIOHandler.hpp"
#include "RelativityConfig.hpp"

#include <iostream>
#include <memory>


/////////////////////////////////////////////
/// \brief main
/// \return
///
/// \author Logan Barnes
/////////////////////////////////////////////
int
main(
     const int    argc, ///< number of arguments
     const char **argv  ///< array of argument strings
     )
{
  shs::Driver::printProjectInfo(
                                rel::PROJECT_NAME,
                                rel::VERSION_MAJOR,
                                rel::VERSION_MINOR,
                                rel::VERSION_PATCH
                                );

  try
  {
    //
    // create world to handle physical updates
    // and ioHandler to interface between the
    // world and the user
    //
    rel::RelativityWorld world;
    rel::RelativityIOHandler io( world );

    //
    // pass world and ioHandler to driver
    // to manage event loop
    //
    shs::ContinuousDriver driver( world, io );

    //
    // run program
    //
    return driver.exec( argc - 1, &argv[ 1 ] );
  }
  catch ( const std::exception &e )
  {
    std::cerr << "ERROR: program failed: " << e.what( ) << std::endl;
  }

  // should only reach this point after an exception
  return EXIT_FAILURE;

} // main
