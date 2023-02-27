#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include "date.h"
#include "transaction.h"
using namespace std;

Transaction parse(string record)
{
	/*Implement this function to parse each record into Transaction
	 object and return */ 

	istringstream stream; //new object for putting record into
	stream.str(record); //populates stream with contents of record
	string d, m, y, h, min;
	string pro, pri, payT, n, c, s, coun;

	getline(stream, d, '/');   //grabs day
	getline(stream, m, '/');   //grabs month
	getline(stream, y, ' ');       //grabs year
	getline(stream, h, ':');   //grabs hour
	getline(stream, min, ','); //grabs minute

	Date newDate(stoi(y), stoi(m), stoi(d), stoi(h), stoi(min)); //makes new date with information grabbed

	getline(stream, pro, ','); //grabs product
	getline(stream, pri, ','); //grabs price
	getline(stream, payT, ',');//grabs payment Type
	getline(stream, n, ',');   //grabs name
	getline(stream, c, ',');   //grabs city
	getline(stream, s, ',');   //grabs state
	getline(stream, coun, ',');//grabs country
		
	Transaction newRecord(newDate, pro, stoi(pri), payT, n, c, s, coun);

	return newRecord;
}

/*Function to return the filesize in bytes*/
int fileSize(string filename)
{
	ifstream in_file(filename,ios::binary);
	in_file.seekg(0,ios::end);
	int file_size=in_file.tellg();

	return file_size;
}

/*Function to readfile and return vector of Transaction
objects.*/
vector<Transaction> readFile(string filename)
{

	/*Handle file not found exception by throwing the string
	"filename" and also handle big file exception by 
	throwing the filesize*/
	

	vector<Transaction> transactions;
	string line;

	ifstream myFile(filename);

	//FILE NOT FOUND EXCEPTION
	try
	{
		if (!myFile.is_open()) { throw filename; }

	}
	catch (string filename)
	{
		cout << "File " << filename << " not found." << endl;
		return transactions;
	}

	//BIG FILE EXCEPTION
	try
	{ 
		if (fileSize(filename) > 5000) { throw fileSize(filename); }

	}
	catch(int fileS)
	{
		cout << "File size: " << fileS << ". Limit exceeded." << endl;
		return transactions;
	}

	int lineCount=0;
	while(getline(myFile,line))
	{
		//Parse the line here ignoring the first line
		if(lineCount>0)
		{
			transactions.push_back(parse(line));
		}
		lineCount++;
	}

	return transactions;	
}

/*Template function to sort and print*/
template <class T>
void sortAndPrint(vector<T> records,int size)
{
	//Implement this function to sort the vectors and print

	//bubble sort
	for (int i = 0; i < size - 1; i++) {

		for (int j = 0; j < size - i - 1; j++)
		{
			if (records[j] > records[j + 1]) 
			{
				T temp;
				temp = records[j];
				records[j] = records[j + 1];
				records[j + 1] = temp;
			}
		}
	}
	//print
	for (int x = 0; x < size; x++) {

		cout << records[x] << endl;

	}
}

int main(int argc,char * argv[])
{
	//Wrong file name
	string wrongFile="wrongfile.csv";

	//Big file name
	string bigFile="bigFile.csv";

	//Correct file name
	string file="SalesJan2009.csv";

	//vector to hold all the transactions
	vector<Transaction> transactions;

	cout<<"Reading wrongfile.csv"<<endl;
	transactions=readFile(wrongFile);

	cout<<"Reading bigFile.csv"<<endl;
	transactions=readFile(bigFile);

	cout<<"Reading SalesJan2009.csv"<<endl;
	transactions= readFile(file);

	cout <<"File read."<<transactions.size()<<" transactions returned"<<endl;
	
	//BAD ALLOC EXCEPTION
	try
	{
		while (true)
		{
			new int[100000000ul];
		}

		throw bad_alloc();
	}
	catch(bad_alloc error)
	{
		cout << "Allocation Failed." <<  error.what() << endl;
	}

	//sort by name
	vector<string> names;
	vector<int> price;
	vector<Date> dates;
	
	//LENGTH ERROR EXCEPTION
	try {

		//Resizing the vectors	
		names.resize(names.max_size() + 1);
		price.resize(price.max_size() + 1);
		dates.resize(dates.max_size() + 1);

	}
	catch (length_error error)
	{
		cout << "Length error." << error.what() << endl;
		names.resize(25);
		price.resize(25);
		dates.resize(25);
	}

	//OUT OF RANGE EXCEPTION
	try {

		int number;
		cout << "Enter the number of records to sort(1-25):";
		cin >> number;

		if (number > 25) { throw out_of_range(to_string(number)); }

		for (int i = 0; i < number; i++)
		{
			names.at(i) = transactions[i].getName();
			price.at(i) = transactions[i].getPrice();
			dates.at(i) = transactions[i].getDate();
		}
		sortAndPrint(names, number);
		sortAndPrint(dates, number);
		sortAndPrint(price, number);

	}
	catch (exception error)
	{
		cout << "Number of records to sort exceed the maximum vector size." << error.what() << endl;

	}

	return 0;
}