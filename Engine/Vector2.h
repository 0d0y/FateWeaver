#pragma once
#include <D2D1Helper.h>
#include <vector>

namespace McCol
{
	class Vector2 : public D2D_VECTOR_2F
	{
	public:
		Vector2() = default;

		Vector2(const float& x, const float& y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2(const D2D_VECTOR_2F& vector)
		{
			this->x = vector.x;
			this->y = vector.y;
		}

		Vector2(const Vector2&) = default;

		Vector2& operator=(const Vector2&) = default;

		Vector2(Vector2&&) = default;

		Vector2& operator=(Vector2&&) = default;

		~Vector2() = default;

		Vector2 operator+(const Vector2& vector) const
		{
			return { this->x + vector.x, this->y + vector.y };
		}

		Vector2 operator-(const Vector2& vector) const
		{
			return { this->x - vector.x, this->y - vector.y };
		}

		Vector2 operator*(float scalar) const
		{
			return { this->x * scalar, this->y * scalar };
		}

		Vector2 operator*(const Vector2& vector) const
		{
			return { this->x * vector.x, this->y * vector.y };
		}

		Vector2 operator/(float scalar) const
		{
			return { this->x / scalar, this->y / scalar };
		}

		Vector2& operator+=(const Vector2& vector)
		{
			this->x += vector.x;
			this->y += vector.y;

			return *this;
		}

		Vector2& operator-=(const Vector2& vector)
		{
			this->x -= vector.x;
			this->y -= vector.y;
			return *this;
		}

		Vector2& operator*=(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}

		Vector2& operator*=(const Vector2& vector)
		{
			this->x *= vector.x;
			this->y *= vector.y;
			return *this;
		}

		Vector2& operator/=(float scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			return *this;
		}

		bool operator==(const Vector2& vector) const
		{
			return (this->x == vector.x && this->y == vector.y);
		}

		float Length() const
		{
			return sqrtf(this->x * this->x + this->y * this->y);
		}

		float LengthSquared() const
		{
			return (this->x * this->x + this->y * this->y);
		}

		float Normalize()
		{
			const float length = Length();

			if (length > 0.0f)
			{
				const float invLength = 1.0f / length;
				this->x *= invLength;
				this->y *= invLength;
			}

			return length;
		}

		float Dot(const Vector2& vector) const
		{
			return x * vector.x + y * vector.y;
		}

		Vector2 Perpendicular() const
		{
			return Vector2(-y, x);
		}
	};
}