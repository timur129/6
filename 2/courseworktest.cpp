#include "pch.h"
#include "CppUnitTest.h"
#include "../semestr_project//Calc.h"
#include "../semestr_project/Calc.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace courseworktest
{
	TEST_CLASS(courseworktest)
	{
	public:
		calc* c;

		TEST_METHOD_INITIALIZE(co)
		{
			c = new calc();
		}

		TEST_METHOD_CLEANUP(cod)
		{
			delete c;
		}
		
		TEST_METHOD(perform)
		{
			c->push_back("1", 1.0);
			c->check_type(c->return_data());
			c->push_back("+", 0.0);
			c->check_type(c->return_data());
			c->push_back("2", 2.0);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 3.0);
		}

		TEST_METHOD(perform1)
		{
			c->push_back("3", 1.0);
			c->check_type(c->return_data());
			c->push_back("-", 0.0);
			c->check_type(c->return_data());
			c->push_back("2", 2.0);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 1.0);
		}

		TEST_METHOD(perform2)
		{
			c->push_back("10", 10.0);
			c->check_type(c->return_data());
			c->push_back("*", 0.0);
			c->check_type(c->return_data());
			c->push_back("2.2", 2.2);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 22.0);
		}

		TEST_METHOD(perform3)
		{
			c->push_back("10", 10.0);
			c->check_type(c->return_data());
			c->push_back("/", 0.0);
			c->check_type(c->return_data());
			c->push_back("2.5", 2.5);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 4.0);
		}

		TEST_METHOD(perform4)
		{
			c->push_back("sin", 0.0);
			c->check_type(c->return_data());
			c->push_back("0", 0);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 0.0);
		}

		TEST_METHOD(perform5)
		{
			c->push_back("cos", 0.0);
			c->check_type(c->return_data());
			c->push_back("pi", pi);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), -1.0);
		}

		TEST_METHOD(perform6)
		{
			c->push_back("ln", 0.0);
			c->check_type(c->return_data());
			c->push_back("eps", e);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 0.0);
		}

		TEST_METHOD(perform7)
		{
			c->push_back("lg", 0.0);
			c->check_type(c->return_data());
			c->push_back("10", 10.0);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 0.0);
		}

		TEST_METHOD(perform8)
		{
			c->push_back("lg", 0.0);
			c->check_type(c->return_data());
			c->push_back("10", 10.0);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 0.0);
		}

		TEST_METHOD(perform9)
		{
			c->push_back("sqrt", 0.0);
			c->check_type(c->return_data());
			c->push_back("4", 4.0);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 2.0);
		}

		TEST_METHOD(perform0)
		{
			c->push_back("cuber", 0.0);
			c->check_type(c->return_data());
			c->push_back("27", 27.0);
			c->check_type(c->return_data());
			c->inf_to_pref();
			Assert::AreEqual(c->count(), 3.0);
		}
	};
}