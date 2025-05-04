#include<iostream>
#include<string>
using namespace std;

class candidate;
class election;
class locelect;
class natelect;
class result;
class emanager;
class voter;
class admin;


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

	void viewresult(emanager* mgr);
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
	bool getisstarted()const {
		return isstarted;
	}
	bool getisended()const {
		return isended;
	}
	int getccount()const {
		return ccount;
	}
	candidate getcand(int index)const {
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

class voter : public user 
{
private:
	string name;
	int ccode;
	int age;
	bool vloc;
	bool vnat;

public:
	voter() : user()
	{
		name = "";
		ccode = 0;
		age = 0;
		vloc = false;
		vnat = false;
	}

	voter(const string& uname, const string& pwd, const string& n, int city, int a)
		: user(uname, pwd) {
		name = n;
		ccode = city;
		age = a;
		vloc = false;
		vnat = false;
	}
	void viewel(emgr* mgr) 
	{
		cout << "\n===== View Elections =====" << endl;
		cout << "1. Local Elections" << endl;
		cout << "2. National Elections" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";

		int choice;
		cin >> choice;

		if (choice == 1) {
			locelect* elect = mgr->findlelect(ccode);
			if (elect == nullptr) {
				cout << "No local election found for your city code." << endl;
				return;
			}

			elect->dispdetails();
		}
		else if (choice == 2)
		{
			natelect* elect = mgr->getnelect();
			if (elect == nullptr) {
				cout << "No national election found." << endl;
				return;
			}

			elect->dispdetails();
		}
	}

	void vote(emgr* mgr)
	{
		cout << "\n===== Cast Vote =====" << endl;
		cout << "1. Local Election" << endl;
		cout << "2. National Election" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";

		int choice;
		cin >> choice;

		if (choice == 1) 
		{
			if (vloc)
			{
				cout << "You have already voted in the local election." << endl;
				return;
			}

			locelect* elect = mgr->findlelect(ccode);
			if (elect == nullptr) {
				cout << "No local election found for your city code." << endl;
				return;
			}

			if (!elect->getisstarted() || elect->getisended()) 
			{
				cout << "Election is not active." << endl;
				return;
			}

			cout << "\n===== Local Election: " << elect->getname() << " =====" << endl;
			cout << "Candidates:" << endl;

			for (int i = 0; i < elect->getccount(); i++) 
			{
				candidate cand = elect->getcand(i);
				cout << i + 1 << ". ID: " << cand.getcid()
					<< ", Name: " << cand.getname()
					<< ", Party: " << cand.getparty() << endl;
			}

			int cchoice;
			cout << "Enter candidate number to vote (1-" << elect->getccount() << "): ";
			cin >> cchoice;

			if (cchoice >= 1 && cchoice <= elect->getccount())
			{
				
				int candId = elect->getcand(cchoice - 1).getcid();

				
				candidate* candPtr = mgr->findcand(candId);
				if (candPtr != nullptr)
				{
					candPtr->incvote();
					vloc = true;
					cout << "Vote cast successfully for " << candPtr->getname() << "." << endl;
				}
			}
			else {
				cout << "Invalid candidate number." << endl;
			}
		}
		else if (choice == 2) 
		{
			if (vnat) {
				cout << "You have already voted in the national election." << endl;
				return;
			}

			natelect* elect = mgr->getnelect();
			if (elect == nullptr) {
				cout << "No national election found." << endl;
				return;
			}

			if (!elect->getisstarted() || elect->getisended()) 
			{
				cout << "Election is not active." << endl;
				return;
			}

			cout << "\n===== National Election: " << elect->getname() << " =====" << endl;
			cout << "Candidates:" << endl;

			for (int i = 0; i < elect->getccount(); i++)
			{
				candidate cand = elect->getcand(i);
				cout << i + 1 << ". ID: " << cand.getcid()
					<< ", Name: " << cand.getname()
					<< ", Party: " << cand.getparty() << endl;
			}

			int cchoice;
			cout << "Enter candidate number to vote (1-" << elect->getccount() << "): ";
			cin >> cchoice;

			if (cchoice >= 1 && cchoice <= elect->getccount())
			{
				
				int candId = elect->getcand(cchoice - 1).getcid();

				candidate* candPtr = mgr->findcand(candId);
				if (candPtr != nullptr) 
				{
					candPtr->incvote();
					vnat = true;
					cout << "Vote cast successfully for " << candPtr->getname() << "." << endl;
				}
			}
			else {
				cout << "Invalid candidate number." << endl;
			}
		}
	}

	void status() 
	{
		cout << "\n===== Vote Status =====" << endl;
		cout << "Local Election: " << (vloc ? "Voted" : "Not Voted") << endl;
		cout << "National Election: " << (vnat ? "Voted" : "Not Voted") << endl;
	}

	void viewres(emgr* mgr)
	{
		cout << "\n===== View Results =====" << endl;
		cout << "1. Local Election Results" << endl;
		cout << "2. National Election Results" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";

		int choice;
		cin >> choice;

		if (choice == 1) 
		{
			if (!vloc) 
			{
				cout << "You have not voted in the local election." << endl;
				return;
			}

			locelect* elect = mgr->findlelect(ccode);
			if (elect == nullptr)
			{
				cout << "No local election found for your city code." << endl;
				return;
			}

			if (!elect->getisended())
			{
				cout << "Election has not ended yet. Results are not available." << endl;
				return;
			}

			result res(elect);
			res.disprvoter();
		}
		else if (choice == 2)
		{
			if (!vnat) {
				cout << "You have not voted in the national election." << endl;
				return;
			}

			natelect* elect = mgr->getnelect();
			if (elect == nullptr) {
				cout << "No national election found." << endl;
				return;
			}

			if (!elect->getisended()) {
				cout << "Election has not ended yet. Results are not available." << endl;
				return;
			}

			result res(elect);
			res.disprvoter();
		}
	}


	int getccode() const {
		return ccode;
	}

	bool getvloc() const {
		return vloc;
	}

	bool getvnat() const {
		return vnat;
	}

	string getname() const {
		return name;
	}

	int getage() const {
		return age;
	}

	void setvloc(bool status) {
		vloc = status;
	}

	void setvnat(bool status) {
		vnat = status;
	}
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
	void resultvoter() 
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

		cout << "\n-----Election Results-----" << endl;
		cout << "Election Name: " << electptr->getname() << endl;

		candidate winner = getwinner();
		if (winner.getcid() != 0)
		{
			cout << "\nWinner: " << winner.getname() << " (" << winner.getparty() << ") with " << winner.getvotes() << " Votes." << endl;
		}
		else
		{
			cout << "\nNo Winner Selected Yet!" << endl;
		}
	}
	void resultcandidate(int cid) 
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

		candidate target;
		bool found = false;
		for (int i = 0; i < electptr->getccount(); i++) 
		{
			candidate cand = electptr->getcand(i);
			if (cand.getcid() == cid) 
			{
				target = cand;
				found = true;
				break;
			}
		}

		if (!found) 
		{
			cout << "Candidate not found in this election." << endl;
			return;
		}

		cout << "\n-----Your Election Results-----" << endl;
		cout << "Election Name: " << electptr->getname() << endl;
		cout << "Your Votes: " << target.getvotes() << endl;

		candidate winner = getwinner();
		if (winner.getcid() == cid) 
		{
			cout << "Congratulations! You Won the Election." << endl;
		}
		else if (winner.getcid() != 0) 
		{
			cout << "Winner: " << winner.getname()<< " (" << winner.getparty() << ") with "<< winner.getvotes() << " Votes." << endl;
		}
		else 
		{
			cout << "No Winner Determined." << endl;
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

	candidate* cand;
	int ccount;
public:
	emanager()
	{
		lelection = NULL;
		lcount = 0;
		nelection = NULL;
		hasnat = 0;
		cand = NULL;
		ccount = 0;
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

	void displayle() 
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
	void displaycand(const string& cat) 
	{
		bool found = false;

		cout << "\n===== " << cat << " Candidates =====" << endl;
		for (int i = 0; i < ccount; i++) 
		{
			if (cand[i].getcat() == cat) 
			{
				cout << "ID: " << cand[i].getcid() << endl;
				cout<< "Name: " << cand[i].getname() << endl;
				cout<< "Party: " << cand[i].getparty() << endl;;

				if (cat == "local") 
				{
					cout << "City Code: " << cand[i].getcode();
				}

				cout << endl;
				found = true;
			}
		}

		if (!found) {
			cout << "No " << cat << " candidates found." << endl;
		}
	}

	localelection* findlelect(int ccode)
	{
		for (int i = 0; i < lcount; i++)
		{
			if (lelection[i].getccode() == ccode)
			{
				return &lelection[i];
			}
		}
		return NULL;
	}

	nationalelection* getnelect()
	{
		if (hasnat)
		{
			return nelection;
		}
		return NULL;
	}

	void addcandidate(candidate* c) 
	{
		candidate* newcand = new candidate[ccount + 1];

		for (int i = 0; i < ccount; i++) 
		{
			newcand[i] = cand[i];
		}

		newcand[ccount] = *c;

		delete[] cand;
		cand = newcand;
		ccount++;

		cout << "Candidate Added Successfully!" << endl;
	}

	candidate* findcand(int cid) 
	{
		for (int i = 0; i < ccount; i++) 
		{
			if (cand[i].getcid() == cid) 
			{
				return &cand[i];
			}
		}
		return NULL;
	}
	candidate* findcandbyuname(const string& uname) 
	{
		for (int i = 0; i < ccount; i++) 
		{
			if (cand[i].getusername() == uname) 
			{
				return &cand[i];
			}
		}
		return nullptr;
	}

	candidate* geteligiblecands(const string& cat, int ccode, int& count) 
	{
		count = 0;
		for (int i = 0; i < ccount; i++) 
		{
			if (cand[i].getcat() == cat) 
			{
				if (cat == "local") 
				{
					if (cand[i].getcode() == ccode) 
					{
						count++;
					}
				}
				else 
				{
					count++;
				}
			}
		}

		if (count == 0) 
		{
			return NULL;
		}
		
		candidate* ecand = new candidate[count];
		int index = 0;

		for (int i = 0; i < ccount; i++) 
		{
			if (cand[i].getcat() == cat) 
			{
				if (cat == "local") 
				{
					if (cand[i].getcode() == ccode) 
					{
						ecand[index++] = cand[i];
					}
				}
				else 
				{
					ecand[index++] = cand[i];
				}
			}
		}

		return ecand;
	}

	void addctoe() 
	{
		int choice;
		cout << "\n-----Add Candidates to Election-----" << endl;
		cout << "1. Local Election" << endl;
		cout << "2. National Election" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) 
		{
			int ccode;
			cout << "Enter city code: ";
			cin >> ccode;

			localelection* elect = findlelect(ccode);
			if (elect == NULL) 
			{
				cout << "No Election Found for City Code " << ccode << endl;
				return;
			}

			if (elect->getisstarted()) 
			{
				cout << "Cannot add Candidates to an Election that has already Started!" << endl;
				return;
			}

			int count;
			candidate* ecands = geteligiblecands("local", ccode, count);

			if (count == 0) 
			{
				cout << "No Eligible Candidates found for this City Code." << endl;
				return;
			}

			cout << "\nEligible Candidates:" << endl;
			for (int i = 0; i < count; i++) 
			{
				cout << i + 1 << ". ID: " << ecands[i].getcid() << endl;
				cout << "Name: " << ecands[i].getname() << endl;
				cout<< "Party: " << ecands[i].getparty() << endl;
			}

			int cidx;
			char cadd = 'y';

			while (cadd == 'y' || cadd == 'Y') 
			{
				cout << "Enter candidate number to add (1-" << count << ") or -1 to exit: ";
				int input;
				cin >> input;

				if (input == -1) 
				{
					break;
				}

				cidx = input - 1;

				if (cidx >= 0 && cidx < count) 
				{
					candidate* candPtr = findcand(ecands[cidx].getcid());
					if (candPtr != NULL) 
					{
						elect->addcand(candPtr);
						cout << "Candidate added to election." << endl;
					}
				}
				else
				{
					cout << "Invalid candidate number." << endl;
				}

				cout << "Add another candidate? (y/n): ";
				cin >> cadd;
			}

			delete[] ecands;
		}
		else if (choice == 2) 
		{
			nationalelection* elect = getnelect();
			if (elect == NULL) 
			{
				cout << "No national election found." << endl;
				return;
			}

			if (elect->getisstarted()) 
			{
				cout << "Cannot add candidates to an election that has already started." << endl;
				return;
			}

			int count;
			candidate* ecands = geteligiblecands("national", 0, count);

			if (count == 0) 
			{
				cout << "No eligible candidates found." << endl;
				return;
			}

			cout << "\nEligible Candidates:" << endl;
			for (int i = 0; i < count; i++) 
			{
				cout << i + 1 << ". ID: " << ecands[i].getcid() << endl;
				cout << "Name: " << ecands[i].getname() << endl;
				cout<< "Party: " << ecands[i].getparty() << endl;
			}

			int cidx;
			char cadd = 'y';

			while (cadd == 'y' || cadd == 'Y') 
			{
				cout << "Enter candidate number to add (1-" << count << ") or -1 to exit: ";
				int input;
				cin >> input;

				if (input == -1) 
				{
					break;
				}

				cidx = input - 1;

				if (cidx >= 0 && cidx < count) 
				{
					candidate* candPtr = findcand(ecands[cidx].getcid());
					if (candPtr != NULL) 
					{
						elect->addcand(candPtr);
						cout << "Candidate added to election." << endl;
					}
				}
				else 
				{
					cout << "Invalid candidate number." << endl;
				}

				cout << "Add another candidate? (y/n): ";
				cin >> cadd;
			}

			delete[] ecands;
		}
	}

	void startelection() 
	{
		int choice;
		cout << "\n-----Start Election-----" << endl;
		cout << "1. Local Election" << endl;
		cout << "2. National Election" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) 
		{
			int ccode;
			cout << "Enter city code: ";
			cin >> ccode;

			localelection* elect = findlelect(ccode);
			if (elect == NULL) 
			{
				cout << "No Election Found for city code " << ccode << endl;
				return;
			}

			if (elect->getisstarted()) 
			{
				cout << "Election has already started." << endl;
				return;
			}

			if (elect->getccount() == 0) 
			{
				cout << "Cannot start election with no candidates." << endl;
				return;
			}

			elect->start();
		}
		else if (choice == 2) 
		{
			nationalelection* elect = getnelect();
			if (elect == NULL) 
			{
				cout << "No National Election Found." << endl;
				return;
			}

			if (elect->getisstarted()) 
			{
				cout << "Election has already started." << endl;
				return;
			}

			if (elect->getccount() == 0) 
			{
				cout << "Cannot start election with no candidates." << endl;
				return;
			}

			elect->start();
		}
	}

	void endelection() 
	{
		int choice;
		cout << "\n-----End Election-----" << endl;
		cout << "1. Local Election" << endl;
		cout << "2. National Election" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) 
		{
			int ccode;
			cout << "Enter city code: ";
			cin >> ccode;

			localelection* elect = findlelect(ccode);
			if (elect == NULL) 
			{
				cout << "No Election Found for city code " << ccode << endl;
				return;
			}

			if (!elect->getisstarted()) 
			{
				cout << "Election has not started yet." << endl;
				return;
			}

			if (elect->getisended()) 
			{
				cout << "Election has already ended." << endl;
				return;
			}

			elect->end();
		}
		else if (choice == 2) 
		{
			nationalelection* elect = getnelect();
			if (elect == NULL) 
			{
				cout << "No National Election found." << endl;
				return;
			}

			if (!elect->getisstarted()) 
			{
				cout << "Election has not started yet." << endl;
				return;
			}

			if (elect->getisended()) 
			{
				cout << "Election has already ended." << endl;
				return;
			}

			elect->end();
		}
	}

	void viewresult() 
	{
		int choice;
		cout << "\n-----View Results-----" << endl;
		cout << "1. Local Election Results" << endl;
		cout << "2. National Election Results" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) 
		{
			int ccode;
			cout << "Enter city code: ";
			cin >> ccode;

			localelection* elect = findlelect(ccode);
			if (elect == NULL) 
			{
				cout << "No Election found for City code " << ccode << endl;
				return;
			}

			if (!elect->getisended()) 
			{
				cout << "Election has not ended yet. Results are not available." << endl;
				return;
			}

			result res(elect);
			res.resultadmin();
		}
		else if (choice == 2) 
		{
			nationalelection* elect = getnelect();
			if (elect == NULL) 
			{
				cout << "No National Election found." << endl;
				return;
			}

			if (!elect->getisended()) 
			{
				cout << "Election has not ended yet. Results are not available." << endl;
				return;
			}

			result res(elect);
			res.resultadmin();
		}
	}

	void mgrmenu()
	{
		int choice;
		cout << "\n-----Manage Election-----" << endl;
		cout << "1. Add Candidates to Election" << endl;
		cout << "2. Start Election" << endl;
		cout << "3. End Election" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) 
		{
		case 1:
			addctoe();
			break;
		case 2:
			startelection();
			break;
		case 3:
			endelection();
			break;
		default:
			break;
		}
	}


};
class user {
protected:
	string username;
	string password;

public:
	user(const string& uname = "", const string& pwd = "") 
	{
		username = uname;
		password = pwd;
	}

