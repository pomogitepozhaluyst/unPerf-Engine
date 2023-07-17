#include <cmath>
#include <iostream>

#define Vec4 Quaternion

float pi = 3.14f;
float rad = 3.14f/180.0f;
class Vec2 {
public:
  float x;
  float y;

  Vec2() = default;

  Vec2(float x1, float y1) {
    x = x1;
    y = y1;
  }
  float Length() { return sqrtf(pow(x, 2) + pow(y, 2)); }

  Vec2 Normalize() {
      float length = Length();
      return Vec2(x / length, y / length);
  }
  Vec2 operator+(Vec2 other) const { return Vec2(x + other.x, y + other.y); }

  Vec2 &operator+=(Vec2 other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 operator-(Vec2 other) const { return Vec2(x - other.x, y - other.y); }

  Vec2 &operator-=(Vec2 other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  bool operator==(Vec2 other) const {
    if (x == other.x && y == other.y) {
      return 1;
    } else {
      return 0;
    }
  }

  bool operator!=(Vec2 other) const {
    if (x == other.x && y == other.y) {
      return 0;
    } else {
      return 1;
    }
  }

  Vec2 operator*(float other) const { return Vec2(x * other, y * other); }

  Vec2 &operator*=(float other) {
    x *= other;
    y *= other;
    return *this;
  }

  Vec2 operator/(float other) const { return Vec2(x / other, y / other); }

  Vec2 &operator/=(float other) {
    x /= other;
    y /= other;
    return *this;
  }

  Vec2 Direction() {
    return Vec2(x / sqrtf(x * x + y * y), y / sqrtf(x * x + y * y));
  }


};

float DotProduct(Vec2 first, Vec2 second) {
  return (first.x * second.x + first.y * second.y);
}

class Vec3 {
public:
  float x;
  float y;
  float z;

  Vec3() = default;

  Vec3(float x1, float y1, float z1) {
    x = x1;
    y = y1;
    z = z1;
  }

  Vec3 operator+(Vec3 other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
  }

  Vec3 &operator+=(Vec3 other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  Vec3 operator-(Vec3 other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
  }

  Vec3 &operator-=(Vec3 other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  Vec3 &operator=(Vec3 other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  bool operator==(Vec3 other) const {
    if (x == other.x && y == other.y && z == other.z) {
      return 1;
    } else {
      return 0;
    }
  }

  bool operator!=(Vec3 other) const {
    if (x == other.x && y == other.y && z == other.z) {
      return 0;
    } else {
      return 1;
    }
  }

  Vec3 operator*(Vec3 other) {
      return Vec3(x * other.x, y * other.y, z * other.z);
  }

  Vec3 operator*(float other) const {
    return Vec3(x * other, y * other, z * other);
  }

  Vec3 &operator*=(float other) {
    x *= other;
    y *= other;
    z *= other;
    return *this;
  }

  Vec3 operator/(float other) const {
    return Vec3(x / other, y / other, z / other);
  }

  Vec3 &operator/=(float other) {
    x /= other;
    y /= other;
    z /= other;
    return *this;
  }

  Vec3 operator-() const { return Vec3(-x, -y, -z); }

  Vec3 Normalize() {
    float length = Length();
    return Vec3(x / length, y / length, z / length);
  }

  float Length() { return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

  Vec3 Direction() {
    return Vec3(x / sqrtf(x * x + y * y + z * z),
                y / sqrtf(x * x + y * y + z * z),
                z / sqrtf(x * x + y * y + z * z));
  }
};

float DotProduct(Vec3 first, Vec3 second) {
  return (first.x * second.x + first.y * second.y + first.z * second.z);
}

Vec3 CrossProduct(Vec3 first, Vec3 second) {
  return Vec3(first.y * second.z - first.z * second.y,
              -(first.x * second.z - first.z * second.x),
              first.x * second.y - second.x * first.y);
}

template <typename OStream>
OStream &&operator<<(OStream &&os, const Vec3 &vec) {
  os << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
  return os;
}

class Quaternion {
public:
  float a;
  Vec3 v;

  Quaternion() = default;

  Quaternion(float a1, float x, float y, float z) {
    a = a1;
    v = Vec3(x, y, z);
  }

  Quaternion(float a1, Vec3 v1) {
    a = a1;
    v = v1;
  }  
  Quaternion(Vec3 v1, float a1) {
    a = v1.x;
    v.x = v1.y;
    v.y = v1.z;
    v.z = a1;
  }

  Quaternion operator+(Quaternion other) {
    return Quaternion(a + other.a, v + other.v);
  }

  Quaternion &operator+=(Quaternion other) {
    a += other.a;
    v += other.v;
    return *this;
  }

  Quaternion operator-(Quaternion other) {
    return Quaternion(a - other.a, v - other.v);
  }

  Quaternion &operator-=(Quaternion other) {
    a -= other.a;
    v -= other.v;
    return *this;
  }

  Quaternion operator*(float other) { return Quaternion(a * other, v * other); }

  Quaternion &operator*=(float other) {
    a *= other;
    v *= other;
    return *this;
  }

  Quaternion operator/(float other) { return Quaternion(a / other, v / other); }

  Quaternion &operator/=(float other) {
    a /= other;
    v /= other;
    return *this;
  }

  Quaternion Normalize() { return (*this / Length()); }

  float Length() { return sqrtf(a * a + v.x * v.x + v.y * v.y + v.z * v.z); }

  Quaternion &operator=(Quaternion other) {
    a = other.a;
    v = other.v;
    return *this;
  }

  Quaternion Inverse() { return (Conjugate() / AbsInSquere()); }

  Quaternion Conjugate() { return Quaternion(a, -v); }

  float AbsInSquere() {
    Quaternion second = Conjugate();
    second =
        Quaternion(a * second.a - DotProduct(second.v, v),
                   second.v * a + v * second.a + CrossProduct(v, second.v));
    return second.a;
  }
};

Quaternion CrossProduct(Quaternion first, Quaternion second) {
  return Quaternion(first.a * second.a - DotProduct(second.v, first.v),
                    second.v * first.a + first.v * second.a +
                        CrossProduct(first.v, second.v));
}

template <typename OStream>
OStream &&operator<<(OStream &&os, const Quaternion &q) {
  os << '(' << q.a << ',' << q.v.x << ',' << q.v.y << ',' << q.v.z << ')';
  return os;
}

class Mat2 {
public:
  float matrix[2][2];
  Mat2() = default;

  Mat2(float a) {
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        matrix[i][j] = a;
  }

  Mat2 E() {
    Mat2 result = Mat2();
    result.matrix[0][0] = 1;
    result.matrix[1][1] = 1;
    return result;
  }
  Mat2(float a1, float a2) {
    for (int i = 0; i < 2; i++) {
      matrix[i][0] = a1;
      matrix[i][0] = a2;
    }
  }

  Mat2 operator==(Mat2 other) {
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (matrix[i][j] != other.matrix[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  Mat2 operator!=(Mat2 other) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (matrix[i][j] != other.matrix[i][j]) {
          return true;
        }
      }
    }
    return false;
  }

  Mat2 operator+(Mat2 other) {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
    return result;
  }

  Mat2 operator-(Mat2 other) {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
    return result;
  }

  Mat2 &operator-=(Mat2 other) {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        matrix[i][j] -= other.matrix[i][j];
    return *this;
  }

  Mat2 &operator+=(Mat2 other) {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        matrix[i][j] += other.matrix[i][j];
    return *this;
  }

  Mat2 &operator=(Mat2 other) {
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        matrix[i][j] = other.matrix[i][j];
    return *this;
  }

  Mat2 operator*(Mat2 other) {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) {
        for (int r = 0; r < 2; r++)
          result.matrix[j][i] += matrix[r][i] * other.matrix[j][r];
      }
    return result;
  }

  Mat2 &operator*=(Mat2 other) {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) {
        for (int r = 0; r < 2; r++)
          result.matrix[j][i] += matrix[r][i] * other.matrix[j][r];
      }
    *this = result;
    return (*this);
  }

  Mat2 &operator*=(float other) {
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) {
        matrix[i][j] *= other;
      }
    return (*this);
  }

  Mat2 &operator/=(float other) {
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) {
        matrix[i][j] /= other;
      }
    return (*this);
  }

  Mat2 operator*(float other) {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) {
        result.matrix[i][j] = matrix[i][j] * other;
      }
    return result;
  }

  Mat2 operator/(float other) {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) {
        result.matrix[i][j] = matrix[i][j] / other;
      }
    return result;
  }

