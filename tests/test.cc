#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../float16_t.hpp"
#include <cmath>
#include <iostream>
#include <bitset>
#include <limits>

void print( float x )
{
    using numeric::float16_t_private::float32_to_float16;
    using numeric::float16_t_private::float16_to_float32;

    auto f16 = float32_to_float16( x );
    std::cout << x << " => " << f16 << std::endl;

    auto f32 = float16_to_float32( f16.bits_ );
    std::cout << "f32 => " << f32 << std::endl;

    //_Float16 _f16 = x;
    //float _x = _f16 * 1.0f;
    //std::cout << _x << std::endl;

    std::cout << "****************************" << std::endl;
}

TEST_CASE( "32_2_16", "[32_2_16]" )
{
    print( 0.000000059604645 );
    print( 0.000000059604647 );
    print( 0.0 );
    print( -0.000000059604645 );
    print( -0.000000059604644 );
    print( 0.000060975552f  );
    print( -0.000060975552f  );

    print( 0.00006103515625  );
    print( -0.00006103515625  );

    print( 65504.0f  );
    print( -65504.0f  );
    print( 65505.0f  );
    print( -65505.0f  );

    print( 0.999511720f  );
    print( -0.999511720f  );

    print( 1.0f  );
    print( -1.0f  );

    print(  1.00097656f  );
    print(  -1.00097656f  );

    print( std::numeric_limits<float>::infinity() );
    print( std::numeric_limits<float>::quiet_NaN() );

    print( 16504.0f  );
    print( -16204.0f  );

    for ( float x = -1.0f; x <= 1.0f; x+= 0.013 )
    {
        numeric::float16_t f{x};
        std::cout << x << " : " << f << std::endl;
    }
}

TEST_CASE( "f1", "[f1]" )
{
    float const mx = 10.0;
    float const interval = mx / 1000.0;
    float x = -mx;
    for ( ; x < mx; x += interval )
    {
        numeric::float16_t const f_{ x };
        float const x_ = float( f_ );
        REQUIRE( std::abs(x- x_) < 0.01f );
    }
}

TEST_CASE( "constant", "[constant]" )
{
    using namespace numeric;

    //std::cout << "fp16_epsilon:\t" << fp16_epsilon << std::endl;
    std::cout << "fp16_infinity:\t" << fp16_infinity << std::endl;
    std::cout << "fp16_max:\t" << fp16_max << std::endl;
    std::cout << "fp16_max_subnormal:\t" << fp16_max_subnormal << std::endl;
    std::cout << "fp16_min:\t" << fp16_min << std::endl;
    std::cout << "fp16_min_positive:\t" << fp16_min_positive << std::endl;
    std::cout << "fp16_min_positive_subnormal:\t" << fp16_min_positive_subnormal << std::endl;
    std::cout << "fp16_nan:\t" << fp16_nan << std::endl;
    std::cout << "fp16_infinity_negative:\t" << fp16_infinity_negative << std::endl;

    std::cout << "fp16_one:\t" << fp16_one << std::endl;
    std::cout << "fp16_zero:\t" << fp16_zero << std::endl;
    std::cout << "fp16_zero_negative:\t" << fp16_zero_negative << std::endl;
    std::cout << "fp16_e:\t" << fp16_e << std::endl;
    std::cout << "fp16_pi:\t" << fp16_pi << std::endl;

    std::cout << "E:\t" <<  float16_t{2.71828182845904523536f} << std::endl;
    std::cout << "PI:\t" <<  float16_t{3.141592653589f} << std::endl;
    std::cout << "NAN:\t" <<  float16_t{std::numeric_limits<float>::quiet_NaN()} << std::endl;
}

TEST_CASE( "neg", "[neg]" )
{
    auto one = numeric::fp16_one;
    std::cout << "one:\t" << one << std::endl;
    std::cout << "neg one:\t" << -one << std::endl;
    for ( float x = -1.0f; x < 1.0f; x += 0.023 )
    {
        numeric::float16_t x_ = x;
        std::cout << x_ << ":\t" << -x_ << std::endl;
    }
}

TEST_CASE( "pos", "[pos]" )
{
    for ( float x = -1.0f; x < 1.0f; x += 0.023 )
    {
        numeric::float16_t x_ = x;
        std::cout << x_ << ":\t" << +x_ << std::endl;
    }
}

TEST_CASE( "example", "[example]" )
{
    using numeric::float16_t;

    float16_t f = 1.1f;
    {
        std::cout << "f =" << f << std::endl;
        std::cout << "float(f) =" << float(f) << std::endl;
        std::cout << "f++ =" << f++ << std::endl;
        std::cout << "++f =" << ++f << std::endl;
        std::cout << "f-- =" << f-- << std::endl;
        std::cout << "--f =" << --f << std::endl;
    }
    std::cout << "********" << std::endl;


    float16_t g = -1.3f;
    {
        std::cout << "f+g = " << f+g << std::endl;
        std::cout << "f-g = " << f-g << std::endl;
        std::cout << "f*g = " << f*g << std::endl;
        std::cout << "f/g = " << f/g << std::endl;
    }
    std::cout << "********" << std::endl;

    float16_t h = 0.27f;
    {
        std::cout << "numeric::sin(h) = " << numeric::sin(h) << std::endl;
        std::cout << "numeric::cos(h) = " << numeric::cos(h) << std::endl;
        std::cout << "numeric::sqrt(h) = " << numeric::sqrt(h) << std::endl;
        std::cout << "numeric::cbrt(h) = " << numeric::cbrt(h) << std::endl;
    }
    std::cout << "********" << std::endl;

}

