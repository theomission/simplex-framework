#include <Simplex/Testing.h>
#include <Simplex/Support/TypeDefs.h>

// SIMD
TEST ( SimplexSupportTypeDefs, VF32SizeIs16Bytes )
{
  VF32 number;
  ASSERT_EQ ( 16, sizeof(number) );
}

// Floats
TEST ( SimplexSupportTypeDefs, F32SizeIs4Bytes )
{
  F32 number = 0.1;
  ASSERT_EQ ( 4, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, F32IsFloat )
{
  F32 number = 0.55;
  ASSERT_LT ( 0.55 - number, 0.000001 );
}

TEST ( SimplexSupportTypeDefs, F64SizeIs8Bytes )
{
  F64 number = 0.1;
  ASSERT_EQ ( 8, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, F64IsFloat )
{
  F64 number = 0.55;
  ASSERT_LT ( 0.55 - number, 0.000001 );
}

// Signed ints
TEST ( SimplexSupportTypeDefs, I8SizeIs1Byte )
{
  I8 number = 0;
  ASSERT_EQ ( 1, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, I8IsSigned )
{
  I8 number = -1;
  ASSERT_EQ ( -1, number );
}

TEST ( SimplexSupportTypeDefs, I16SizeIs2Bytes )
{
  I16 number = 0;
  ASSERT_EQ ( 2, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, I16IsSigned )
{
  I16 number = -1;
  ASSERT_EQ ( -1, number );
}

TEST ( SimplexSupportTypeDefs, I32SizeIs4Bytes )
{
  I32 number = 0;
  ASSERT_EQ ( 4, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, U32IsSigned )
{
  I32 number = -1;
  ASSERT_EQ ( -1, number );
}

TEST ( SimplexSupportTypeDefs, I64SizeIs8Bytes )
{
  I64 number = 0;
  ASSERT_EQ ( 8, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, I64IsSigned )
{
  I64 number = -1;
  ASSERT_EQ ( -1, number );
}

// Unsigned ints
TEST ( SimplexSupportTypeDefs, U8SizeIs1Byte )
{
  U8 number = 0;
  ASSERT_EQ ( 1, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, U8IsUnsigned )
{
  U8 number = -1;
  ASSERT_EQ ( 255, number );
}

TEST ( SimplexSupportTypeDefs, U16SizeIs2Bytes )
{
  U16 number = 0;
  ASSERT_EQ ( 2, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, U16IsUnsigned )
{
  U16 number = -1;
  ASSERT_EQ ( 65535, number );
}

TEST ( SimplexSupportTypeDefs, U32SizeIs4Bytes )
{
  U32 number = 0;
  ASSERT_EQ ( 4, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, U32IsUnsigned )
{
  U32 number = -1;
  ASSERT_EQ ( 4294967295, number );
}

TEST ( SimplexSupportTypeDefs, U64SizeIs8Bytes )
{
  U64 number = 0;
  ASSERT_EQ ( 8, sizeof(number) );
}

TEST ( SimplexSupportTypeDefs, U64IsUnsigned )
{
  U64 number = -1;
  ASSERT_EQ ( 18446744073709551615u, number );
}

