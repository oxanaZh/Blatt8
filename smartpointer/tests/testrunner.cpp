#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>

/**
 * Hier wird der Testrunner erstellt, die registrierten Testsuites dem runner hinzugefuegt und schliesslich
 * mit der TextUi ausgefuehrt (Fliestextausgabe).
 */
int main(int argc, char* argv[]) {
    std::string testPath = (argc > 1) ? std::string(argv[1]) : "";

    // Create the event manager and test controller
    CppUnit::TestResult controller;

    // Add a listener that colllects test result
    CppUnit::TestResultCollector result;
    controller.addListener(&result);

    CppUnit::BriefTestProgressListener progressListener;
    controller.addListener(&progressListener);

    // Add the top suite to the test runner
    CppUnit::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    try {
        std::cout << "Running " << testPath;
        runner.run(controller, testPath);

        std::cerr << std::endl;

        // Print test in a compiler compatible format.
        CppUnit::CompilerOutputter outputter(&result, std::cerr);
        outputter.write();
    } catch (std::invalid_argument &e)  // Test path not resolved
    {
        std::cerr << std::endl << "ERROR: " << e.what() << std::endl;
        return 0;
    }

    return result.wasSuccessful() ? 0 : 1;
}