  Mat2 operator+(float other) {
    Mat2 result = Mat2();
    result.matrix[0][0] -= other;
    result.matrix[1][1] -= other;
    return result;
  }

  Mat2 &operator+=(float other) {
    Mat2 result = Mat2();
    matrix[0][0] -= other;
    matrix[1][1] -= other;
    return (*this);
  }

  Vec2 operator*(Vec2 other) {
    Vec2 result = Vec2();
    result.x += other.x * matrix[0][0] + other.y * matrix[0][1];
    result.y += other.x * matrix[1][0] + other.y * matrix[1][1];
    return result;
  }

  Mat2 Transpos() {
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        result.matrix[i][j] = matrix[j][i];
    return result;
  }

  Mat2 Inverse() {
    float det = Determinant();
    Mat2 result = Mat2();
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        result.matrix[i][j] = matrix[1 - i][1 - j] / det * powf(-1, i + j);
      }
    }
    return result;
  }

  float Determinant() {
    return (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]);
  }

  Vec2 GetString(int i) {
    Vec2 str = Vec2(matrix[i][0], matrix[i][1]);
    return str;
  }

  Vec2 GetColumn(int i) {
    Vec2 str = Vec2(matrix[0][i], matrix[1][i]);
    return str;
  }
};

template <typename OStream> OStream &&operator<<(OStream &&os, const Mat2 &m) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++)
      os << m.matrix[i][j] << ' ';
    os << '\n';
  }
  return os;
}

