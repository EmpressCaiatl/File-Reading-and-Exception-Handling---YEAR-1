#include <iostream>
using namespace std;
/*Date class to hold the full date and time*/
class Date
{
	//friend function to overlaed insertion operator to print the date
	friend ostream& operator<<(ostream& obj,Date d);
private:
	int year;
	int month;
	int day;
	int hour;
	int min;
public:
	Date(int y,int m,int d,int h,int mi)
	{
		year=y;
		month=m;
		day=d;
		hour=h;
		min=mi;
	}
	Date()
	{

	}

	/*overloading > operator to check which date is later. 
	Date returned by this function is the later one*/
	bool operator>(Date& other)
	{
		if(year>other.year)
			return true;
		else if(year==other.year && month>other.month )
			return true;
		else if(year==other.year && month==other.month && day>other.day)
			return true;
		else if(year==other.year && month==other.month && day==other.day && hour>other.hour)
			return true;
		else if(year==other.year && month==other.month && day==other.day && hour==other.hour && min>other.min)
			return true;
		else
			return false;
	}
	virtual ~Date(){/*do this*/}
};
ostream& operator<<(ostream& obj,Date d)
{
	obj<<d.year<<"/"<<d.month<<"/"<<d.day<<" "<<d.hour<<":"<<d.min;
	return obj;
}