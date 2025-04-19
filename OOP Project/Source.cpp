#include<iostream>
#include<string>
using namespace std;

class candidate {
private:
	string name;
	int ccode;
	int cid;
	string username;
	string password;
	string party;
	string catagory;
	int votes;
public:
	candidate(string n = " ", int city = 0, int id = 0, string uname = "", string pwd = "", string pty = "", string cat = "") :
		name(n), ccode(city), cid(id), username(uname), password(pwd), party(pty), catagory(cat), votes(0)
	{}
	string getname()const {
		return name;
	}
	int getcode() const {
		return ccode;
	}
	int getcid() const {
		return cid;
	}
	string getparty() const {
		return party;
	}
	string getcat() const {
		return catagory;
	}
	int getvotes() const {
		return votes;

	}
	string getusername() const {
		return username;
	}
	void setvotes(int v) {
		votes = v;
	}
	void disinfo() {
		cout << "candidate ID: " << cid << endl;
		cout << "Name:" << name << endl;
		cout << "City code: " << ccode << endl;
		cout << "Party: " << party << endl;
		cout << "Catagory: " << catagory << endl;
	}

	void incvote() {
		votes++;
	}bool login(string uname, string pwd) {
		return (username == uname) && (password == pwd);

	}

};
class election {
protected:
	string name;
	string rules;
	bool isstarted;
	bool isended;
	candidate* cands;
	int ccount;
public:
	election(string n = "", string r = "", bool s = false, bool e = false) :
		name(n), rules(r), isstarted(s), isended(e)
	{}
	 virtual ~election() {
		delete[] cands;
	}
	string getname() const {
		return name;
	}
	bool getisstarted() const {
		return isstarted;
	}
	bool getisended() const {
		return isended;
	}
	int getccount() const {
		return ccount;
	}
	candidate getcand(int index) {
		if (index >= 0 && index < ccount) {
			return cands[index];
		}
		return candidate();

	}

	virtual void dispdetails() = 0;
	void addand(candidate* cptr) {
		if (isstarted) {
			cout << " Cannot add candidate after election has started." << endl;
			return;
		}
		candidate* newcands = new candidate[ccount+1];
		for (int i = 0; i < ccount; i++) {
			newcands[i] = cands[i];
		
		}
		newcands[ccount] = *cptr;

		delete[] cands;
		cands = newcands;
		ccount++;

	}

};


class locelect :public election {
private:
	int ccode;
public:
	locelect(string name="", string r=" ",int city= 0) : election(name, r) {
		this->ccode = city;
	}
	void dispdetails() {
		cout << "\n===== Local Election Details =====\n" << endl;
		cout << "Election Name: " << getname() << endl;
		cout << "City Code: " << ccode << endl;
		cout << "Rules: " << rules << endl;
		cout << "Status: " << (getisstarted() ? "Started" : "Not Started") << endl;
		cout << "Ended : " << (getisended() ? "Yes" : "No") << endl;
	}
	int getccode() const {
		return ccode;
	}
};

class result
{
private:
	election* electptr;
public:
	result(election* eptr = NULL)
	{
		electptr = eptr;
	}
	void resultadmin()
	{
		if (electptr == NULL)
		{
			cout << "No Election Data Available!" << endl;
			return;
		}
		else if (!electptr->getisended())
		{
			cout << "Election is not ended yet." << endl;
			return;
		}
		cout << "\n----Election Result-----\n";
		cout << "Election Name:" << electptr->getname()<<endl;
		cout << "Total Candidates:" << electptr->getccount() << endl;
	}
};

class emanager
{
private:
	locale* lelection;
	int lcount;
public:
	emanager()
	{
		lelection = NULL;
		lcount = 0;
	}
	void addlelect(locelect* e)
	{
		locelect* newe = new locelect[lcount + 1];
		for (int i = 0; i < lcount; i++)
		{
			newe[i] = lelection[i];
		}

		newe[lcount] = *e;
		delete[] lelection;
		lelection = newe;
		lcount++;

		cout << "Local election Added Successfully!" << endl;
	}
};

int main() 
{

	return 0;
}
