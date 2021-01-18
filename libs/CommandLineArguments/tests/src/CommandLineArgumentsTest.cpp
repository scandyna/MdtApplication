/****************************************************************************
 **
 ** Copyright (C) 2019-2020 Philippe Steinmann.
 **
 ** This file is part of MdtApplication library.
 **
 ** MdtApplication is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** MdtApplication is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with MdtApplication. If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#include "Mdt/CommandLineArguments.h"
#include "catch2/catch.hpp"
#include <string>

using namespace Mdt;


bool stringsAreEqual(const char *a, const char *b)
{
  return std::string(a) == std::string(b);
}

TEST_CASE("Construct_argc_argv")
{
  SECTION("appname")
  {
    const char *argv[1] = {"appname"};
    CommandLineArguments args(1, const_cast<char**>(argv));
    REQUIRE( args.argumentCount() == 1 );
    REQUIRE( !args.isNull() );
    REQUIRE( !args.isCopy() );
    REQUIRE( stringsAreEqual(args.argumentVector()[0], "appname") );
  }

  SECTION("appname,0")
  {
    const char *argv[2] = {"appname",0};
    CommandLineArguments args(1, const_cast<char**>(argv));
    REQUIRE( args.argumentCount() == 1 );
    REQUIRE( stringsAreEqual(args.argumentVector()[0], "appname") );
    REQUIRE( args.argumentVector()[1] == 0 );
  }

  SECTION("appname,arg1,0")
  {
    const char *argv[3] = {"appname","arg1",0};
    CommandLineArguments args(2, const_cast<char**>(argv));
    REQUIRE( args.argumentCount() == 2 );
    REQUIRE( stringsAreEqual(args.argumentVector()[0], "appname") );
    REQUIRE( stringsAreEqual(args.argumentVector()[1], "arg1") );
    REQUIRE( args.argumentVector()[2] == 0 );
  }
}

TEST_CASE("Construct_initList")
{
  SECTION("appname")
  {
    CommandLineArguments args({"appname"});
    REQUIRE( args.argumentCount() == 1 );
    REQUIRE( !args.isNull() );
    REQUIRE( args.isCopy() );
    REQUIRE( stringsAreEqual(args.argumentVector()[0], "appname") );
    REQUIRE( args.argumentVector()[1] == 0 );
  }

  SECTION("appname,arg1")
  {
    CommandLineArguments args({"appname","arg1"});
    REQUIRE( args.argumentCount() == 2 );
    REQUIRE( stringsAreEqual(args.argumentVector()[0], "appname") );
    REQUIRE( stringsAreEqual(args.argumentVector()[1], "arg1") );
    REQUIRE( args.argumentVector()[2] == 0 );
  }
}

TEST_CASE("CopyConstruct")
{
  SECTION("(argc,argv):appname,arg1")
  {
    const char *argv[3] = {"appname","arg1",0};
    CommandLineArguments args1(2, const_cast<char**>(argv));
    CommandLineArguments args2(args1);
    REQUIRE( args2.argumentCount() == 2 );
    REQUIRE( args2.argumentVector() != args1.argumentVector() );
    REQUIRE( stringsAreEqual(args2.argumentVector()[0], "appname") );
    REQUIRE( stringsAreEqual(args2.argumentVector()[1], "arg1") );
    REQUIRE( args2.argumentVector()[2] == 0 );
  }

  SECTION("(initList):appname,arg1")
  {
    CommandLineArguments args1({"appname","arg1"});
    CommandLineArguments args2(args1);
    REQUIRE( args2.argumentCount() == 2 );
    REQUIRE( args2.argumentVector() != args1.argumentVector() );
    REQUIRE( stringsAreEqual(args2.argumentVector()[0], "appname") );
    REQUIRE( stringsAreEqual(args2.argumentVector()[1], "arg1") );
    REQUIRE( args2.argumentVector()[2] == 0 );
  }

}

TEST_CASE("CopyAssign")
{
  SECTION("(argc,argv):appname,arg1")
  {
    const char *argv[3] = {"appname","arg1",0};
    CommandLineArguments args1(2, const_cast<char**>(argv));
    REQUIRE( args1.argumentCount() == 2 );

    CommandLineArguments args2;
    REQUIRE( args2.argumentCount() == 0 );

    args2 = args1;
    REQUIRE( args2.argumentCount() == 2 );
    REQUIRE( args2.argumentVector() != args1.argumentVector() );
    REQUIRE( stringsAreEqual(args2.argumentVector()[0], "appname") );
    REQUIRE( stringsAreEqual(args2.argumentVector()[1], "arg1") );
    REQUIRE( args2.argumentVector()[2] == 0 );
  }

  SECTION("(initList):appname,arg1")
  {
    CommandLineArguments args1({"appname","arg1"});
    REQUIRE( args1.argumentCount() == 2 );

    CommandLineArguments args2;
    REQUIRE( args2.argumentCount() == 0 );

    args2 = args1;
    REQUIRE( args2.argumentCount() == 2 );
    REQUIRE( args2.argumentVector() != args1.argumentVector() );
    REQUIRE( stringsAreEqual(args2.argumentVector()[0], "appname") );
    REQUIRE( stringsAreEqual(args2.argumentVector()[1], "arg1") );
    REQUIRE( args2.argumentVector()[2] == 0 );
  }

  SECTION("assign to itself")
  {
    CommandLineArguments args1({"appname","arg1"});
    REQUIRE( args1.argumentCount() == 2 );

    args1 = args1;
    REQUIRE( args1.argumentCount() == 2 );
    REQUIRE( stringsAreEqual(args1.argumentVector()[0], "appname") );
    REQUIRE( stringsAreEqual(args1.argumentVector()[1], "arg1") );
    REQUIRE( args1.argumentVector()[2] == 0 );
  }
}
