#include<iostream>
#include"Admin.h"
#include"User.h"

#include<mysql.h>
using namespace std;
string HOST = "localhost";
string USER = "root";
string PASSWORD = "Mehtab2046";
string DATABASE = "Event_Management";


int main() {
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, HOST.c_str(), USER.c_str(), PASSWORD.c_str(), DATABASE.c_str(), 3306, NULL, 0);

	if (conn) {
		cout << "connection succfully" << endl;
		int testerChoice = 6;
		while (testerChoice != 99) {
			std::cout << "*************************************************************************************" << std::endl;
			std::cout << "*                                                                                   *" << std::endl;
			std::cout << "*                                                                                   *" << std::endl;
			std::cout << "*                                                                                   *" << std::endl;
			std::cout << "*                         Welcome To Event Management System                        *" << std::endl;
			std::cout << "*                                                                                   *" << std::endl;
			std::cout << "*                                                                                   *" << std::endl;
			std::cout << "*                                                                                   *" << std::endl;
			std::cout << "*************************************************************************************" << std::endl;
			std::cout << "1-Admin Side " << std::endl;
			std::cout << "2-Client Side " << std::endl;
			std::cout << "99-Exit" << std::endl;
			std::cin >> testerChoice;
			std::system("cls");
			if (testerChoice == 1) {
				//Shifting to Admin Pannel
				Admin RootUser(804, "Abid Islam", "abid777@gmail.com", "03009876543", 7788, conn);
				RootUser.AdminSideSystem(RootUser);
			}
			else if (testerChoice == 2) {
				User tempUser(conn);


				int newUser = 10;
				while (newUser != 99) {
					std::cout << "1-Log Inn" << std::endl;
					std::cout << "2-Sign Inn" << std::endl;
					std::cout << "99-Exit" << std::endl;
					std::cin >> newUser;
					std::system("cls");
					if (newUser == 1) {
						if (tempUser.login(tempUser)) {
							std::string currentName = tempUser.name;



							std::system("cls");
							tempUser.UserSideSystem(currentName);
						}
						else {
							std::system("cls");
							std::cout << "Login failed. Returning to the main menu." << std::endl;
						}
					}
					else if (newUser == 2) {
						std::system("cls");
						tempUser.registerUser();

					}

				}



			}

		}
	}
	else
	{
		cout << mysql_error(conn) << endl;
	}
	/*return 0;*/
}