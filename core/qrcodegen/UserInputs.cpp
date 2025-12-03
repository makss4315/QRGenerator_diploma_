#include "UserInputs.h"
#include<iostream>
#include<string>

std::string UserInputs::UserPath= "";

void UserInputs::PathInit() {
    std::cout<<"Pls Enter path to save ur qr code: ";
    std::cin>>UserPath;
}

std::string UserInputs::GetUserPathInput() {
return UserPath;

}