class Mat3 {
public:
  float matrix[3][3];
  Mat3() = default;

  Mat3(int a) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        matrix[i][j] = a;
  }

  Mat3 operator+(Mat3 other) {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
    return result;
  }

  Mat3 E() {
    Mat3 result = Mat3();
    result.matrix[0][0] = 1;
    result.matrix[1][1] = 1;
    result.matrix[2][2] = 1;
    return result;
  }

  Mat3 operator-(Mat3 other) {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
    return result;
  }

  Mat3 &operator-=(Mat3 other) {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        matrix[i][j] -= other.matrix[i][j];
    return *this;
  }

  Mat3 &operator+=(Mat3 other) {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        matrix[i][j] += other.matrix[i][j];
    return *this;
  }

  Mat3 &operator=(Mat3 other) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        matrix[i][j] = other.matrix[i][j];
    return *this;
  }

  Mat3 operator*(Mat3 other) {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        for (int r = 0; r < 3; r++)
          result.matrix[j][i] += matrix[r][i] * other.matrix[j][r];
      }
    return result;
  }

  Mat3 &operator*=(Mat3 other) {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        for (int r = 0; r < 3; r++)
          result.matrix[j][i] += matrix[r][i] * other.matrix[j][r];
      }
    *this = result;
    return (*this);
  }

  Mat3 operator*(float other) {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        result.matrix[i][j] = matrix[i][j] * other;
      }
    return result;
  }

  Mat3 &operator*=(float other) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        matrix[i][j] *= other;
      }
    return (*this);
  }

  Mat3 &operator/=(float other) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        matrix[i][j] /= other;
      }
    return (*this);
  }

  Mat3 operator/(float other) {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        result.matrix[i][j] = matrix[i][j] / other;
      }
    return result;
  }

  Mat3 operator==(Mat3 other) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (matrix[i][j] != other.matrix[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  Mat3 operator!=(Mat3 other) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (matrix[i][j] != other.matrix[i][j]) {
          return true;
        }
      }
    }
    return false;
  }

  Vec3 operator*(Vec3 other) {
    Vec3 result = Vec3();
    result.x += other.x * matrix[0][0] + other.y * matrix[1][0] +
                other.z * matrix[2][0];
    result.y += other.x * matrix[0][1] + other.y * matrix[1][1] +
                other.z * matrix[2][1];
    result.z += other.x * matrix[0][2] + other.y * matrix[1][2] +
                other.z * matrix[2][2];
    return result;
  }

  Mat3 operator+(float other) {
    Mat3 result = Mat3();
    result.matrix[0][0] += other;
    result.matrix[1][1] += other;
    result.matrix[2][2] += other;
    return result;
  }

  Mat3 &operator+=(float other) {
    matrix[0][0] += other;
    matrix[1][1] += other;
    matrix[2][2] += other;
    return (*this);
  }

  Mat3 &operator-=(float other) {
    matrix[0][0] -= other;
    matrix[1][1] -= other;
    matrix[2][2] -= other;
    return (*this);
  }

  Mat3 operator-(float other) {
    Mat3 result = Mat3();
    result.matrix[0][0] -= other;
    result.matrix[1][1] -= other;
    result.matrix[2][2] -= other;
    return result;
  }

  Mat3 Transpos() {
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        result.matrix[i][j] = matrix[j][i];
    return result;
  }

  float Determinant() {
    return (matrix[0][0] * matrix[1][1] * matrix[2][2] +
            matrix[0][1] * matrix[1][2] * matrix[2][0] +
            matrix[0][2] * matrix[1][0] * matrix[2][1] -
            matrix[2][0] * matrix[1][1] * matrix[0][2] -
            matrix[0][0] * matrix[1][2] * matrix[2][1] -
            matrix[0][1] * matrix[1][0] * matrix[2][2]);
  }

  Mat3 Inverse() {
    float det = Determinant();
    Mat3 result = Mat3();
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        result.matrix[i][j] =
            AlgAddition(i, j).Determinant() / det * powf(-1, i + j);
      }
    }
    return result.Transpos();
  }

  Vec3 GetString(int i) {
      Vec3 str = Vec3(matrix[i][0], matrix[i][1], matrix[i][2]);
      return str;
  }

  Vec3 GetColumn(int i) {
      Vec3 str = Vec3(matrix[0][i], matrix[1][i], matrix[2][i]);
      return str;
  }


