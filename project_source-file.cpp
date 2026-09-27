/*Start of Project*/

/*Header Files*/
#include <iostream> // for input output stream 
#include <string> // for string manipulation 
#include <iomanip> // for formatting
#include <fstream> // for file handling
#include <sstream> // for string reading manipulation

using namespace std;

/*Structure Declaration*/
struct ClientInformation {
	string clientName;
	int ID;
	string productName;
	string productType;
	int quantity;
	bool isOrderPlaced;
	bool isSignedUp;
	bool isDesigned;
	bool isStructured;
	bool isTested;
	bool isMaintenance;
}; // end of structure declaration

struct staff {
	string name;
	int ID;
	string departmentCode;
};
/*End of all structure declartions*/
/*Global Variables*/
int clients = 0;
// end of global variables

/*Function Declarations*/
void mainMenu(void);
void doubleSpace(void);
void line(void);
void clientMenu(void);
bool isFileEmpty(string);
void signUp(ClientInformation*);
void placeOrder(ClientInformation*);
void updateRecord(ClientInformation*);
void saveData(ClientInformation*);
void deleteOrder(ClientInformation*);
void display(ClientInformation*);
void loadData(ClientInformation*);
bool func(string&);
void organizationalMenu(void);
void displayLine(void);
void orderProcessing(ClientInformation*);
void orderProcessing();
void designingPhase(ClientInformation*, staff);
void ifSignUpButNoOrder(ClientInformation*);
void structurePhase(ClientInformation*, staff);
void testingPhase(ClientInformation*, staff);
void maintenancePhase(ClientInformation*, staff);
void checkOrderStatus(ClientInformation*);
void reportGenerating(ClientInformation*, staff, staff, staff, staff);
/*end of function declarations*/

