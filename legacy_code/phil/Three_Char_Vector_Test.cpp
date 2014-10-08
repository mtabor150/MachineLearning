/*
 * Three_Char_Vector.cpp test file
 */

 #include "Three_Char_Vector.h"

 int main()
 {
 	struct three_char_vector count;
	count = three_char_count("aaaa");
	print_vector(count);
	cout << "-------------" << endl;

	struct three_char_vector count2;
	count2 = three_char_count("aaabbbb");
	print_vector(count2);
	cout << VAngle(count,count2) << endl;

	//adds the three char count of the text to an existing vector
	three_char_count_with_vector("aaabbbb", &count);
	cout << "adac" << endl;
	print_vector(count);



	ifstream t("MobyDick.txt");
	string str;

	t.seekg(0, ios::end);   
	str.reserve(t.tellg());
	t.seekg(0, ios::beg);

	str.assign((istreambuf_iterator<char>(t)),
	            istreambuf_iterator<char>());
	cout << "the" << endl;
	struct three_char_vector count3;
	cout << "the2" << endl;
	count3 = three_char_count(str);
	cout << "the3" << endl;
	print_vector(count3);
	cout << "hello" << endl;
	

	return 0;
 }