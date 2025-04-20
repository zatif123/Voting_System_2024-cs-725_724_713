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
	void viewvotes() {
		cout << "You hae received " << votes << "votes." << endl;
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
	{
	}
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
	void addcand(candidate* cptr) {
		if (isstarted) {
			cout << " Cannot add candidate after election has started." << endl;
			return;
		}
		candidate* newcands = new candidate[ccount + 1];
		for (int i = 0; i < ccount; i++) {
			newcands[i] = cands[i];

		}
		newcands[ccount] = *cptr;

		delete[] cands;
		cands = newcands;
		ccount++;

	}
	void start() {
		if (ccount == 0) {
			cout << "Cannot start Election with no candiadates." << endl;
			return;
		}
		isstarted = true;
		cout << "Election " << name << "has started." << endl;

	}
	void end() {
		if (!isstarted) {
			cout << "Cannot end an electionthat hasnot started." << endl;
			return;
		}
		isended = true;
		cout << "Election " << name << "has ended." << endl;
		calcresult();
	}
	virtual void calcresult() = 0;

};


class localelection :public election {
private:
	int ccode;
public:
	localelection(string name = "", string r = " ", int city = 0) : election(name, r) {
		this->ccode = city;
	}
	void dispdetails() {
		cout << "\n===== Local Election Details =====\n" << endl;
		cout << "Election Name: " << getname() << endl;
		cout << "City Code: " << ccode << endl;
		cout << "Rules: " << rules << endl;
		cout << "Status: " << (getisstarted() ? "Started" : "Not Started") << endl;
		cout << "Ended : " << (getisended() ? "Yes" : "No") << endl;
		cout << "Number of Candidates: " << getccount() << endl;

		if (getccount() > 0) {
			cout << "\n Candidates:" << endl;
			for (int i = 0;i < getccount();i++){
				candidate cand = getcand(i);
				cout<<i+1<<" . Id: <<cand.getcid()"<<", Name:"<<cand.getname()
					<< ", Party:" << cand.getparty() << endl;

			}
		}
	}
	void calcresult() {
		if (!getisended()) {
			cout << "Cannot calculate results for an election that hasn't ended." << endl;
			return;

		}
		cout << "calculating results for local election in city code " << ccode << "...." << endl;

		int mvotes = -1;
		candidate winner;
		bool haswinner = false;

		for (int i = 0; i < getccount(); i++) {
			candidate cand = getcand(i);
			if (cand.getvotes() > mvotes) {
				mvotes = cand.getvotes();
				winner = cand;
				haswinner = true;
			}
		}
		if (haswinner) {
			cout << "Winner: " << winner.getname() <<"with "<<mvotes<< "votes."<< endl;
		}
		else {
			cout << "No Winner Determined." << endl;
		}
	}
	int getccode() const {
		return ccode;
	}
};
class nationalelection :public election {
public:
	nationalelection(string name = "", string r = " ") : election(name, r) 
	{}
	void dispdetails() {
		cout << "\n=====National Election Details=====" << endl;
		cout << "Election Name: " << getname() << endl;
		cout << "Rules:" << rules << endl;
		cout << "Status:" <<(getisstarted()? "Started" : "Not Started") << endl;
		cout << "Ended:" <<(getisended() ?"Yes" : "No") << endl;
		cout << "Number of Candidates:" <<getccount() << endl;
		if (getccount()>0)
		{
			cout << "\nCandidates:" << endl;
			for (int i = 0; i < getccount(); i++) {
				candidate cand = getcand(i);
				cout << i + 1 << ".ID: " << cand.getcid()
					<< ",Name:" << cand.getname()
					<< ",Party:" << cand.getparty() << endl;


			}
		}
	}
	void calcresult()  {
		if (!getisended()) 
		{
			cout << "Cannot calculate results for an election that hasn't ended." << endl;
			return;
		}

		cout << "Calculating results for national election..." << endl;

		int mvotes = -1;
		candidate winner;
		bool hasWinner = false;

		for (int i = 0; i < getccount(); i++)
		{
			candidate cand = getcand(i);
			if (cand.getvotes() > mvotes) {
				mvotes = cand.getvotes();
				winner = cand;
				hasWinner = true;
			}
		}

		if (hasWinner)
		{
			cout << "Winner: " <<winner.getname() << " with" << mvotes << " votes." << endl;
		}
		else 
		{
			cout << "No winner determined." << endl;
		}
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

	candidate getwinner() 
	{
		if (electptr == NULL || !electptr->getisended() || electptr->getccount() == 0) 
		{
			return candidate();
		}

		candidate winner = electptr->getcand(0);
		int votes = winner.getvotes();

		for (int i = 1; i < electptr->getccount(); i++) 
		{
			candidate cand = electptr->getcand(i);
			if (cand.getvotes() > votes) 
			{
				winner = cand;
				votes = cand.getvotes();
			}
		}
		return winner;
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
		cout << "Election Name:" << electptr->getname() << endl;
		cout << "Total Candidates:" << electptr->getccount() << endl;

		cout << "\nVotes by Candidate:" << endl;
		for (int i = 0; i < electptr->getccount(); i++) 
		{
			candidate cand = electptr->getcand(i);
			cout << "Candidate ID: " << cand.getcid() << endl;
			cout<< "Name: " << cand.getname() << endl;
			cout<< "Party: " << cand.getparty() << endl;
			cout<< "Votes: " << cand.getvotes() << endl;
		}

		candidate winner = getwinner();
		if (winner.getcid() != 0) 
		{
			cout << "\nWinner: " << winner.getname()<< " (" << winner.getparty() << ") with "<< winner.getvotes() << " Votes." << endl;
		}
		else 
		{
			cout << "\nNo Winner Selected Yet!" << endl;
		}
	}
};

class emanager
{
private:
	localelection* lelection;
	int lcount;

