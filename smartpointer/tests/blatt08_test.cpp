#include <iostream>
#include <vector>
#include <string>

#include "blatt08_test.h"

/*  Bezueglich Valgrind: still reachable
 *
 *  Valgrind zeigt evtl. sog. reachable blocks in der Leak Summary an.
 *  Dies ist jedoch kein Fehler, sondern eher eine Warnung.
 *
 *  Das Verhalten der Compiler kann hierbei variieren.
 *  Die verschiedenen Librarys, die wir nutzen, haben zum Teil
 *  ihre eigene Speicherverwaltung und geben nicht unbedingt
 *  alle frei gewordenen Speicherbereiche sofort zurueck an das System,
 *  sondern behalten es sich vor um es evtl. spaeter erneut zu nutzen.
 *
 *  Der "Fehler" kann z.B. schon dadurch entstehen indem wir iostream includen.
 */

//Testsuite fuer den test-runner registrieren
CPPUNIT_TEST_SUITE_REGISTRATION(Blatt08_Testsuite);

void Blatt08_Testsuite::setUp(void) {
    //wird vor den Tests ausgefuehrt.
    //Z.B. fuer das erstellen von Objekten
}

void Blatt08_Testsuite::tearDown(void) {
    //wird nach den Tests ausgefuehrt.
    //Z.B. fuer das Loeschen von Objekten
}

static std::vector<void*> saveOldAdress(0);

/*
 * Hilfsklassen
 */
class A {
public:
    A() {
    }
    virtual int getNum() {
        return 42;
    }
    virtual ~A() {
        saveOldAdress.push_back(this);
    }
};

class B: public A {
public:
    B() {
    }
    virtual int getNum() {
        return 24;
    }
    virtual ~B() {
    }
};

template<typename T>
int func(const SmartPointer<T> &p) {
    return p->getNum();
}

// ==========================================================================

/*
 * Test ob eine Klasse NullPointerException existiert, die eine echte Exception
 * ist (d.h. letztlich von `exception` erbt).
 */
void Blatt08_Testsuite::testIfNullPointerExists() {
    NullPointerException np;
    std::string message { np.what() };

    CPPUNIT_ASSERT_MESSAGE(
            "Existiert eine Klasse NullPointerException, die eine echte Exception ist (d.h. letztlich von `exception` erbt)?",
            message.length() > 0);
}

// ==========================================================================

/*
 * Test ob eine Klasse RefCounter existiert.
 */
void Blatt08_Testsuite::testIfRefCounterExists() {
    RefCounter rc;

    CPPUNIT_ASSERT_MESSAGE("Existiert eine Klasse RefCounter?", true);
}

/*
 * Ist die getRefCount() Methode implementiert?
 */
void Blatt08_Testsuite::testGetRefCount() {
    RefCounter rc;

    CPPUNIT_ASSERT_MESSAGE("Ist die getRefCount() Methode implementiert?",
            rc.getRefCount() == 0);
}

/*
 * Funktioniert die Methode `RefCounter::inc()`?
 */
void Blatt08_Testsuite::testRefCounterInc() {
    RefCounter rc;

    rc.inc();
    CPPUNIT_ASSERT_MESSAGE("Funktioniert die Methode `RefCounter::inc()`?",
            rc.getRefCount() == 1);

    rc.inc();
    CPPUNIT_ASSERT_MESSAGE("Funktioniert die Methode `RefCounter::inc()`?",
            rc.getRefCount() == 2);

    rc.inc();
    CPPUNIT_ASSERT_MESSAGE("Funktioniert die Methode `RefCounter::inc()`?",
            rc.getRefCount() == 3);
}

/*
 * Funktioniert die Methode `RefCounter::dec()`?
 */
void Blatt08_Testsuite::testRefCounterDec() {
    RefCounter rc;

    rc.inc();
    rc.inc();
    rc.inc();

    rc.dec();
    CPPUNIT_ASSERT_MESSAGE("Funktioniert die Methode `RefCounter::dec()`?",
            rc.getRefCount() == 2);

    rc.dec();
    CPPUNIT_ASSERT_MESSAGE("Funktioniert die Methode `RefCounter::dec()`?",
            rc.getRefCount() == 1);

    rc.dec();
    CPPUNIT_ASSERT_MESSAGE("Funktioniert die Methode `RefCounter::dec()`?",
            rc.getRefCount() == 0);
}

