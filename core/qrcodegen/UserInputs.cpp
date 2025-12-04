#include "UserInputs.h"
#include<iostream>
#include<string>

std::string UserInputs::UserPath;
std::string UserInputs::UserFileName;
std::string UserInputs::UserTextToConvert;

void UserInputs::UserPathInit() {
    std::cout<<"Pls Enter path to save ur qr code: ";
    std::cin>>UserPath;
}

std::string UserInputs::GetUserPathInput() {
return UserPath;
}

void UserInputs::UserFileNameInit() {
    std::cout<<"Pls Enter file name to save ur qr code: ";
    std::cin>>UserFileName;
}

std::string UserInputs::GetUserFileName() {
    return UserFileName;
}

void UserInputs::UserTextToConvertInit() {
    std::cout<<"Pls Enter text or link to convert: ";
    std::cin>>UserTextToConvert;

}

std::string UserInputs::GetUserTextToConvert() {
    return UserTextToConvert;
}