	virtual ~user() {
	}

	bool login(const string& uname, const string& pwd) 
	{
		return (username == uname) && (password == pwd);
	}

	string getusername() const 
	{
		return username;
	}
};
	
class admin : public user
{
public:
	admin() : user()
	{
		username = "admin";
		password = "admin123";
	}

	admin(const string& uname, const string& pwd) : user(uname, pwd)
	{
	}
	void createcand(emanager* mgr) 
	{
		string name;
		int ccode;
		int cid;
		string username;
		string password;
		string party;
		string category;

		cout << "\n===== Create Candidate =====" << endl;

		cin.ignore();

		cout << "Enter candidate name: ";
		getline(cin, name);

		cout << "Enter city code: ";
		cin >> ccode;

		cout << "Enter candidate ID: ";
		cin >> cid;

		cin.ignore();

		cout << "Enter username: ";
		getline(cin, username);

		cout << "Enter password: ";
		getline(cin, password);

		cout << "Enter party name: ";
		getline(cin, party);

		cout << "Enter category (local/national): ";
		getline(cin, category);

		candidate* cptr = new candidate(name, ccode, cid, username, password, party, category);
		mgr->addcandidate(cptr);
		delete cptr;	
	}
	void viewel(emanager* mgr) 
	{
		int choice;
		cout << "\n===== View Elections =====" << endl;
		cout << "1. Local Elections" << endl;
		cout << "2. National Elections" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) 
		{
			mgr->displayle();
		}
		else if (choice == 2) 
		{
			mgr->displayne();
		}
	}

	void viewcands(emanager* mgr) 
	{
		int choice;
		cout << "\n===== View Candidates =====" << endl;
		cout << "1. Local Candidates" << endl;
		cout << "2. National Candidates" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) 
		{
			mgr->displaycand("local");
		}
		else if (choice == 2) 
		{
			mgr->displaycand("national");
		}
	}
	void creel(emanager* mgr)
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

			localelection* elect = new localelection(name, rules, ccode);
			mgr->addlelection(elect);
			delete elect;
		}
		else if (choice == 2)
		{
			string name;
			string rules;

			cin.ignore();

			cout << "Enter election name: ";
			getline(cin, name);

			cout << "Enter election rules: ";
			getline(cin, rules);

			nationalelection* elect = new nationalelection(name, rules);
			mgr->addnelection(elect);
			delete elect;
		}
	}
};
void candidate::viewresult(emanager* mgr) 
{
	string cat = getcat();
	int cid = getcid();

	if (cat == "local") 
	{
		localelection* elect = mgr->findlelect(getcode());
		if (elect != nullptr && elect->getisended()) 
		{
			result res(elect);
			cout << "Local election results for your candidacy:" << endl;
		}
		else 
		{
			cout << "No ended election found for your city code." << endl;
		}
	}
	else if (cat == "national") 
	{
		nationalelection* elect = mgr->getnelect();
		if (elect != nullptr && elect->getisended()) 
		{
			result res(elect);
			cout << "National election results for your candidacy:" << endl;
		}
		else 
		{
			cout << "No ended national election found." << endl;
		}
	}
}

