#include "../controller/controller.h"
#include <gtest/gtest.h>

TEST(Model, Test1) {
	FILE *fp = fopen("../obj/test.obj", "rb");

	s21::Controller control;
	control.OpenModel(fp);

	EXPECT_EQ(control.GetVertex().size(), 9);
	EXPECT_EQ(control.GetFacets().size(), 12);

	int f[6] = {0, 1, 1, 2, 0, 2};
	for (size_t j = 0; j < control.GetFacets().size()/2; ++j) {
		EXPECT_EQ(control.GetFacets()[j], f[j]);
	}

	double v[9] = {0, 1, -1, 1, 0, -1, 1, 1, 1};
	for (size_t j = 0; j < control.GetVertex().size(); ++j) {
		EXPECT_EQ(control.GetVertex()[j], v[j]);
	}

	int n = control.GetVertex().size();
	
	control.ChangeModelScale(s21::ChangeModel::kScale, 3);
	double s[9] = {0, 3, -3, 3, 0, -3, 3, 3, 3};
	for (int k = 0; k < n; ++k) {
		EXPECT_EQ(control.GetVertex()[k], s[k]);
	}

	control.ChangeModelParams(s21::ChangeModel::kMoveX, 3);
	double mx[9] = {3, 3, -3, 6, 0, -3, 6, 3, 3};
	for (int k = 0; k < n; ++k) {
		EXPECT_EQ(control.GetVertex()[k], mx[k]);
	}

	control.ChangeModelParams(s21::ChangeModel::kMoveY, 3);
	double my[9] = {3, 6, -3, 6, 3, -3, 6, 6, 3};
	for (int k = 0; k < n; ++k) {
		EXPECT_EQ(control.GetVertex()[k], my[k]);
	}

	control.ChangeModelParams(s21::ChangeModel::kMoveZ, 1);
	double mz[9] = {3, 6, -2, 6, 3, -2, 6, 6, 4};
	for (int k = 0; k < n; ++k) {
		EXPECT_EQ(control.GetVertex()[k], mz[k]);
	}

	control.ChangeModelAngle(s21::ChangeModel::kRotateX, 1);
	double rx[9] = {3.000000, 4.924756, 3.968221,  6.000000, 3.303849,
					1.443808, 6.000000, -0.124070, 7.210035};
	for (int k = 0; k < n; ++k) {
		EXPECT_EQ(control.GetVertex()[k] - rx[k] < 1e-6, true);
	}

	control.ChangeModelAngle(s21::ChangeModel::kRotateY, 1);
	double ry[9] = {-1.718236, 4.924756, 4.668452, 2.026891, 3.303849,
					5.828919, -2.825222, -0.124070, 8.944425};
	for (int k = 0; k < n; ++k) {
		EXPECT_EQ(control.GetVertex()[k] - ry[k] < 1e-6, true);
	}

	control.ChangeModelAngle(s21::ChangeModel::kRotateZ, 1);
	double rz[9] = {-5.072406, 1.215011, 4.668452, -1.684959, 3.490647,
					5.828919, -1.422072, -2.444377, 8.944425};
	for (int k = 0; k < n; ++k) {
		EXPECT_EQ(control.GetVertex()[k] - rz[k] < 1e-6, true);
	}
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

