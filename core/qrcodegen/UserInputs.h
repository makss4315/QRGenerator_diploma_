#pragma once

#include <string>
class UserInputs{
      public:

        static void PathInit();
        static  std::string GetUserPathInput();



    private:
    static std::string UserPath;
};