int main() { // start of main function

	// initializing the staff organizational control's information inorder to perform operations on orders
	/*Start of staff strucre initialization*/
	staff design = { "Emp1",101,"E1DP101" };
	staff structure = { "Emp2",102,"E2DS102" };
	staff testing = { "Emp3",103,"E3DT103" };
	staff maintenance = { "Emp4",104,"E4DM104" };
	/*end of structure initialization*/

	/*Creating struct array*/
	ClientInformation arr[20]; // room for maximum of 20 individuals

	if (isFileEmpty("clients.txt")) { // checking whether the file is empty or not. if the file is empty it will display file is empty, kindly do input.
		cout << "File is Empty!\n";
	}
	else {
		loadData(arr); // loading data from the file in case the file is not empty		
		/*display(arr);*/ // displaying data from file
		cout << "Data has been loaded from \"clients.txt\" successfully.\n";
	}
	system("pause");

	/*choiceVariables*/
	int mainMenuChoice = 0, clientMenuChoice = 0, orgChoice = 0, processingChoice = 0;
	/*End of choice variables*/

	do { // start of outer do while loop of main menu choices
		mainMenu(); // calling main menu function 
		cin >> mainMenuChoice; // input choice
		/*if else conditions*/
		if (mainMenuChoice == 1) {
			do { // clientMenu do while loop
				clientMenu();
				cin >> clientMenuChoice; // input clientServices choice
				/*start of conditional structure*/
				if (clientMenuChoice == 1) {
					signUp(arr); // calling sign up function
				}
				else if (clientMenuChoice == 2) {
					placeOrder(arr); // calling order placement function
				}
				else if (clientMenuChoice == 3) { // checking orderstatus choice
					checkOrderStatus(arr); // calling check ordre status function
				}
				else if (clientMenuChoice == 4) { // update record
					updateRecord(arr); // updating record function call
				}
				else if (clientMenuChoice == 5) {
					deleteOrder(arr); // deleting order / cancelling order function call
				}
				else if (clientMenuChoice == 6) {
					line();
					cout << "Exiting System.\n";
					cout << "Loading.................\n";
					cout << "System Exited Successfully.\n";
					line();
					system("pause");
				}
				else {
					cout << "Invalid Input.\n";
				}
				/*End of conditional structure*/
			} while (clientMenuChoice != 6); // end of clientMenu do while loop
		}
		else if (mainMenuChoice == 2) { // organizational control menu choice
			do { // start of the organizational control's parent do while loop
				organizationalMenu();
				cin >> orgChoice;
				if (orgChoice == 1) {
					display(arr); // calling dislay function
					system("pause");
				}
				else if (orgChoice == 2) { // ordre processing choice
					do { // start of do while loop of order processing 4 options (desing,struct,testing,maintenance)
						orderProcessing();
						cin >> processingChoice;
						if (processingChoice == 1) { // desinging choice
							designingPhase(arr, design); // calling designing phase function
						} // end of designing phase
						else if (processingChoice == 2) { // structure choice
							structurePhase(arr, structure);
						}
						else if (processingChoice == 3) { // testing choice
							testingPhase(arr, testing);
						}
						else if (processingChoice == 4) { // maintenance choice
							maintenancePhase(arr, maintenance); // caling maintenace function to perform it
						}
						else if (processingChoice == 5) { // exit
							line();
							cout << "Exiting Order Processing Unit.\n";
							cout << "Loading.................\n";
							cout << "System Exited Successfully.\n";
							line();
							system("pause");
						}
						else {
							cout << "Invliad Input.\n";
							system("pause");
						}
					} while (processingChoice != 5); // end of do while loop of 4 options
				}
				else if (orgChoice == 3) {
					line();
					cout << "Exiting Organizational Control...\n";
					cout << "Loading.................\n";
					line();
					system("pause");
				}
				else {
					cout << "Invalid Input.\n";
					system("pause");
				}
			} while (orgChoice != 3); // end of parent do while loop
		}
		else if (mainMenuChoice == 3) {
			line();
			cout << "Exiting System Successfully!" << endl;
			cout << "Loading.................\n";
			line();
			system("pause");
		}
		else {
			cout << "Invalid Input.\n";
			system("pause");
		}
	} while (mainMenuChoice != 3); // end of the outer parent do while loop

	ifSignUpButNoOrder(arr); // calling each time to check wether an individual have only signup but not place any order
	reportGenerating(arr, design, structure, testing, maintenance); // generating report depending upon if the order has done completely.
	display(arr); // calling display function
	saveData(arr); // saving data depending upon if the order has been placed successfully
	if (clients == 0) { // clearing file if no order eixits.
		ofstream clearFile;
		clearFile.open("clients.txt", ios::trunc); // opening file in trunc mode
		clearFile.close(); // closing file
	} // end of file

	return 0; // returning zero of the main function
} // end of the main function

/*Start of User defined functions definitions*/
void mainMenu(void) {
	/*start of main menu function*/
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|            SURGICAL INDUSTRY MANAGEMENT SYSTEM             |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace();
	cout << "1. Client Services\n";
	cout << "2. Organizational Control\n";
	cout << "3. Exit\n";
	doubleSpace();
	line();
	cout << "Enter Your Choice: ";
} // end of main menu function
void doubleSpace(void) { // start of double space function
	cout << endl << endl;
} // end of double space function
void line(void) {
	cout << "============================================================\n";
} // end of line function (used in the project for formatting)
void clientMenu(void) {
	system("cls"); // clearing screen and displaying the client services title
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                       CLIENT SERVICES                      |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space
	cout << "1. Sign Up\n"; // displaying the menu driven choices of client services
	cout << "2. Place Order\n";
	cout << "3. Check Order Status\n";
	cout << "4. Update Record\n";
	cout << "5. Cancel Order\n";
	cout << "6. Exit\n";
	doubleSpace(); // again adding double space
	line(); // adding a line
	cout << "Enter Your Choice: "; // displaying msssage
} // end of client menu function

bool isFileEmpty(string fileName) { // to check whether the file is empty or not
	ifstream file(fileName);
	return file.peek() == std::ifstream::traits_type::eof();
} // end of function