TEST_CASE( "constant2", "[constant2]" )
{
    using numeric::float16_t;
    {
        float16_t h = 0.5f;
        std::cout << "f16(0.5) = " << h << std::endl;
        h = -0.5f;
        std::cout << "f16(-0.5) = " << h << std::endl;
        h = -1.0f;
        std::cout << "f16(-1) = " << h << std::endl;
        h = 1.0f;
        std::cout << "f16(1) = " << h << std::endl;
        h = 2.0f;
        std::cout << "f16(2) = " << h << std::endl;
        h = -2.0f;
        std::cout << "f16(-2) = " << h << std::endl;
    }
    {
        float16_t h = 1.0f;
        std::uint16_t v = h;
        std::cout << h << " - " << v << std::endl;
        std::cout << float16_t(static_cast<std::uint16_t>(v+1)) << " - " << v+1 << std::endl;
        float16_t h1 =  float16_t(static_cast<std::uint16_t>(v+1));
        float diff = float(h1) - float(h);
        std::cout << "EPS: " << diff << " - " << float16_t{diff} << std::endl;
    }
    std::cout << "\n";
    {
        float16_t h = numeric::fp16_min_positive;
        float f = h;
        std::cout << "fp16_min: " << std::scientific << f << std::endl;
        std::cout << "fp16_min at hexfloat: " << std::hexfloat << f << std::endl;
    }
    std::cout << "\n";
    {
        float16_t h = numeric::fp16_max;
        float f = h;
        std::cout << "fp16_max: " << std::scientific << f << std::endl;
        std::cout << "fp16_max at hexfloat: " << std::hexfloat << f << std::endl;
    }

    std::cout << "\n";
    {
        std::cout
        << std::numeric_limits<float16_t>::lowest() << '\t'
        << std::numeric_limits<float16_t>::min() << '\t'
        << std::numeric_limits<float16_t>::max() << '\n';
    }
}

TEST_CASE( "fmin_correctness", "[fmin]" )
{
    using numeric::float16_t;
    using numeric::fmin;

    CHECK( fmin( float16_t{1.0f}, float16_t{2.0f} ) == float16_t{1.0f} );
    CHECK( fmin( float16_t{-3.0f}, float16_t{-2.0f} ) == float16_t{-3.0f} );
}

TEST_CASE( "constant_encodings", "[constants]" )
{
    using namespace numeric;
    CHECK( static_cast<std::uint16_t>( fp16_one_negative ) == 0xbc00 );
    CHECK( static_cast<std::uint16_t>( fp16_half_negative ) == 0xb800 );
    CHECK( float( fp16_one_negative ) == Catch::Detail::Approx( -1.0f ) );
    CHECK( float( fp16_half_negative ) == Catch::Detail::Approx( -0.5f ) );
}

TEST_CASE( "classification", "[classify]" )
{
    using namespace numeric;

    CHECK( is_nan( fp16_nan ) );
    CHECK_FALSE( is_finite( fp16_nan ) );
    CHECK_FALSE( is_inf( fp16_nan ) );

    CHECK( is_inf( fp16_infinity ) );
    CHECK( is_inf( fp16_infinity_negative ) );
    CHECK_FALSE( is_finite( fp16_infinity ) );

    CHECK( is_finite( fp16_zero ) );
    CHECK( is_finite( fp16_zero_negative ) );
    CHECK_FALSE( is_normal( fp16_min_positive_subnormal ) );
    CHECK( is_normal( fp16_min_positive ) );
}

TEST_CASE( "comparisons_follow_ieee", "[compare]" )
{
    using namespace numeric;

    float16_t pos_zero = fp16_zero;
    float16_t neg_zero = fp16_zero_negative;
    CHECK( pos_zero == neg_zero );
    CHECK_FALSE( pos_zero < neg_zero );
    CHECK_FALSE( neg_zero < pos_zero );
    CHECK_FALSE( std::signbit( float( pos_zero ) ) );
    CHECK( std::signbit( float( neg_zero ) ) );

    // cancellation should produce +0 with correct classification
    float16_t one = fp16_one;
    float16_t minus_one = fp16_one_negative;
    auto sum = one + minus_one;
    CHECK( sum == fp16_zero );
    CHECK_FALSE( std::signbit( float( sum ) ) );
    CHECK( is_finite( sum ) );

    float16_t nan = fp16_nan;
    float16_t another_one = fp16_one;
    CHECK_FALSE( nan == nan );
    CHECK( nan != nan );
    CHECK_FALSE( nan < another_one );
    CHECK_FALSE( another_one < nan );
    CHECK_FALSE( nan > another_one );
    CHECK_FALSE( another_one > nan );
}
