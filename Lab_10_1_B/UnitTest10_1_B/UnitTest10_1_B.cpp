#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10_1_B/Lab_10_1_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101B
{
	TEST_CLASS(UnitTest101B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student p[3];
			p[0].spec = KOMP_NAUKY;   p[0].prohramuvannya = 5;
			p[1].spec = INFORMATYKA;  p[1].chyselni_metody = 5;   // не програмування!
			p[2].spec = KOMP_NAUKY;   p[2].prohramuvannya = 3;
			int k = CountProhramuvannyaMark(p, 3, 5);
			Assert::AreEqual(1, k);

		}
	};
}
