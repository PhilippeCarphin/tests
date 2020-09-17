import XCTest

import hello_worldTests

var tests = [XCTestCaseEntry]()
tests += hello_worldTests.allTests()
XCTMain(tests)