int main() {
	emanager* mgr = new emanager();
	admin* adm = new admin();

	cout << "===== Online Voting System =====" << endl;
	cout << "Welcome to the Online Voting System!" << endl;
	cout << "This system allows for managing elections, candidates, and voters." << endl;
	cout << "Default admin credentials: username: admin, password: admin123" << endl;
	cout << "===============================" << endl;

	bool running = true;
	while (running) {
		cout << "\n===== Online Voting System =====" << endl;
		cout << "1. Admin" << endl;
		cout << "2. Candidate" << endl;
		cout << "3. Voter" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";

		int choice;
		cin >> choice;

		switch (choice) {
		case 1: {
			string uname, pwd;
			cout << "\n===== Admin Login =====" << endl;
			cout << "Username: ";
			cin >> uname;
			cout << "Password: ";
			cin >> pwd;

			if (adm->login(uname, pwd)) {
				cout << "Login successful!" << endl;

				bool arun = true;
				while (arun) {
					cout << "\n===== Admin Menu =====" << endl;
					cout << "1. Create Election" << endl;
					cout << "2. Create Candidate" << endl;
					cout << "3. Exit" << endl;
					cout << "Enter your choice: ";

					int achoice;
					cin >> achoice;

					switch (achoice) {
					case 1:
						adm->creel(mgr);
						break;
					case 2:
						adm->createcand(mgr);
						break;
					case 3:
						arun = false;
						cout << "Returning to main menu." << endl;
						break;
					default:
						cout << "Invalid choice. Please try again." << endl;
					}
				}
			}
			else {
				cout << "Invalid username or password." << endl;
			}
			break;
		}
		case 2: {
			string uname, pwd;
			cout << "\n===== Candidate Login =====" << endl;
			cout << "Username: ";
			cin >> uname;
			cout << "Password: ";
			cin >> pwd;

			candidate* cptr = mgr->findcandbyuname(uname);
			if (cptr != nullptr && cptr->login(uname, pwd)) {
				cout << "Login successful!" << endl;

				bool crun = true;
				while (crun) {
					cout << "\n===== Candidate Menu =====" << endl;
					cout << "1. View Info" << endl;
					cout << "2. View Votes Received" << endl;
					cout << "3. View Result" << endl;
					cout << "4. Exit" << endl;
					cout << "Enter your choice: ";

					int cchoice;
					cin >> cchoice;

					switch (cchoice) {
					case 1:
						cptr->disinfo();
						break;
					case 2:
						cptr->viewvotes();
						break;
					case 3:
						cptr->viewresult(mgr);
						break;
					case 4:
						crun = false;
						cout << "Returning to main menu." << endl;
						break;
					default:
						cout << "Invalid choice. Please try again." << endl;
					}
				}
			}
			else {
				cout << "Invalid username or password." << endl;
			}
			break;
		}
		
		case 3: {
			cout << "Voter functionality will be implemented in the next version." << endl;
			break;
		}
		case 4:
			running = false;
			cout << "Exiting system. Goodbye!" << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	delete mgr;
	delete adm;
	return 0;
}

