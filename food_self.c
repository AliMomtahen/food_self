#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"function.h"



#define FILE_ADDRESS "users.txt"
#define ADMIN -10
#define YES 1
#define NO 0
#define NO_EVRYBODY_LOGIN -1
#define EMPTY 0










int main() {


	//this pointer point to head of student link list
	inform *users = (inform *)malloc(sizeof(inform));

	//this head of halls node
	hall_node *halls = (hall_node *)malloc(sizeof(hall_node));
	halls->size_list = EMPTY;//in start size of node is 0


							 //this variable show that who is login
	long long login_mod = NO_EVRYBODY_LOGIN;


	int file_is_empty = NO;
	FILE *file;
	file = fopen(FILE_ADDRESS, "r");
	if (file == NULL) {//check file exist or not
		file = fopen(FILE_ADDRESS, "w");
		fclose(file);
		file = fopen(FILE_ADDRESS, "r");
	}
	int i = 0;


	inform *head = users;
	inform *end;

	//read information from file and save it
	while (feof(file) == 0) {

		//check we read the first line of file or not
		if (i == 0) {
			read_student_file(head, file);

			head->next = NULL;
			end = head;
			head->former = NULL;
			head->Money = EMPTY;
			head->Foods_reserved = NULL;
			//check file is empty or no
			if (head->Uname[0] == EOF)
				break;

			i++;

		}
		else if (i >= 1) {
			inform *s = (inform *)malloc(sizeof(inform));
			if (s == NULL)
				exit(EXIT_FAILURE);
			read_student_file(s, file);

			head->next = s;
			s->Money = EMPTY;
			s->Foods_reserved = NULL;
			s->former = head;
			head = s;
			end = s;
			i++;
		}


	}

	end->next = NULL;
	users->size_list = i;
	users->End_list = end;

	fclose(file);


	//this is head of foods link list
	food * foods = (food *)malloc(sizeof(food));
	foods->size_list = EMPTY;//in start size of node is 0

	
	//this is head of coupon bin link list
	node_bin_Coupon *coupons = NULL;




	while (1) {

		//this variable show and save the command that user inputed
		char *command;
		command = Read_Dinamic_str_CommandLine();

		//check that command is login or not and handle it
		if (Check_Equal_str(command, "login") == YES) {
			//check that none user login befor and dont logout  		
			if (login_mod != NO_EVRYBODY_LOGIN) {
				Prevent_Print_additional_notifiction();
				printf("not possible\n");
			}
			else {
				login_mod = login(users);
			}
		}

		//check that command is signup or not and handle it
		else if (Check_Equal_str(command, "signup") == YES) {
			//check that none user login befor and dont logout
			if (login_mod != NO_EVRYBODY_LOGIN) {
				Prevent_Print_additional_notifiction();
				printf("not possible\n");
			}
			else {
				signup(users);
			}
		}

		//check that command is logout or not and handle it
		else if (Check_Equal_str(command, "logout") == YES) {
			logout(users, &login_mod);
		}
		//check that command is add_hall or not and handle it
		else if (Check_Equal_str(command, "add_hall")) {
			//check login admin
			if (login_mod == ADMIN)
				add_hall(halls);
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is add_food or not and handle it
		else if (Check_Equal_str(command, "add_food")) {
			//check login admin
			if (login_mod == ADMIN)
				add_food(foods, halls);
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is add_coupon or not and handle it
		else if (Check_Equal_str(command, "add_coupon")) {
			//check login admin
			if (login_mod == ADMIN)
				add_coupon(&coupons);
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is show_money or not and handle it
		else if (Check_Equal_str(command, "show_money")) {
			if (login_mod != ADMIN && login_mod != NO_EVRYBODY_LOGIN) {
				show_money(users);
			}
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}

		}
		//check that command is get_money or not and handle it
		else if (Check_Equal_str(command, "get_money")) {
			if (login_mod != ADMIN && login_mod != NO_EVRYBODY_LOGIN) {
				get_money(users);
			}
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is menu or not and handle it
		else if (Check_Equal_str(command, "menu")) {
			if (login_mod != ADMIN && login_mod != NO_EVRYBODY_LOGIN) {
				menu(foods);
			}
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is reserve or not and handle it
		else if (Check_Equal_str(command, "reserve")) {
			if (login_mod != ADMIN && login_mod != NO_EVRYBODY_LOGIN) {
				reserve(users, foods, coupons, NO);
			}
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is reserve_discount or not and handle it
		else if (Check_Equal_str(command, "reserve_discount")) {
			if (login_mod != ADMIN && login_mod != NO_EVRYBODY_LOGIN) {
				reserve(users, foods, coupons, YES);
			}
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is show_reserved or not and handle it
		else if (Check_Equal_str(command, "show_reserved")) {
			if (login_mod != ADMIN && login_mod != NO_EVRYBODY_LOGIN) {
				show_reserved(users->person_now_login->Foods_reserved);
			}
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is food_report or not and handle it
		else if (Check_Equal_str(command, "food_report")) {
			if (login_mod == ADMIN ) {
				food_report(foods);
			}
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//check that command is hall_report or not and handle it
		else if (Check_Equal_str(command, "hall_report")) {
			if (login_mod == ADMIN ) {
				hall_report(halls);
			}
			else {
				Prevent_Print_additional_notifiction();
				printf("permission denied\n");
			}
		}
		//if command is "exit" exit the program 
		else if (Check_Equal_str(command, "exit")) {
			break;
		}
		else {
			//if command is wrong
			Prevent_Print_additional_notifiction();
			printf("command is not defined\n");
		}


		free(command);


	}//end while





	 // free the memory in end of program
	free_memory(users,coupons, halls, foods);




	return 0;
}




//////////////////////       __          _     
//////////////////////      |__   |\ |  | \   
//////////////////////      |__   | \|  |_/   
//////////////////////                  


