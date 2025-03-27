#include <gtest/gtest.h>
#include "utils/math_matrix.hh"
using namespace Parrot;

// MatTest
template<class T>
class MatTest : public testing::Test {
public:
	// (constructor)
	using testing::Test::Test;
};
// :: types
using MatTypes = ::testing::Types<
	// int
	Mat<int, 3, 3>,
	// uint
	Mat<uint, 3, 3>,
	// float
	Mat<float, 1, 1>,
	Mat<float, 1, 2>, Mat<float, 2, 1>, Mat<float, 2, 2>,
	Mat<float, 2, 3>, Mat<float, 3, 2>, Mat<float, 3, 3>,
	Mat<float, 3, 4>, Mat<float, 4, 3>, Mat<float, 4, 4>,
	Mat<float, 4, 10>, Mat<float, 10, 4>, Mat<float, 10, 10>,
	// double
	Mat<double, 3, 3>
>;
TYPED_TEST_SUITE(MatTest, MatTypes);

// VecTest
template<class T>
class VecTest : public testing::Test {
public:
	// (constructor)
	using testing::Test::Test;
};
// VecTypes
using VecTypes = ::testing::Types<
	// int
	Mat<int, 3, 1>,
	// uint
	Mat<uint, 3, 1>,
	// float
	Mat<float, 1, 1>,
	Mat<float, 2, 1>, Mat<float, 3, 1>, Mat<float, 4, 1>,
	Mat<float, 10, 1>,
	// double
	Mat<double, 3, 1>
>;
TYPED_TEST_SUITE(VecTest, VecTypes);

// at
TYPED_TEST(MatTest, at) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			mat.at(COLS * row + col) = COLS * row + col;
		}
	}
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			EXPECT_EQ(mat.at(COLS * row + col), COLS * row + col);
			EXPECT_EQ(mat.at(COLS * row + col), mat.at(row, col));
		}
	}
}

// zeros
TYPED_TEST(MatTest, zeros) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat = zeros<TypeParam::Type, ROWS, COLS>();
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(mat.at(i), 0);
	}
}
// identity
TYPED_TEST(MatTest, identity) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	if constexpr (ROWS == COLS) {
		TypeParam mat = identity<TypeParam::Type, ROWS>();
		for (int row = 0; row < ROWS; ++row) {
			for (int col = 0; col < COLS; ++col) {
				EXPECT_EQ(mat.at(row, col), int(row == col));
			}
		}
	}
	TypeParam mat = zeros<TypeParam::Type, ROWS, COLS>();
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(mat.at(i), 0);
	}
}

// operatorUnaryMinus
TYPED_TEST(MatTest, operatorUnaryMinus) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat.at(i) = i;
	}
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ((-mat).at(i), -mat.at(i));
	}
}
// operatorAssignAdd
TYPED_TEST(MatTest, operatorAssignAdd) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat1;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat1.at(i) = i;
	}
	TypeParam mat2;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat2.at(i) = 999 * i;
	}
	mat1 += mat2;
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(mat1.at(i), 1000 * i);
	}
}
// operatorAssignSub
TYPED_TEST(MatTest, operatorAssignSub) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat1;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat1.at(i) = 1001 * i;
	}
	TypeParam mat2;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat2.at(i) = i;
	}
	mat1 -= mat2;
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(mat1.at(i), 1000 * i);
	}
}
// operatorAssignMul
TYPED_TEST(MatTest, operatorAssignMul) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat.at(i) = i;
	}
	mat *= TypeParam::Type(1000);
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(mat.at(i), 1000 * i);
	}
}
// operatorAssignDiv
TYPED_TEST(MatTest, operatorAssignDiv) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat.at(i) = 10 * i;
	}
	mat /= TypeParam::Type(10);
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(mat.at(i), i);
	}
}

// operatorAdd
TYPED_TEST(MatTest, operatorAdd) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat1;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat1.at(i) = i;
	}
	TypeParam mat2;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat2.at(i) = 999 * i;
	}
	TypeParam result = mat1 + mat2;
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(result.at(i), 1000 * i);
	}
}
// operatorSub
TYPED_TEST(MatTest, operatorSub) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat1;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat1.at(i) = 1001 * i;
	}
	TypeParam mat2;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat2.at(i) = i;
	}
	TypeParam result = mat1 - mat2;
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(result.at(i), 1000 * i);
	}
}
// operatorMul
TYPED_TEST(MatTest, operatorMul) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat.at(i) = i;
	}
	TypeParam result = mat * TypeParam::Type(1000);
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(result.at(i), 1000 * i);
	}
}
// operatorDiv
TYPED_TEST(MatTest, operatorDiv) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat.at(i) = 10 * i;
	}
	TypeParam result = mat / TypeParam::Type(10);
	for (int i = 0; i < ROWS * COLS; ++i) {
		EXPECT_EQ(result.at(i), i);
	}
}

