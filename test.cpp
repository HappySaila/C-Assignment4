#include<iostream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "src/Image.h"

using namespace WLSGRA012;
using namespace std;

TEST_CASE("Equality","[Equality]"){
    
	SECTION("Testing == Operator"){
		Image a;
		a << "Lenna_hat_mask.pgm";

		Image b;
		b << "Lenna_hat_mask.pgm";

		Image c;
		c << "Lenna_standard.pgm";

		REQUIRE(a==b);
		REQUIRE(!a==c);
		REQUIRE(!b==c);
		
	}
}

TEST_CASE("Load","[Load]"){
    
	SECTION("Testing << Operator"){
		Image a;
		a << "Lenna_hat_mask.pgm";

		Image b;
		b.Read("Lenna_hat_mask.pgm");

		REQUIRE(a==b);
	}
}

TEST_CASE("Save","[Save]"){
    
	SECTION("Testing >> Operator"){
		Image a;
		a.Read("Lenna_hat_mask.pgm");
		Image b;
		b.Read("Lenna_hat_mask.pgm");

		a >> "test1.pgm";
		b.Write("test2.pgm");

		Image c;
		c.Read("../CreatedImages/test1.pgm");
		Image d;
		d.Read("../CreatedImages/test2.pgm");

		REQUIRE(c==d);
		REQUIRE(c==a);
		REQUIRE(c==b);
		REQUIRE(d==a);
		REQUIRE(d==b);
	}
}

TEST_CASE("Iterators","[Iterators]"){
    
	SECTION("Testing Iterators"){
		Image a;
		a << "Lenna_hat_mask.pgm";
		Image b;
		b << "Lenna_hat_mask.pgm";

		//increase pixel data by 1 using iterators
		
		for(int i = 0; i < a.GetDimensions(); ++i) {
			int val = a.GetData().get()[i] + 1;
			val = (val > 255) ? 255 : (val < 0) ? 0 : val;
			a.GetData().get()[i] = val;
		}
		
		//increase pixel data by 1 using for loop

		Image::iterator beg = b.begin(), end = b.end();
		while (beg != end){
			int pixel = *beg+1;
			beg = pixel;
			++beg;
		}

		REQUIRE(a==b);
		
	}
}

TEST_CASE("Operators","[Operators]"){
    
	SECTION("Testing Operators"){
		Image a;
		a << "Lenna_standard.pgm";
		Image b;
		b << "Lenna_hat_mask.pgm";

		Image c;
		c = b-a;
		!c;


		Image d;
		d << "Lenna_standard.pgm";
		Image e;
		e << "Lenna_hat_mask.pgm";
		Image f;
		f = e / d;

		Image g;
		g = c - f;

		Image h;
		e << "Lenna_hat_mask.pgm";
		!e;

		REQUIRE(e==g);
		
	}
}

TEST_CASE("Copy operator","[Constructor]"){
    
	SECTION("Testing Constuctor Copy"){
		Image a;
		a << "Lenna_standard.pgm";

		Image b(a);

		REQUIRE(a==b);
	}
}


TEST_CASE("Constructor Copy Assignment","[Constructor]"){
	SECTION("Testing Constructor Copy Assignment"){
		Image a;
		a << "Lenna_standard.pgm";

		Image b = a;

		REQUIRE(a==b);
	}
}

