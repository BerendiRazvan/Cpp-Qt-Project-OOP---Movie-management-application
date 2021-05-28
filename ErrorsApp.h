#pragma once
#include <iostream>
#include <string>

using namespace std;



class RepoException {
private:
	string eroare;

public:
	RepoException(string eroare) :eroare{ eroare } {}

	string returnError() {
		return eroare;
	}

};



class RepoFisException {
private:
	string eroare;

public:
	RepoFisException(string eroare) :eroare{ eroare } {}

	string returnError() {
		return eroare;
	}

};

class ServException {
private:
	string eroare;

public:
	ServException(string eroare) :eroare{ eroare } {}

	string returnError() {
		return eroare;
	}

};



class CosException {
private:
	string eroare;

public:
	CosException(string eroare) :eroare{ eroare } {}

	string returnError() {
		return eroare;
	}

};

