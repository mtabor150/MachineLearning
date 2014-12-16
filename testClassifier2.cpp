#include <Python/Python.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>
#include "ClassifiedDataSet.h"
#include "DataSet.h"
#include "Distribution.h" 
#include "Classifier.h"
using namespace std; 

#define DEBUGGING false

//map to hold all of the blogs in the training set
map<string, ClassifiedDataSet<NgramVector> > holding_map;

vector<string> vector_of_bloggers()
{
    vector<string> ret_vect;
  //embedded python test
  PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pArgs;

  Py_Initialize();

  //add current directory to sys.path
  PyObject* sysPath = PySys_GetObject((char*)"path");
  PyList_Append(sysPath, PyString_FromString("."));
  pName = PyString_FromString("directory_read");
  pModule = PyImport_Import(pName);
  pArgs = PyTuple_New(0);
  Py_DECREF(pName);

  if(pModule != NULL)
  {
    pFunc = PyObject_GetAttrString(pModule, "get_blogger_names");
    if(pFunc && PyCallable_Check(pFunc))
    {
      pValue = PyObject_CallObject(pFunc, pArgs);
    }
  }
  //iterate through pValue
  if(PySequence_Check(pValue))
  {
    int len = PySequence_Length(pValue);
    for(int i=0; i<len; i++)
    {
      PyObject *item = PySequence_GetItem(pValue, i);

      string value = PyString_AsString(item);
      ret_vect.push_back(value);

      Py_DECREF(item);
    }
  }

  Py_DECREF(pValue);

  Py_Finalize();

  return ret_vect;
}

vector<string> vector_of_blogscontent(string blogger_name)
{
  vector<string> ret_vect;


  PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pArgs;

  Py_Initialize();

  //add current directory to sys.path
  PyObject* sysPath = PySys_GetObject((char*)"path");
  PyList_Append(sysPath, PyString_FromString("."));
  pName = PyString_FromString("directory_read");
  pModule = PyImport_Import(pName);
  pArgs = PyTuple_New(1);
  PyTuple_SetItem(pArgs,0, PyString_FromString(blogger_name.c_str()));
  Py_DECREF(pName);

  if(pModule != NULL)
  {

    pFunc = PyObject_GetAttrString(pModule, "get_blogger_blogs");

    if(pFunc && PyCallable_Check(pFunc))
    {
      pValue = PyObject_CallObject(pFunc, pArgs);
    }
  }
  //iterate through pValue
  if(PySequence_Check(pValue))
  {
    int len = PySequence_Length(pValue);
    for(int i=0; i<len; i++)
    {
      PyObject *item = PySequence_GetItem(pValue, i);

      string value = PyString_AsString(item);
      ret_vect.push_back(value);

      Py_DECREF(item);
    }
  }

  Py_DECREF(pValue);

  Py_Finalize();


  return ret_vect;
}

//adds all of the bloggers and a certain percentage of their blogs
//this assumes we are starting from an empty classifier
void add_all_bloggers(int key_size)
{
  //empty holding map
  holding_map.erase(holding_map.begin(), holding_map.end());

  //Get the file name for each blogger
  vector<string> blogger_names = vector_of_bloggers();
  if(DEBUGGING)
  {
    for(int i=0; i<blogger_names.size(); i++)
    {
      cout << blogger_names[i] << endl;
    }
  }

  //create vector of NgramVectors for each blogger
  //take random 20 percent out and place in test classified data set
  //place other 80 percent into classified data set
  for(int i=0; i<blogger_names.size(); i++)
  {
    string blogger_name = blogger_names[i];
    ClassifiedDataSet<NgramVector> *new_classified_data_set = new ClassifiedDataSet<NgramVector>();

    //fetch vector of all file names in the directory for the blogger
    vector<string> blogs_content = vector_of_blogscontent(blogger_name);

    for(int j=0; j<blogs_content.size(); j++)
    {
      NgramVector *new_vector = new NgramVector("", "", "", key_size);
      new_vector->input_string(blogs_content[j]);
      /*
      for(int k = 3; k<key_size; k++)
      {
        //cout << "k = " << k << endl;
        NgramVector temp_vect = NgramVector("", "", "", k);
        //cout << "a" << endl;
        temp_vect.input_string(blogs_content[j]);
        //cout << "b" << endl;
        (*new_vector) += temp_vect;
        //cout << "c" << endl;
      }*/
      new_vector->set_lang(blogger_name);
      new_vector->set_author(to_string(j));
      new_classified_data_set->push_back(*new_vector);
    }
    holding_map[blogger_name] = *new_classified_data_set;
  }


}