void signUp(ClientInformation* arr) { // start of sign up function
	system("cls"); // clearing screen & displaying the sign up menu
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                           SIGN UP                          |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space by calling fucntion
	cout << "Enter Your Name: "; // asking the client's name
	cin >> arr[clients].clientName; // storing in the data structure
	cout << "Enter Your ID: "; // asking for id
	bool isDuplicate = false; // id uniqueness algorithm
	do { // start of do while loop
		cin >> arr[clients].ID;
		for (int i = 0; i < clients; i++) { // start of for loop
			if ((arr[i].ID == arr[clients].ID) && (i != clients)) { // start of if 
				isDuplicate = true;
				cout << "ID has already taken! Enter a unqique ID: ";
				break;
			} // end of if
			else { // start of else part
				isDuplicate = false;
			} // end of else part
		} // end of for loop
	} while (isDuplicate); // end of do while loop
	cout << "Client Added Successfully!\n";
	arr[clients].isSignedUp = true; // making true to signed up
	system("pause");
	// incrementing the index after adding
	clients++; // incrementing after signing up
} // end of sign up function

void placeOrder(ClientInformation* arr) { // start of place order function
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                       ORDER PLACEMENT                      |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space
	int id = 0, loc = -1;
	bool isFound = false;
	cout << "Enter Your ID: ";
	cin >> id;
	for (int i = 0; i < clients; i++) { // start of for loop   <-Linear Search->
		if (id == arr[i].ID) { // start of if 
			cout << "ID found at index \"" << i << "\" .\n";
			isFound = true;
			loc = i; // storing the location of the index
			break;
		} // end of if
	} // end of for loop
	if (isFound && arr[loc].isOrderPlaced != true) { // start of if conditional block of code
		cout << "Enter Product Name: ";
		cin >> arr[loc].productName;
		cout << "Enter Product Type: ";
		cin >> arr[loc].productType;
		cout << "Enter Product Quantity: ";
		cin >> arr[loc].quantity;
		arr[loc].isOrderPlaced = true;
		cout << "Order with an ID: " << arr[loc].ID << " has successfully placed.\n";
	} // end of if
	else if (isFound && arr[loc].isOrderPlaced) {
		cout << "You have Already Placed an Order!\n";
	}
	else {
		cout << "You have not signed up!\n";
	}
	system("pause"); // waits for the user to press any key in order to continue
} // end of place order function

void updateRecord(ClientInformation* arr) { // start of update record function
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                        UPDATE RECORD                       |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace();
	line();
	int id = 0, loc = -1;
	bool isFound = false;
	cout << "Enter Your ID: ";
	cin >> id;
	for (int i = 0; i < clients; i++) { // start of for loop <-Linear Search->
		if (arr[i].ID == id) { // start of if
			isFound = true;
			loc = i;
			cout << "ID found at index \"" << i << "\" .\n";
			break;
		} // end of if
	} // end of for loop
	if (isFound) { // start of conditional structure if id found
		int choice = 0;
		cout << "Which information do you want to update?\n";
		cout << "1. Sign Up\n";
		cout << "2. Order Placement\n";
		cout << "3. Exit\n";
		cin >> choice;
		if (choice == 1) { // for sign up condition updation
			cout << "Which information do you want to update?\n";
			int signUpChoice = 0;
			cout << "1. Name\n";
			cout << "2. ID\n";
			cout << "3. Exit\n";
			line();
			cout << "Enter Your Choice: ";
			cin >> signUpChoice;
			if (signUpChoice == 1) {
				cout << "Enter Updated Name: ";
				cin >> arr[loc].clientName;
			}
			else if (signUpChoice == 2) {
				cout << "Enter Updated ID: ";
				bool isDuplicate = false;
				do { // duplication ensuring algorithm / start of do while loop
					cin >> arr[loc].ID;
					for (int i = 0; i < clients; i++) { // start of for loop
						if ((arr[i].ID == arr[loc].ID) && (i != loc)) {
							isDuplicate = true;
							cout << "ID has already taken! Enter a unqique ID: ";
							break;
						}
						else {
							isDuplicate = false;
						}
					} // end of for loop
				} while (isDuplicate); // end of do while loop
			} // end of else part
			else if (signUpChoice == 3) {
				cout << "Exit Successfully.\n";
			}
			else {
				cout << "Invalid Input.\n";
			}

		} // end of sign up information updation conditional part 
		else if (choice == 2) { // orderplacement updation code
			if (arr[loc].isOrderPlaced == true) {
				int order = 0;
				cout << "Which information do you want to update?\n";
				line();
				cout << "1. Product Name\n";
				cout << "2. Product Type\n";
				cout << "3. Product Quantity\n";
				cout << "4. Exit\n";
				line();
				cout << "Enter Your Choice: ";
				cin >> order;
				if (order == 1) {
					cout << "Enter Updated Product Name: ";
					cin >> arr[loc].productName;
				}
				else if (order == 2) {
					cout << "Enter Updated Product Type: ";
					cin >> arr[loc].productType;
				}
				else if (order == 3) {
					cout << "Enter Updated Product Quantity: ";
					cin >> arr[loc].quantity;
				}
				else if (order == 4) {
					line();
					cout << "Exiting Successfully.\n";
					cout << "Loading...\n";
					cout << "System Exited Successfully.\n";
					line();
				}
				else {
					cout << "Invalid Input.\n";
				}

			} // end of if conditional block of code
			else { // else part if order has not placed
				cout << "No orde with ID: \"" << loc << "\" has been placed!\n";
			}
		}
		else if (choice == 3) { // third choice of the outer parent do while loop
			line();
			cout << "Exiting successfully.\n";
			cout << "Loading..." << endl;
			cout << "Exited successfully.\n";
			line();
		}
		else { // last one for invalid input
			cout << "Invalid Input!\n";
		}
	} // end of if found conditional control
	else {
		cout << "ID not found!\n";
	}
	system("pause"); // wait for the user to press any key
} // end of update function 