private:
  Mat2 AlgAddition(int k1, int k2) {
    Mat2 result = Mat2();
    int i1 = 0;
    int j1 = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (i != k1 && j != k2) {
          result.matrix[i1][j1] = matrix[i][j];
          j1++;
        }
      }
      j1 = 0;
      if (i != k1)
        i1++;
    }
    return (result);
  }


};

template <typename OStream> OStream &&operator<<(OStream &&os, const Mat3 &m) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      os << m.matrix[i][j] << ' ';
    os << '\n';
  }
  return os;
}

class Mat4 {
public:
  float matrix[4][4];
  Mat4() = default;

  Mat4(int a) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        matrix[i][j] = a;
  }
  Mat4(float a,
       float b, float c, float d) {
      for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
              matrix[i][j] = 0;
      matrix[0][0] = a;
      matrix[1][1] = b;
      matrix[2][2] = c;
      matrix[3][3] = d;

  }



  Mat4(Vec3 v) {
      matrix[0][0] = v.x;
      matrix[1][1] = v.y;
      matrix[2][2] = v.z;
      matrix[3][3] = 1.0f;
  }

  Mat4 E() {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.matrix[0][0] = 0;
        }
    }
    result.matrix[0][0] = 1;
    result.matrix[1][1] = 1;
    result.matrix[2][2] = 1;
    result.matrix[3][3] = 1;
    return result;
  }



  Mat4 operator+(Mat4 other) {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
    return result;
  }

  Mat4 operator-(Mat4 other) {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
    return result;
  }

  Mat4 &operator-=(Mat4 other) {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        matrix[i][j] -= other.matrix[i][j];
    return *this;
  }

  Mat4 &operator+=(Mat4 other) {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        matrix[i][j] += other.matrix[i][j];
    return *this;
  }

  Mat4 &operator=(Mat4 other) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        matrix[i][j] = other.matrix[i][j];
    return *this;
  }

  Mat4 operator*(Mat4 other) {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) {
        for (int r = 0; r < 4; r++)
          result.matrix[j][i] += matrix[r][i] * other.matrix[j][r];
      }
    return result;
  }

  Mat4 operator+(float other) {
    Mat4 result = Mat4();
    result.matrix[0][0] += other;
    result.matrix[1][1] += other;
    result.matrix[2][2] += other;
    result.matrix[3][3] += other;
    return result;
  }

  Mat4 operator-(float other) {
    Mat4 result = Mat4();
    result.matrix[0][0] -= other;
    result.matrix[1][1] -= other;
    result.matrix[2][2] -= other;
    result.matrix[3][3] -= other;
    return result;
  }

  Mat4 &operator+=(float other) {
    matrix[0][0] += other;
    matrix[1][1] += other;
    matrix[2][2] += other;
    matrix[3][3] += other;
    return (*this);
  }

  Mat4 &operator-=(float other) {
    matrix[0][0] -= other;
    matrix[1][1] -= other;
    matrix[2][2] -= other;
    matrix[3][3] -= other;
    return (*this);
  }

  Mat4 operator*(float other) {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) {
        result.matrix[i][j] = matrix[i][j] * other;
      }
    return result;
  }

  Mat4 &operator*=(float other) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) {
        matrix[i][j] *= other;
      }
    return (*this);
  }

  Quaternion operator*(Quaternion q) {
    Quaternion result = Quaternion();
    result.a = matrix[0][0] * q.a + matrix[1][0] * q.v.x +
               matrix[2][0] * q.v.y + matrix[3][0] * q.v.z;
    result.v.x = matrix[0][1] * q.a + matrix[1][1] * q.v.x +
                 matrix[2][1] * q.v.y + matrix[3][1] * q.v.z;
    result.v.y = matrix[0][2] * q.a + matrix[1][2] * q.v.x +
                 matrix[2][2] * q.v.y + matrix[3][2] * q.v.z;
    result.v.z = matrix[0][3] * q.a + matrix[1][3] * q.v.x +
                 matrix[2][3] * q.v.y + matrix[3][3] * q.v.z;
    return result;
  }

  Mat4 operator==(Mat4 other) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (matrix[i][j] != other.matrix[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  Mat4 operator!=(Mat4 other) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (matrix[i][j] != other.matrix[i][j]) {
          return true;
        }
      }
    }
    return false;
  }

  Mat4 operator/(float other) {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) {
        result.matrix[i][j] = matrix[i][j] / other;
      }
    return result;
  }

  Mat4 Transpos() {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        result.matrix[i][j] = matrix[j][i];
    return result;
  }

  float Determinant() {
    float determinant = 0;
    for (int j = 0; j < 4; j++) {
      determinant +=
          matrix[0][j] * AlgAddition(0, j).Determinant() * powf(-1, j);
    }
    return determinant;
  }

  Mat4 Inverse() {
    float det = Determinant();
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.matrix[i][j] =
            AlgAddition(i, j).Determinant() / det * powf(-1, i + j);
      }
    }
    return result.Transpos();
  }
  
  Quaternion GetString(int i) {
      Quaternion str = Quaternion(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
      return str;
  }

  Quaternion GetColumn(int i) {
      Quaternion str = Quaternion(matrix[0][i], matrix[1][i], matrix[2][i], matrix[3][i]);
      return str;
  }
private:
  Mat3 AlgAddition(int k1, int k2) {
    Mat3 result = Mat3();
    int i1 = 0;
    int j1 = 0;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (i != k1 && j != k2) {
          result.matrix[i1][j1] = matrix[i][j];
          j1++;
        }
      }
      j1 = 0;
      if (i != k1)
        i1++;
    }
    return (result);
  }


};


