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
int main() 
{

	return 0;
}
