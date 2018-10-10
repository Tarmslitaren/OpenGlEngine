#pragma once
#ifndef CONVERTERS_HEADER
#define CONVERTERS_HEADER
#include <sstream>
#include <string>
#include "CU_Vector.h"
#include "CU_Matrix.h"


namespace Convert
{
	std::string IntToString(int &aInt);
	std::string FloatToString(const float aFloat);
	std::string DoubleToString(const double aDouble);
	std::wstring IntToWString(int &aInt);
	std::wstring FloatToWString(float &aFloat);
	std::string WStringToString(std::wstring &aWString);
	std::wstring StringToWString(std::string &aString);
	//D3DXMATRIX ConvertToD3DMatrix(CU::Matrix44f aMatrix);
	//const CU::Matrix44f& ConvertFromD3DMatrix(D3DXMATRIX aMatrix);
	double StringToDouble(std::string aString);
	float StringToFloat(std::string aString);
	float AweRound(float afloat);
	CU::Vector2i ConvertPosToIndexes(CU::Vector2f aPos,int aTileSize);
	CU::Vector2f ConvertIndexesToPos(const CU::Vector2i& aIndexInGrid,const int& aTileSize);
	float ConvertToPercent(float aCurrentValue, float aMaxValue);
	void ConvertToNormalizedCoordSystem(CU::Vector2f &aPosition, CU::Vector2f &aResolution);
	void ConvertFromNormalizedCoordSystem(CU::Vector2f &aPosition, CU::Vector2f &aResolution);
	float ConvertToPercentFW(float aCurrentValue, float aMaxValue);
	void WholePathToFilename(std::string &aPath);
	void GetFileName(std::string &aPath);
	float DegreeToRadian(float aDegree);
	float RadianToDegree(float aRadian);
	
}
#endif