template <typename OStream> OStream &&operator<<(OStream &&os, const Mat4 &m) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      os << m.matrix[i][j] << ' ';
    os << '\n';
  }
  return os;
}

Vec3 Perspective2(Vec3 v, float fov, float distantToProtection, float f,
                  float aspect) {
  float height = tan(fov * 1.57f / 180.0f) * distantToProtection;
  float width = height * aspect;
  return Vec3(-v.x * distantToProtection / width,
              -v.y * distantToProtection / height,
              v.z * (f + distantToProtection) / (f - distantToProtection) -
                  (2 * distantToProtection * f) / (distantToProtection - f));
}

Vec3 Perspective(Vec3 v, float fov, float width, float height, float near,
                 float far) {
  float ratio = width / height;
  return Vec3(v.x / ratio / tan(fov * 1.57f / 180.0f), v.y / tan(fov * 1.57f / 180.0f),
              v.z * ((far + near) / (far - near)) -
                  (2 * far * near) / (far - near));
}

Quaternion Perspective(Quaternion q, float fov, float width, float height,
                       float near, float far) {
  float ratio = width / height;
  return Quaternion(q.a / ratio / tan(fov * 1.57f / 180.0f), q.v.x / tan(fov * 1.57f / 180.0f),
                    q.v.y * (far + near) / (far - near) +
                        q.v.z * (2 * far * near) / (far - near),
                    q.v.y);
}

