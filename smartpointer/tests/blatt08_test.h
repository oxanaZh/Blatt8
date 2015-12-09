#include <cppunit/extensions/HelperMacros.h>
#include "../src/SmartPointer.h"
#include "../src/RefCounter.h"

/**
 * Die Testsuite.
 */
class Blatt08_Testsuite: public CPPUNIT_NS::TestFixture {

CPPUNIT_TEST_SUITE (Blatt08_Testsuite);

    CPPUNIT_TEST(testIfNullPointerExists);

    CPPUNIT_TEST(testIfRefCounterExists);
    CPPUNIT_TEST(testGetRefCount);
    CPPUNIT_TEST(testRefCounterInc);
    CPPUNIT_TEST(testRefCounterDec);
    CPPUNIT_TEST(testRefCounterZero);

    CPPUNIT_TEST(testIfClassExists);
    CPPUNIT_TEST(testConstructorParameterless);
    CPPUNIT_TEST(testConstructorNullPtr);
    CPPUNIT_TEST(testConstructorNullPtr2);
    CPPUNIT_TEST(testCopyConstructorPtr);
    CPPUNIT_TEST(testCopyConstructorRef);
    CPPUNIT_TEST(testCopyConstructorRef2);
    CPPUNIT_TEST(testCallDestructorEmpty);
    CPPUNIT_TEST(testCallDestructorCountOne);
    CPPUNIT_TEST(testCallDestructorCountThree);
    CPPUNIT_TEST(testArrowOperatorNull);
    CPPUNIT_TEST(testArrowOperator);
    CPPUNIT_TEST(testDereferenceOperatorNull);
    CPPUNIT_TEST(testDereferenceOperator);
    CPPUNIT_TEST(testGetObjectNull);
    CPPUNIT_TEST(testGetObject);
    CPPUNIT_TEST(testGetRefCounterNull);
    CPPUNIT_TEST(testGetRefCounter);
    CPPUNIT_TEST(testAssignmentPtrNullNullptr);
    CPPUNIT_TEST(testAssignmentPtrNullptr);
    CPPUNIT_TEST(testAssignmentPtrNull);
    CPPUNIT_TEST(testAssignmentPtr);
    CPPUNIT_TEST(testAssignmentPtrSelfassignment);
    CPPUNIT_TEST(testAssignmentPtrComplex);
    CPPUNIT_TEST(testAssignmentRefSelfassignmentComplex);
    CPPUNIT_TEST(testAssignmentRefNullNullptr);
    CPPUNIT_TEST(testAssignmentRefNullNullptr2);
    CPPUNIT_TEST(testAssignmentRefNullptr);
    CPPUNIT_TEST(testAssignmentRefNull);
    CPPUNIT_TEST(testAssignmentRef);
    CPPUNIT_TEST(testAssignmentRefSelfassignment);
    CPPUNIT_TEST(testAssignmentRefComplex);
    CPPUNIT_TEST(testAssignmentRefSelfassignmentComplex);
    CPPUNIT_TEST(testAssignmentRefSelfassignmentComplex2);
    CPPUNIT_TEST(testCompareNullNull);
    CPPUNIT_TEST(testCompareNullObject);
    CPPUNIT_TEST(testCompareObjectNull);
    CPPUNIT_TEST(testCompareUnequalObjects);
    CPPUNIT_TEST(testCompareEqualObjects);
    CPPUNIT_TEST(testNotCompareNullNull);
    CPPUNIT_TEST(testNotCompareNullObject);
    CPPUNIT_TEST(testNotCompareObjectNull);
    CPPUNIT_TEST(testNotCompareUnequalObjects);
    CPPUNIT_TEST(testNotCompareEqualObjects);
    CPPUNIT_TEST(testBoolEmptySmartptr);
    CPPUNIT_TEST(testBoolNotEmptySmartptr);

    CPPUNIT_TEST(testPolymorphism);
    CPPUNIT_TEST(testSPAsParameterPerReference);

    CPPUNIT_TEST_SUITE_END ()
    ;

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testIfNullPointerExists(void);

    void testIfRefCounterExists(void);
    void testGetRefCount(void);
    void testRefCounterInc(void);
    void testRefCounterDec(void);
    void testRefCounterZero(void);

    void testIfClassExists(void);
    void testConstructorParameterless(void);
    void testConstructorNullPtr(void);
    void testConstructorNullPtr2(void);
    void testCopyConstructorPtr(void);
    void testCopyConstructorRef(void);
    void testCopyConstructorRef2(void);
    void testCallDestructorEmpty(void);
    void testCallDestructorCountOne(void);
    void testCallDestructorCountThree(void);
    void testArrowOperatorNull(void);
    void testArrowOperator(void);
    void testDereferenceOperatorNull(void);
    void testDereferenceOperator(void);
    void testGetObjectNull(void);
    void testGetObject(void);
    void testGetRefCounterNull(void);
    void testGetRefCounter(void);
    void testAssignmentPtrNullNullptr(void);
    void testAssignmentPtrNullptr(void);
    void testAssignmentPtrNull(void);
    void testAssignmentPtr(void);
    void testAssignmentPtrSelfassignment(void);
    void testAssignmentPtrComplex(void);
    void testAssignmentPtrSelfassignmentComplex(void);
    void testAssignmentRefNullNullptr(void);
    void testAssignmentRefNullNullptr2(void);
    void testAssignmentRefNullptr(void);
    void testAssignmentRefNull(void);
    void testAssignmentRef(void);
    void testAssignmentRefSelfassignment(void);
    void testAssignmentRefComplex(void);
    void testAssignmentRefSelfassignmentComplex(void);
    void testAssignmentRefSelfassignmentComplex2(void);
    void testCompareNullNull(void);
    void testCompareNullObject(void);
    void testCompareObjectNull(void);
    void testCompareUnequalObjects(void);
    void testCompareEqualObjects(void);
    void testNotCompareNullNull(void);
    void testNotCompareNullObject(void);
    void testNotCompareObjectNull(void);
    void testNotCompareUnequalObjects(void);
    void testNotCompareEqualObjects(void);
    void testBoolEmptySmartptr(void);
    void testBoolNotEmptySmartptr(void);

    void testPolymorphism(void);
    void testSPAsParameterPerReference(void);
};
