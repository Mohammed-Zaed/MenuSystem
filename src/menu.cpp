#include <iostream>
#include "config.h"
#include "iMenu.h"
#include "menuloader.h"


// Creating Menu Pages : FirstMenu and SecondMenu
class FirstMenu : public iMenu
{
    public:
        virtual void display()
            {
                std::cout << "\n--------------------------" << std::endl;
                std::cout << "Welcome to First Menu Page" << std::endl;
                std::cout << "Press 'm' for message" << std::endl;
                std::cout << "--------------------------" << std::endl;
            }

        virtual bool handle(uint8_t command) 
        {
            bool ret = false;

            switch (command)
            {
                case 'm':
                    {
                        std::cout << "Hi! from first menu page" << std::endl;
                        ret = true;
                    }
                    break;

                default:
                    {
                        ret = false;
                    }
                    break;
            }

            return ret;
        }
};

class SecondMenu : public iMenu
{
    public:
        virtual void display()
            {
                std::cout << "\n--------------------------" << std::endl;
                std::cout << "Welcome to Second Menu Page" << std::endl;
                std::cout << "Press 'm' for message" << std::endl;
                std::cout << "--------------------------" << std::endl;
            }

        virtual bool handle(uint8_t command) 
        {
            bool ret = false;

            switch (command)
            {
                case 'm':
                    {
                        std::cout << "Hi! from second menu page" << std::endl;
                        ret = true;
                    }
                    break;

                default:
                    {
                        ret = false;
                    }
                    break;
            }

            return ret;
        }
};

int 
main ()
{
    // Instantiate Menu Pages
    FirstMenu firstMenu;
    SecondMenu SecondMenu;

    // Instantiate Menu loader class with required page size and number of characters in header text.
    MenuLoader <10, 10> menuLoader("DEMO CODE");

    // Add Menu pages to menu loader class
    menuLoader.addMenu(&firstMenu);
    menuLoader.addMenu(&SecondMenu);

    bool isContinue = true;

    // Display menu
    while (isContinue)
    {
        menuLoader.display();
        uint8_t cmd = 0;
        std::cin >> cmd;
        isContinue = menuLoader.handle(cmd);
    }
    
    return 0U;
}