Mat4 Perspective(float fov, float ratio, float near,
    float far) {
    float tg = tan(fov / 2);
    float tmp = far-near;
    Mat4 result = Mat4(1.0f/(ratio * tg),  1.0f/tg, -(far + near) / tmp, 0.0f);
    result.matrix[3][2] = -(2.0f * far * near) / tmp;
    result.matrix[2][3] = -1.0f;
    return result;
}

Vec3 QRotationX(Vec3 v, float angle) {
  Quaternion q = Quaternion(cos(angle * 1.57 / 180),
                            Vec3(1, 0, 0) * sin(angle * 1.57 / 180));
  Quaternion result =
      CrossProduct(CrossProduct(q, Quaternion(0, v)), q.Inverse());
  return result.v;
}

Vec3 QRotationY(Vec3 v, float angle) {
  Quaternion q = Quaternion(cos(angle * 1.57 / 180),
                            Vec3(0, 1, 0) * sin(angle * 1.57 / 180));
  Quaternion result =
      CrossProduct(CrossProduct(q, Quaternion(0, v)), q.Inverse());
  return result.v;
}

Vec3 QRotationZ(Vec3 v, float angle) {
  Quaternion q = Quaternion(cos(angle * 1.57 / 180),
                            Vec3(0, 0, 1) * sin(angle * 1.57 / 180));
  Quaternion result =
      CrossProduct(CrossProduct(q, Quaternion(0, v)), q.Inverse());
  return result.v;
}

Mat4 MRotationX(float angle) {
  Mat4 rMatrix = Mat4().E();
  rMatrix.matrix[1][1] = cos(angle * pi / 180);
  rMatrix.matrix[2][2] = cos(angle * pi / 180);
  rMatrix.matrix[2][1] = sin(angle * pi / 180);
  rMatrix.matrix[1][2] = -sin(angle * pi / 180);
  return rMatrix;
}

Mat4 MRotationY(float angle) {
    Mat4 rMatrix = Mat4().E();
    rMatrix.matrix[0][0] = cos(angle * pi / 180);
    rMatrix.matrix[2][2] = cos(angle * pi / 180);
    rMatrix.matrix[0][2] = sin(angle * pi / 180);
    rMatrix.matrix[2][0] = -sin(angle * pi / 180);
    return rMatrix;
}