/*
 * Funktioniert die Methode `RefCounter::isZero()`?
 */
void Blatt08_Testsuite::testRefCounterZero() {
    RefCounter rc;

    CPPUNIT_ASSERT_MESSAGE("Initial sollte `RefCounter::isZero()` wahr sein.",
            rc.isZero());

    rc.inc();
    CPPUNIT_ASSERT_MESSAGE(
            "Nach `RefCounter::inc()` sollte `RefCounter::isZero()` falsch sein.",
            !rc.isZero());

    rc.dec();
    CPPUNIT_ASSERT_MESSAGE(
            "Nach `RefCounter::inc()` und `RefCounter::dec()` sollte `RefCounter::isZero()` wieder wahr sein.",
            rc.isZero());
}

// ==========================================================================

/*
 * Test ob eine Klasse SmartPointer existiert, diese als Template angelegt
 * wurde und deren Konstruktor implementiert ist.
 */
void Blatt08_Testsuite::testIfClassExists() {
    SmartPointer<A> smart_A { new A };

    CPPUNIT_ASSERT_MESSAGE(
            "Existiert eine Klasse SmartPointer und ist diese als Template angelegt mit einem implementierten Konstruktor?",
            true);
}

/*
 * Test ob der Konstruktor richtig implementiert wurde.
 * Parameterloser Konstruktor
 */
void Blatt08_Testsuite::testConstructorParameterless() {
    SmartPointer<A> smart_A1;

    CPPUNIT_ASSERT_MESSAGE(
            "Kommt der Konstruktor auch mit ohne Parameter klar?",
            smart_A1.getObject() == nullptr);

    CPPUNIT_ASSERT_MESSAGE(
            "Kommt der Konstruktor auch mit ohne Parameter klar?",
            smart_A1.getRefCounter() == nullptr);
}

/*
 * Test ob der Konstruktor richtig implementiert wurde.
 * Konstruktor mit nullptr
 */
void Blatt08_Testsuite::testConstructorNullPtr() {
    SmartPointer<A> smart_A1 { nullptr };

    CPPUNIT_ASSERT_MESSAGE(
            "Kommt der Konstruktor auch mit einem nullptr als Parameter klar?",
            smart_A1.getObject() == nullptr);

    CPPUNIT_ASSERT_MESSAGE(
            "Kommt der Konstruktor auch mit einem nullptr als Parameter klar?",
            smart_A1.getRefCounter() == nullptr);
}

/*
 * Test ob der Konstruktor richtig implementiert wurde.
 * Konstruktor mit 0
 */
void Blatt08_Testsuite::testConstructorNullPtr2() {
    SmartPointer<A> smart_A1 { 0 };

    CPPUNIT_ASSERT_MESSAGE(
            "Kommt der Konstruktor auch mit einer 0 als Parameter klar?",
            smart_A1.getObject() == nullptr);

    CPPUNIT_ASSERT_MESSAGE(
            "Kommt der Konstruktor auch mit einer 0 als Parameter klar?",
            smart_A1.getRefCounter() == nullptr);
}

/*
 * Test ob der Copykonstruktor implementiert wurde.
 * Konstruktor mit "echtem" Objekt-Pointer
 */
void Blatt08_Testsuite::testCopyConstructorPtr() {
    A *a = new A; // kein delete noetig -- SmartPointer should do the trick :)
    SmartPointer<A> smart_A1 { a };

    CPPUNIT_ASSERT_MESSAGE("Ist der Copykonstruktor (Pointer) implementiert?",
            smart_A1.getObject() == a);

    CPPUNIT_ASSERT_MESSAGE("RefCount-Object sollte vorhanden sein",
            smart_A1.getRefCounter() != nullptr);

    CPPUNIT_ASSERT_MESSAGE("RefCount sollte jetzt 1 sein",
            smart_A1.getRefCounter()->getRefCount() == 1);
}

