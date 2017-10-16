#include "ifs.h"

void IFS::readFile(const char* filename)
{
	assert(filename != NULL);
	m_transMatrix.clear();
	m_transProbality.clear();

	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		perror("Error opening file");
		return;
	}

	int number = 0;
	fscanf(f, "%d\n", &number);

	n = number;

	for (int i = 0; i < n; i++)
	{
		float prob = 0.0;
		fscanf(f, "%f", &prob);
		m_transProbality.push_back(prob);

		Matrix m;
		m.Read3x3(f);
		m_transMatrix.push_back(m);
	}
}

void IFS::fractalRendering(Image &img, int pointNum, int iterTimes, const char *outputFile) const
{
	int height = img.Height(), width = img.Width();
	Vec3f black(0.0f, 0.0f, 0.0f), white(255.0f, 255.0f, 255.0f);
	img.SetAllPixels(white);

	vector<Vec2f> initPoints;

	for (int i = 0; i < pointNum; i++)
	{
		Vec2f randomPoint((float)(rand() % width), (float)(rand() % height));
		initPoints.push_back(randomPoint);
	}

	for (int i = 0; i < iterTimes; i++)
	{
		for (int j = 0; j < initPoints.size(); j++)
		{
			float ran = (float)(rand()) / (float)(RAND_MAX);
			float p = m_transProbality[0];
			int index = 0;
			while (p < ran && index < (n - 1)){
				p += m_transProbality[++index];
			}
			Matrix transMatrix = m_transMatrix[index];
			Vec2f t(initPoints[j].x() / (double)(width), initPoints[j].y() / (double)(height));
			transMatrix.Transform(t);
			initPoints[j].Set(t.x() * width, t.y() * height);
		}
	}

	int x_min = UINT_MAX, x_max = INT_MIN, y_min = UINT_MAX, y_max = INT_MIN;
	for (int i = 0; i < initPoints.size(); ++i) {
		if (initPoints[i].x() < x_min) x_min = initPoints[i].x();
		if (initPoints[i].x() > x_max) x_max = initPoints[i].x();

		if (initPoints[i].y() < y_min) y_min = initPoints[i].y();
		if (initPoints[i].y() > y_max) y_max = initPoints[i].y();
	}

	if (x_min < 0) {
		for (int i = 0; i < initPoints.size(); ++i) {
			initPoints[i].Set(initPoints[i].x() - x_min, initPoints[i].y());
		}

		x_max -= x_min;
	}

	if (y_min < 0) {
		for (int i = 0; i < initPoints.size(); ++i)
			initPoints[i].Set(initPoints[i].x(), initPoints[i].y() - y_min);

		y_max -= y_min;
	}

	if (x_max >= width || y_max >= height) {
		int d = (x_max > y_max) ? x_max : y_max;
		double f1 = (double)(width) / (double)(d), f2 = (double)(height) / (double)(d);

		for (int i = 0; i < initPoints.size(); ++i)
			initPoints[i].Set(initPoints[i].x() * (f1 - 0.01), initPoints[i].y() * (f2 - 0.01));
	}

	for (int i = 0; i < initPoints.size(); ++i) {
		img.SetPixel(initPoints[i].x(), initPoints[i].y(), black);
	}

	img.SaveTGA(outputFile);
}