//TODO: improve matrix multiplication tests
// operatorMatrixMul
TYPED_TEST(MatTest, operatorMatrixMul) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	Mat<TypeParam::Type, ROWS, COLS> mat1;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat1.at(i) = (((i % COLS) % 2) ? i : 0);
	}
	Mat<TypeParam::Type, COLS, ROWS> mat2;
	for (int i = 0; i < COLS * ROWS; ++i) {
		mat2.at(i) = (((i / ROWS) % 2) ? 0 : i);
	}
	auto result = mat1 * mat2;
	for (int i = 0; i < ROWS * ROWS; ++i) {
		EXPECT_EQ(result.at(i), 0);
	}
}
// operatorMatrixAssignMul
TYPED_TEST(MatTest, operatorMatrixAssignMul) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	if constexpr (ROWS == COLS) {
		Mat<TypeParam::Type, ROWS, COLS> mat1;
		for (int i = 0; i < ROWS * COLS; ++i) {
			mat1.at(i) = (((i % COLS) % 2) ? i : 0);
		}
		Mat<TypeParam::Type, COLS, ROWS> mat2;
		for (int i = 0; i < COLS * ROWS; ++i) {
			mat2.at(i) = (((i / ROWS) % 2) ? 0 : i);
		}
		mat1 *= mat2;
		for (int i = 0; i < ROWS * ROWS; ++i) {
			EXPECT_EQ(mat1.at(i), 0);
		}
	}
}

// dot
TYPED_TEST(VecTest, dot) {
	static constexpr int N = TypeParam::ROWS;
	TypeParam vec1, vec2;
	typename TypeParam::Type expected = 0;
	for (int i = 0; i < N; ++i) {
		vec1.at(i) = i;
		vec2.at(i) = i * 1000;
		expected += i * i * 1000;
	}
	EXPECT_EQ(dot(vec1, vec2), dot(vec2, vec1));
	typename TypeParam::Type result = dot(vec1, vec2);
	EXPECT_EQ(result, expected);
}
// cross
TYPED_TEST(VecTest, cross) {
	static constexpr int N = TypeParam::ROWS;
	if constexpr (N == 3) {
		TypeParam forward = TypeParam(0, 0, 1);
		TypeParam right = TypeParam(1, 0, 0);
		TypeParam up = TypeParam(0, 1, 0);
		EXPECT_EQ(cross(right, forward), up);
		EXPECT_EQ(cross(forward, right), -up);
		EXPECT_EQ(cross(up, right), forward);
		EXPECT_EQ(cross(right, up), -forward);
		EXPECT_EQ(cross(forward, up), right);
		EXPECT_EQ(cross(up, forward), -right);
		static constexpr typename TypeParam::Type TWO = 2, THREE = 3, SIX = 6;
		EXPECT_EQ(cross(right * TWO, forward * THREE), up * SIX);
	}
}
// magnitude
TYPED_TEST(VecTest, magnitude) {
	static constexpr int N = TypeParam::ROWS;
	if constexpr (std::is_floating_point_v<typename TypeParam::Type>) {
		TypeParam vec;
		typename TypeParam::Type expected = 0;
		for (int i = 0; i < N; ++i) {
			vec.at(i) = i;
			expected += i * i;
		}
		typename TypeParam::Type result = magnitude(vec);
		EXPECT_FLOAT_EQ(result * result, expected);
	}
}
// length
TYPED_TEST(VecTest, length) {
	static constexpr int N = TypeParam::ROWS;
	if constexpr (std::is_floating_point_v<typename TypeParam::Type>) {
		TypeParam vec;
		for (int i = 0; i < N; ++i) {
			vec.at(i) = i;
		}
		EXPECT_FLOAT_EQ(length(vec), magnitude(vec));
	}
}
// dist
TYPED_TEST(VecTest, dist) {
	static constexpr int N = TypeParam::ROWS;
	if constexpr (std::is_floating_point_v<typename TypeParam::Type>) {
		TypeParam vec1, vec2;
		for (int i = 0; i < N; ++i) {
			vec1.at(i) = i;
			vec2.at(i) = i * 1000;
		}
		typename TypeParam::Type result = dist(vec1, vec2);
		EXPECT_FLOAT_EQ(result, length(vec2 - vec1));
	}
}