void saveData(ClientInformation* arr) { // start of the saveData function
	ofstream save; // declaration of ofstream variable
	save.open("clients.txt", ios::out); // opening file in writing mode
	if (!save.is_open()) { // erro handling
		cerr << "Failed to open \"clients.txt\".\n";
	} // end of if
	else { // formatting headings
		save << left << setw(25) << "Client Name"
			<< left << setw(10) << "ID"
			<< left << setw(25) << "Product Name"
			<< left << setw(25) << "Product Type"
			<< left << setw(10) << "Quantity"
			<< left << setw(10) << "Designing"
			<< left << setw(15) << "Structure"
			<< left << setw(15) << "Testing"
			<< left << setw(15) << "Maintenance" << endl;
		for (int i = 0; i < clients; i++) { // start of the loop
			if (arr[i].isOrderPlaced) { // saving data if order has been placed
				save << left << setw(25) << arr[i].clientName
					<< left << setw(10) << arr[i].ID
					<< left << setw(25) << arr[i].productName
					<< left << setw(25) << arr[i].productType
					<< left << setw(10) << arr[i].quantity;
				if (arr[i].isDesigned == true) {
					save << left << setw(10) << "Done";
				}
				else {
					save << left << setw(10) << "Pending";
				}

				if (arr[i].isStructured == true) {
					save << left << setw(15) << "Done";
				}
				else {
					save << left << setw(15) << "Pending";
				}

				if (arr[i].isTested == true) {
					save << left << setw(15) << "Done";
				}
				else {
					save << left << setw(15) << "Pending";
				}

				if (arr[i].isMaintenance == true) {
					save << left << setw(15) << "Done";
				}
				else {
					save << left << setw(15) << "Pending";
				}
				save << endl;
			} // end of if order has been placed conditional block of code
		} // end of for loop
	} // end of else part of of the code
	save.close(); // closing file after the process
} // end of the saveData function

void deleteOrder(ClientInformation* arr) { // deleting a record function
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                      Cancelling Order                      |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space
	bool isFound = false;
	int id = 0, loc = -1;
	cout << "Enter ID to Delete the Information: ";
	cin >> id;
	for (int i = 0; i < clients; i++) { // start of for loop
		if (id == arr[i].ID) { // start of if
			isFound = true;
			loc = i;
			cout << "An with ID \"" << arr[i].ID << "\" found at the index " << i << endl;
			break;
		} // end of if
	} // end of for loop
	if ((isFound == true) && (arr[loc].isOrderPlaced == true)) { // processing if order has been placed
		for (int i = loc; i < clients - 1; i++) { // start of for loop
			arr[i] = arr[i + 1]; // shifting of indices
		} // end of for loop
		clients--;
		cout << "Order Deleted Successfully.\n";
	} // end of if conditional block of code
	else {
		cout << "Order has not been placed.\n";
	}
	system("pause");
} // end of deletion function