unordered_map<int, NgramVector> get_test_blogs(int key_size)
{
  unordered_map<int, NgramVector> test_blogs;

  PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pArgs;

  Py_Initialize();

  //add current directory to sys.path
  PyObject* sysPath = PySys_GetObject((char*)"path");
  PyList_Append(sysPath, PyString_FromString("."));
  pName = PyString_FromString("directory_read");
  pModule = PyImport_Import(pName);
  pArgs = PyTuple_New(0);
  //PyTuple_SetItem(pArgs,0, PyString_FromString(blogger_name.c_str()));
  Py_DECREF(pName);

  if(pModule != NULL)
  {

    pFunc = PyObject_GetAttrString(pModule, "get_test_blogs");

    if(pFunc && PyCallable_Check(pFunc))
    {
      pValue = PyObject_CallObject(pFunc, pArgs);//pArgs);
    }
  }

  //iterate through pValue
  if(PySequence_Check(pValue))
  {
    int len = PySequence_Length(pValue);
    for(int i=0; i<len; i++)
    {
      NgramVector *temp_vect = new NgramVector("", "", "", key_size);
      PyObject *item = PySequence_GetItem(pValue, i);

      string value = PyString_AsString(item);
      temp_vect->input_string(value);
      test_blogs[i] = (*temp_vect);
      Py_DECREF(item);
    }
  }

  Py_DECREF(pValue);

  Py_Finalize();

  return test_blogs;
}

int main(){
  
  vector<int> percentage;
  vector<int> attempts;
  vector<int> incorrect;

  


  //iterate ten times randomly
  for(int key_size = 5; key_size <=5; key_size++)
  {
    cout << "=====================================" << endl;
    cout << "key_size = " << key_size << endl;

    int total_guessed = 0;
    int total_incorrect = 0;
    //read in all blogs for the test
    add_all_bloggers(key_size);

    for(int test_iteration = 0; test_iteration < 1; test_iteration++)
    {
      int iterations = 0;
      int num_wrong = 0;

      cout << "test_iteration: " << test_iteration << endl;
      //need a classifiedDataSet for each blogger
      //filled with a random 80 percent of their blogs
      Classifier<NgramVector> irish_classifier;

      unordered_map<int, NgramVector> test_map;
      //pick a certain percentage of random NgramVectors from each blogger's classifiedDataSet
      //and place into a new classifiedDataSet to be added to the 'irish_classifier'
      //double percent = 0.9;
      for(auto it=holding_map.begin(); it!=holding_map.end(); ++it)
      {
        //new classifiedDataSet
        ClassifiedDataSet<NgramVector> *new_dataset = new ClassifiedDataSet<NgramVector>();

        int size = it->second.size();

        //int new_size = size * percent;

        /*
        map<int,int> random_nums;
        srand((unsigned)time(NULL));
        while(random_nums.size() < new_size)
        {
          int new_num = rand()%size;
          random_nums[new_num] = 1;
        }*/
        
        for(int i=0; i < size; i++)
        {
          new_dataset->push_back(it->second[i]);
          //test_dataset.push_back(it->second[i]);
        }
        irish_classifier.add_classified_dataset(*new_dataset, it->first);
      }

      //train the classifier by calculating the info_gain
      irish_classifier.calculate_info_gain();

      test_map = get_test_blogs(key_size);

      ofstream myfile;
      myfile.open ("test_answers2.csv");
      
      myfile << "Id,Prediction" << endl;

      //attempt to classify the NgramVectors in test_dataset;
      for(int i=0; i<test_map.size(); i++)
      {
        iterations++;
        //cout << "------------------------------" << endl;
        //string expected = test_dataset[i].get_lang();
        //cout << "exptected: " << expected << endl;
        string return_val = irish_classifier.naive_classify(test_map[i]);
        //cout << "actual:    " << return_val << endl;
        myfile   << to_string(i +1) << ".txt," << return_val << endl;
        
      }
      myfile.close();
      /*
      cout << "num guessed: " << iterations << endl;
      cout << "num wrong  : " << num_wrong  << endl;
      cout << "percent    : " << (double)(iterations-num_wrong)/(double)(iterations) << endl;
      total_guessed += iterations;
      total_incorrect += num_wrong;*/
    }
    /*
    cout << "-------------------------------" << endl;
    cout << "for key_size of " << key_size << endl;
    cout << "total guessed    : " << total_guessed << endl;
    cout << "total incorrect  : " << total_incorrect  << endl;
    cout << "percent correct  : " << (double)(total_guessed - total_incorrect)/(double)(total_guessed) << endl;*/
  }
}