class MathUtil
{
public:
	static const float E;
	static const float Log10E;
	static const float Log2E;
	static const float Pi;
	static const float PiOver2;
	static const float PiOver4;
	static const float TwoPi;
	static const float MaxFloat;
	static const float MinFloat;
	static const float Epsilon;
	
	static float ToDegrees(float radians);
	static float ToRadians(float degrees);
	static Vector2 VectorFromAngle(float angle_in_degrees);
	static float AngleFromVector(const Vector2& v1);
	static float AngleFromVectors(const Vector2& v1, const Vector2& v2);
	static int RoundToInt(double x);
	static int RandomInt(int maximum);
	static int RandomIntInRange(int min, int max);
	static int RandomIntWithError(int target, int error);
	static float RandomFloat(float maximum=1.0f);
	static float RandomFloatInRange(float min, float max);
	static float RandomFloatWithError(float target, float error);
	static bool RandomBool();
	static Vector2 RandomVector();
	static Vector2 RandomVector(const Vector2& maxValues);
	static Vector2 RandomVector(const Vector2& minValues, const Vector2& maxValues);
	static Vector2List RandomPointField(int numPoints, const Vector2& minValue, const Vector2& maxValue, float minDistance=0.5f);
	static bool FuzzyEquals(float value1, float value2, float epsilon=Epsilon);
	static bool FuzzyEquals(const Vector2& v1, const Vector2& v2, float epsilon=Epsilon);
	static Vector2 ScreenToWorld(int x, int y);
	static Vector2 ScreenToWorld(const Vec2i& screenCoordinates);
	static Vector2 WorldToScreen(float x, float y);
	static Vector2 WorldToScreen(const Vector2& worldCoordinates);
	static Vector2 GetWorldDimensions();
	static float PixelsToWorldUnits(float pixels);
	static float WorldUnitsToPixels(float worldUnits);
	static float DeltaAngle(float A1, float A2);
	static float VectorDeltaAngle(const Vector2& v1, const Vector2& v2);
};

