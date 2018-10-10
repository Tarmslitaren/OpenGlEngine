#include "stdafx.h"
#include "Converters.h"

std::string Convert::IntToString(int &aInt)
{
	std::stringstream outStream;
	outStream << aInt;
	return outStream.str();
}

/*D3DXMATRIX Convert::ConvertToD3DMatrix(CU::Matrix44f aMatrix)
{
	float* fulhacksaken;
	D3DXMATRIX matrix;
	fulhacksaken = matrix;
	//fulhacksaken[0] = aMatrix.myMatrix[0][0];

	fulhacksaken[0] = aMatrix.myMatrix[0][0];
	fulhacksaken[1] = aMatrix.myMatrix[0][1];
	fulhacksaken[2] = aMatrix.myMatrix[0][2];
	fulhacksaken[3] = aMatrix.myMatrix[0][3];

	fulhacksaken[4] = aMatrix.myMatrix[1][0];
	fulhacksaken[5] = aMatrix.myMatrix[1][1];
	fulhacksaken[6] = aMatrix.myMatrix[1][2];
	fulhacksaken[7] = aMatrix.myMatrix[1][3];

	fulhacksaken[8] = aMatrix.myMatrix[2][0];
	fulhacksaken[9] = aMatrix.myMatrix[2][1];
	fulhacksaken[10]= aMatrix.myMatrix[2][2];
	fulhacksaken[11]= aMatrix.myMatrix[2][3];

	fulhacksaken[12]= aMatrix.myMatrix[3][0];
	fulhacksaken[13]= aMatrix.myMatrix[3][1];
	fulhacksaken[14]= aMatrix.myMatrix[3][2];
	fulhacksaken[15]= aMatrix.myMatrix[3][3];

	return matrix;
}*/

std::string Convert::FloatToString(const float aFloat)
{
	std::stringstream outStream;
	outStream << aFloat;
	return outStream.str();
}

std::string Convert::DoubleToString(const double aFloat)
{
	std::stringstream outStream;
	outStream << aFloat;
	return outStream.str();
}

std::wstring Convert::IntToWString(int &aInt)
{
	std::wstringstream converter;
	std::wstring  wstr;
	converter << aInt;
	converter >> wstr;
	return wstr;
}

std::wstring Convert::FloatToWString(float &aFloat)
{
	std::wstringstream converter;
	std::wstring  wstr;
	converter << aFloat;
	converter >> wstr;
	return wstr;
}

std::string Convert::WStringToString(std::wstring &aWString)
{
	std::string temp(aWString.begin(), aWString.end());
	temp.assign(aWString.begin(), aWString.end());

	return temp; 
}


std::wstring Convert::StringToWString(std::string &aString)
{
	std::wstring temp(aString.length(),L' ');
	std::copy(aString.begin(), aString.end(), temp.begin());
	return temp; 
}

double Convert::StringToDouble(std::string aString)
{
	return atof(aString.c_str());
}

float Convert::StringToFloat(std::string aString)
{
	return static_cast<float>(atof(aString.c_str()));
}


float Convert::AweRound(float afloat)
{
	if (afloat < 0.0f)
	{
		afloat  -= 0.5f;
	}
	else
	{
		afloat  += 0.5f;
	}
	return floor(afloat);
}

CU::Vector2i Convert::ConvertPosToIndexes(CU::Vector2f aPos,int aTileSize)
{
	return CU::Vector2i(((static_cast<int>(AweRound(aPos.myX)) - aTileSize/2)/aTileSize),((static_cast<int>(AweRound(aPos.myY)) - aTileSize/2)/aTileSize));
}

CU::Vector2f Convert::ConvertIndexesToPos(const CU::Vector2i& aIndexInGrid,const int& aTileSize)
{
	float x = static_cast<float>(aIndexInGrid.myX * aTileSize) + static_cast<float>(aTileSize) * 0.5f;
	float y = static_cast<float>(aIndexInGrid.myY * aTileSize) + static_cast<float>(aTileSize) * 0.5f;
	return CU::Vector2f(x, y);
}

float Convert::ConvertToPercent(float aCurrentValue, float aMaxValue)
{
	return 100-((aCurrentValue/aMaxValue)*100);


}

float Convert::ConvertToPercentFW(float aCurrentValue, float aMaxValue)
{
	return ((aCurrentValue/aMaxValue)*100);


}

void Convert::ConvertToNormalizedCoordSystem(CU::Vector2f &aPosition, CU::Vector2f &aResolution)
{
	aPosition.myX = ((aPosition.myX - aResolution.myX/2) / aResolution.myX)*2;
	aPosition.myY = -((aPosition.myY - aResolution.myY/2) / aResolution.myY)*2;
}
void Convert::ConvertFromNormalizedCoordSystem(CU::Vector2f &aPosition, CU::Vector2f &aResolution)
{
	aPosition.myX = (aPosition.myX * (aResolution.myX/2)) + aResolution.myX/2;
	aPosition.myY = (aPosition.myY * (aResolution.myY/2)) + aResolution.myY/2;
}

void Convert::WholePathToFilename(std::string &aPath)
{
	std::string complete = "";
	for (int i=aPath.size()-1; i> 0; i--)
	{
		if (aPath[i] == '\\' || aPath[i] == '/' )
		{
			break;
		}
		complete.insert(complete.begin(), aPath[i]);

	}
	aPath = complete;

}

void Convert::GetFileName( std::string &aPath )
{
	std::string complete = "";
	for (int i=aPath.size()-1; i> 0; i--)
	{
		if (aPath[i] == '\\' || aPath[i] == '/' )
		{
			break;
		}
		complete.insert(complete.begin(), aPath[i]);

	}
	aPath = complete;
}

float Convert::DegreeToRadian(float aDegree)
{
	return (aDegree * 3.14159265f) / 180;
}

float Convert::RadianToDegree(float aRadian)
{
	return aRadian * (180 / 3.14159265f);
}