/*
 * Test ob der Copykonstruktor implementiert wurde.
 * Copy-Konstruktor mit Referenz auf "echten" Smartpointer (mit Objekt-Pointer)
 */
void Blatt08_Testsuite::testCopyConstructorRef() {
    A *a = new A; // kein delete noetig -- SmartPointer should do the trick :)
    SmartPointer<A> smart_A1 { a };
    SmartPointer<A> smart_A2 = smart_A1;

    CPPUNIT_ASSERT_MESSAGE("Ist der Copykonstruktor (Referenz) implementiert?",
            smart_A1.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE("Ist der Copykonstruktor (Referenz) implementiert?",
            smart_A2.getObject() == a);

    CPPUNIT_ASSERT_MESSAGE("RefCount-Object sollte vorhanden sein",
            smart_A1.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("RefCount-Objekte sollten identisch sein",
            smart_A1.getRefCounter() == smart_A2.getRefCounter());

    CPPUNIT_ASSERT_MESSAGE("RefCount sollte jetzt 2 sein",
            smart_A1.getRefCounter()->getRefCount() == 2);
}

/*
 * Test ob der Copykonstruktor implementiert wurde.
 * Copy-Konstruktor mit Referenz auf leeren Smartpointer
 */
void Blatt08_Testsuite::testCopyConstructorRef2() {
    SmartPointer<A> smart_A1;
    SmartPointer<A> smart_A2 = smart_A1;

    CPPUNIT_ASSERT_MESSAGE("Ist der Copykonstruktor (Referenz) implementiert?",
            smart_A1.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Ist der Copykonstruktor (Referenz) implementiert?",
            smart_A2.getObject() == nullptr);

    CPPUNIT_ASSERT_MESSAGE("RefCount-Object sollte nicht vorhanden sein",
            smart_A1.getRefCounter() == nullptr);
    CPPUNIT_ASSERT_MESSAGE("RefCount-Object sollte nicht vorhanden sein",
            smart_A2.getRefCounter() == nullptr);
}

/*
 * Verhaelt sich der Destruktor vom SP korrekt?
 * Leerer Smartpointer
 */
void Blatt08_Testsuite::testCallDestructorEmpty() {
    saveOldAdress.clear();

    {
        SmartPointer<A> p1;
    }

    CPPUNIT_ASSERT_MESSAGE(
            "Kein Objekt-Destruktor darf aufgerufen worden sein.",
            saveOldAdress.size() == 0);
}

/*
 * Wird der Destruktor aufgerufen?
 * RefCount == 0
 */
void Blatt08_Testsuite::testCallDestructorCountOne() {
    saveOldAdress.clear();
    A *a = new A;
    A *b = new A;
    void *temp = &(*a);
    SmartPointer<A> p1 { a };

    p1 = b;

    CPPUNIT_ASSERT_MESSAGE(
            "Destruktor: Objektpointer sollte auf das neue Objekt zeigen",
            p1.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount sollte vorhanden sein",
            p1.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount sollte Wert 1 haben",
            p1.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Wurde der Destruktor vom richtigen Objekt aufgerufen?", temp,
            saveOldAdress.back());
    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Wurde der Objekt-Destruktor nur einmal aufgerufen?", 1,
            (int )saveOldAdress.size());
}

/*
 * Der Destruktor wurde aufgerufen?!
 * RefCount > 0
 */
void Blatt08_Testsuite::testCallDestructorCountThree() {
    saveOldAdress.clear();
    A *a = new A;
    A *b = new A;
    SmartPointer<A> p1 { a };
    SmartPointer<A> p2(p1);
    SmartPointer<A> p3(p2);

    p1 = b;

    CPPUNIT_ASSERT_MESSAGE(
            "Destruktor: Objektpointer sollte auf das neue Objekt zeigen",
            p1.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount sollte vorhanden sein",
            p1.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount sollte Wert 1 haben",
            p1.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE(
            "Destruktor: Objektpointer sollte auf das alte Objekt zeigen",
            p2.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount sollte vorhanden sein",
            p2.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount sollte Wert 2 haben",
            p2.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Destruktor: Objektpointer sollte auf das alte Objekt zeigen",
            p3.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount sollte vorhanden sein",
            p3.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount sollte Wert 2 haben",
            p3.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount p1 != p2",
            p1.getRefCounter() != p2.getRefCounter());
    CPPUNIT_ASSERT_MESSAGE("Destruktor: RefCount p2 == p3",
            p2.getRefCounter() == p3.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Der Objekt-Destruktor sollte nicht aufgerufen worden sein", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der -> Operator ueberladen wurde.
 * Dereferenzierung eines leeren Smartpointers (NullPointerException)
 */
void Blatt08_Testsuite::testArrowOperatorNull() {
    SmartPointer<A> smart_A;

    CPPUNIT_ASSERT_THROW_MESSAGE(
            "Wird eine NullPointerException beim Dereferenzieren geworfen, wenn ein SmartPointer ein Nullpointer ist?",
            smart_A->getNum(), NullPointerException);
}

/*
 * Test ob der -> Operator ueberladen wurde.
 * Dereferenzierung eines nicht-leeren Smartpointers
 */
void Blatt08_Testsuite::testArrowOperator() {
    SmartPointer<A> smart_A { new A };

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Ist der -> Operator ueberladen?", 42,
            smart_A->getNum());
}

/*
 * Test ob der Stern-Operator ueberladen wurde.
 * Dereferenzierung eines leeren Smartpointers (NullPointerException)
 */
void Blatt08_Testsuite::testDereferenceOperatorNull() {
    SmartPointer<B> smart_B;

    CPPUNIT_ASSERT_THROW_MESSAGE(
            "Wird eine NullPointerException beim Dereferenzieren geworfen, wenn ein SmartPointer ein Nullpointer ist?",
            *smart_B, NullPointerException);
}

/*
 * Test ob der Stern-Operator ueberladen wurde.
 * Dereferenzierung eines nicht-leeren Smartpointers
 */
void Blatt08_Testsuite::testDereferenceOperator() {
    SmartPointer<B> smart_B { new B };

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Ist der * Operator ueberladen?", 24,
            (*smart_B).getNum());
}

/*
 * Test ob der SmartPointer<T>::getObject() implementiert wurde.
 * leerer Smartpointer
 */
void Blatt08_Testsuite::testGetObjectNull() {
    SmartPointer<A> smart_A;

    CPPUNIT_ASSERT_MESSAGE("Ist SmartPointer<T>::getObject() implementiert?",
            smart_A.getObject() == nullptr);
}

/*
 * Test ob der SmartPointer<T>::getObject() implementiert wurde.
 * Smartpointer mit Objekt
 */
void Blatt08_Testsuite::testGetObject() {
    A *a = new A;
    SmartPointer<A> smart_A { a };

    CPPUNIT_ASSERT_MESSAGE("Ist SmartPointer<T>::getObject() implementiert?",
            smart_A.getObject() == a);
}

/*
 * Test ob der SmartPointer<T>::getRefCounter() implementiert wurde.
 * Leerer Smartpointer
 */
void Blatt08_Testsuite::testGetRefCounterNull() {
    SmartPointer<A> smart_A;

    CPPUNIT_ASSERT_MESSAGE(
            "Ist SmartPointer<T>::getRefCounter() implementiert?",
            smart_A.getRefCounter() == nullptr);
}

/*
 * Test ob der SmartPointer<T>::getRefCounter() implementiert wurde.
 * Smartpointer mit Objekt
 */
void Blatt08_Testsuite::testGetRefCounter() {
    A *a = new A;
    SmartPointer<A> smart_A { a };

    CPPUNIT_ASSERT_MESSAGE(
            "Ist SmartPointer<T>::getRefCounter() implementiert?",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Ist SmartPointer<T>::getRefCounter() implementiert?",
            smart_A.getRefCounter()->getRefCount() == 1);
}

/*
 * Test ob der Zuweisungsoperator fuer Pointer korrekt ueberladen wurde.
 * Smartpointer zeigt auf nullptr und nullptr wird zugewiesen ("Selfassignment" mit Sonderwert)
 */
void Blatt08_Testsuite::testAssignmentPtrNullNullptr() {
    saveOldAdress.clear();
    SmartPointer<A> smart_A;

    smart_A = nullptr;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte nullptr sein",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte nullptr sein",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Pointer korrekt ueberladen wurde.
 * Smartpointer zeigt auf Objekt und nullptr wird zugewiesen (normales Assignment mit Sonderwert)
 */
void Blatt08_Testsuite::testAssignmentPtrNullptr() {
    saveOldAdress.clear();
    A *a = new A;
    void *temp = &(*a);
    SmartPointer<A> smart_A { a };

    smart_A = nullptr;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte nullptr sein",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte nullptr sein",
            smart_A.getRefCounter() == nullptr);
    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Wurde der Objekt-Destruktor nur einmal aufgerufen?",
            1, (int )saveOldAdress.size());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Wurde der Destruktor vom richtigen Objekt aufgerufen?",
            temp, saveOldAdress.back());
}

