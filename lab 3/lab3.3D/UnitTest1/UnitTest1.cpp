#include "CppUnitTest.h"
#include <sstream>
#include <iostream>
#include <type_traits>
#include <limits>
#include <stdexcept>

#include "../lab3.3D/Object.h"
#include "../lab3.3D/Number.h"
#include "../lab3.3D/RealMath.h"
#include "../lab3.3D/RealPub.h"
#include "../lab3.3D/RealPriv.h"
#include "../lab3.3D/PackedSize.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NumberRealTests
{
    static const float EPS = 1e-5f;
    static const float INF = numeric_limits<float>::infinity();
    static const float NANF = numeric_limits<float>::quiet_NaN();

    class CoutCapture
    {
        ostringstream buf;
        streambuf* old;
    public:
        CoutCapture() : old(cout.rdbuf(buf.rdbuf())) {}
        ~CoutCapture() { cout.rdbuf(old); }
        string str() const { return buf.str(); }
    };

    class CinFeed
    {
        istringstream in;
        streambuf* old;
    public:
        explicit CinFeed(const string& text) : in(text), old(cin.rdbuf(in.rdbuf())) {}
        ~CinFeed() { cin.rdbuf(old); }
    };

    TEST_CLASS(ObjectTests)
    {
    public:
        TEST_METHOD(CounterTracksCreationAndDestruction)
        {
            unsigned int before = Object::Count();
            {
                Number a;
                Number b(2);
                RealPub c;
                RealPriv d;
                Assert::AreEqual(before + 4, Object::Count());
            }
            Assert::AreEqual(before, Object::Count());
        }

        TEST_METHOD(CopyConstructorCountsAsNewObject)
        {
            unsigned int before = Object::Count();
            {
                Number a(1);
                Number b(a);
                RealPub c(a);            
                RealPub d(c);
                RealPriv e(a);
                RealPriv f(e);
                Assert::AreEqual(before + 6, Object::Count());
            }
            Assert::AreEqual(before, Object::Count());
        }

        TEST_METHOD(AssignmentDoesNotChangeCounter)
        {
            Number a(1), b(2);
            unsigned int before = Object::Count();
            a = b;
            Assert::AreEqual(before, Object::Count());
        }

        TEST_METHOD(ArraysAreCounted)
        {
            unsigned int before = Object::Count();
            {
                Number arr[3] = { Number(1), Number(2.5f), Number() };
                Assert::AreEqual(before + 3, Object::Count());

                Number* dyn = new Number[2]{ Number(5), Number(0.5f) };
                Assert::AreEqual(before + 5, Object::Count());
                delete[] dyn;
                Assert::AreEqual(before + 3, Object::Count());
            }
            Assert::AreEqual(before, Object::Count());
        }

        TEST_METHOD(FailedConstructionDoesNotLeakCount)
        {
            unsigned int before = Object::Count();
            Assert::ExpectException<invalid_argument>([] { Number n(INF); });
            Assert::ExpectException<invalid_argument>([] { RealPub r(NANF); });
            Assert::AreEqual(before, Object::Count());
        }

        TEST_METHOD(CountIsAvailableThroughPrivateDerived)
        {
            Assert::AreEqual(Object::Count(), RealPriv::Count());
        }
    };

    TEST_CLASS(NumberTests)
    {
    public:
        TEST_METHOD(DefaultConstructorGivesZero)
        {
            Number n;
            Assert::AreEqual(0.0f, n.getValue());
        }

        TEST_METHOD(InitConstructor)
        {
            Number n(3.5f);
            Assert::AreEqual(3.5f, n.getValue());
        }

        TEST_METHOD(CopyConstructor)
        {
            Number a(-2.25f);
            Number b(a);
            Assert::AreEqual(-2.25f, b.getValue());
        }

        TEST_METHOD(SetterAndInit)
        {
            Number n;
            n.setValue(7);
            Assert::AreEqual(7.0f, n.getValue());
            n.Init(-8.5f);
            Assert::AreEqual(-8.5f, n.getValue());
        }

        TEST_METHOD(SettersRejectNonFinite)
        {
            Number n(1);
            Assert::ExpectException<invalid_argument>([&] { n.setValue(INF); });
            Assert::ExpectException<invalid_argument>([&] { n.setValue(-INF); });
            Assert::ExpectException<invalid_argument>([&] { n.setValue(NANF); });
            Assert::ExpectException<invalid_argument>([&] { n.Init(NANF); });
        
            Assert::AreEqual(1.0f, n.getValue());
        }

        TEST_METHOD(Assignment)
        {
            Number a(4), b;
            b = a;
            Assert::AreEqual(4.0f, b.getValue());

            Number c;
            c = b = Number(9);        
            Assert::AreEqual(9.0f, b.getValue());
            Assert::AreEqual(9.0f, c.getValue());
        }

        TEST_METHOD(Add)
        {
            Number a(1.5f), b(2.5f);
            Assert::AreEqual(4.0f, a.add(b).getValue(), EPS);
            Assert::AreEqual(4.0f, (a + b).getValue(), EPS);
            Assert::AreEqual(1.5f, a.getValue());     
        }

        TEST_METHOD(Div)
        {
            Number a(7.5f), b(2);
            Assert::AreEqual(3.75f, a.div(b).getValue(), EPS);
            Assert::AreEqual(3.75f, (a / b).getValue(), EPS);
        }

        TEST_METHOD(DivByZeroThrows)
        {
            Number a(1), zero(0);
            Assert::ExpectException<domain_error>([&] { a.div(zero); });
            Assert::ExpectException<domain_error>([&] { a / zero; });
        }

        TEST_METHOD(ToStringAndStringConversion)
        {
            Number n(3.5f);
            Assert::AreEqual(string("value = 3.5"), n.toString());
            string s = n;
            Assert::AreEqual(string("value = 3.5"), s);
        }

        TEST_METHOD(StreamOutput)
        {
            Number n(2);
            ostringstream out;
            out << n;
            Assert::AreEqual(string("value = 2"), out.str());
        }

        TEST_METHOD(DisplayPrintsToStdout)
        {
            Number n(2);
            CoutCapture cap;
            n.Display();
            Assert::AreEqual(string("value = 2\n"), cap.str());
        }

        TEST_METHOD(ReadFromKeyboard)
        {
            Number n;
            CinFeed feed("3.25");
            CoutCapture cap;
            n.Read();
            Assert::AreEqual(3.25f, n.getValue());
            Assert::AreEqual(string("value = ? "), cap.str()); 
        }

        TEST_METHOD(StreamInput)
        {
            Number n;
            istringstream in("5.5");
            {
                CoutCapture cap;           
                in >> n;
            }
            Assert::AreEqual(5.5f, n.getValue());
        }

        TEST_METHOD(PrefixIncDec)
        {
            Number n(1);
            Number& r = ++n;
            Assert::IsTrue(&r == &n);
            Assert::AreEqual(2.0f, n.getValue());
            --n; --n;
            Assert::AreEqual(0.0f, n.getValue());
        }

        TEST_METHOD(PostfixIncDecReturnOldValue)
        {
            Number n(1);
            Number old = n++;
            Assert::AreEqual(1.0f, old.getValue());
            Assert::AreEqual(2.0f, n.getValue());

            Number old2 = n--;
            Assert::AreEqual(2.0f, old2.getValue());
            Assert::AreEqual(1.0f, n.getValue());
        }
    };

    TEST_CLASS(RealMathTests)
    {
    public:
        TEST_METHOD(PowBasic)
        {
            Assert::AreEqual(1024.0f, RealMath::Pow(2, 10), EPS);
            Assert::AreEqual(1.0f, RealMath::Pow(5, 0), EPS);
            Assert::AreEqual(0.125f, RealMath::Pow(8, -1), EPS);
            Assert::AreEqual(-8.0f, RealMath::Pow(-2, 3), EPS); 
        }

        TEST_METHOD(PowDomainErrors)
        {
            Assert::ExpectException<domain_error>([] { RealMath::Pow(0, -1); });
            Assert::ExpectException<domain_error>([] { RealMath::Pow(-8, 0.5f); });
        }

        TEST_METHOD(PowOverflow)
        {
            Assert::ExpectException<overflow_error>([] { RealMath::Pow(10, 1000); });
        }

        TEST_METHOD(LogBasic)
        {
            Assert::AreEqual(0.0f, RealMath::Log(1), EPS);
            Assert::AreEqual(1.0f, RealMath::Log(2.7182818f), EPS);
            Assert::AreEqual(3.0f, RealMath::Log(8, 2), EPS);
            Assert::AreEqual(2.0f, RealMath::Log(100, 10), EPS);
        }

        TEST_METHOD(LogDomainErrors)
        {
            Assert::ExpectException<domain_error>([] { RealMath::Log(0); });
            Assert::ExpectException<domain_error>([] { RealMath::Log(-5); });
            Assert::ExpectException<domain_error>([] { RealMath::Log(8, 1); });
            Assert::ExpectException<domain_error>([] { RealMath::Log(8, 0); });
            Assert::ExpectException<domain_error>([] { RealMath::Log(8, -2); });
        }
    };

    TEST_CLASS(RealPubTests)
    {
    public:
        TEST_METHOD(Constructors)
        {
            RealPub a;
            Assert::AreEqual(0.0f, a.getValue());

            RealPub b(2.5f);
            Assert::AreEqual(2.5f, b.getValue());

            RealPub c(b);
            Assert::AreEqual(2.5f, c.getValue());

            Number base(9);
            RealPub d(base);           
            Assert::AreEqual(9.0f, d.getValue());
        }

        TEST_METHOD(Pow)
        {
            RealPub a(8);
            Assert::AreEqual(64.0f, a.pow(2).getValue(), EPS);
            Assert::AreEqual(0.125f, a.pow(-1).getValue(), EPS);
            Assert::AreEqual(2.828427f, a.pow(0.5f).getValue(), EPS);
            Assert::AreEqual(1.0f, a.pow(0).getValue(), EPS);
            Assert::AreEqual(8.0f, a.getValue());      
        }

        TEST_METHOD(PowErrors)
        {
            Assert::ExpectException<domain_error>([] { RealPub(0).pow(-1); });
            Assert::ExpectException<domain_error>([] { RealPub(-8).pow(0.5f); });
            Assert::ExpectException<overflow_error>([] { RealPub(10).pow(1000); });
        }

        TEST_METHOD(Log)
        {
            RealPub a(8);
            Assert::AreEqual(2.0794415f, a.log().getValue(), EPS);
            Assert::AreEqual(3.0f, a.log(2).getValue(), EPS);
            Assert::AreEqual(0.0f, RealPub(1).log().getValue(), EPS);
        }

        TEST_METHOD(LogErrors)
        {
            Assert::ExpectException<domain_error>([] { RealPub(0).log(); });
            Assert::ExpectException<domain_error>([] { RealPub(-8).log(); });
            Assert::ExpectException<domain_error>([] { RealPub(8).log(1); });
            Assert::ExpectException<domain_error>([] { RealPub(8).log(-2); });
        }

        TEST_METHOD(AddAndDivReturnRealPub)
        {
            RealPub a(8), b(2);
            RealPub s = a + b;
            RealPub d = a / b;
            Assert::AreEqual(10.0f, s.getValue(), EPS);
            Assert::AreEqual(4.0f, d.getValue(), EPS);
            Assert::AreEqual(10.0f, a.add(b).getValue(), EPS);  
            Assert::AreEqual(4.0f, a.div(b).getValue(), EPS);
        }

        TEST_METHOD(DivByZeroThrows)
        {
            RealPub a(8), zero;
            Assert::ExpectException<domain_error>([&] { a / zero; });
        }

        TEST_METHOD(Assignment)
        {
            RealPub a(3), b;
            b = a;
            Assert::AreEqual(3.0f, b.getValue());
        }

        TEST_METHOD(IncDecAllForms)
        {
            RealPub a(1);
            RealPub& r = ++a;
            Assert::IsTrue(&r == &a);
            Assert::AreEqual(2.0f, a.getValue());

            RealPub old = a++;
            Assert::AreEqual(2.0f, old.getValue());
            Assert::AreEqual(3.0f, a.getValue());

            --a;
            RealPub old2 = a--;
            Assert::AreEqual(2.0f, old2.getValue());
            Assert::AreEqual(1.0f, a.getValue());
        }

        TEST_METHOD(StringConversionAndDisplayInherited)
        {
            RealPub a(2);
            string s = a;                
            Assert::AreEqual(string("value = 2"), s);

            CoutCapture cap;
            a.Display();
            Assert::AreEqual(string("value = 2\n"), cap.str());
        }

        TEST_METHOD(InheritedIO)
        {
            RealPub a;
            istringstream in("4.5");
            {
                CoutCapture cap;
                in >> a;             
            }
            Assert::AreEqual(4.5f, a.getValue());

            ostringstream out;
            out << a;
            Assert::AreEqual(string("value = 4.5"), out.str());
        }

        TEST_METHOD(ArraysOfObjects)
        {
            RealPub arr[2] = { RealPub(4), RealPub(100) };
            Assert::AreEqual(4.0f, arr[0].getValue());
            Assert::AreEqual(100.0f, arr[1].getValue());

            RealPub* dyn = new RealPub[2]{ RealPub(9), RealPub(1) };
            Assert::AreEqual(9.0f, dyn[0].getValue());
            Assert::AreEqual(1.0f, dyn[1].getValue());
            delete[] dyn;
        }
    };

    TEST_CLASS(RealPrivTests)
    {
    public:
        TEST_METHOD(ConstructorsAndAccessors)
        {
            RealPriv a;
            Assert::AreEqual(0.0f, a.getValue());

            RealPriv b(2.5f);
            RealPriv c(b);
            Assert::AreEqual(2.5f, c.getValue());

            Number base(9);
            RealPriv d(base);
            Assert::AreEqual(9.0f, d.getValue());

            d.setValue(4);
            Assert::AreEqual(4.0f, d.getValue());
            d.Init(-1.5f);
            Assert::AreEqual(-1.5f, d.getValue());
            Assert::AreEqual(string("value = -1.5"), d.toString());
        }

        TEST_METHOD(SetterRejectsNonFinite)
        {
            RealPriv a(1);
            Assert::ExpectException<invalid_argument>([&] { a.setValue(INF); });
            Assert::ExpectException<invalid_argument>([&] { a.Init(NANF); });
            Assert::AreEqual(1.0f, a.getValue());
        }

        TEST_METHOD(PowAndLog)
        {
            RealPriv a(8);
            Assert::AreEqual(64.0f, a.pow(2).getValue(), EPS);
            Assert::AreEqual(0.125f, a.pow(-1).getValue(), EPS);
            Assert::AreEqual(2.0794415f, a.log().getValue(), EPS);
            Assert::AreEqual(3.0f, a.log(2).getValue(), EPS);
        }

        TEST_METHOD(PowAndLogErrors)
        {
            Assert::ExpectException<domain_error>([] { RealPriv(0).pow(-1); });
            Assert::ExpectException<domain_error>([] { RealPriv(-8).pow(0.5f); });
            Assert::ExpectException<overflow_error>([] { RealPriv(10).pow(1000); });
            Assert::ExpectException<domain_error>([] { RealPriv(0).log(); });
            Assert::ExpectException<domain_error>([] { RealPriv(8).log(1); });
        }

        TEST_METHOD(AddAndDiv)
        {
            RealPriv a(8), b(2);
            Assert::AreEqual(10.0f, (a + b).getValue(), EPS);
            Assert::AreEqual(4.0f, (a / b).getValue(), EPS);
            Assert::AreEqual(10.0f, a.add(b).getValue(), EPS);
            Assert::AreEqual(4.0f, a.div(b).getValue(), EPS);
        }

        TEST_METHOD(DivByZeroThrows)
        {
            RealPriv a(8), zero;
            Assert::ExpectException<domain_error>([&] { a / zero; });
            Assert::ExpectException<domain_error>([&] { a.div(zero); });
        }

        TEST_METHOD(AssignmentAndString)
        {
            RealPriv a(3), b;
            b = a;
            Assert::AreEqual(3.0f, b.getValue());
            string s = b;
            Assert::AreEqual(string("value = 3"), s);
        }

        TEST_METHOD(IncDecAllForms)
        {
            RealPriv a(1);
            ++a;
            Assert::AreEqual(2.0f, a.getValue());

            RealPriv old = a++;
            Assert::AreEqual(2.0f, old.getValue());
            Assert::AreEqual(3.0f, a.getValue());

            --a;
            RealPriv old2 = a--;
            Assert::AreEqual(2.0f, old2.getValue());
            Assert::AreEqual(1.0f, a.getValue());
        }

        TEST_METHOD(DisplayAndRead)
        {
            RealPriv a(2);
            {
                CoutCapture cap;
                a.Display();
                Assert::AreEqual(string("value = 2\n"), cap.str());
            }
            {
                CinFeed feed("6.5");
                CoutCapture cap;
                a.Read();
            }
            Assert::AreEqual(6.5f, a.getValue());
        }

        TEST_METHOD(OwnIO)
        {
            RealPriv p;
            istringstream in("-7");
            {
                CoutCapture cap;
                in >> p;
            }
            Assert::AreEqual(-7.0f, p.getValue());

            ostringstream out;
            out << p;
            Assert::AreEqual(string("value = -7"), out.str());
        }
    };

    TEST_CLASS(InheritanceTests)
    {
    public:
        TEST_METHOD(PublicConvertsToBases)
        {
            Assert::IsTrue((is_convertible<RealPub*, Number*>::value));
            Assert::IsTrue((is_convertible<RealPub&, Number&>::value));
            Assert::IsTrue((is_convertible<RealPub*, Object*>::value));
            Assert::IsTrue((is_convertible<Number*, Object*>::value));
        }

        TEST_METHOD(PrivateDoesNotConvertToBases)
        {
            Assert::IsFalse((is_convertible<RealPriv*, Number*>::value));
            Assert::IsFalse((is_convertible<RealPriv&, Number&>::value));
            Assert::IsFalse((is_convertible<RealPriv*, Object*>::value));
        }
    };

    TEST_CLASS(SizeTests)
    {
    public:
        TEST_METHOD(UnpackedSizes)
        {
            Assert::AreEqual(sizeof(float), sizeof(Number));
            Assert::AreEqual(sizeof(Number), sizeof(RealPub));
            Assert::AreEqual(sizeof(Number), sizeof(RealPriv));
        }

        TEST_METHOD(PackedSizes)
        {
            Assert::AreEqual(sizeof(Object), SizeObjectPacked());
            Assert::AreEqual(sizeof(float), SizeNumberPacked());
            Assert::AreEqual(SizeNumberPacked(), SizeRealPubPacked());
            Assert::AreEqual(SizeNumberPacked(), SizeRealPrivPacked());
        }
    };
}