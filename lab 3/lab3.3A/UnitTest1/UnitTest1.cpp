#include "CppUnitTest.h"
#include <sstream>
#include <iostream>
#include <type_traits>
#include <limits>
#include <stdexcept>
#include "../lab3.3A/Complex.h"
#include "../lab3.3A/ComplexPub.h"
#include "../lab3.3A/ComplexPriv.h"
#include "../lab3.3A/PackedSize.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ComplexTests
{
    static const double EPS = 1e-12;
    class CoutCapture
    {
        ostringstream buf;
        streambuf* old;
    public:
        CoutCapture() : old(cout.rdbuf(buf.rdbuf())) {}
        ~CoutCapture() { cout.rdbuf(old); }
        string str() const { return buf.str(); }
    };

    TEST_CLASS(ComplexBaseTests)
    {
    public:
        TEST_METHOD(DefaultConstructorGivesZero)
        {
            Complex c;
            Assert::AreEqual(0.0, c.getX());
            Assert::AreEqual(0.0, c.getY());
        }

        TEST_METHOD(InitConstructors)
        {
            Complex a(3);
            Assert::AreEqual(3.0, a.getX());
            Assert::AreEqual(0.0, a.getY());

            Complex b(3, 4);
            Assert::AreEqual(3.0, b.getX());
            Assert::AreEqual(4.0, b.getY());
        }

        TEST_METHOD(CopyConstructor)
        {
            Complex a(1.5, -2.5);
            Complex b(a);
            Assert::AreEqual(1.5, b.getX());
            Assert::AreEqual(-2.5, b.getY());
        }

        TEST_METHOD(SettersAndInit)
        {
            Complex c;
            c.setX(7);
            c.setY(-8);
            Assert::AreEqual(7.0, c.getX());
            Assert::AreEqual(-8.0, c.getY());

            c.Init(1, 2);
            Assert::AreEqual(1.0, c.getX());
            Assert::AreEqual(2.0, c.getY());
        }

        TEST_METHOD(SettersRejectNonFinite)
        {
            Complex c(1, 1);
            const double inf = numeric_limits<double>::infinity();
            const double nan = numeric_limits<double>::quiet_NaN();

            Assert::ExpectException<invalid_argument>([&] { c.setX(inf); });
            Assert::ExpectException<invalid_argument>([&] { c.setY(nan); });
            Assert::ExpectException<invalid_argument>([&] { Complex t(inf); });
            Assert::ExpectException<invalid_argument>([&] { Complex t(0, nan); });

            Assert::AreEqual(1.0, c.getX());
            Assert::AreEqual(1.0, c.getY());
        }

        TEST_METHOD(ToStringAndStreamOutput)
        {
            Complex c(3, 4);
            Assert::AreEqual(string("(3, 4)"), c.toString());

            ostringstream out;
            out << c;
            Assert::AreEqual(string("(3, 4)"), out.str());
        }

        TEST_METHOD(DisplayPrintsToStdout)
        {
            Complex c(1, 2);
            CoutCapture cap;
            c.Display();
            Assert::AreEqual(string("(1, 2)\n"), cap.str());
        }

        TEST_METHOD(StreamInput)
        {
            Complex c;
            istringstream in("5 -6");
            {
                CoutCapture cap;       
                in >> c;
            }
            Assert::AreEqual(5.0, c.getX());
            Assert::AreEqual(-6.0, c.getY());
        }
    };

    TEST_CLASS(ComplexPubTests)
    {
    public:
        TEST_METHOD(Constructors)
        {
            ComplexPub a;
            Assert::AreEqual(0.0, a.getX());
            Assert::AreEqual(0.0, a.getY());

            ComplexPub b(2, 3);
            ComplexPub c(b);
            Assert::AreEqual(2.0, c.getX());
            Assert::AreEqual(3.0, c.getY());

            Complex base(9, 8);
            ComplexPub d(base);         
            Assert::AreEqual(9.0, d.getX());
            Assert::AreEqual(8.0, d.getY());
        }

        TEST_METHOD(Sub)
        {
            ComplexPub a(1, 2), b(3, -4);
            ComplexPub r = a.sub(b);
            Assert::AreEqual(-2.0, r.getX(), EPS);
            Assert::AreEqual(6.0, r.getY(), EPS);

            ComplexPub r2 = a - b;       
            Assert::AreEqual(-2.0, r2.getX(), EPS);
            Assert::AreEqual(6.0, r2.getY(), EPS);
        }

        TEST_METHOD(Div)
        {
            ComplexPub a(1, 2), b(3, -4);
            ComplexPub r = a.div(b);
            Assert::AreEqual(-0.2, r.getX(), EPS);
            Assert::AreEqual(0.4, r.getY(), EPS);

            ComplexPub r2 = a / b;
            Assert::AreEqual(-0.2, r2.getX(), EPS);
            Assert::AreEqual(0.4, r2.getY(), EPS);
        }

        TEST_METHOD(DivByZeroThrows)
        {
            ComplexPub a(1, 2), zero(0, 0);
            Assert::ExpectException<invalid_argument>([&] { a.div(zero); });
            Assert::ExpectException<invalid_argument>([&] { a / zero; });
        }

        TEST_METHOD(Conj)
        {
            ComplexPub a(3, -4);
            ComplexPub c = a.conj();
            Assert::AreEqual(3.0, c.getX());
            Assert::AreEqual(4.0, c.getY());

            ComplexPub t = ~a;
            Assert::AreEqual(3.0, t.getX());
            Assert::AreEqual(4.0, t.getY());

            ComplexPub back = ~t;        
            Assert::AreEqual(3.0, back.getX());
            Assert::AreEqual(-4.0, back.getY());
        }

        TEST_METHOD(Assignment)
        {
            ComplexPub a(1, 2), b;
            b = a;
            Assert::AreEqual(1.0, b.getX());
            Assert::AreEqual(2.0, b.getY());
        }

        TEST_METHOD(StringConversion)
        {
            ComplexPub a(1, 2);
            string s = a;
            Assert::AreEqual(string("(1, 2)"), s);
        }

        TEST_METHOD(PrefixIncDec)
        {
            ComplexPub a(1, 5);
            ComplexPub& r1 = ++a;
            Assert::IsTrue(&r1 == &a);
            Assert::AreEqual(2.0, a.getX());
            Assert::AreEqual(5.0, a.getY());  

            --a; --a;
            Assert::AreEqual(0.0, a.getX());
        }

        TEST_METHOD(PostfixIncDecReturnOldValue)
        {
            ComplexPub a(1, 5);
            ComplexPub old = a++;
            Assert::AreEqual(1.0, old.getX());
            Assert::AreEqual(2.0, a.getX());

            ComplexPub old2 = a--;
            Assert::AreEqual(2.0, old2.getX());
            Assert::AreEqual(1.0, a.getX());
        }

        TEST_METHOD(InheritedIO)
        {
            ComplexPub a;
            istringstream in("4 7");
            {
                CoutCapture cap;
                in >> a;                  
            }
            Assert::AreEqual(4.0, a.getX());
            Assert::AreEqual(7.0, a.getY());

            ostringstream out;
            out << a;
            Assert::AreEqual(string("(4, 7)"), out.str());
        }

        TEST_METHOD(ArraysOfObjects)
        {
            ComplexPub arr[3] = { ComplexPub(1), ComplexPub(2, 3), ComplexPub() };
            Assert::AreEqual(1.0, arr[0].getX());
            Assert::AreEqual(3.0, arr[1].getY());
            Assert::AreEqual(0.0, arr[2].getX());

            ComplexPub* dyn = new ComplexPub[2]{ ComplexPub(5, 5), ComplexPub(1, 1) };
            Assert::AreEqual(5.0, dyn[0].getX());
            Assert::AreEqual(1.0, dyn[1].getY());
            delete[] dyn;
        }
    };

    TEST_CLASS(ComplexPrivTests)
    {
    public:
        TEST_METHOD(ConstructorsAndAccessors)
        {
            ComplexPriv a;
            Assert::AreEqual(0.0, a.getX());
            Assert::AreEqual(0.0, a.getY());

            ComplexPriv b(2, 3);
            ComplexPriv c(b);
            Assert::AreEqual(2.0, c.getX());
            Assert::AreEqual(3.0, c.getY());

            c.setX(10);
            c.Init(4, 5);
            Assert::AreEqual(4.0, c.getX());
            Assert::AreEqual(5.0, c.getY());
            Assert::AreEqual(string("(4, 5)"), c.toString());
        }

        TEST_METHOD(SubDivConj)
        {
            ComplexPriv a(1, 2), b(3, -4);

            ComplexPriv s = a - b;
            Assert::AreEqual(-2.0, s.getX(), EPS);
            Assert::AreEqual(6.0, s.getY(), EPS);

            ComplexPriv d = a / b;
            Assert::AreEqual(-0.2, d.getX(), EPS);
            Assert::AreEqual(0.4, d.getY(), EPS);

            ComplexPriv c = ~b;
            Assert::AreEqual(3.0, c.getX());
            Assert::AreEqual(4.0, c.getY());
        }

        TEST_METHOD(DivByZeroThrows)
        {
            ComplexPriv a(1, 2), zero;
            Assert::ExpectException<invalid_argument>([&] { a / zero; });
            Assert::ExpectException<invalid_argument>([&] { a.div(zero); });
        }

        TEST_METHOD(AssignmentAndString)
        {
            ComplexPriv a(1, 2), b;
            b = a;
            Assert::AreEqual(1.0, b.getX());
            string s = b;
            Assert::AreEqual(string("(1, 2)"), s);
        }

        TEST_METHOD(IncDec)
        {
            ComplexPriv a(1, 5);
            ++a;
            Assert::AreEqual(2.0, a.getX());
            ComplexPriv old = a++;
            Assert::AreEqual(2.0, old.getX());
            Assert::AreEqual(3.0, a.getX());
            --a;
            ComplexPriv old2 = a--;
            Assert::AreEqual(2.0, old2.getX());
            Assert::AreEqual(1.0, a.getX());
        }

        TEST_METHOD(OwnIO)
        {
            ComplexPriv p;
            istringstream in("6 -7");
            {
                CoutCapture cap;
                in >> p;
            }
            Assert::AreEqual(6.0, p.getX());
            Assert::AreEqual(-7.0, p.getY());

            ostringstream out;
            out << p;
            Assert::AreEqual(string("(6, -7)"), out.str());
        }
    };

    TEST_CLASS(InheritanceTests)
    {
    public:
        TEST_METHOD(PublicConvertsToBase)
        {
            Assert::IsTrue((is_convertible<ComplexPub*, Complex*>::value));
            Assert::IsTrue((is_convertible<ComplexPub&, Complex&>::value));
        }

        TEST_METHOD(PrivateDoesNotConvertToBase)
        {
            Assert::IsFalse((is_convertible<ComplexPriv*, Complex*>::value));
            Assert::IsFalse((is_convertible<ComplexPriv&, Complex&>::value));
        }
    };

    TEST_CLASS(SizeTests)
    {
    public:
        TEST_METHOD(PackedAndUnpackedSizes)
        {
            Assert::AreEqual(2 * sizeof(double), sizeof(Complex));
            Assert::AreEqual(sizeof(Complex), sizeof(ComplexPub));
            Assert::AreEqual(sizeof(Complex), sizeof(ComplexPriv));

            Assert::AreEqual(2 * sizeof(double), SizeComplexPacked());
            Assert::AreEqual(SizeComplexPacked(), SizeComplexPubPacked());
            Assert::AreEqual(SizeComplexPacked(), SizeComplexPrivPacked());
        }
    };
}