/*
 * Test ob der Zuweisungsoperator fuer Pointer korrekt ueberladen wurde.
 * Normales Assignment: Null-Smartpointer, neues Objekt wird zugewiesen
 */
void Blatt08_Testsuite::testAssignmentPtrNull() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A;

    smart_A = a;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte auf das neue Objekt zeigen",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte Wert 1 haben",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Pointer korrekt ueberladen wurde.
 * Normales Assignment: Smartpointer mit Objekt, neues Objekt wird zugewiesen
 */
void Blatt08_Testsuite::testAssignmentPtr() {
    saveOldAdress.clear();
    A *a = new A;
    A *b = new A;
    void *temp = &(*a);
    SmartPointer<A> smart_A { a };

    smart_A = b;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte auf das neue Objekt zeigen",
            smart_A.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte Wert 1 haben",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Wurde der Objekt-Destruktor nur einmal aufgerufen?",
            1, (int )saveOldAdress.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Wurde der Destruktor vom richtigen Objekt aufgerufen?",
            temp, saveOldAdress.back());
}

/*
 * Test ob der Zuweisungsoperator fuer Pointer korrekt ueberladen wurde.
 * Self-Assignment mit Pointern
 */
void Blatt08_Testsuite::testAssignmentPtrSelfassignment() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A { a };

    smart_A = a;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte immer noch aufs alte Objekt zeigen",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte Wert 1 haben",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Pointer korrekt ueberladen wurde.
 * Normales Assignment: Smartpointer mit Objekt, neues Objekt wird zugewiesen (komplexeres Szenario)
 */
