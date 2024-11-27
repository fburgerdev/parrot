#pragma once
#include "matrix.hh"

namespace Parrot {
	// translate
	template<typename T>
	Mat4x4<T> translate(const Mat4x4<T>& target, const Vec3<T> vec) {
		Mat4x4<T> out(target);
		out.at(0, 3) += vec.x;
		out.at(1, 3) += vec.y;
		out.at(2, 3) += vec.z;
		return out;
	}
	// scale
	template<typename T>
	Mat4x4<T> scale(const Mat4x4<T>& target, const Vec3<T>& vec) {
		Mat4x4<T> out(target);
		out.at(0, 0) *= vec.x;
		out.at(0, 1) *= vec.x;
		out.at(0, 2) *= vec.x;
		out.at(1, 0) *= vec.y;
		out.at(1, 1) *= vec.y;
		out.at(1, 2) *= vec.y;
		out.at(2, 0) *= vec.z;
		out.at(2, 1) *= vec.z;
		out.at(2, 2) *= vec.z;
		return out;
	}
	// rotate (euler)
	template<typename T>
	Mat4x4<T> rotate(const Mat4x4<T>& target, const Vec3<T>& vec) {
		Mat4x4<T> rot = zeros<T, 4>();
		T sina = std::sin(rot.y);
		T cosa = std::cos(rot.y);
		T sinb = std::sin(rot.x);
		T cosb = std::cos(rot.x);
		T sinc = std::sin(rot.z);
		T cosc = std::cos(rot.z);

		// row 1
		rot.at(0, 0) = cosa * cosc + sina * sinc * sinb;
		rot.at(0, 1) = cosa * sinc - sina * sinb * cosc;
		rot.at(0, 2) = sina * cosb;
		// row 2
		rot.at(1, 0) = -sinc * cosb;
		rot.at(1, 1) = cosb * cosc;
		rot.at(1, 2) = sinb;
		// row 3
		rot.at(2, 0) = -sina * cosc + cosa * sinc * sinb;
		rot.at(2, 1) = -sina * sinc - cosa * sinb * cosc;
		rot.at(2, 2) = cosa * cosb;
		// row 4
		rot.at(3, 3) = 1;
		return rot * target;
	}

	// ViewMatrix
	template<typename T>
    Mat4x4<T> ViewMatrix(const Vec3<T>& position, const Vec3<T>& rotation) {
        Mat4x4<T> rot_mat = transposed(rotation_matrix(transform.rot));
        Mat4x4<T> trans_mat = translation_matrix(-transform.pos);
        return transposed(rotate(translate(identity<T, 4>(), -position), rotation));
    }
	// PerspectiveMatrix
	template<typename T>
    Mat4x4<T> PerspectiveMatrix(T fov, Vec2<T> z_range, T aspect_ratio) {
        Mat4x4<T> proj_mat = zeros<T, 4>();
		// scale
        T tan_fov = 1.0f / std::tan(fov / 2);
		proj_mat.at(0, 0) = tan_fov;
        proj_mat.at(1, 1) = tan_fov * aspect_ratio;
        // clip z to [0, 1]
		/*
        proj_mat.at(2, 2) = z_range.y / (z_range.y - z_range.x);
        proj_mat.at(2, 3) = -z_range.x * z_range.y / (z_range.y - z_range.x);
		*/
		// clip z to [-1, 1] (for OpenGL)
        proj_mat.at(2, 2) = 2 * z_range.y / (z_range.y - z_range.x) - 1;
        proj_mat.at(2, 3) = -2 * z_range.x * z_range.y / (z_range.y - z_range.x);
		// forward z
        proj_mat.at(3, 2) = 1;
        return proj_mat;
    }
	// OrthographicMatrix
	template<typename T>
    Mat4x4<T> OrthographicMatrix(T scale, Vec2<T> z_range, T aspect_ratio) {
        Mat4x4<T> proj_mat = zeros<T, 4>();
		// scale
        proj_mat.at(0, 0) = 1 / scale;
        proj_mat.at(1, 1) = aspect_ratio / scale;
        // clip z to [0, 1]
		/*
        proj_mat.at(2, 2) = 1 / (z_range.y - z_range.x);
        proj_mat.at(2, 3) = -z_range.x / (z_range.y - z_range.x);
		*/
		// clip z to [-1, 1] (for OpenGL)
        proj_mat.at(2, 2) = 2 / (z_range.y - z_range.x);
        proj_mat.at(2, 3) = -2 * z_range.x / (z_range.y - z_range.x) - 1;
		// forward z
        proj_mat.at(3, 3) = 1;
        return proj_mat;
    }
 //  // ViewProjectionMatrix
 //	 template<typename T>
 //  Mat4x4<T> ViewProjectionMatrix(const SceneObject& camera_obj, T aspect_ratio) {
 //      Mat4x4<T> proj_mat = zeros<T, 4>();
 //      const Camera& camera = camera_obj.get_camera();
 //      if (camera.mode == CameraMode::Perspective) {
 //          proj_mat = create_perspective_projection_matrix(camera.perspective.fov, camera.perspective.z_range, aspect_ratio);
 //      }
 //      else if (camera.mode == CameraMode::Orthographic) {
 //          proj_mat = create_orthographic_projection_matrix(camera.orthographic.scale, camera.orthographic.z_range, aspect_ratio);
 //      }
 //      return proj_mat * create_view_matrix(camera_obj.transform);
 //  }
 //	 template<typename T>
 //  void projection3D_scene_obj_draw_prepare(const Scene& scene, const SceneObject& scene_obj, Material& material) {
 //      T aspect_ratio = 1.5f;
 //      material.set_mat4f("u_mvp", create_view_projection_matrix(scene.get_main_camera(), aspect_ratio) * transformation_matrix(scene_obj.transform));
 //      material.set_mat4f("u_rot", rotation_matrix(scene_obj.transform.rot));
 //  }
}