// normalize(d)
TYPED_TEST(MatTest, normalize) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	if constexpr (std::is_floating_point_v<typename TypeParam::Type>) {
		TypeParam mat;
		for (int i = 0; i < ROWS * COLS; ++i) {
			mat.at(i) = i + 1;
		}
		TypeParam& mat_ref = normalize(mat);
		EXPECT_EQ(&mat_ref, &mat);
		EXPECT_FLOAT_EQ(length(mat), 1);
	}
}
TYPED_TEST(MatTest, normalized) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	if constexpr (std::is_floating_point_v<typename TypeParam::Type>) {
		TypeParam mat;
		for (int i = 0; i < ROWS * COLS; ++i) {
			mat.at(i) = i + 1;
		}
		EXPECT_FLOAT_EQ(length(normalized(mat)), 1);
	}
}

// transpose(d)
TYPED_TEST(MatTest, transpose) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	if constexpr (ROWS == COLS) {
		TypeParam mat;
		for (int i = 0; i < ROWS * COLS; ++i) {
			mat.at(i) = i;
		}
		TypeParam& mat_ref = transpose(transpose(mat));
		EXPECT_EQ(&mat_ref, &mat);
		for (int i = 0; i < ROWS * COLS; ++i) {
			EXPECT_EQ(mat.at(i), i);
		}
	}
}
TYPED_TEST(MatTest, transposed) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat.at(i) = i;
	}
	EXPECT_EQ(transposed(transposed(mat)), mat);
}

// insert
TYPED_TEST(MatTest, insert) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	if constexpr (ROWS >= 2 && COLS >= 2) {
		TypeParam mat;
		for (int i = 0; i < ROWS * COLS; ++i) {
			mat.at(i) = i;
		}

		Mat2x2<typename TypeParam::Type> to_insert;
		to_insert.at(0, 0) = 1000;
		to_insert.at(0, 1) = 2000;
		to_insert.at(1, 0) = 3000;
		to_insert.at(1, 1) = 4000;

		// bottom-right
		TypeParam& mat_ref = insert(mat, to_insert, { ROWS - 2, COLS - 2 });
		EXPECT_EQ(&mat_ref, &mat);
		for (int i = 0; i < ROWS * COLS; ++i) {
			if (i == COLS * (ROWS - 2) + (COLS - 2)) {
				EXPECT_EQ(mat.at(i), 1000);
			}
			else if (i == COLS * (ROWS - 2) + (COLS - 1)) {
				EXPECT_EQ(mat.at(i), 2000);
			}
			else if (i == COLS * (ROWS - 1) + (COLS - 2)) {
				EXPECT_EQ(mat.at(i), 3000);
			}
			else if (i == COLS * (ROWS - 1) + (COLS - 1)) {
				EXPECT_EQ(mat.at(i), 4000);
			}
			else {
				EXPECT_EQ(mat.at(i), i);
			}
		}
	}
}
// resize
TYPED_TEST(MatTest, resize) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat.at(i) = i + 1;
	}
	auto result = resize<ROWS + 1, COLS + 2>(mat, { 1, 2 });
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			EXPECT_EQ(result.at(row + 1, col + 2), (COLS * row + col) + 1);
		}
	}
	for (int row = 0; row < ROWS + 1; ++row) {
		EXPECT_EQ(result.at(row, 0), 0);
		EXPECT_EQ(result.at(row, 1), 0);
	}
	for (int col = 0; col < COLS + 2; ++col) {
		EXPECT_EQ(result.at(0, col), 0);
	}
}

// << (stream)
TYPED_TEST(MatTest, operatorStream) {
	static constexpr int ROWS = TypeParam::ROWS, COLS = TypeParam::COLS;
	TypeParam mat;
	for (int i = 0; i < ROWS * COLS; ++i) {
		mat.at(i) = i;
	}
	strstream stream;
	stream << mat;
	string str = stream.str();
	usize number_begin = 0;
	for (int i = 0; i < ROWS * COLS; ++i) {
		while (number_begin < str.size() && !std::isdigit(str[number_begin])) {
			++number_begin;
		}
		if (number_begin == str.size()) {
			FAIL();
		}
		usize number_end = number_begin;
		while (number_end < str.size() && std::isdigit(str[number_end])) {
			++number_end;
		}
		usize number_length = number_end - number_begin;
		EXPECT_EQ(str.substr(number_begin, number_length), std::to_string(i));
		number_begin = number_end;
	}
}