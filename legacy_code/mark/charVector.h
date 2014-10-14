#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct cluster{
  unordered_map<string, float> centroid;
  vector<unordered_map<string, float> > neighbors;
};

void makeVector(unordered_map<string, float>* charVector, string text);
void printVector(unordered_map<string, float>* vector);
void addVectors(unordered_map<string, float>* vectorA, unordered_map<string, float>* vectorB, unordered_map<string, float>* destV);
float vAngle(unordered_map<string, float>* vectorA, unordered_map<string, float>* vectorB);
float vDistance(unordered_map<string, float>* vectorA, unordered_map<string, float>* vectorB);
void meanVector(vector< unordered_map<string, float> >* vectors, unordered_map<string, float>* vMean);
void initCentroids(int k, vector< unordered_map<string, float> >* vectors, vector< unordered_map<string, float> >* centroids);
bool equivalence(unordered_map<string, float> *vA, unordered_map<string, float> *vB);
void kMeans(int k, vector< unordered_map<string, float> >* vectors, vector<cluster>* clusters);