void Blatt08_Testsuite::testAssignmentPtrComplex() {
    saveOldAdress.clear();
    A *a = new A;
    A *b = new A;
    SmartPointer<A> p1 { a };
    SmartPointer<A> p2(p1);
    SmartPointer<A> p3(p2);

    p1 = b;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte auf das neue Objekt zeigen",
            p1.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            p1.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte Wert 1 haben",
            p1.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte auf das alte Objekt zeigen",
            p2.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            p2.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte Wert 2 haben",
            p2.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte auf das alte Objekt zeigen",
            p3.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            p3.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte Wert 2 haben",
            p3.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount p1 und p2 sollten unterschiedlich sein",
            p1.getRefCounter() != p2.getRefCounter());
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount p2 und p3 sollten gleich sein",
            p2.getRefCounter() == p3.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Pointer korrekt ueberladen wurde.
 * Self-Assignment mit Pointern (komplexeres Szenario)
 */
void Blatt08_Testsuite::testAssignmentPtrSelfassignmentComplex() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> p1 { a };
    SmartPointer<A> p2(p1);
    SmartPointer<A> p3(p2);

    p1 = a;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte auf das alte Objekt zeigen",
            p1.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            p1.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte noch Wert 3 haben",
            p1.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte auf das alte Objekt zeigen",
            p2.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            p2.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte Wert 3 haben",
            p2.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objektpointer sollte auf das alte Objekt zeigen",
            p3.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte vorhanden sein",
            p3.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount sollte Wert 3 haben",
            p3.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount p1 und p2 sollten gleich sein",
            p1.getRefCounter() == p2.getRefCounter());
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Pointer: RefCount p2 und p3 sollten gleich sein",
            p2.getRefCounter() == p3.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Pointer: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Smartpointer zeigt auf nullptr und nullptr-Smartpointer wird zugewiesen ("Selfassignment" mit Sonderwert)
 */
