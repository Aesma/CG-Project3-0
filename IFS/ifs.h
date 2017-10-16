#ifndef IFS_H
#define IFS_H

#include "image.h"
#include "matrix.h"
#include "vectors.h"
#include <vector>

using namespace std;

class IFS
{
public:
	IFS() : n(0) {}
	IFS(const char *filename) { readFile(filename); }
	void readFile(const char *filename);
	void fractalRendering(Image &img, int pointNum, int iterTimes, const char *outputFile) const;
	~IFS() {};
private:
	int n;

	vector<Matrix> m_transMatrix;
	vector<float> m_transProbality;
};

#endif