	nationalelection* nelection;
	bool hasnat;
public:
	emanager()
	{
		lelection = NULL;
		lcount = 0;
		nelection = NULL;
		hasnat = 0;
	}

	void addlelection(localelection* e)
	{
		localelection* newe = new localelection[lcount + 1];
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

	void addnelection(nationalelection* e) {
		if (hasnat) {
			cout << "National Election Already Exists!" << endl;
			return;
		}

		nelection = new nationalelection(*e);
		hasnat = true;
		cout << "National Election Added Successfully!" << endl;
	}

	void displayel() 
	{
		if (lcount == 0) 
		{
			cout << "No Local Elections Found." << endl;
			return;
		}
		cout << "\n-----Local Elections-----" << endl;
		for (int i = 0; i < lcount; i++) 
		{
			cout << i + 1 << ". City Code: " << lelection[i].getccode() << endl;
			cout<< "Name: " << lelection[i].getname() << endl;
			cout<< "Status: " << (lelection[i].getisstarted() ? "Started" : "Not Started") << endl;
			cout<< "Ended: " << (lelection[i].getisended() ? "Yes" : "No") << endl;
		}
	}

	void displayne() 
	{
		if (!hasnat) 
		{
			cout << "No National Election Found." << endl;
			return;
		}

		cout << "\n-----National Election-----" << endl;
		cout << "Name: " << nelection->getname() << endl;
		cout << "Status: " << (nelection->getisstarted() ? "Started" : "Not Started") << endl;
		cout<< "Ended: " << (nelection->getisended() ? "Yes" : "No") << endl;
	}

};
	class user {
	protected:
		string username;
		string password;

	public:
		user(const string& uname = "", const string& pwd = "") {
			username = uname;
			password = pwd;
		}

		virtual ~user() {
		}

		bool login(const string& uname, const string& pwd) {
			return (username == uname) && (password == pwd);
		}

		string getusername() const {
			return username;
		}
	};
	
	class admin : public user {
	public:
		admin() : user() 
		{
			username = "admin";
			password = "admin123";
		}

		admin(const string& uname, const string& pwd)
			: user(uname, pwd)
		{
		}

		void creel(emgr* mgr) 
		   {
			int choice;
			cout << "\n===== Create Election =====" << endl;
			cout << "1. Local Election" << endl;
			cout << "2. National Election" << endl;
			cout << "3. Exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			if (choice == 1) 
			{
				string name;
				string rules;
				int ccode;

				cout << "Enter city code: ";
				cin >> ccode;
				cin.ignore();

				cout << "Enter election name: ";
				getline(cin, name);

				cout << "Enter election rules: ";
				getline(cin, rules);

				locelect* elect = new locelect(name, rules, ccode);
				mgr->addlelect(elect);
				delete elect; 
			}
			else if (choice == 2) {
				string name;
				string rules;

				cin.ignore();

				cout << "Enter election name: ";
				getline(cin, name);

				cout << "Enter election rules: ";
				getline(cin, rules);

				natelect* elect = new natelect(name, rules);
				mgr->addnelect(elect);
				delete elect; 
			}
		}


	int main()
	{

		return 0;
	}