void Blatt08_Testsuite::testAssignmentRefNullNullptr() {
    saveOldAdress.clear();
    SmartPointer<A> smart_A;

    smart_A = smart_A;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte nullptr sein",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte nullptr sein",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Smartpointer zeigt auf nullptr und nullptr-Smartpointer wird zugewiesen ("Selfassignment" mit Sonderwert)
 */
void Blatt08_Testsuite::testAssignmentRefNullNullptr2() {
    saveOldAdress.clear();
    SmartPointer<A> smart_A, smart_B;

    smart_A = smart_B;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte nullptr sein",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte nullptr sein",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte nullptr sein",
            smart_B.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte nullptr sein",
            smart_B.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Smartpointer zeigt auf Objekt und nullptr-Smartpointer wird zugewiesen (normales Assignment mit Sonderwert)
 */
void Blatt08_Testsuite::testAssignmentRefNullptr() {
    saveOldAdress.clear();
    A *a = new A;
    void *temp = &(*a);
    SmartPointer<A> smart_A { a }, smart_B;

    smart_A = smart_B;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte nullptr sein",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte nullptr sein",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte nullptr sein",
            smart_B.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte nullptr sein",
            smart_B.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Wurde der Objekt-Destruktor nur einmal aufgerufen?",
            1, (int )saveOldAdress.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Wurde der Destruktor vom richtigen Objekt aufgerufen?",
            temp, saveOldAdress.back());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Normales Assignment: Null-Smartpointer, neues Objekt wird zugewiesen
 */
void Blatt08_Testsuite::testAssignmentRefNull() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A, smart_B { a };

    smart_A = smart_B;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das neue Objekt zeigen",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 2 haben",
            smart_A.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das neue Objekt zeigen",
            smart_B.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            smart_B.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 2 haben",
            smart_B.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount-Pointer sollten identisch sein",
            smart_A.getRefCounter() == smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Normales Assignment: Smartpointer mit Objekt, neues Objekt wird zugewiesen
 */
void Blatt08_Testsuite::testAssignmentRef() {
    saveOldAdress.clear();
    A *a = new A;
    A *b = new A;
    void *temp = &(*a);
    SmartPointer<A> smart_A { a }, smart_B { b };

    smart_A = smart_B;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das neue Objekt zeigen",
            smart_A.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 2 haben",
            smart_A.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das neue Objekt zeigen",
            smart_B.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            smart_B.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 2 haben",
            smart_B.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount-Pointer sollten identisch sein",
            smart_A.getRefCounter() == smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Wurde der Objekt-Destruktor nur einmal aufgerufen?",
            1, (int )saveOldAdress.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Wurde der Destruktor vom richtigen Objekt aufgerufen?",
            temp, saveOldAdress.back());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Self-Assignment mit Referenzen
 */
void Blatt08_Testsuite::testAssignmentRefSelfassignment() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A { a };

    smart_A = smart_A;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte immer noch aufs alte Objekt zeigen",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 1 haben",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Normales Assignment: Smartpointer mit Objekt, neues Objekt wird zugewiesen (komplexeres Szenario)
 */
void Blatt08_Testsuite::testAssignmentRefComplex() {
    saveOldAdress.clear();
    A *a = new A;
    A *b = new A;
    SmartPointer<A> p1 { a };
    SmartPointer<A> p2(p1);
    SmartPointer<A> p3(b);

    p1 = p3;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das neue Objekt zeigen",
            p1.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p1.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 2 haben",
            p1.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das alte Objekt zeigen",
            p2.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p2.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 1 haben",
            p2.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das alte Objekt zeigen",
            p3.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p3.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 2 haben",
            p3.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount p1 und p2 sollten unterschiedlich sein",
            p1.getRefCounter() != p2.getRefCounter());
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount p1 und p3 sollten gleich sein",
            p1.getRefCounter() == p3.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Self-Assignment mit Referenzen (komplexeres Szenario)
 */
void Blatt08_Testsuite::testAssignmentRefSelfassignmentComplex() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> p1 { a };
    SmartPointer<A> p2(p1);
    SmartPointer<A> p3(p2);

    p1 = p1;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das alte Objekt zeigen",
            p1.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p1.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte noch Wert 3 haben",
            p1.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das alte Objekt zeigen",
            p2.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p2.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 3 haben",
            p2.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das alte Objekt zeigen",
            p3.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p3.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 3 haben",
            p3.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount p1 und p2 sollten gleich sein",
            p1.getRefCounter() == p2.getRefCounter());
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount p2 und p3 sollten gleich sein",
            p2.getRefCounter() == p3.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Zuweisungsoperator fuer Referenzen korrekt ueberladen wurde.
 * Self-Assignment mit Referenzen (komplexeres Szenario)
 */
void Blatt08_Testsuite::testAssignmentRefSelfassignmentComplex2() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> p1 { a };
    SmartPointer<A> p2(p1);
    SmartPointer<A> p3(p2);

    p1 = p3;

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das alte Objekt zeigen",
            p1.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p1.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte noch Wert 3 haben",
            p1.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das alte Objekt zeigen",
            p2.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p2.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 3 haben",
            p2.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objektpointer sollte auf das alte Objekt zeigen",
            p3.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte vorhanden sein",
            p3.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount sollte Wert 3 haben",
            p3.getRefCounter()->getRefCount() == 3);

    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount p1 und p2 sollten gleich sein",
            p1.getRefCounter() == p2.getRefCounter());
    CPPUNIT_ASSERT_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: RefCount p2 und p3 sollten gleich sein",
            p2.getRefCounter() == p3.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Zuweisungsoperator fuer Referenzen: Objekt-Destruktor darf hier nicht aufgerufen werden",
            0, (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 2x leere Smartpointer
 */
void Blatt08_Testsuite::testCompareNullNull() {
    saveOldAdress.clear();
    SmartPointer<A> smart_A, smart_B;

    CPPUNIT_ASSERT_MESSAGE("Vergleich leerer Smartpointer", smart_A == smart_B);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 1x leerer Smartpointer, 1x Objekt
 */
void Blatt08_Testsuite::testCompareNullObject() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A, smart_B { a };

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich leerer Smartpointer mit Object-Smartpointer",
            !(smart_A == smart_B));

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_B.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 1x Objekt, 1x leerer Smartpointer
 */
void Blatt08_Testsuite::testCompareObjectNull() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A { a }, smart_B;

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich Object-Smartpointer mit leerem Smartpointer",
            !(smart_A == smart_B));

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 2x Smartpointer mit ungleichen Objekten
 */