Mat4 MRotationZ(float angle) {
    Mat4 rMatrix = Mat4().E();
    rMatrix.matrix[0][0] = cos(angle * pi / 180);
    rMatrix.matrix[0][1] = -sin(angle * pi / 180);
    rMatrix.matrix[1][0] = sin(angle * pi / 180);
    rMatrix.matrix[1][1] = cos(angle * pi / 180);
    return rMatrix;
}

Mat3 MRotationX3(float angle) {
    Mat3 rMatrix = Mat3().E();
    rMatrix.matrix[1][1] = cos(angle * pi / 180);
    rMatrix.matrix[2][2] = cos(angle * pi / 180);
    rMatrix.matrix[2][1] = sin(angle * pi / 180);
    rMatrix.matrix[1][2] = -sin(angle * pi / 180);
    return rMatrix;
}

Mat3 MRotationY3(float angle) {
    Mat3 rMatrix = Mat3().E();
    rMatrix.matrix[0][0] = cos(angle * pi / 180);
    rMatrix.matrix[2][2] = cos(angle * pi / 180);
    rMatrix.matrix[0][2] = sin(angle * pi / 180);
    rMatrix.matrix[2][0] = -sin(angle * pi / 180);
    return rMatrix;
}

Mat3 MRotationZ3(float angle) {
    Mat3 rMatrix = Mat3().E();
    rMatrix.matrix[0][0] = cos(angle * pi / 180);
    rMatrix.matrix[0][1] = -sin(angle * pi / 180);
    rMatrix.matrix[1][0] = sin(angle * pi / 180);
    rMatrix.matrix[1][1] = cos(angle * pi / 180);
    return rMatrix;
}

Vec3 QRotation(Vec3 v, Vec3 axis, float angle) {
  Quaternion q = Quaternion(cos(angle * 1.57 / 180),
                            axis.Normalize() * sin(angle * 1.57 / 180));
  Quaternion result =
      CrossProduct(CrossProduct(q, Quaternion(0, v)), q.Inverse());
  return result.v;
}

Mat3 QRotationMat(Vec3 l, float angle) {
  Mat3 rMatrix = Mat3().E();
  angle = angle * 1.7 / 180;
  Quaternion q = Quaternion(cos(angle), l.Normalize() * sin(angle));
  rMatrix.matrix[0][0] = 1 - 2 * q.v.y * q.v.y - 2 * q.v.z * q.v.z;
  rMatrix.matrix[0][1] = 2 * q.v.x * q.v.y - 2 * q.v.z * q.a;
  rMatrix.matrix[0][2] = 2 * q.v.x * q.v.z + 2 * q.v.y * q.a;

  rMatrix.matrix[1][0] = 2 * q.v.x * q.v.y + 2 * q.v.z * q.a;
  rMatrix.matrix[1][1] = 1 - 2 * q.v.x * q.v.x - 2 * q.v.z * q.v.z;
  rMatrix.matrix[1][2] = 2 * q.v.y * q.v.z - 2 * q.v.x * q.a;

  rMatrix.matrix[2][0] = 2 * q.v.x * q.v.z - 2 * q.v.y * q.a;
  rMatrix.matrix[2][1] = 2 * q.v.y * q.v.z + 2 * q.v.x * q.a;
  rMatrix.matrix[2][2] = 1 - 2 * q.v.x * q.v.x - 2 * q.v.y * q.v.y;

  return rMatrix;
}