void display(ClientInformation* arr) { // start of display function
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                      Displaying Info                       |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double Space
	displayLine(); // adding line
	cout << left << setw(25) << "Client Name"
		<< left << setw(10) << "ID"
		<< left << setw(25) << "Product Name"
		<< left << setw(25) << "Product Type"
		<< left << setw(10) << "Quantity"
		<< left << setw(10) << "Designing"
		<< left << setw(15) << "Structure"
		<< left << setw(15) << "Testing"
		<< left << setw(15) << "Maintenance" << endl;
	displayLine(); // adding double line

	for (int i = 0; i < clients; i++) { // start of the loop
		if (arr[i].isOrderPlaced == true) { // saving data if order has been placed
			cout << left << setw(25) << arr[i].clientName
				<< left << setw(10) << arr[i].ID
				<< left << setw(25) << arr[i].productName
				<< left << setw(25) << arr[i].productType
				<< left << setw(10) << arr[i].quantity;
			if (arr[i].isDesigned == true) {
				cout << left << setw(10) << "Done";
			}
			else {
				cout << left << setw(10) << "Pending";
			}

			if (arr[i].isStructured == true) {
				cout << left << setw(15) << "Done";
			}
			else {
				cout << left << setw(15) << "Pending";
			}

			if (arr[i].isTested == true) {
				cout << left << setw(15) << "Done";
			}
			else {
				cout << left << setw(15) << "Pending";
			}

			if (arr[i].isMaintenance == true) {
				cout << left << setw(15) << "Done";
			}
			else {
				cout << left << setw(15) << "Pending";
			}
			cout << endl;
			displayLine();
		} // end of if order has been placed
	}  // end of the for loop
} // end of the display function

void loadData(ClientInformation* arr) { // this function loads data from text file to array
	ifstream read; // ifstream read variable
	int i = 0; // itertor variable for reading
	read.open("clients.txt", ios::in); // opening file clients.txt in reading mode
	if (!read.is_open()) { // error handling
		cerr << "Failed to open \"clients.txt\" in reading mode.\n";
	} // end of if
	else { // start of else part of code
		string heading = "", line = "", boolean = ""; // null strings
		getline(read, heading); // reading headings
		while (getline(read, line)) { // reading data line by line
			istringstream iss(line); // istringstream variable for reading / string manipulation
			iss >> arr[i].clientName;
			iss >> arr[i].ID;
			iss >> arr[i].productName;
			iss >> arr[i].productType;
			iss >> arr[i].quantity;
			iss >> boolean;
			arr[i].isDesigned = func(boolean);
			iss >> boolean;
			arr[i].isStructured = func(boolean);
			iss >> boolean;
			arr[i].isTested = func(boolean);
			iss >> boolean;
			arr[i].isMaintenance = func(boolean);
			arr[i].isOrderPlaced = true;
			arr[i].isSignedUp = true;
			++i; // incrementing
		} // end of reading while loop
		clients = i; // updating the number of clients
	} // end of else part of the code
	/*cout << "Number of clients is: " << clients << " in the reading mode.\n";*/
	system("pause");
	read.close(); // closing file after reading
} // end of the load function

bool func(string& str) { // for string mainpulation
	if (str.compare("Done") == 0) {
		str = "";
		return 1;
	}
	else {
		str = "";
		return 0;
	}
} // end of function

void organizationalMenu() { // start of organizational menu function
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                   Organizational Control                   |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space
	cout << "1. View All Orders\n";
	cout << "2. Order Processing\n";
	cout << "3. Back to the Main Menu\n";
	doubleSpace();
	line();
	cout << "Enter Your Choice: ";
} // end of function

void displayLine(void) { // line function for structural organization 
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------\n";
} // end of function

void orderProcessing() { // start of orderProcessing function
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                      Order Processing                      |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space
	cout << "1. Designing Phase\n";
	cout << "2. Structure Phase\n";
	cout << "3. Testing Phase\n";
	cout << "4. Maintenance Phase\n";
	cout << "5. Exit\n";
	doubleSpace();
	line();
	cout << "Enter Your Choice: ";
} // end of orderProcessing function