void Blatt08_Testsuite::testCompareUnequalObjects() {
    saveOldAdress.clear();
    A *a = new A;
    A *b = new A;
    SmartPointer<A> smart_A { a }, smart_B { b };

    CPPUNIT_ASSERT_MESSAGE("Vergleich Smartpointer mit ungleichen Objekten",
            !(smart_A == smart_B));

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_B.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 2x Smartpointer mit gleichen Objekten
 */
void Blatt08_Testsuite::testCompareEqualObjects() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A { a }, smart_B { smart_A };

    CPPUNIT_ASSERT_MESSAGE("Vergleich Smartpointer mit gleichen Objekten",
            smart_A == smart_B);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_A.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_B.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() == smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 2x leere Smartpointer
 */
void Blatt08_Testsuite::testNotCompareNullNull() {
    saveOldAdress.clear();
    SmartPointer<A> smart_A, smart_B;

    CPPUNIT_ASSERT_MESSAGE("Vergleich leerer Smartpointer",
            !(smart_A != smart_B));

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 1x leerer Smartpointer, 1x Objekt
 */
void Blatt08_Testsuite::testNotCompareNullObject() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A, smart_B { a };

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich leerer Smartpointer mit Object-Smartpointer",
            smart_A != smart_B);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_B.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 1x Objekt, 1x leerer Smartpointer
 */
void Blatt08_Testsuite::testNotCompareObjectNull() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A { a }, smart_B;

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich Object-Smartpointer mit leerem Smartpointer",
            smart_A != smart_B);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 2x Smartpointer mit ungleichen Objekten
 */
