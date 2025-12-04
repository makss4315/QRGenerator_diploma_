#pragma once

#include <string>
class UserInputs{
      public:

        static void UserPathInit();
        static  std::string GetUserPathInput();

        static void UserFileNameInit();
        static std::string GetUserFileName();

        static void UserTextToConvertInit();
        static std::string GetUserTextToConvert();


    private:
    static std::string UserTextToConvert;
    static std::string UserPath;
    static std::string UserFileName;
};