void ifSignUpButNoOrder(ClientInformation* arr) {
	/*this function deletes the clients who have not placed order but only signed up*/
	bool isFound = false;
	int loc = -1;
	for (int i = 0; i < clients; i++) {
		if (arr[i].isOrderPlaced != true) {
			cout << "An order with an ID \"" << arr[i].ID << "\" found with null order status.\n";
			loc = i;
			isFound = true;
			for (int j = i; j < clients - 1; j++) {
				arr[j] = arr[j + 1]; // shifting the indicies
			} // end of inner for loop
			clients--;
			i--; // decrementing the i to again check the shifting index
		} // end of if
	} // end of for loop
} // end of main function

void designingPhase(ClientInformation* arr, staff D) { // start of designing phase function
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                      Designing Phase                       |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space
	bool isFound = false;
	int idEmp = 0, clientID = 0, loc = -1;  // variables initializations
	cout << "Enter ID of Designing Department: ";
	cin >> idEmp; // 

	if (idEmp == D.ID) { // if the input id matches with the id of the employee workin at designing phase department
		cout << "ID matched Successfully!\n";
		cout << "Enter Client ID to Desing Product: ";
		cin >> clientID;
		for (int i = 0; i < clients; i++) { // start of for loop
			if (clientID == arr[i].ID) { // start of if
				loc = i;
				isFound = true;
				cout << "ID found at index \"" << i << "\"" << endl;
				break;
			} // end of if
		} // end of for loop

		if ((isFound == true) && (arr[loc].isOrderPlaced == true)) {
			/*If the id of the client found and order is placed, then it would be working*/
			arr[loc].isDesigned = true; // marking true as designing phase
			cout << "An order with ID \"" << clientID << "\" has successfully designed.\n";
			system("pause");
		} // end of if 
		else {
			cout << "An order with ID \"" << clientID << "\" not found.\n";
			system("pause");
		}
	} // end of outer if 
	else if(!isFound) {
		cout << "Department Id not found!.\n";
		system("pause");
	}
} // end of designing phase function


void structurePhase(ClientInformation* arr, staff S) {
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                      Structure Phase                       |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space
	bool isFound = false;
	int idEmp = 0; // variables initializations
	int clientID = 0, loc = -1;
	cout << "Enter ID of Structre Evaluation Department: ";
	cin >> idEmp; // input

	if (idEmp == S.ID) { // if the input id matches with the id of the employee workin at designing phase department
		cout << "ID matched Successfully!\n";
		cout << "Enter Client ID to make Structure of the Product: ";
		cin >> clientID;
		for (int i = 0; i < clients; i++) { // start of for loop
			if (clientID == arr[i].ID) { // start of if
				loc = i; // storing the location of the index
				isFound = true;
				cout << "ID found at index \"" << i << "\"" << endl;
				break; // breaking the loop after the process
			} // end of if
		} // end of for loop

		if ((isFound == true) && (arr[loc].isOrderPlaced == true) && (arr[loc].isDesigned == true)) {
			/*If the id of the client found and order is placed, then it would be working*/
			arr[loc].isStructured = true; // marking true as designing phase
			cout << "An order with ID \"" << clientID << "\" has successfully structured.\n";

		} // end of if 
		else if ((isFound == true) && (arr[loc].isOrderPlaced == true) && (arr[loc].isDesigned != true)) {
			cout << "An order with ID \"" << clientID << "\ has not been designed yet.\n";
		} // the above condition makes sure that wether the product has been designed in order to make its structrue
		else {
			cout << "An order with ID \"" << clientID << "\" not found.\n";
		}
	} // end of outer if
	else if (!isFound) {
		cout << "Department Id not found!.\n";
	}
	system("pause"); // wait for the user to press any key
} // end of structure designing phase function

