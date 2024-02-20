#pragma once
#include <Vector3.h>
#include <Matrix4x4.h>
#include <corecrt_math.h>


Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

// 内積
float Dot(const Vector3& v1, const Vector3& v2);

// 長さ(ノルム)
float Length(const Vector3& v);

// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);
Matrix4x4 Multiply44(const Matrix4x4& matrix, const Matrix4x4& matrixa);

// 1.X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
// 2.Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);
// 3.Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

//アフィン変換行列の作成
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// 正規化
Vector3 Normalize(const Vector3& v);

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 3.ビューポート変換行列
Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);

// 座標変還
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// プロトタイプ宣言
void Add(Vector3& v1, Vector3& v2);
Vector3 Add(const Vector3& v1, const Vector3& v2);

//Vector引き算
Vector3 SubtractionV3(const Vector3& v1, const Vector3& v2);
