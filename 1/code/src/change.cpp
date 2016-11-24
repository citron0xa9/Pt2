
#include <cstdlib>
#include <iostream>
#include <fstream>


/*
*********************************************************************
Basic linked list implementation for efficient representation of Change output follows
*/
typedef struct ChangeTuple {
	unsigned int value;
	unsigned int amount;
	struct ChangeTuple *next;
	struct ChangeTuple *prev;
} ChangeTuple_t;

typedef struct ChangeData {
	ChangeTuple_t *first;
	ChangeTuple_t *last;
} ChangeData_t;


ChangeTuple_t* CreateEntry(unsigned int value, unsigned int amount)
{
	ChangeTuple_t *entry = new ChangeTuple_t;

	entry->value = value;
	entry->amount = amount;
	entry->next = NULL;
	entry->prev = NULL;

	return entry;
}

void DeleteEntry(ChangeTuple_t *entry)
{
	delete entry;
}

void AddEntry(ChangeData_t *data, ChangeTuple_t *entry)
{
	if (data->last) {	//is there already an element in the structure?
		//yes --> link entries and update last entry ptr of main struct
		data->last->next = entry;
		entry->prev = data->last;
		
		data->last = entry;
	} else {
		//no --> update first and last ptr of main struct
		data->first = entry;
		data->last = entry;
	}
}

void RemoveFirstEntry(ChangeData_t *data)
{
	//only do if there IS a first entry
	if (data->first) {
		ChangeTuple_t *entry = data->first;

		//remove links
		if (entry->next) {
			entry->next->prev = NULL;
		}
		
		//update first (and last) ptr of main struct
		if (entry->next) {
			data->first = entry->next;
		} else {
			data->first = NULL;
			data->last = NULL;
		}
		DeleteEntry(entry);
	}
}

ChangeData_t* CreateChangeData()
{
	ChangeData_t *data = new ChangeData_t;

	data->first = NULL;
	data->last = NULL;

	return data;
}

void DeleteChangeData(ChangeData_t *data)
{
	for(ChangeTuple_t *entry=data->first; entry != NULL; entry=data->first) {//last statement because loop ends with RemoveFirstEntry
		RemoveFirstEntry(data);
	}

	delete data;
}
/*
Linked list implementation end
***********************************************************************
*/

const unsigned int MoneyTypes[] = {5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};	//has to be in correct order
const unsigned int MoneyTypesAmount = sizeof(MoneyTypes)/sizeof(MoneyTypes[0]);

void change(const int due, const int paid, ChangeData_t *ChangeDat)
{
	// ToDo: Exercise 3.a - return set of change tuples
	//( assert(due <= paid) ) could be written for extra security but main should catch all invalid args
	unsigned int diff = paid - due;

	for (int i=0; i<MoneyTypesAmount; i++) {
		if (diff/MoneyTypes[i]) {
			ChangeTuple *tuple = CreateEntry(MoneyTypes[i], diff/MoneyTypes[i]);
			AddEntry(ChangeDat, tuple);

			diff = diff % MoneyTypes[i];
		}
	}
}

#if 0
void output(char *str, bool IsFileOutput, FILE *out)
{
	if (IsFileOutput) {
		size_t count = strlen(str);
		size_t written = fwrite(str, sizeof(char), count, out);
		if (written < count) {
			std::cerr << "Error writing to file" << std::endl;
			//should exit normally but only a few writes are done so better let the program end normally
		}
	} else {
		std::cout << str;
	}
}
#endif

int main(int argc, char * argv[])
{
	if( (argc != 3) && (argc != 5) )
		return 1;	// invalid number of parameters

	const int due  = std::atoi(argv[1]); 
	const int paid = std::atoi(argv[2]);

	bool FileOutput = false;
	if (argc == 5) {
		if ( (argv[3][0] == '-') && (argv[3][1] == 'o') && (argv[3][2] == 0) ) { //is third argument -o ?
			//if it is set option FileOutput to true
			FileOutput = true;
		} else {
			//if not --> invalid argument
			return 2;
		}
	}
	
	//test wether values are correct
	if ( (due > paid) || (due < 0) || (paid < 0) ) {
		return 3;
	}

	ChangeData_t *ChangeDat = CreateChangeData();
	change(due, paid, ChangeDat);

	#if 0
	FILE *out = NULL;

	if (FileOutput) {
		out = fopen(argv[4], "w");
		if (!out) {
			std::cerr << "Cant open file" << std::endl;
			return 4;
		}
	}
	#endif
	
	std::ostream *out;
	std::ofstream file;
	if (FileOutput) {
		file.open(argv[4], std::ios::out | std::ios::trunc);
		if (!file.is_open()) {
			std::cerr << "Error opening file" << std::endl;
			return 4;
		}
		out = &file;
	} else {
		out = &std::cout;
	}
	// ToDo: Exercise 3.b - print change data as CSV to console 
	(*out) << "coin,num" << std::endl;
	//char str[70];		//both numbers (coin, num) are 32 bit --> 2*32 = 64 --> max 64 chars if base was 2 --> base 10 has less chars
				//+ 3 chars for space, comma and \n = 67 + 1 null byte = 68 ~ 70
	for (ChangeTuple_t *entry=ChangeDat->first; entry != NULL; entry = ChangeDat->first) {	//last statement: because loop ends with RemoveFirstEntry
		//snprintf(str, sizeof(str)-1, "%d ,%d\n", entry->value, entry->amount);
		(*out) << entry->value << "," << entry->amount << std::endl;

		RemoveFirstEntry(ChangeDat);
	}

	if (FileOutput) {
		static_cast<std::ofstream*>(out)->close();
	}

	return 0;
}
