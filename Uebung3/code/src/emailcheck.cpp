#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

#define ENTRIES 7

std::wstring dataset[ENTRIES][4] = { { L"max.muestermann@bmw.de", L"Max", L"Mustermann", L"SAP" },
    { L"juergen.doellner@hpi.de", L"Jürgen", L"Döllner", L"HPI" },
    { L"soeren.discher@hpi.de", L"Sören", L"Discher", L"HPI" } ,
    { L"daniel.maeller@hpi.de", L"Daniel", L"Mäller", L"HPI" },
    { L"paul.deissler@hertha.de", L"Sebastian", L"Deißler", L"herTha" },
	{ L"mueller.marga@sap.com", L"Marga", L"Müller", L"SAP" },
    { L"h.boss@service.bayer.com", L"Hugo", L"Boss", L"Bayer" }};

//Replaces [from] with [to] in [str]
void ReplaceAll(std::wstring& str, const std::wstring& from, const std::wstring& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

//ToDo 3.1a - implement use std::transform()
void caseConvert(std::wstring& str) {
   std::transform(str.begin(),str.end(),str.begin(), ::tolower);
}

//ToDo 3.1b - implement replacement for ä, ö, ü, ß with ae,oe,ue,ss
//			- use ReplaceAll. wstrings are declared the same way as normal strings but with an "L" in front
void replace(std::wstring& str) {
  ReplaceAll(str,L"ä",L"ae");
  ReplaceAll(str,L"ü",L"ue");
  ReplaceAll(str,L"ö",L"oe");
  ReplaceAll(str,L"ß",L"ss");
}

//ToDo 3.1c - check if email is correct
bool emailCheck(std::wstring mail, std::wstring firstname, std::wstring name, std::wstring company)
{
	std::wstring generalCheck(L"^[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}$");

	//create 2 different regex patterns: 1 for mails like firstname.lastname and 1 for lastname.firstname
	std::wstring tokenCheckStartFirstname = std::wstring(L"^(") + firstname[0] + L"|" + firstname + L")[_.-]{1}(" + name[0] + L"|" + name + L")@[a-z0-9.-]*(" + company + L")[a-z0-9.-]*\\.[a-z]{2,4}$";
	std::wstring tokenCheckStartLastname = std::wstring(L"^(") + name[0] + L"|" + name + L")[_.-]{1}(" + firstname[0] + L"|" + firstname + L")@[a-z0-9.-]*(" + company + L")[a-z0-9.-]*\\.[a-z]{2,4}$";

	#if 0
	bool match1 = regex_match(mail, std::wregex(generalCheck));
	bool match2 = rgex_match(mail, std::wregex(tokenCheckStartFirstname));
	#endif

	if( regex_match(mail, std::wregex(generalCheck) ) && (regex_match(mail, std::wregex(tokenCheckStartFirstname) ) || regex_match(mail, std::wregex(tokenCheckStartLastname)) ) )
		return true;
	else
		return false;   
}

int main(int argc, char * argv[])
{
    for (int i = 0; i < ENTRIES; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            replace(dataset[i][j]);
            caseConvert(dataset[i][j]);
        }
        
        std::cout << emailCheck(dataset[i][0], dataset[i][1], dataset[i][2], dataset[i][3]) << std::endl;
	std::wcout << dataset[i][0] <<  "; " << dataset[i][1] << ", " << dataset[i][2] << ", " << dataset[i][3] << std::endl;

    }
    
    return 0;
    
}
