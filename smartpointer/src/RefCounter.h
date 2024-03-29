/*
 * RefCounter.h
 *
 */

#ifndef REFCOUNTER_H_
#define REFCOUNTER_H_

/*
 * ===========================================================================
 * Hilfsklasse zum Zaehlen der Referenzen (Schnittstelle)
 * ===========================================================================
 */
class RefCounter {
public:
    RefCounter();
    void inc();
    void dec();
    bool isZero() const;
    unsigned int getRefCount() const;

    RefCounter(const RefCounter&) = delete;
    RefCounter &operator=(const RefCounter&) = delete;

private:
    unsigned int n; // How many SmartPointer share ownership of "our" object?
};

#endif /* REFCOUNTER_H_ */

