#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

class Student
{
	string name;
	string Id;
	int nos;
	int sem = 1;
	float val = 0.0;
	float Sgpa = 0.0;
	float Tgpa = 0.0;
	float Tcrehr = 0.0;

public:

	void capatial(string& s)
	{
		for (int i = 0; i < s.size(); i++)
		{
			s[i] = toupper(s[i]);
		}
	}

	void check(string& s, fstream& rdr)
	{

		char x;
		while (rdr.get(x))
		{
			for (int i = 0; x == s[i]; i++)
			{
				rdr.get(x);
				if (i == 10)
				{
					this->sem++;
					for (int i = 0; i < 8; i++)
					{
						rdr.get(x);
					}

					this->val = this->val + (x - 48);
					rdr.get(x);
					char ch = x;
					if (ch == '\n')
					{
						break;
					}
					float a = 0;
					rdr.get(x);
					a = (x - 48);
					a = a / 10.0;
					this->val = this->val + a;

					rdr.get(x);
					ch = x;
					if (ch == '\n')
					{
						break;
					}

					a = a + (x - 48);
					a = a / 100;
					this->val = this->val + a;

				}
			}
		}
	}

	void Initialization(fstream& rdr)

	{
		rdr.open("DataSavings.txt", ios::in);
		cout << "Enter the name of Student : ";
		cin.ignore();
		getline(cin, this->name);
		cout << endl;
		cout << "Enter the Student ID : ";
		getline(cin, this->Id);
		capatial(this->Id);
		check(this->Id, rdr);
		cout << endl;
		cout << "Enter the total number of sujects : ";
		cin >> this->nos;
		cout << endl;
		rdr.close();
	}

	float CalculateGPA()
	{
		int Ch = 0;  float per = 0; float Tmarks = 0; float Omarks = 0; string Sname; string grade;
		float gpa = 0;
		for (int i = 0; i < this->nos; i++)
		{
			cout << "Enter the name of Subject " << i + 1 << " : ";
			cin >> Sname;
			cout << endl;

			cout << "Enter the Credit hours of " << Sname << " : ";
			cin >> Ch;
			cout << endl;

			cout << "Enter the Total Marks of " << Sname << " : ";
			cin >> Tmarks;
			cout << endl;

			cout << "Enter the Obtained Marks of " << Sname << " : ";
			cin >> Omarks;
			cout << endl;

			per = (Omarks / Tmarks) * 100;

			if (per >= 90 && per <= 100)
			{
				grade = "A+";
				gpa = 4.0;
			}
			else if (per >= 80 && per < 90)
			{
				grade = "A-";
				gpa = 3.7;
			}
			else if (per >= 70 && per < 80)
			{
				grade = "B+";
				gpa = 3.3;
			}
			else if (per >= 60 && per < 70)
			{
				grade = "B";
				gpa = 3.0;
			}
			else if (per >= 50 && per < 60)
			{
				grade = "B-";
				gpa = 2.7;

			}
			else if (per >= 40 && per < 50)
			{
				grade = "C+";
				gpa = 2.3;
			}
			else if (per >= 30 && per < 40)
			{
				grade = "C";
				gpa = 2.0;
			}
			else if (per >= 20 && per < 30)
			{
				grade = "C-";
				gpa = 1.7;
			}
			else
			{
				grade = "F";
				gpa = 0.0;
			}

			cout << Sname << "  ---> " << grade << endl;
			gpa *= Ch;
			this->Tcrehr += Ch;
			this->Sgpa += gpa;
		}
		this->Sgpa = this->Sgpa / this->Tcrehr;
		return (this->Sgpa);
	}

	float CalculateCGPA()
	{
		this->Tgpa = (this->val + this->Sgpa) / this->sem;
		return this->Tgpa;
	}

	string getname()
	{
		return this->name;
	}

	string getID()
	{
		return this->Id;
	}
};

int main()
{
	int NOS = 0;
	cout << "Enter the number of students :  ";
	cin >> NOS;
	cout << endl;
	Student* s = new Student[NOS];
	float* gpaarray = new float[NOS];
	float* Cgpaarray = new float[NOS];

	fstream rdr;

	for (int i = 0; i < NOS; i++)
	{
		s[i].Initialization(rdr);
		gpaarray[i] = (s[i].CalculateGPA());
		Cgpaarray[i] = (s[i].CalculateCGPA());
		rdr.open("DataSavings.txt", ios::app);
		rdr << s[i].getID();
		rdr << "        ";
		rdr << gpaarray[i];
		rdr << endl;
		rdr.close();
	}
	cout << "Do you want to see the total GPA (Y/N)";
	char sym;
	cin >> sym;

	if (sym == 'N' || sym == 'n')
	{
		exit(1);
	}
	else
	{
		system("cls");
		cout << setw(20) << "Students Name " << setw(20) << "Students ID " << setw(20) << "Students SGPA" << setw(20) << "Students CGPA" << endl << endl;
		for (int i = 0; i < NOS; i++)
		{
			cout << setw(20) << s[i].getname() << setw(20) << s[i].getID() << setw(20) << fixed << setprecision(2) << gpaarray[i] << setw(20) << fixed << setprecision(2) << Cgpaarray[i] << endl;
		}
	}


	cout << endl << endl << endl;
	delete[] s;
	return 0;
}