void Blatt08_Testsuite::testNotCompareUnequalObjects() {
    saveOldAdress.clear();
    A *a = new A;
    A *b = new A;
    SmartPointer<A> smart_A { a }, smart_B { b };

    CPPUNIT_ASSERT_MESSAGE("Vergleich Smartpointer mit ungleichen Objekten",
            smart_A != smart_B);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == b);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_B.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob der Vergleichssoperator korrekt ueberladen wurde.
 * 2x Smartpointer mit gleichen Objekten
 */
void Blatt08_Testsuite::testNotCompareEqualObjects() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A { a }, smart_B { smart_A };

    CPPUNIT_ASSERT_MESSAGE("Vergleich Smartpointer mit gleichen Objekten",
            !(smart_A != smart_B));

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_A.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am Objektpointer aendern",
            smart_B.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_B.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Vergleich sollte nichts am RefCount-Wert aendern",
            smart_B.getRefCounter()->getRefCount() == 2);

    CPPUNIT_ASSERT_MESSAGE(
            "Vergleich sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() == smart_B.getRefCounter());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Vergleich sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test fuer Bool-Operator.
 * leerer Smartpointer
 */
void Blatt08_Testsuite::testBoolEmptySmartptr() {
    saveOldAdress.clear();
    SmartPointer<A> smart_A;

    CPPUNIT_ASSERT_MESSAGE("Bool-Operator mit leerem Objekt",
            (!smart_A == true));

    CPPUNIT_ASSERT_MESSAGE(
            "Bool-Operator sollte nichts am Objektpointer aendern",
            smart_A.getObject() == nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Bool-Operator sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() == nullptr);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Bool-Operator sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test fuer Bool-Operator.
 * nicht-leerer Smartpointer
 */
void Blatt08_Testsuite::testBoolNotEmptySmartptr() {
    saveOldAdress.clear();
    A *a = new A;
    SmartPointer<A> smart_A { a };

    CPPUNIT_ASSERT_MESSAGE("Bool-Operator mit nicht-leerem Objekt",
            (smart_A == true));

    CPPUNIT_ASSERT_MESSAGE(
            "Bool-Operator sollte nichts am Objektpointer aendern",
            smart_A.getObject() == a);
    CPPUNIT_ASSERT_MESSAGE(
            "Bool-Operator sollte nichts am RefCount-Pointer aendern",
            smart_A.getRefCounter() != nullptr);
    CPPUNIT_ASSERT_MESSAGE(
            "Bool-Operator sollte nichts am RefCount-Wert aendern",
            smart_A.getRefCounter()->getRefCount() == 1);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Bool-Operator sollte keinen Objekt-Destruktor aufrufen", 0,
            (int )saveOldAdress.size());
}

/*
 * Test ob Polymorphie funktioniert.
 */
void Blatt08_Testsuite::testPolymorphism() {
    SmartPointer<A> smart_B;

    smart_B = new B;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Funktioniert die Polymorphie?", 24,
            smart_B->getNum());
}

/*
 * Smartpointer als Parameter per Referenz uebergeben
 */
void Blatt08_Testsuite::testSPAsParameterPerReference() {
    SmartPointer<A> smart_A { new A };

    CPPUNIT_ASSERT_EQUAL_MESSAGE(
            "Kann man Smartpointer als Parameter per Referenz uebergeben?", 42,
            func(smart_A));
}