void testingPhase(ClientInformation* arr, staff T) { // start of testing phase function
	system("cls"); // clearing screen
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                       Testing Phase                        |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace(); // adding double space
	bool isFound = false;
	int idEmp = 0; // variables initialization
	int clientID = 0, loc = -1;
	cout << "Enter ID of Product Testing Department: ";
	cin >> idEmp; // input
	// start of conditional block of code
	if (idEmp == T.ID) { // if the input id matches with the id of the employee workin at designing phase department
		cout << "ID matched Successfully!\n";
		cout << "Enter Client ID to test Product: ";
		cin >> clientID;
		for (int i = 0; i < clients; i++) { // start of for loop
			if (clientID == arr[i].ID) { // start of if
				loc = i;
				isFound = true;
				cout << "ID found at index \"" << i << "\"" << endl;
				break;
			} // end of if
		} // end of for loop

		if ((isFound == true) && (arr[loc].isOrderPlaced == true) && (arr[loc].isStructured == true)) {
			/*If the id of the client found and order is placed, then it would be working*/
			arr[loc].isTested = true; // marking true as designing phase
			cout << "An order with ID \"" << clientID << "\" has successfully tested.\n";

		} // end of if 
		else if ((isFound == true) && (arr[loc].isOrderPlaced == true) && (arr[loc].isStructured != true)) {
			cout << "An order with ID \"" << clientID << "\ has not been structured yet.\n";
		} // the above condition makes sure that wether the product has been designed in order to make its structrue
		else if(!isFound) {
			cout << "An order with ID \"" << clientID << "\" not found.\n";
		}
	} // end of outer if
	else {
		cout << "Department Id not found!.\n";
	}
	system("pause");
} // end of testing function

void maintenancePhase(ClientInformation* arr, staff M) {  //start of maintenance function
	system("cls");
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                     Maintenance Phase                      |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace();
	bool isFound = false;
	int idEmp = 0; // variables initializations
	int clientID = 0, loc = -1;
	cout << "Enter ID of Product Maintenance Department: ";
	cin >> idEmp; // user input
	// start of conditional block of code
	if (idEmp == M.ID) { // if the input id matches with the id of the employee workin at designing phase department
		cout << "ID matched Successfully!\n";
		cout << "Enter Client ID to perform Product Maintenance Operations: ";
		cin >> clientID;
		for (int i = 0; i < clients; i++) { // start of for loop
			if (clientID == arr[i].ID) { // start of if
				loc = i;
				isFound = true;
				cout << "ID found at index \"" << i << "\"" << endl;
				break;
			} // end of if
		} // end of for loop

		if ((isFound == true) && (arr[loc].isOrderPlaced == true) && (arr[loc].isTested == true)) {
			/*If the id of the client found and order is placed, then it would be working*/
			arr[loc].isMaintenance = true; // marking true as designing phase
			cout << "An order with ID \"" << clientID << "\" has successfully maintained.\n";

		} // end of if 
		else if ((isFound == true) && (arr[loc].isOrderPlaced == true) && (arr[loc].isTested != true)) {
			cout << "An order with ID \"" << clientID << "\ has not been tested yet.\n";
		} // the above condition makes sure that wether the product has been designed in order to make its structrue
		else if (!isFound) {
			cout << "An order with ID \"" << clientID << "\" not found.\n";
		}
	} // end of outer if
	else {
		cout << "Department Id not found!.\n";
	}
	system("pause");
} // end of maintenance function