Mat4 QRotationMat2(Vec4 l) {
    Mat4 rMatrix = Mat4().E();
    Quaternion q = l;
    rMatrix.matrix[0][0] = 1 - 2 * q.v.y * q.v.y - 2 * q.v.z * q.v.z;
    rMatrix.matrix[0][1] = 2 * q.v.x * q.v.y - 2 * q.v.z * q.a;
    rMatrix.matrix[0][2] = 2 * q.v.x * q.v.z + 2 * q.v.y * q.a;

    rMatrix.matrix[1][0] = 2 * q.v.x * q.v.y + 2 * q.v.z * q.a;
    rMatrix.matrix[1][1] = 1 - 2 * q.v.x * q.v.x - 2 * q.v.z * q.v.z;
    rMatrix.matrix[1][2] = 2 * q.v.y * q.v.z - 2 * q.v.x * q.a;

    rMatrix.matrix[2][0] = 2 * q.v.x * q.v.z - 2 * q.v.y * q.a;
    rMatrix.matrix[2][1] = 2 * q.v.y * q.v.z + 2 * q.v.x * q.a;
    rMatrix.matrix[2][2] = 1 - 2 * q.v.x * q.v.x - 2 * q.v.y * q.v.y;

    return rMatrix;
}

Vec2 Scaling(Vec2 v, Vec2 scale) { return Vec2(v.x * scale.x, v.y * scale.y); }

Vec3 Scaling(Vec3 v, Vec3 scale) {
  return Vec3(v.x * scale.x, v.y * scale.y, v.z * scale.z);
}

Quaternion Scaling(Quaternion q, Quaternion scale) {
  return Quaternion(q.a * scale.a, q.v.x * scale.v.x, q.v.y * scale.v.y,
                    q.v.z * scale.v.z);
}

Vec3 Translate(Vec3 v, Vec3 move) {
  return Vec3(v.x + move.x, v.y + move.y, v.z + move.z);
}

Vec2 Translate(Vec2 v, Vec2 move) { return Vec2(v.x + move.x, v.y + move.y); }

Mat4 LookAt(Vec3 from, Vec3 to, Vec3 worldUp) {
    Vec3 forward = from - to;
    Vec3 right = CrossProduct(worldUp, forward);
    Vec3 up = CrossProduct(forward, right);

    Mat4 result;
    result.matrix[0][0] = right.x;
    result.matrix[1][0] = right.y;
    result.matrix[2][0] = right.z;
    result.matrix[3][0] = -DotProduct(right, from);


    result.matrix[0][1] = up.x;
    result.matrix[1][1] = up.y;
    result.matrix[2][1] = up.z;
    result.matrix[3][1] = -DotProduct(up, from);


    result.matrix[0][2] = forward.x;
    result.matrix[1][2] = forward.y;
    result.matrix[2][2] = forward.z;
    result.matrix[3][2] = -DotProduct(forward, from);

    result.matrix[0][3] = 0;
    result.matrix[1][3] = 0;
    result.matrix[2][3] = 0;
    result.matrix[3][3] = 1.0f;
    return result;
}

Mat3 LookAt3x3(Vec3 from, Vec3 to, Vec3 worldUp) {
    Vec3 forward = from - to;
    Vec3 right = CrossProduct(worldUp, forward);
    Vec3 up = CrossProduct(forward, right);

    Mat3 result;
    result.matrix[0][0] = right.x;
    result.matrix[1][0] = right.y;
    result.matrix[2][0] = right.z;
    result.matrix[3][0] = -DotProduct(right, from);


    result.matrix[0][1] = up.x;
    result.matrix[1][1] = up.y;
    result.matrix[2][1] = up.z;
    result.matrix[3][1] = -DotProduct(up, from);


    result.matrix[0][2] = forward.x;
    result.matrix[1][2] = forward.y;
    result.matrix[2][2] = forward.z;
    result.matrix[3][2] = -DotProduct(forward, from);

    return result;
}

float angle(Vec3 v1, Vec3 v2) {
    
    return 180.0f*acos(DotProduct(v1, v2) / (v1.Length()*v2.Length()))/pi;
}

Mat4 matTranslate(Vec3 t) {
    Mat4 result = Mat4().E();
    result.matrix[3][0] = t.x;
    result.matrix[3][1] = t.y;
    result.matrix[3][2] = t.z;
    return result;
}