void checkOrderStatus(ClientInformation* arr) { // start of checking order status function
	system("cls");
	cout << "\t\t\t\t\t ============================================================ \n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                   Checking Order Status                    |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t|                                                            |\n";
	cout << "\t\t\t\t\t ============================================================ \n";
	doubleSpace();
	bool isFound = false; // variables initializaation
	int id = 0, loc = -1;
	cout << "Enter Your ID: ";
	cin >> id;
	for (int i = 0; i < clients; i++) { // stat of for loop linear search
		if (id == arr[i].ID) {
			isFound = true;
			loc = i; // performing linear search and storing the location of the index into loc
			cout << "ID found at the index \"" << loc << "\".\n";
			break; // breaking the loop after the process
		} // end of if 
	} // end of for loop
	line();
	if (arr[loc].isOrderPlaced == true) {
		if (arr[loc].isDesigned == true) {
			cout << "Product Designing with an ID \"" << arr[loc].ID << "\" is Done.\n";
		}
		else {
			cout << "Product Designing with an ID \"" << arr[loc].ID << "\" is Pending.\n";
		}

		if (arr[loc].isStructured == true) {
			cout << "Product Structue Evaluation with an ID \"" << arr[loc].ID << "\" is Done.\n";
		}
		else {
			cout << "Product Structure Evaluation with an ID \"" << arr[loc].ID << "\" is Pending.\n";
		}

		if (arr[loc].isTested == true) {
			cout << "Product Testing with an ID \"" << arr[loc].ID << "\" is Done.\n";
		}
		else {
			cout << "Product Testing with an ID \"" << arr[loc].ID << "\" is Pending.\n";
		}
		if (arr[loc].isMaintenance == true) {
			cout << "Product Maintenance with an ID \"" << arr[loc].ID << "\" is Done.\n";
		}
		else {
			cout << "Product Maintenance with an ID \"" << arr[loc].ID << "\" is Pending.\n";
		}
	} // end of parent conditional block of code
	else if ((arr[loc].isOrderPlaced == false) && (isFound == true)) {
		cout << "No order with the ID \"" << arr[loc].ID << "\" has been placed.\n";
	}
	else {
		cout << "ID not found.\n";
	}
	line(); // adding line
	system("pause");
} // end of checkOrderStatus function

void reportGenerating(ClientInformation* arr, staff D, staff S, staff T, staff M) { // report generating
	ofstream finalReport;
	finalReport.open("Final_Product_Release_Report.txt", ios::out | ios::app); // opening the file in writing mode by appending each time
	if (!finalReport.is_open()) { // error handling
		cerr << "Failed to open \" Final_Product_Release_Report.txt \"" << endl;
	}
	else { // else part of the code
		for (int i = 0; i < clients; i++) { // start of for loop
			if ((arr[i].isDesigned == true) && (arr[i].isMaintenance == true) && (arr[i].isStructured == true) && (arr[i].isTested == true)) {
				finalReport << "**********************************************************************************************************************************\n";
				finalReport << "|                                                                                                                                |\n";
				finalReport << "|                                                             FINAL REPORT                                                       |\n";
				finalReport << "|                                                                                                                                |\n";
				finalReport << "**********************************************************************************************************************************\n";
				finalReport << "\n\n\n";
				finalReport << "========================================================\n";
				finalReport << "Name: " << arr[i].clientName << endl;
				finalReport << "ID: " << arr[i].ID << endl;
				finalReport << "Product Name: " << arr[i].productName << endl;
				finalReport << "Product Type: " << arr[i].productType << endl;
				finalReport << "Product Quantity: " << arr[i].quantity << endl << endl;
				finalReport << "********************Designed By********************" << endl << endl;
				finalReport << "Name: " << D.name << endl;
				finalReport << "ID: " << D.ID << endl;
				finalReport << "Department-Code: " << D.departmentCode << endl << endl;
				finalReport << "******************Structured By********************" << endl << endl;
				finalReport << "Name: " << S.name << endl;
				finalReport << "ID: " << S.ID << endl;
				finalReport << "Department-Code: " << S.departmentCode << endl << endl;
				finalReport << "*********************Tested By*********************" << endl << endl;
				finalReport << "Name: " << T.name << endl;
				finalReport << "ID: " << T.ID << endl;
				finalReport << "Department-Code: " << T.departmentCode << endl << endl;
				finalReport << "*******************Maintained By*******************" << endl << endl;
				finalReport << "Name: " << M.name << endl;
				finalReport << "ID: " << M.ID << endl;
				finalReport << "Department-Code: " << M.departmentCode << endl;
				// deleting the successfully done order from the data structure
				for (int j = i; j < clients - 1; j++) { // start of for loop
					arr[j] = arr[j + 1];
				} // end of for loop
				clients--; // decresing the number of clients
				finalReport << "========================================================\n";
			} // end of if 
		} // end of for loop
	} // else part of the code
	finalReport.close(); // closing file after writing
} // end of else part of the report writing conditonal block of code
/*End of project*/
/*PROJECT PRESENTATION 9TH JULY, 2024, UCP, PROGRAMMING FUNDAMENTALS...*/